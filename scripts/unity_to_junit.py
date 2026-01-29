#!/usr/bin/env python3
import sys
import xml.etree.ElementTree as ET

def parse_unity_output(unity_file):
    """Parse Unity output file and return list of (test_name, result, message)."""
    tests = []
    with open(unity_file, "r") as f:
        for line in f:
            line = line.strip()
            if line.startswith("TEST:"):
                # Example: TEST:test_function:PASS or TEST:test_function:FAIL:message
                parts = line.split(":")
                if len(parts) >= 3:
                    test_name = parts[1]
                    result = parts[2]
                    message = parts[3] if len(parts) > 3 else ""
                    tests.append((test_name, result, message))
    return tests

def build_junit_xml(tests):
    """Build JUnit XML tree from parsed tests."""
    testsuite = ET.Element("testsuite", name="UnityTests", tests=str(len(tests)))
    failures = 0

    for test_name, result, message in tests:
        case = ET.SubElement(testsuite, "testcase", classname="Unity", name=test_name)
        if result.upper() == "FAIL":
            failures += 1
            failure = ET.SubElement(case, "failure", message=message or "Assertion failed")
            failure.text = message or "Test failed"

    testsuite.set("failures", str(failures))
    testsuite.set("errors", "0")
    testsuite.set("skipped", "0")

    return ET.ElementTree(testsuite)

def main():
    if len(sys.argv) != 3:
        print("Usage: unity_to_junit.py <unity_output.txt> <junit.xml>")
        sys.exit(1)

    unity_file, junit_file = sys.argv[1], sys.argv[2]
    tests = parse_unity_output(unity_file)
    tree = build_junit_xml(tests)
    tree.write(junit_file, encoding="utf-8", xml_declaration=True)

if __name__ == "__main__":
    main()

