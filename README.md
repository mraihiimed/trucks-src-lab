# trucks-src-lab

[![pipeline status](https://gitlab.com/mraihi.imed/trucks-src-lab/badges/main/pipeline.svg)](https://gitlab.com/mraihi.imed/trucks-src-lab/-/pipelines)
[![coverage report](https://gitlab.com/mraihi.imed/trucks-src-lab/badges/main/coverage.svg)](https://gitlab.com/mraihi.imed/trucks-src-lab/-/commits/main)

A reproducible lab environment for experimenting with **embedded systems security**, **CI/CD pipelines**, and **automotive protocol validation**.  
This project demonstrates safe coding practices, vulnerability detection, and automated testing using Unity, cppcheck, OWASP Dependency Check, and GitLab CI/CD.

---

## Features
- Safe C demo module (`src/vuln_demo.c`) with memory, logging, and string handling examples.
- Unity-based unit tests (`tests/test_vuln_demo.c`) for reproducible validation.
- Static analysis with cppcheck.
- Dependency scanning with OWASP Dependency Check.
- Coverage enforcement with gcov and GitLab CI/CD thresholds.
- Policy gate to ensure builds, tests, and analysis pass before merging.

---

## Project Structure

```plaintext
trucks-sec-lab/
├── build/              # Compiled binaries and test artifacts
├── can/                # CAN bus simulation scripts
├── ci/                 # Static analysis logs
├── docs/               # Documentation (e.g., safety.md)
├── reports/            # Test and scan reports
├── scripts/            # Utility scripts (unity_to_junit.py)
├── src/                # Source code (demo + main + header)
├── tests/              # Unit tests and headers
├── unity/              # Minimal Unity framework
├── tara/               # Threat analysis and risk assessment
├── README.md           # Project documentation
└── .gitlab-ci.yml      # GitLab CI/CD pipeline configuration
# Build demo
gcc -Wall -Wextra -O2 -o build/vuln_demo src/vuln_demo.c src/vuln_demo_main.c

# Run demo
./build/vuln_demo

# Run unit tests
gcc -Wall -Wextra -fprofile-arcs -ftest-coverage -Iunity \
    -o build/test_vuln_demo tests/test_vuln_demo.c src/vuln_demo.c unity/unity.c
./build/test_vuln_demo
