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

TEST_F(CelsiusTest, CompoundAssignmentWorksWithCelsius) {
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

TEST_F(CelsiusTest, CompoundAssignmentWorksWithInts) {
  Celsius c;
  c1.set(50);
  c2.set(25);
  c.set(100);
  // try to add 50 to the temperature
  c += c1;
  // getScaled should return 150*4 = 600
  EXPECT_EQ(c.getScaled(), 600);
  // now try to subtract 25
  c -= c2;
  // get scaled should return 125*4 = 500
  EXPECT_EQ(c.getScaled(), 500);
}

TEST_F(CelsiusTest, PlusAndMinusWithIntsWorks) {
  Celsius c;
  c1.set(100);
  c = c1 + 50;
  EXPECT_EQ(c.getScaled(), 600);
  c = c1 - 25;
  EXPECT_EQ(c.getScaled(), 300);
}

TEST_F(CelsiusTest, PlusAndMinusWithCelsiusWorks) {
  Celsius c;
  c1.set(100);
  c2.set(25);
  c = c1 + c2;
  EXPECT_EQ(c.getScaled(), 500);
  c = c1 - c2;
  EXPECT_EQ(c.getScaled(), 300);
}

TEST_F(CelsiusTest, UnaryIncrementWorks) {
  Celsius c;
  EXPECT_EQ((c++).getScaled(), 0);
  EXPECT_EQ(c.getScaled(), 1);
  EXPECT_EQ((++c).getScaled(), 2);
  EXPECT_EQ(c.getScaled(), 2);
}

TEST_F(CelsiusTest, UnaryDecrementWorks) {
  Celsius c;
  EXPECT_EQ((c--).getScaled(), 0);
  EXPECT_EQ(c.getScaled(), -1);
  EXPECT_EQ((--c).getScaled(), -2);
  EXPECT_EQ(c.getScaled(), -2);
}

TEST_F(CelsiusTest, ToStringWorksForPositive) {
  Celsius c;
  uint8_t strLen;
  char str[7] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0'};

  // an Celsius object just intialized should have a temp of 0
  // this temperature should stringify to "0.0", with strlen 3
  //char str1[6];
  strLen = c.toString(str);
  EXPECT_STREQ("0.0", str);
  EXPECT_EQ(strLen, 3);
  for(uint8_t i=0; i<strLen; i++) {
    str[i] = '\0';
  }

  // now let's try 100.0 degrees
  c.set(100);
  strLen = c.toString(str);
  EXPECT_STREQ("100.0", str);
  EXPECT_EQ(strLen, 5);
  for(uint8_t i=0; i<strLen; i++) {
    str[i] = '\0';
  }

  // 4567.25 degrees
  // x4 = 18269
  c.setScaled(18269, TEMP_POWER);
  strLen = c.toString(str);
  EXPECT_STREQ("4567.0", str);
  EXPECT_EQ(strLen, 6);
  for(uint8_t i=0; i<strLen; i++) {
    str[i] = '\0';
  }

  // 982.75 degrees
  // x4 = 3931
  c.setScaled(3931, TEMP_POWER);
  strLen = c.toString(str);
  EXPECT_STREQ("982.5", str);
  EXPECT_EQ(strLen, 5);
  for(uint8_t i=0; i<strLen; i++) {
    str[i] = '\0';
  }

  // 32.5 degrees
  // x4 = 65
  c.setScaled(130, TEMP_POWER);
  strLen = c.toString(str);
  EXPECT_STREQ("32.5", str);
  EXPECT_EQ(strLen, 4);
}

TEST_F(CelsiusTest, ToStringWorksForNegative) {
  Celsius c;
  uint8_t strLen;
  char str[8] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};

  // now let's try -100.0 degrees
  c.set(-100);
  strLen = c.toString(str);
  EXPECT_STREQ("-100.0", str);
  EXPECT_EQ(strLen, 6);
  for(uint8_t i=0; i<strLen; i++) {
    str[i] = '\0';
  }

  // 4567.25 degrees
  // x4 = 18269
  c.setScaled(-18269, TEMP_POWER);
  strLen = c.toString(str);
  EXPECT_STREQ("-4567.0", str);
  EXPECT_EQ(strLen, 7);
  for(uint8_t i=0; i<strLen; i++) {
    str[i] = '\0';
  }

  // 982.75 degrees
  // x4 = 3931
  c.setScaled(-3931, TEMP_POWER);
  strLen = c.toString(str);
  EXPECT_STREQ("-982.5", str);
  EXPECT_EQ(strLen, 6);
  for(uint8_t i=0; i<strLen; i++) {
    str[i] = '\0';
  }

  // 32.5 degrees
  // x4 = 65
  c.setScaled(-130, TEMP_POWER);
  strLen = c.toString(str);
  EXPECT_STREQ("-32.5", str);
  EXPECT_EQ(strLen, 5);
}

TEST_F(CelsiusTest, ToStringWorksForFahrenheit) {
  Celsius c;
  uint8_t strLen;
  char str[5] = {'\0', '\0', '\0', '\0', '\0'};

  // make sure unit selectable function does celsius properly
  strLen = c.toString(TEMP_UNIT_C, str);
  EXPECT_STREQ("0.0", str);
  EXPECT_EQ(strLen, 3);
  for(uint8_t i=0; i<strLen; i++) {
    str[i] = '\0';
  }

  // now let's try it with fahrenheit
  strLen = c.toString(TEMP_UNIT_F, str);
  EXPECT_STREQ("32", str);
  EXPECT_EQ(strLen, 2);
  for(uint8_t i=0; i<strLen; i++) {
    str[i] = '\0';
  }

  // boiling point
  c.set(100);
  strLen = c.toString(TEMP_UNIT_F, str);
  EXPECT_STREQ("212", str);
  EXPECT_EQ(strLen, 3);
  for(uint8_t i=0; i<strLen; i++) {
    str[i] = '\0';
  }

  // -40 degrees
  c.set(-40);
  strLen = c.toString(TEMP_UNIT_F, str);
  EXPECT_STREQ("-40", str);
  EXPECT_EQ(strLen, 3);
  for(uint8_t i=0; i<strLen; i++) {
    str[i] = '\0';
  }

  // something with a decimal
  c.setScaled(-815, TEMP_POWER);
  strLen = c.toString(TEMP_UNIT_F, str);
  EXPECT_STREQ("-334", str);
  EXPECT_EQ(strLen, 4);
  for(uint8_t i=0; i<strLen; i++) {
    str[i] = '\0';
  }
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}