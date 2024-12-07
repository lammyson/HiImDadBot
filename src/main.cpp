#include <dpp/dpp.h>

#include <cstdlib>
#include <iostream>
#include <string>

#include "message_listener.hpp"


auto main() -> int {
   try {
      const auto* bot_token_ptr = std::getenv("BOT_TOKEN");
      const std::string bot_token = bot_token_ptr == nullptr ? "" : bot_token_ptr;
      if (bot_token.empty()) {
         throw std::exception("BOT_TOKEN environment variable must be defined!");
      }

      dpp::cluster bot(bot_token, dpp::i_default_intents | dpp::i_message_content);
      message_listener::set_bot(bot);
      bot.on_log(dpp::utility::cout_logger());
      bot.on_message_create(&message_listener::on_message_create);
      bot.start(dpp::st_wait != 0U);

   } catch (const std::exception& e) {
      std::cerr << "exception=" << e.what() << "\n";
      return 1;
   } catch (...) {
      std::cerr << "Caught unknown exception" << "\n";
      return 1;
   }

   return 0;
}
