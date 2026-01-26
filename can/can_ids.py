import time
import can
import collections

CHANNEL = "vcan0"
KNOWN_IDS = {0x123, 0x200, 0x321}
WINDOW = 1.0  # seconds
MAX_RATE = 50 # frames/sec per ID

def main():
    # Use 'interface' instead of 'bustype'
    bus = can.Bus(interface="socketcan", channel=CHANNEL)
    bucket = collections.defaultdict(list)
    last = time.time()
    while True:
        m = bus.recv(timeout=0.2)
        now = time.time()
        if m:
            bucket[m.arbitration_id].append(now)
            if m.arbitration_id not in KNOWN_IDS:
                print(f"[ALERT] Unknown ID 0x{m.arbitration_id:X}")
        if now - last >= WINDOW:
            for arb, times in list(bucket.items()):
                bucket[arb] = [t for t in times if now - t <= WINDOW]
                rate = len(bucket[arb]) / WINDOW
                if rate > MAX_RATE:
                    print(f"[ALERT] High rate on 0x{arb:X}: {rate:.1f} fps")
            last = now

if __name__ == "__main__":
    main()

