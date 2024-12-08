#include <dpp/dpp.h>

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

#include "message_listener.hpp"
#include "slash_commands.hpp"

auto main() -> int {
   try {

      // Get the BOT_TOKEN
      constexpr rsize_t bot_token_max_size = 100;
      std::size_t bot_token_actual_size = 0;
      std::array<char, bot_token_max_size> bot_token_value{};
      const auto err = getenv_s(&bot_token_actual_size, bot_token_value.data(), bot_token_value.size(), "BOT_TOKEN");
      const std::string bot_token = (bot_token_actual_size == 0 || err != 0) ? "" : bot_token_value.data();
      if (bot_token.empty()) {
         throw std::runtime_error("BOT_TOKEN environment variable must be defined!");
      }

      // Create the bot and set some simple stuff
      dpp::cluster bot(bot_token, dpp::i_default_intents | dpp::i_message_content);
      bot.on_log(dpp::utility::cout_logger());

      // Forward messages to the message listener
      bot.on_message_create(&dad_bot::message_listener::on_message_create);
      bot.on_message_update(&dad_bot::message_listener::on_message_update);

      // Forward slash commands to the slash command listener
      bot.on_slashcommand(&dad_bot::on_slash_command);

      // Register slash commands once on startup
      bot.on_ready([&bot](const dpp::ready_t&) {
         if (dpp::run_once<struct register_bot_commands>()) {
            for (const auto& slash_command_info : dad_bot::slash_command_infos)
            {
               std::cout << "Adding slashcommand='" << slash_command_info.command << "' with description='" << slash_command_info.desciption << "'\n";
               bot.global_command_create(dpp::slashcommand(std::string(slash_command_info.command), std::string(slash_command_info.desciption), bot.me.id));
            }
         }
      });

      // Start the bot
      bot.start(dpp::st_wait != 0U);

   } catch (const dpp::exception& e) {
      std::cerr << "dpp::exception=" << e.what() << "\n";
      return 1;
   } catch (const std::exception& e) {
      std::cerr << "std::exception=" << e.what() << "\n";
      return 1;
   } catch (...) {
      std::cerr << "Caught unknown exception" << "\n";
      return 1;
   }

   return 0;
}
