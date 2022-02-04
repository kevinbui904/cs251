#!/usr/bin/python3

import unittest
import test_utilities

class Tests(unittest.TestCase):
  def testCode(self):
    return_value = test_utilities.runIt()
    if return_value != None:
        self.fail(return_value)

unittest.main()
