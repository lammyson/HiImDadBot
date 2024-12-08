#pragma once

#include <dpp/dpp.h>

namespace dad_bot {

class message_listener {
public:
   /// @brief Processes a message
   /// @param event Message event
   static void on_message_create(const dpp::message_create_t& event);

   /// @brief Sets the bot
   /// @param bot discord bot
   static void set_bot(dpp::cluster& bot);

private:
   /// @brief Pointer to the bot
   static dpp::cluster* bot;
};

}  // namespace dad_bot
