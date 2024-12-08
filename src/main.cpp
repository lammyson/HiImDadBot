#include <dpp/dpp.h>

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

#include "message_listener.hpp"

auto main() -> int {
   try {

      constexpr rsize_t bot_token_max_size = 100;
      std::size_t bot_token_actual_size = 0;
      std::array<char, bot_token_max_size> bot_token_value{};
      const auto err = getenv_s(&bot_token_actual_size, bot_token_value.data(), bot_token_value.size(), "BOT_TOKEN");

      const std::string bot_token = (bot_token_actual_size == 0 || err != 0) ? "" : bot_token_value.data();
      if (bot_token.empty()) {
         throw std::runtime_error("BOT_TOKEN environment variable must be defined!");
      }

      dpp::cluster bot(bot_token, dpp::i_default_intents | dpp::i_message_content);
      dad_bot::message_listener::set_bot(bot);
      bot.on_log(dpp::utility::cout_logger());
      bot.on_message_create(&dad_bot::message_listener::on_message_create);
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
