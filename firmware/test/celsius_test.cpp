#include "../src/celsius.h"
#include "gtest/gtest.h"

namespace {

// The fixture for testing class Foo.
class CelsiusTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  CelsiusTest() {
    // You can do set-up work for each test here.
  }

  virtual ~CelsiusTest() {
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
  Celsius c1;
  Celsius c2;
};

// tests that a Celsius object gets intialized at 0
TEST_F(CelsiusTest, IsInitiallyZero) {
  Celsius c;
  EXPECT_EQ(0, c.getScaled());
}

// tests that the setter and getter work
// REMEMBER: getter returns 4*temp
TEST_F(CelsiusTest, SetterAndGetterWork) {
  c1.set(10);
  EXPECT_EQ(4*10, c1.getScaled());
  c2.set(-20);
  EXPECT_EQ(4*-20, c2.getScaled());
}

// tests that setter works at powers of two other than 0 and 2
// since interanl representation is 2^2, lets try scales that are both lesser and greater than this scale
// using 2^3 and 2^1
TEST_F(CelsiusTest, ScaledSetterWorks) {
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
TEST_F(CelsiusTest, ScaledSetterWorksWithNegativeTemps) {
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

TEST_F(CelsiusTest, BooleanOperatorsWork) {
  Celsius lhs;
  Celsius rhs;
  lhs.set(100);
  rhs.set(100);

  // test equals and not equals
  EXPECT_FALSE(lhs != rhs);
  EXPECT_TRUE(lhs == rhs);
  EXPECT_TRUE(lhs >= rhs);
  EXPECT_TRUE(lhs <= rhs);
  rhs.set(99);
  EXPECT_TRUE(lhs != rhs);
  EXPECT_FALSE(lhs == rhs);
  
  // test greater than
  EXPECT_TRUE(lhs > rhs);
  EXPECT_TRUE(lhs >= rhs);
  EXPECT_FALSE(lhs < rhs);
  EXPECT_FALSE(lhs <= rhs);

  // test less than
  rhs.set(101);
  EXPECT_FALSE(lhs > rhs);
  EXPECT_FALSE(lhs >= rhs);
  EXPECT_TRUE(lhs < rhs);
  EXPECT_TRUE(lhs <= rhs);
}

TEST_F(CelsiusTest, BooleanOperatorsWithIntsWork) {
  Celsius lhs;
  lhs.set(100);

  // test equals and not equals
  EXPECT_FALSE(lhs != 100);
  EXPECT_TRUE(lhs == 100);
  EXPECT_TRUE(lhs >= 100);
  EXPECT_TRUE(lhs <= 100);
  EXPECT_TRUE(lhs != 99);
  EXPECT_FALSE(lhs == 99);
  
  // test greater than
  EXPECT_TRUE(lhs > -99);
  EXPECT_TRUE(lhs >= -99);
  EXPECT_FALSE(lhs < -99);
  EXPECT_FALSE(lhs <= -99);

  // test less than
  EXPECT_FALSE(lhs > 101);
  EXPECT_FALSE(lhs >= 101);
  EXPECT_TRUE(lhs < 101);
  EXPECT_TRUE(lhs <= 101);
}

TEST_F(CelsiusTest, CompoundAssignmentWorks) {
  Celsius c;
  c.set(100);
  // try to add 50 to the temperature
  c += 50;
  // getScaled should return 150*4 = 600
  EXPECT_EQ(c.getScaled(), 600);
  // now try to subtract 25
  c -= 25;
  // get scaled should return 125*4 = 500
  EXPECT_EQ(c.getScaled(), 500);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}