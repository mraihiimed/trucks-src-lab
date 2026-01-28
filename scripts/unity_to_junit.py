stages: [build, static_analysis, dep_scan, test, coverage, policy]

variables:
  BUILD_DIR: build

unit_test:
  stage: test
  image: gcc:13
  before_script:
    - apt-get update && apt-get install -y python3
  script:
    - mkdir -p $BUILD_DIR reports
    # Compile Unity tests
    - gcc -Wall -Wextra -fprofile-arcs -ftest-coverage -o $BUILD_DIR/test tests/test_vuln_demo.c src/demo.c unity/unity.c
    # Run Unity tests, capture output
    - ./build/test > reports/unity_output.txt || true
    # Convert Unity output to JUnit XML
    - python3 scripts/unity_to_junit.py reports/unity_output.txt reports/junit.xml
  artifacts:
    when: always
    reports:
      junit: reports/junit.xml
    paths:
      - $BUILD_DIR/test
      - reports/unity_output.txt
      - reports/junit.xml
      - *.gcda
      - *.gcno
    expire_in: 1 week
  rules:
    - if: '$CI_COMMIT_BRANCH == "main"'
      when: always
