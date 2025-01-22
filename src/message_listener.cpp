#include "message_listener.hpp"

#include <dpp/message.h>
#include <dpp/misc-enum.h>
#include <dpp/unicode_emoji.h>

#include <vector>

#include "dad_bot.hpp"

namespace dad_bot {

void message_listener::on_message_create(const dpp::message_create_t& event) {
   if (event.msg.author.is_bot()) {
      return;
   }

   event.from->creator->log(dpp::loglevel::ll_debug, "message create='" + event.msg.content + "'");

   // Try to find 1 or more instances of "I'm <something>" and return a list of 'names' to reply to
   // "Hi <something>! I'm dad!". Also react to the message with 👋
   const std::vector<std::string> names = dad_bot::HiImDadBot(event.msg.content);
   if (!names.empty()) {
      for (const auto& name : names) {
         event.from->creator->message_add_reaction(event.msg, dpp::unicode_emoji::wave);

         const std::string im_dad_reply = "Hi `" + name + "`! I'm dad!";
         event.reply(im_dad_reply, true);
      }
   }
}

void message_listener::on_message_update(const dpp::message_update_t& event) {
   if (event.msg.author.is_bot()) {
      return;
   }

   event.from->creator->log(dpp::loglevel::ll_debug, "message update='" + event.msg.content + "'");

   // Try to find 1 or more instances of "I'm <something>" and return a list of 'names' to reply to
   // "Hi <something>! I'm dad!". Also react to the message with 👋
   const std::vector<std::string> names = dad_bot::HiImDadBot(event.msg.content);
   if (!names.empty()) {
      for (const auto& name : names) {
         event.from->creator->message_add_reaction(event.msg, dpp::unicode_emoji::wave);

         const std::string im_dad_reply = "Hi `" + name + "`! I'm dad!";
         dpp::message msg_to_send{im_dad_reply};
         msg_to_send.set_reference(event.msg.id);
         msg_to_send.channel_id = event.msg.channel_id;
         msg_to_send.allowed_mentions.replied_user = true;
         msg_to_send.allowed_mentions.users.push_back(event.msg.author.id);
         event.from->creator->message_create(msg_to_send);
      }
   }
}

}  // namespace dad_bot
