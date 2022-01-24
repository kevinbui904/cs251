# MAKE SURE TO RUN THESE TESTS USING PYTHON3, NOT PYTHON2!
# AS ALWAYS, DO NOT CHANGE THE TESTS!

import subprocess
import sys
import unittest


def runcmd(cmd, input_text=None):
  splitcmd=cmd.split()
  return subprocess.run(splitcmd, stdout=subprocess.PIPE, input=input_text, check=True)


class HelloTests(unittest.TestCase):
  def testOutput(self):
    runcmd('clang -o hello hello.c')
    output = runcmd('./hello').stdout
    self.assertEqual(output, b'I AM A C PROGRAMMING LEGEND!!!\n')


class PrintingTests(unittest.TestCase):
  def testOutput(self):
    runcmd('clang -o printing printing.c')
    output = runcmd('./printing').stdout

    # See if output contains correct answer somewhere
    self.assertNotEqual(-1, output.find(b"72"))


class TemperatureTestsBasic(unittest.TestCase):
  def testTemperature(self):
    runcmd('clang -o temperature temperature.c')
    #output = subprocess.run('./temperature', stdout=subprocess.PIPE, input=b"97", check=True)
    output = runcmd('./temperature', input_text=b"97").stdout

    # See if output contains correct answer somewhere
    self.assertNotEqual(-1, output.find(b"36.1"))


class TemperatureTestsAdvanced(unittest.TestCase):
  def testInvalidTemperature(self):
    runcmd('clang -o temperature temperature.c')
    output = runcmd('./temperature', input_text=b"-500").stdout

    # See if output contains correct output somewhere
    self.assertNotEqual(-1, output.find(b"Invalid temperature!"))


unittest.main(verbosity=2)
