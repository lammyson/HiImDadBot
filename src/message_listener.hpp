#pragma once

#include <dpp/dispatcher.h>
#include <dpp/dpp.h>

namespace dad_bot {

class message_listener {
public:
   /// @brief Processes a message
   /// @param event Message event
   static void on_message_create(const dpp::message_create_t& event);

   static void on_message_update(const dpp::message_update_t& event);
};

}  // namespace dad_bot
