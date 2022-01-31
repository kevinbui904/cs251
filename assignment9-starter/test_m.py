import unittest
import test_utilities

class Tests(unittest.TestCase):
	
  def testVectorPart1(self):
    return_value = test_utilities.runIt()
    if return_value != None:
        self.fail(return_value)

unittest.main()
