#include "dad_bot.hpp"

#include <re2/re2.h>

#include <algorithm>
#include <iostream>
#include <ostream>

namespace dad_bot {

template<typename T>
void PrintVector(const std::vector<T>& vec, std::ostream& stream)
{
   stream << "[\n";
   if (!vec.empty())
   {
      for (const auto& type : vec)
      {
         stream << "\t'" << type << "'\n";
      }
   }
   stream << "]\n";
}

auto HiImDadBot_Regex(std::string_view input) -> std::string {
   // Finds an occurence of "I'm" or something like it, at least 1 space, and then captures
   // all the text afterwards until the first punctuation or end of line
   static const RE2 regex(R"(^.*[i|I]['|\s]?[a|A]?[m|M]\s+(?s:(.*?))\s*(?:[?!.,;].*|$))");
   assert(regex.ok());

   std::string name;
   RE2::FullMatch(input, regex, &name);
   return name;
}

auto HiImDadBot_Code(std::string_view input) -> std::vector<std::string> {

   // Make the input lowercase
   std::string lowercase_input = std::string(input);
   std::transform(lowercase_input.begin(), lowercase_input.end(), lowercase_input.begin(),
      [](unsigned char c){ return std::tolower(c); });

   // Find all the different variations of " I am " " Iam " " I'm " " Im " and record their positions
   constexpr std::array<std::string, 4> targets = {"i'm ", "im ", "i am ", "iam "};
   std::vector<std::string::size_type> positions;
   for (const auto& target : targets) {
      std::string::size_type pos = 0;
      while ((pos = lowercase_input.find(target, pos)) != std::string::npos) {
         positions.emplace_back(pos);
         pos += target.length();
      }
   }

   // std::cout << "positions=";
   // PrintVector(positions, std::cout);

   // Sort the positions found so substrings can be processed
   std::sort(positions.begin(), positions.end());

   // Get the phrases and put it through the regex to find the possible names
   std::vector<std::string> names;
   for (int i = 0; i < positions.size(); ++i)
   {
      const unsigned int start = positions.at(i);
      const unsigned int end = (i+1) >= positions.size() ? input.size() : positions.at(i+1);

      // std::cout << "possible name='" << input.substr(start, end - start) << "'\n";

      const std::string name = HiImDadBot_Regex(input.substr(start, end - start));
      if (!name.empty())
      {
         names.emplace_back(name);
      }
   }

   // std::cout << "names=";
   // PrintVector(names, std::cout);

   // Get rid of duplicate names
   const auto last = std::unique(names.begin(), names.end());
   names.erase(last, names.end());

   // std::cout << "names=";
   // PrintVector(names, std::cout);

   return names;
}

}  // namespace dad_bot
