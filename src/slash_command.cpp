#include "slash_command.hpp"

#include <dpp/message.h>

#include <random>
#include <variant>

#include "dad_jokes.hpp"

namespace dad_bot::slash_command {

void on_slash_command(const dpp::slashcommand_t& event) {
   // Reply with a random dad joke
   if (event.command.get_command_name() == dad_bot::dadjoke_command()) {
      // Provides a random number when selecting a random dad joke
      static std::random_device rdev;
      static std::mt19937 mt19937(rdev());
      static std::uniform_int_distribution<unsigned int> dist(0, dad_bot::dad_jokes::jokes.size() - 1);

      // Get all parameters
      const auto select_variant = event.get_parameter(dad_bot::select_option());
      const auto ephemeral_variant = event.get_parameter(dad_bot::ephemeral_option());

      // Log what we got
      event.from->creator->log(dpp::loglevel::ll_debug,
         "on_slash_command='" + event.command.get_command_name() +
            (std::holds_alternative<int64_t>(select_variant) ? " " + dad_bot::select_option() + "=" + std::to_string(std::get<int64_t>(select_variant)) : "") +
            (std::holds_alternative<bool>(ephemeral_variant) ? " " + dad_bot::ephemeral_option() + "=" + (std::get<bool>(ephemeral_variant) ? "true" : "false") : "") +
            "'");

      // Check if we need to do an ephemeral reply or not
      dpp::message_flags message_flags{};
      if (std::holds_alternative<bool>(ephemeral_variant) && std::get<bool>(ephemeral_variant)) {
         message_flags = dpp::message_flags::m_ephemeral;
      }

      // No parameters so just reply with a random dad joke
      if (std::holds_alternative<std::monostate>(select_variant)) {
         const auto index = dist(mt19937);
         event.reply(dpp::message(
            "Random dad joke " + std::to_string(index) + '\n' +
            std::string(dad_bot::dad_jokes::jokes.at(index)))
               .set_flags(message_flags));
         return;
      }

      // Reply with a specific dad joke if the select subcommand exists
      if (std::holds_alternative<int64_t>(select_variant)) {
         const auto index = std::get<int64_t>(select_variant);
         event.reply(dpp::message(
               "Selected dad joke " + std::to_string(index) + '\n' +
               std::string(dad_bot::dad_jokes::jokes.at(index)))
                  .set_flags(message_flags));
      }
   }
}

} // namespace dad_bot::slash_command
