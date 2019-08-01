/***********************************************************************************************************************
                                _______           _______  _______  _______  _______
                               (  __   )|\     /|(  __   )(  __   )/ ___   )(  ___  )
                               | (  )  |( \   / )| (  )  || (  )  |\/   )  || (   ) |
                               | | /   | \ (_) / | | /   || | /   |    /   )| (___) |
                               | (/ /) |  ) _ (  | (/ /) || (/ /) |  _/   / |  ___  |
                               |   / | | / ( ) \ |   / | ||   / | | /   _/  | (   ) |
                               |  (__) |( /   \ )|  (__) ||  (__) |(   (__/\| )   ( |
                               (_______)|/     \|(_______)(_______)\_______/|/     \|

   MIT License

   Copyright (c) 2019 Kevin Klein

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
   documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
   rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
   permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
   Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
   WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
   COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
   OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 **********************************************************************************************************************/

#include "gtest/gtest.h"

#include "Application.h"

namespace {

// Tests wether passing an illegaly formed parameter leads to an exception
TEST(ApplicationTest, ThrowsException) {
  // Explicit cast required
  char *args[] = {(char*)"almagrab\0", (char*)"42\0"};

  ASSERT_THROW(AlmaGrab::Application(2, args), std::runtime_error);
}

// Tests wether passing a well formed parameter leads to an exception
TEST(ApplicationTest, ThrowsNoException) {
  // Explicit cast required
  char *args[] = {(char*)"almagrab\0", (char*)"-username=0x002A\0"};

  ASSERT_NO_THROW(AlmaGrab::Application(2, args));
}

// Tests wether requiring a missing parameter leads to an exception
TEST(ApplicationTest, ThrowsForMissingRequired) {
  // Explicit cast required
  char *args[] = {(char*)"almagrab\0", (char*)"-username=0x002A\0"};
  AlmaGrab::Application app(2, args);

  ASSERT_THROW(app.requireParam("password"), std::runtime_error);
}

// Tests wether requiring a given parameter leads to an exception
TEST(ApplicationTest, ThrowsNotForGivenRequired) {
  // Explicit cast required
  char *args[] = {(char*)"almagrab\0", (char*)"-username=0x002A\0"};
  AlmaGrab::Application app(2, args);

  ASSERT_NO_THROW(app.requireParam("username"));
}

// Tests wether hasParam returns correct results
TEST(ApplicationTest, ResultOfHasParam) {
  // Explicit cast required
  char *args[] = {(char*)"almagrab\0", (char*)"-username=0x002A\0"};
  AlmaGrab::Application app(2, args);

  EXPECT_EQ(app.hasParam("username"), true);
  EXPECT_EQ(app.hasParam("password"), false);
}

// Tests wether requireParam returns correct a result
TEST(ApplicationTest, ResultOfRequireParam) {
  // Explicit cast required
  char *args[] = {(char*)"almagrab\0", (char*)"-username=0x002A\0"};
  AlmaGrab::Application app(2, args);

  EXPECT_EQ(app.requireParam("username"), "0x002A");
}

// Tests wether requireParam returns correct a result
TEST(ApplicationTest, ResultOfGetParam) {
  // Explicit cast required
  char *args[] = {(char*)"almagrab\0", (char*)"-username=0x002A\0"};
  AlmaGrab::Application app(2, args);
  std::string str;

  app.getParam("username", str);

  EXPECT_EQ(str, "0x002A");
}

// End of namespace
}