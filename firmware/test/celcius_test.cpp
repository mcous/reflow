#include "../src/celcius.h"
#include "gtest/gtest.h"

namespace {

// The fixture for testing class Foo.
class CelciusTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  CelciusTest() {
    // You can do set-up work for each test here.
  }

  virtual ~CelciusTest() {
    // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  virtual void SetUp() {
    // Code here will be called immediately after the constructor (right
    // before each test).
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }

  // Objects declared here can be used by all tests in the test case for Foo.
  Celcius c1;
  Celcius c2;
};

// tests that a Celcius object gets intialized at 0
TEST_F(CelciusTest, IsInitiallyZero) {
  Celcius c;
  EXPECT_EQ(0, c.getScaled());
}

// tests that the setter and getter work
// REMEMBER: getter returns 4*temp
TEST_F(CelciusTest, SetterAndGetterWork) {
  c1.set(10);
  EXPECT_EQ(4*10, c1.getScaled());
  c2.set(-20);
  EXPECT_EQ(4*-20, c2.getScaled());
}

// tests that setter works at powers of two other than 0 and 2
// since interanl representation is 2^2, lets try scales that are both lesser and greater than this scale
// using 2^3 and 2^1
TEST_F(CelciusTest, ScaledSetterWorks) {
  int16_t temp = 800;
  // try to set the temperature to 800/8 = 100
  // getScaled should return 100*4 = 400
  c1.setScaled(temp, 3);
  EXPECT_EQ(4*100, c1.getScaled());
  // try to set the temperature to 800/2 = 400
  // get scaled should return 400*4 = 1600
  c2.setScaled(temp, 1);
  EXPECT_EQ(4*400, c2.getScaled());

}

// same test as above with negative numbers
TEST_F(CelciusTest, ScaledSetterWorksWithNegativeTemps) {
  int16_t temp = -800;
  // try to set the temperature to -800/8 = -100
  // getScaled should return -100*4 = -400
  c1.setScaled(temp, 3);
  EXPECT_EQ(-400, c1.getScaled());
  // try to set the temperature to -800/2 = -400
  // get scaled should return -400*4 = -1600
  c2.setScaled(temp, 1);
  EXPECT_EQ(-1600, c2.getScaled());
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}