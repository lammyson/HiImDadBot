#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace dad_bot {

/// @brief Looks for multiple instances of "I'm <something>" and returns the list of <somethings>
/// @param input Input text to process
/// @return std::vector<std::string> List of reponses or empty if no reponse
auto HiImDadBot(std::string_view input) -> std::vector<std::string>;

}  // namespace dad_bot
