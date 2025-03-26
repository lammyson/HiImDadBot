#pragma once

#include <dpp/dispatcher.h>
#include <dpp/dpp.h>

namespace dad_bot::message_listener {

/// @brief Processes a new message.
/// Replies with "Hi <blank>! I'm dad!" if it detects a variation of "I'm ".
/// Reacts with a 👋 to the message
/// @param event Message create event
void on_message_create(const dpp::message_create_t& event);

/// @brief Processes an updated message.
/// Replies with "Hi <blank>! I'm dad!" if it detects a variation of "I'm ".
/// Reacts with a 👋 to the message
/// @param event Message update event
void on_message_update(const dpp::message_update_t& event);

} // namespace dad_bot::message_listener
