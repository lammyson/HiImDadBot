#pragma once

#include <dpp/dpp.h>

#include <string>

#include "dad_jokes.hpp"

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
   return "Select which dad joke you want to hear. Valid range is [0," + std::to_string(std::ssize(dad_bot::dad_jokes::jokes)-1) + "]";
}
constexpr auto ephemeral_option() -> std::string {
   return "ephemeral";
}
constexpr auto ephemeral_description() -> std::string {
   return "Whether the reply should be visible only to you or not. Default is false";
}

namespace slash_command {

/// @brief Processes a slash command
/// @param event Slash command event
void on_slash_command(const dpp::slashcommand_t& event);

} // namespace dad_bot::slash_command

} // namespace dad_bot
