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
};

// tests that a Celcius object gets intialized at 0
TEST_F(CelciusTest, IsInitiallyZero) {
  Celcius c;
  EXPECT_EQ(0, c.get());
}

// tests that the setter and getter work
TEST_F(CelciusTest, SetterAndGetterWork) {
  Celcius c;
  c.set(10);
  EXPECT_EQ(10, c.get());
  c.set(20);
  EXPECT_EQ(20, c.get());
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}