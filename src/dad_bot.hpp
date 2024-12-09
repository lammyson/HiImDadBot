#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace dad_bot {

/// @brief Looks for multiple instances of "I'm <something>" and returns the list of <somethings>
/// @param input Input text to process
/// @return std::vector<std::string> List of reponses or empty if no reponse
auto HiImDadBot_Code(std::string_view input) -> std::vector<std::string>;

/// @brief Looks for a single instance of the string "I'm <something>" using a regex
/// @param input Input text to process
/// @return std::string The response or empty if no response
auto HiImDadBot_Regex(std::string_view input) -> std::string;

}  // namespace dad_bot
