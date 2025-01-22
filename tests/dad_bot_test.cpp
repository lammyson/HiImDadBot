#include "dad_bot.hpp"
#include "gtest/gtest.h"
#include "slugify.hpp"

#include <ostream>
#include <string>
#include <string_view>
#include <tuple>
#include <vector>

template<class T>
auto operator<<(std::ostream& stream, std::vector<T>& vec) -> std::ostream& {
   stream << "[\n";
   if (!vec.empty()) {
      for (const auto& type : vec) {
         stream << "\t'" << type << "'\n";
      }
   }
   stream << "]\n";
   return stream;
}

// Test cases for testing that "I am" in some variation is found
struct IamCaseParams {
   using TupleT = std::tuple<std::string, std::string, std::string, std::string, std::string, std::string, std::string>;
   std::string before_text;
   std::string i;
   std::string space;
   std::string a;
   std::string m;
   std::string expected;
   std::string after_text;
   IamCaseParams(TupleT t) :
      before_text(std::get<0>(t)),
      i(std::get<1>(t)),
      space(std::get<2>(t)),
      a(std::get<3>(t)),
      m(std::get<4>(t)),
      expected(std::get<5>(t)),
      after_text(std::get<6>(t))
   {}
};

class IamCaseTest : public testing::TestWithParam<IamCaseParams> {};

const auto IamCaseParamGenerator = testing::ConvertGenerator<IamCaseParams::TupleT>(
   testing::Combine(
      testing::Values("", "           ", "man ", "☠ "),
      testing::Values("i", "I"),
      testing::Values(" "),
      testing::Values("a", "A"),
      testing::Values("m", "M"),
      testing::Values("hungry", "🐕"),
      testing::Values("", "!", "?", ".", ",", "       ", ",.!?  ")));

const auto IamCaseNameGenerator =
   [](const testing::TestParamInfo<IamCaseTest::ParamType>& info) {
      std::string name = std::to_string(info.index) + "_" + info.param.before_text + info.param.i + info.param.space + info.param.a + info.param.m + " " + info.param.expected + info.param.after_text;
      return slugify(name);
   };

TEST_P(IamCaseTest, IamCase) {
   const auto& param = GetParam();
   const std::string input = param.before_text + param.i + param.space + param.a + param.m + " " + param.expected + param.after_text;
   const std::vector<std::string> actual = dad_bot::HiImDadBot(input);
   EXPECT_EQ(std::vector<std::string>{param.expected}, actual) << "input='" << input << "'\nexpected='" << param.expected;// << "'\nactual='" << actual << "'\n";
}

INSTANTIATE_TEST_SUITE_P(HiImDadBot, IamCaseTest, IamCaseParamGenerator, IamCaseNameGenerator);

// Test cases for testing that "I'm" in some variation is found
struct ImCaseParams {
   using TupleT = std::tuple<std::string, std::string, std::string, std::string, std::string, std::string>;
   std::string before_text;
   std::string i;
   std::string apostrophe;
   std::string m;
   std::string expected;
   std::string after_text;
   ImCaseParams(TupleT t) :
      before_text(std::get<0>(t)),
      i(std::get<1>(t)),
      apostrophe(std::get<2>(t)),
      m(std::get<3>(t)),
      expected(std::get<4>(t)),
      after_text(std::get<5>(t))
   {}
};

class ImCaseTest : public testing::TestWithParam<ImCaseParams> {};

const auto ImCaseParamGenerator = testing::ConvertGenerator<ImCaseParams::TupleT>(
   testing::Combine(
      testing::Values("", "           ", "man ", "☠ "),
      testing::Values("i", "I"),
      testing::Values("", "'", R"(")", "‘", "’", "“", "”"),
      testing::Values("m", "M"),
      testing::Values("hungry", "🐕"),
      testing::Values("", "!", "?", ".", ",", "       ", ",.!?  ")));

const auto ImCaseNameGenerator =
   [](const testing::TestParamInfo<ImCaseTest::ParamType>& info) {
      std::string name = std::to_string(info.index) + "_" + info.param.before_text + info.param.i + info.param.apostrophe + info.param.m + " " + info.param.expected + info.param.after_text;
      return slugify(name);
   };

TEST_P(ImCaseTest, Normal) {
   const auto& param = GetParam();
   const std::string input = param.before_text + param.i + param.apostrophe + param.m + " " + param.expected + param.after_text;
   const std::vector<std::string> actual = dad_bot::HiImDadBot(input);
   EXPECT_EQ(std::vector<std::string>{param.expected}, actual) << "input='" << input << "'\nexpected='" << param.expected;// << "'\nactual='" << actual << "'\n";
}

INSTANTIATE_TEST_SUITE_P(HiImDadBot, ImCaseTest, ImCaseParamGenerator, ImCaseNameGenerator);


// Other test cases
struct DadBotTestParams {
   using TupleT = std::tuple<std::string_view, std::string_view, std::string_view>;
   std::string input;
   std::string expected;
   std::string test_case_name;
   DadBotTestParams(TupleT t) :
      input(std::get<0>(t)),
      expected(std::get<1>(t)),
      test_case_name(std::get<2>(t))
   {}
};

class DadBotTest : public testing::TestWithParam<DadBotTestParams> {};

TEST_P(DadBotTest, TestSomething) {
   const auto& param = GetParam();
   const std::vector<std::string> actual = dad_bot::HiImDadBot(param.input);
   std::vector<std::string> expected;
   if (!param.expected.empty())
   {
      expected.push_back(param.expected);
   }
   EXPECT_EQ(expected, actual) << "input='" << param.input << "'\nexpected='" << param.expected;// << "'\nactual='" << actual << "'\n";
}

INSTANTIATE_TEST_SUITE_P(HiImDadBot, DadBotTest,
   testing::Values(
      std::make_tuple("I'm hungry", "hungry", "Normal"),
      std::make_tuple("I'm hungry!", "hungry", "Normal"),
      std::make_tuple("I'm 🚲!", "🚲", "Normal"),
      std::make_tuple("What's happening", "", "Normal"),
      std::make_tuple("", "", "Normal"),
      std::make_tuple("This is so weird. I am confused haha", "confused haha", "Normal"),
      std::make_tuple("const std::string &input", "", "Normal"),
      std::make_tuple("owefj imwoeirj", "", "Normal"),
      std::make_tuple("imwoeifj aowj", "", "Normal"),
      std::make_tuple("wawefiojimawoei aowoeiim aweofiwe.", "aweofiwe", "Normal")),
   [](const testing::TestParamInfo<DadBotTest::ParamType>& info) {
      std::string name = std::to_string(info.index) + "_" + info.param.test_case_name + "_" + info.param.input + "_" + info.param.expected;
      return slugify(name);
   });

TEST(HiImDadBot, Multiple_Im_Iam) {
   std::string im_strings = "I'm apple. I'M bee. i'm cold. i'M different. Im early IM fairly weird!?!?!?! im giraffe iM here. ";
   std::string i_am_strings = "i am igloo. i aM jam. i Am KRAZY.i AM living I am money, I aM nori. i AM OSTRICH I AM      PERSON     ";
   std::string iam_strings = "iam queen iaM rYaN iAm see iAM tortoiseGit Iam underwater IaM vent IAm WaterIAM xylophone!3oirj o3rij23r0    ";
   std::string input = im_strings + i_am_strings + iam_strings;
   std::vector<std::string> names = dad_bot::HiImDadBot(input);
   EXPECT_EQ(24U, names.size());
}

TEST(HiImDadBot, Newline) {
   std::string input = "I'm According to all known laws\nof aviation,";
   std::vector<std::string> names = dad_bot::HiImDadBot(input);
   std::vector<std::string> expected = {"According to all known laws\nof aviation"};
   EXPECT_EQ(expected, names);
}

TEST(HiImDadBot, Tab) {
   std::string input = "I'm According to all known laws\tof aviation,";
   std::vector<std::string> names = dad_bot::HiImDadBot(input);
   std::vector<std::string> expected = {"According to all known laws\tof aviation"};
   EXPECT_EQ(expected, names);
}
