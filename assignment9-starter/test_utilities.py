#!/usr/bin/python3

import subprocess
import sys
import unittest
import signal
import collections

TestResult = collections.namedtuple('TestResult', ['output', 'error'])

def runcmd(cmd):
  splitcmd=cmd.split()
  return subprocess.run(
    splitcmd, 
    stderr=subprocess.STDOUT,
    stdout=subprocess.PIPE,
    encoding='utf-8'
  )

def buildCode():

  # Make sure that warnings aren't suppressed
  with open('vector.c', 'r') as f:
    for line in f.readlines():
      if 'diagnostic' in line and 'ignore' in line:
        return 'Please do not disable warnings.'

  # Compile, show output
  compile_return = runcmd('clang -g -o tester vector.c tester.c')
  print(compile_return.stdout)

  # Make sure that warning causes test to fail
  if ('warning' in compile_return.stdout):
    return 'Testing failed because of compiler warning.'

  return None

def runIt():
  error = buildCode()
  if error != None:
    return error

  # Run it once without valgrind
  print("Running tests without invoking valgrind...\n")
  process_out = runcmd('./tester')
  if process_out.returncode != 0:
    return f"Runtime error! Use this command to view error message: clang -g -o tester vector.c tester.c; ./tester"
  else:
    print(vars(process_out))
    print(process_out.stdout)

  # Run it again with valgrind
  print("Running tests with valgrind invoked...\n")
  valgrind_test_results = run_tests_with_valgrind('./tester')
  if valgrind_test_results.error:
    error_encountered = True
    print('---VALGRIND ERROR---')
    print('Valgrind test results')
    print(valgrind_test_results.output)
    return "Valgrind error (see report above)."
  else:
    print('\tVALGRIND DETECTED NO MEMORY ERRORS!')



def run_tests_with_valgrind(executable_command) -> TestResult:
    '''Run again with valgrind (just student version) and look for errors)'''
    valgrind_command = \
        'ulimit -c 0 && ' + \
        'valgrind ' + \
        '--leak-check=full ' + \
        '--show-leak-kinds=all ' + \
        '--errors-for-leak-kinds=all ' + \
        '--error-exitcode=99 ' + \
        '--track-origins=yes ' + \
        executable_command

    try:
        process = subprocess.run(
            valgrind_command,
            stderr=subprocess.STDOUT,
            stdout=subprocess.PIPE,
            timeout=10,
            shell=True)

        # Verify that there is no error from Valgrind.
        # This looks for the presence of the string
        # "0 errors from 0 contexts" which is that Valgrind prints when
        # no errors.
        valgrind_error_location = (
            process.stdout
            .decode('utf-8')
            .find("ERROR SUMMARY: 0 errors from 0 contexts")
        )
        valgrind_error_found = valgrind_error_location == -1
        return TestResult(process.stdout.decode('utf-8'),
                          valgrind_error_found)
    except subprocess.TimeoutExpired:
        return TestResult("Timed out", True)
