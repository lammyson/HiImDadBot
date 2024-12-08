#include "message_listener.hpp"

#include <dpp/message.h>
#include <dpp/unicode_emoji.h>

#include <iostream>
#include <vector>

#include "dad_bot.hpp"

namespace dad_bot {

dpp::cluster* message_listener::bot = nullptr;

void message_listener::on_message_create(const dpp::message_create_t& event) {
   if (event.msg.author.is_bot()) {
      return;
   }

   std::cout << "message='" << event.msg.content << "'\n";

   const std::vector<std::string> names = dad_bot::HiImDadBot_Code(event.msg.content);
   if (!names.empty()) {
      for (const auto& name : names) {
         const std::string im_dad_reply = "Hi `" + name + "`! I'm dad!";
         bot->message_add_reaction(event.msg, dpp::unicode_emoji::wave);
         event.reply(im_dad_reply, true);
      }
   }
}

void message_listener::set_bot(dpp::cluster& bot) { message_listener::bot = &bot; }

}  // namespace dad_bot
