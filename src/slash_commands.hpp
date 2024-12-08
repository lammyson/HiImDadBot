#pragma once

#include <dpp/dpp.h>

#include <array>
#include <string_view>

namespace dad_bot {
using namespace std::string_view_literals;

// List of slash commands with descriptions
constexpr std::string_view dad_joke_command = "dadjoke"sv;
struct slash_command_info {
   std::string_view command;
   std::string_view desciption;
};
constexpr std::array slash_command_infos {slash_command_info{dad_joke_command, "Tell a dad joke!"sv}};

/// @brief Processes a slash command
/// @param event Slash command event
void on_slash_command(const dpp::slashcommand_t& event);

}  // namespace dad_bot
