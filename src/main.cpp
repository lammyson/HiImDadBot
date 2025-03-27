#include <dpp/appcommand.h>
#include <dpp/dpp.h>
#include <dpp/misc-enum.h>

#include <cstdlib>
#include <stdexcept>
#include <string>

#include "dad_jokes.hpp"
#include "message_listener.hpp"
#include "slash_command.hpp"

auto main() -> int {
   try {
      // Get the BOT_TOKEN
      const auto* bot_token_ptr = getenv("BOT_TOKEN");
      const std::string bot_token = bot_token_ptr == nullptr ? "" : std::string(bot_token_ptr);
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
      bot.on_slashcommand(&dad_bot::slash_command::on_slash_command);

      // Register slash commands once on startup
      bot.on_ready([&bot](const dpp::ready_t&) {
         if (dpp::run_once<struct register_bot_commands>()) {
            for (const auto& slash_command_info : dad_bot::slash_command::slash_command_infos) {
               bot.log(dpp::loglevel::ll_debug, "Adding slashcommand='" + std::string(slash_command_info.command) +
                                                    "' with description='" +
                                                    std::string(slash_command_info.description) + "'");
               bot.global_command_create(
                  dpp::slashcommand(std::string(slash_command_info.command), std::string(slash_command_info.description), bot.me.id)
                        .add_option(
                           dpp::command_option(dpp::command_option_type::co_integer, "index", "Select which dad joke you want to hear")
                              .set_min_value(0)
                              .set_max_value(std::ssize(dad_bot::dad_jokes::jokes)-1))
                        .add_option(
                           dpp::command_option(dpp::command_option_type::co_string, "all", "Print all dad jokes")
                              .add_choice(dpp::command_option_choice("all", "all"))
                        ));
            }
         }
      });

      // Start the bot
      bot.start(dpp::st_wait != 0U);

   } catch (const dpp::exception& e) {
      std::cerr << "dpp::exception='" << e.what() << "'\n";
      return 1;
   } catch (const std::exception& e) {
      std::cerr << "std::exception='" << e.what() << "'\n";
      return 1;
   } catch (...) {
      std::cerr << "Caught unknown exception" << "\n";
      return 1;
   }

   return 0;
}
