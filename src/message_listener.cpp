#include "message_listener.hpp"

#include <dpp/message.h>
#include <dpp/misc-enum.h>
#include <dpp/unicode_emoji.h>

#include <random>
#include <vector>

#include "dad_bot.hpp"

namespace dad_bot {

namespace {

constexpr std::string wave_emoji = "👋";

auto make_reply(const std::string& name) -> std::string
{
   static constexpr std::array dad_names = {
      "dad",
      "father",
      "papa",
      "baba",
      "abba",
      "padre",
      "pops",
      "patriarch",
      "ama",
      "sir",
      "old man",
      "vader"
   };

   // Provides a random number when selecting a random dad joke
   static std::random_device rdev;
   static std::mt19937 mt19937(rdev());
   static std::uniform_int_distribution<unsigned int> dist(0, dad_names.size() - 1);

   const auto index = dist(mt19937);
   return "Hi `" + name + "`! I'm " + dad_names.at(index) + "!";
}

}

void message_listener::on_message_create(const dpp::message_create_t& event) {
   if (event.msg.author.is_bot()) {
      return;
   }

   event.from->creator->log(dpp::loglevel::ll_debug, "on_message_create='" + event.msg.content + "'");

   // Try to find 1 or more instances of "I'm <something>" and return a list of 'names' to reply to
   // "Hi <something>! I'm dad!". Also react to the message with 👋
   const std::vector<std::string> names = dad_bot::HiImDadBot(event.msg.content);
   if (!names.empty()) {
      for (const auto& name : names) {
         event.from->creator->message_add_reaction(event.msg, wave_emoji);

         event.reply(make_reply(name), true);
      }
   }
}

void message_listener::on_message_update(const dpp::message_update_t& event) {
   if (event.msg.author.is_bot()) {
      return;
   }

   event.from->creator->log(dpp::loglevel::ll_debug, "on_message_update='" + event.msg.content + "'");

   // Try to find 1 or more instances of "I'm <something>" and return a list of 'names' to reply to
   // "Hi <something>! I'm dad!". Also react to the message with 👋
   const std::vector<std::string> names = dad_bot::HiImDadBot(event.msg.content);
   if (!names.empty()) {
      for (const auto& name : names) {
         event.from->creator->message_add_reaction(event.msg, wave_emoji);

         dpp::message msg_to_send{make_reply(name)};
         msg_to_send.set_reference(event.msg.id);
         msg_to_send.channel_id = event.msg.channel_id;
         msg_to_send.allowed_mentions.replied_user = true;
         msg_to_send.allowed_mentions.users.push_back(event.msg.author.id);
         event.from->creator->message_create(msg_to_send);
      }
   }
}

}  // namespace dad_bot
