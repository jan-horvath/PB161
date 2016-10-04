/**
 *  String Wrapper
 */


#include "StringWrapper.hpp"
#include <numeric>
#include <array>
#include <functional>
#include <gtest/gtest.h>


using Wrapper = StringWrapper;
using ConstWrap = const Wrapper;

/// \brief Test of constructor
TEST(StringWrapper, Construction) {
    const char *expected = "Hello world";
    Wrapper wrapper{expected};
    ConstWrap cWrap{expected};
    EXPECT_EQ(expected, wrapper.get());
    const std::string &ref = wrapper.getReference();
    EXPECT_EQ(expected, ref);
    const std::string &constRef = cWrap.get();
    EXPECT_EQ(expected, constRef);
}

/// \brief Test of get saved string
TEST(StringWrapper, Get) {
    const char *expected = "Hello world";
    Wrapper wrapper{expected};
    ConstWrap cWrap{expected};
    EXPECT_EQ(expected, wrapper.get());
    const std::string &constRef = cWrap.get();
    EXPECT_EQ(expected, constRef);
}

/// \brief Test of get refence to saved string
TEST(StringWrapper, GetReference) {
    const char *expected = "Hello world";
    Wrapper wrapper{expected};
    const std::string &ref = wrapper.getReference();
    EXPECT_EQ(expected, ref);
}

/// \brief Test of upper method, muttable and immutable
TEST(StringWrapper, Upper) {
    const char *input = " Hello World! ";
    const char *expected = " HELLO WORLD! ";
    Wrapper wrapper{input};
    ConstWrap cWrapper{input};
    EXPECT_EQ(expected, wrapper.upper().get());
    EXPECT_EQ(expected, cWrapper.copyUpper().get());
}

/// \brief Test of lower method, muttable and immutable
TEST(StringWrapper, Lower) {
    const char *input = " Hello WoRlD! ";
    const char *expected = " hello world! ";
    Wrapper wrapper{input};
    ConstWrap cWrapper{input};
    EXPECT_EQ(expected, wrapper.lower().get());
    EXPECT_EQ(expected, cWrapper.copyLower().get());
}

/// \brief Test of split method
TEST(StringWrapper, Split) {
    const char *input = " Hello World";
    Wrapper emptyWrapper{""};
    Wrapper wrapper{input};
    std::vector<std::string> nonEmptyVector{""};
    std::vector<std::string> expected1 = {" Hello World"};
    std::vector<std::string> expected2{" Hello World"};
    std::vector<std::string> expected3{" He", "", "o Wor", "d"};
    std::vector<std::string> expected4{" He", "o Wor", "d"};
    EXPECT_EQ(emptyWrapper.split("", false), nonEmptyVector);
    EXPECT_EQ(wrapper.split("", true), expected1);
    EXPECT_EQ(wrapper.split("Q", true), expected2);
    EXPECT_EQ(wrapper.split("l", true), expected3);
    EXPECT_EQ(wrapper.split("l", false), expected4);
}

/// \brief Test of ltrim method, muttable and immutable
TEST(StringWrapper, LTrim) {
    const char *input1 = "   Hello!\n ";
    const char *input2 = "       \n  \n     ";
    const char *expected1 = "Hello!\n ";
    const char *expected2 = "";
    Wrapper wrapper1{input1};
    Wrapper wrapper2{input2};
    ConstWrap cWrapper1{input1};
    ConstWrap cWrapper2{input2};
    EXPECT_EQ(wrapper1.leftTrim().get(), expected1);
    EXPECT_EQ(wrapper2.leftTrim().get(), expected2);
    EXPECT_EQ(cWrapper1.copyLeftTrim().get(), expected1);
    EXPECT_EQ(cWrapper2.copyLeftTrim().get(), expected2);

}

/// \brief Test of rtrim method, muttable and immutable
TEST(StringWrapper, RTrim) {
    const char *input1 = "   Hello!\n ";
    const char *input2 = "       \n  \n     ";
    const char *expected1 = "   Hello!";
    const char *expected2 = "";
    Wrapper wrapper1{input1};
    Wrapper wrapper2{input2};
    ConstWrap cWrapper1{input1};
    ConstWrap cWrapper2{input2};
    EXPECT_EQ(wrapper1.rightTrim().get(), expected1);
    EXPECT_EQ(wrapper2.rightTrim().get(), expected2);
    EXPECT_EQ(cWrapper1.copyRightTrim().get(), expected1);
    EXPECT_EQ(cWrapper2.copyRightTrim().get(), expected2);

}

/// \brief Test of trim method, muttable and immutable
TEST(StringWrapper, Trim) {
    const char *input1 = "   Hello!\n ";
    const char *input2 = "       \n  \n     ";
    const char *expected1 = "Hello!";
    const char *expected2 = "";
    Wrapper wrapper1{input1};
    Wrapper wrapper2{input2};
    ConstWrap cWrapper1{input1};
    ConstWrap cWrapper2{input2};
    EXPECT_EQ(wrapper1.trim().get(), expected1);
    EXPECT_EQ(wrapper2.trim().get(), expected2);

    EXPECT_EQ(cWrapper1.copyTrim().get(), expected1);
    EXPECT_EQ(cWrapper2.copyTrim().get(), expected2);

}

/// \brief Test of ReplaceString method, muttable and immutable
TEST(StringWrapper, ReplaceString) {
    const char *input = "ABCD ABC AB A";
    const char *expected1 = "ABCD ABC AB A";
    const char *expected2 = "C++CD C++C C++ A";
    Wrapper wrapper{input};
    ConstWrap cWrapper{input};
    EXPECT_EQ(wrapper.replace("AB", "AB").get(), expected1);
    EXPECT_EQ(wrapper.replace("NOT_PRESENT", "RANDOM").get(), expected1);
    EXPECT_EQ(wrapper.replace("AB", "C++").get(), expected2);

    EXPECT_EQ(cWrapper.copyReplace("AB", "AB").get(), expected1);
    EXPECT_EQ(cWrapper.copyReplace("NOT_PRESENT", "RANDOM").get(), expected1);
    EXPECT_EQ(cWrapper.copyReplace("AB", "C++").get(), expected2);

}

/// \brief Test of ReplaceChar method, muttable and immutable
TEST(StringWrapper, ReplaceChar) {
    const char *input = "ABCD ABC AB A";
    const char *expected1 = "ABCD ABC AB A";
    const char *expected2 = "AXCD AXC AX A";
    Wrapper wrapper{input};
    ConstWrap cWrapper{input};
    EXPECT_EQ(wrapper.replaceChar('B', 'B').get(), expected1);
    EXPECT_EQ(wrapper.replaceChar('G', 'K').get(), expected1);
    EXPECT_EQ(wrapper.replaceChar('B', 'X').get(), expected2);

    EXPECT_EQ(cWrapper.copyReplaceChar('B', 'B').get(), expected1);
    EXPECT_EQ(cWrapper.copyReplaceChar('G', 'K').get(), expected1);
    EXPECT_EQ(cWrapper.copyReplaceChar('B', 'X').get(), expected2);
}

/// \brief Test of Sequence of methods, muttable and immutable
TEST(StringWrapper, SequenceOfMethods) {
    const char *input1 = "\n Hello World!!! \n";
    const char *expected1 = "HELLO0WORLD!!!0";
    const char *input2 = "";
    const char *expected2 = "";
    Wrapper wrapper{input1};
    ConstWrap cWrapper{input1};
    Wrapper wrapper1{input2};
    ConstWrap cWrapper1{input2};

    EXPECT_EQ(wrapper.leftTrim().replaceChar(' ', '0').rightTrim().upper().get(), expected1);
    EXPECT_EQ(cWrapper.copyLeftTrim().copyReplaceChar(' ', '0').copyRightTrim().copyUpper().get(), expected1);
    EXPECT_EQ(wrapper1.trim().replace("something", "something else").rightTrim().lower().get(), expected2);
    EXPECT_EQ(cWrapper1.copyTrim().copyReplace("something", "something else").copyRightTrim().copyLower().get(),
              expected2);
}
