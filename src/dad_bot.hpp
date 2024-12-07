#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace dad_bot {

/// @brief Replies with "Hi <blank>! I'm dad!" if it detects a variation of "I'm "
/// @param input Some message
/// @return std::string The response or empty if no response
auto HiImDadBot_Regex(std::string_view input) -> std::string;

auto HiImDadBot_Code(std::string_view input) -> std::vector<std::string>;

}  // namespace dad_bot
