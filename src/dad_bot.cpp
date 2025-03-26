#include "dad_bot.hpp"

#include <re2/re2.h>

#include <algorithm>
#include <ostream>

using namespace std::literals;

namespace dad_bot {

// Helper functions
namespace {
/// @brief Helper method to print a vector to an output stream
/// @tparam T Some type that can be printed by std::ostream
/// @param vec Vector to print
/// @param stream Output stream to print the vector to
template <typename T>
void PrintVector(const std::vector<T>& vec, std::ostream& stream) {
   stream << "[\n";
   if (!vec.empty()) {
      for (const auto& type : vec) {
         stream << "\t'" << type << "'\n";
      }
   }
   stream << "]\n";
}

auto HiImDadBot_Regex(std::string_view input) -> std::string {
   // Finds an occurence of "I'm" or something like it, at least 1 space, and then captures
   // all the text afterwards until the first punctuation or end of line
   static const RE2 regex(R"(^.*[i|I]['|"|‘|’|“|”|\s]?[a|A]?[m|M]\s+(?s:(.*?))\s*(?:[?!.,;].*|$))");
   assert(regex.ok());

   std::string name;
   RE2::FullMatch(input, regex, &name);
   return name;
}
}

auto HiImDadBot(std::string_view input) -> std::vector<std::string> {
   // Make the input lowercase
   std::string lowercase_input = std::string(input);
   std::ranges::transform(lowercase_input, lowercase_input.begin(),
                  [](unsigned char uchar) { return std::tolower(uchar); });

   // Find all the different variations of " I am " " Iam " " I'm " " Im " and record their positions
   constexpr std::array targets = {"i'm "sv, R"(i"m )"sv, "i‘m "sv, "i’m "sv, "i“m "sv, "i”m "sv, "im "sv, "i am "sv, "iam "sv};
   std::vector<std::string_view::size_type> positions;
   for (const auto& target : targets) {
      std::string_view::size_type pos = 0;
      while ((pos = lowercase_input.find(target, pos)) != std::string::npos) {
         positions.emplace_back(pos);
         pos += target.length();
      }
   }

   // Sort the positions found so substrings can be processed
   std::ranges::sort(positions);

   // Get the phrases and put it through the regex to find the possible names
   std::vector<std::string> names;
   for (int i = 0; i < positions.size(); ++i) {
      const unsigned int start = positions.at(i);

      // TODO - Maybe just make the end input.size()?
      const unsigned int end = (i + 1) >= positions.size() ? input.size() : positions.at(i + 1);

      const std::string name = HiImDadBot_Regex(input.substr(start, end - start));
      if (!name.empty()) {
         names.emplace_back(name);
      }
   }

   // Get rid of duplicate names
   const auto last = std::ranges::unique(names);
   names.erase(std::ranges::begin(last), std::end(names));

   return names;
}

}  // namespace dad_bot
