#pragma once

#include <dpp/dpp.h>

#include <string>

namespace dad_bot {

/// @brief Dad joke slash command variables
constexpr auto dadjoke_command() -> std::string {
   return "dadjoke";
}
constexpr auto dadjoke_description() -> std::string {
   return "Tell a dad joke!";
}
constexpr auto select_option() -> std::string {
   return "select";
}
constexpr auto select_description() -> std::string {
   return "Select which dad joke you want to hear";
}
constexpr auto ephemeral_option() -> std::string {
   return "ephemeral";
}
constexpr auto ephemeral_description() -> std::string {
   return "Whether the reply should be visible only to you or not (default is false)";
}

namespace slash_command {

/// @brief Processes a slash command
/// @param event Slash command event
void on_slash_command(const dpp::slashcommand_t& event);

} // namespace dad_bot::slash_command

} // namespace dad_bot
