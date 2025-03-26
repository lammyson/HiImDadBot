#pragma once

#include <dpp/dpp.h>

#include <array>
#include <string_view>

namespace dad_bot::slash_command {

using namespace std::string_view_literals;

/// @brief Holds a slash command with a description
struct slash_command_info {
   /// @brief Slash command text
   std::string_view command;
   /// @brief Slash command description
   std::string_view description;
};

/// @brief Dad joke slash command string
constexpr std::string_view dad_joke_command = "dadjoke"sv;

/// @brief List of slash commands with descriptions
constexpr std::array slash_command_infos{
   slash_command_info{
      .command=dad_joke_command,
      .description="Tell a dad joke!"sv
   }
};

/// @brief Processes a slash command
/// @param event Slash command event
void on_slash_command(const dpp::slashcommand_t& event);

} // namespace dad_bot::slash_command
