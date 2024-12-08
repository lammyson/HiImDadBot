#include "message_listener.hpp"

#include <dpp/message.h>
#include <dpp/unicode_emoji.h>

#include <iostream>
#include <vector>

#include "dad_bot.hpp"

namespace dad_bot {

void message_listener::on_message_create(const dpp::message_create_t& event) {
   if (event.msg.author.is_bot()) {
      return;
   }

   std::cout << "message create='" << event.msg.content << "'\n";

   const std::vector<std::string> names = dad_bot::HiImDadBot_Code(event.msg.content);
   if (!names.empty()) {
      for (const auto& name : names) {
         const std::string im_dad_reply = "Hi `" + name + "`! I'm dad!";
         event.from->creator->message_add_reaction(event.msg, dpp::unicode_emoji::wave);
         event.reply(im_dad_reply, true);
      }
   }
}

void message_listener::on_message_update(const dpp::message_update_t& event)
{
   if (event.msg.author.is_bot()) {
      return;
   }

   std::cout << "message update='" << event.msg.content << "'\n";

   const std::vector<std::string> names = dad_bot::HiImDadBot_Code(event.msg.content);
   if (!names.empty()) {
      for (const auto& name : names) {
         const std::string im_dad_reply = "Hi `" + name + "`! I'm dad!";
         event.from->creator->message_add_reaction(event.msg, dpp::unicode_emoji::wave);

         dpp::message msg_to_send{event.msg};
         msg_to_send.set_reference(event.msg.id);
         msg_to_send.channel_id = event.msg.channel_id;
         msg_to_send.allowed_mentions.replied_user = true;
         msg_to_send.allowed_mentions.users.push_back(event.msg.author.id);
         event.from->creator->message_create(msg_to_send);
      }
   }
}

}  // namespace dad_bot
