#include "slash_commands.hpp"

#include "dad_jokes.hpp"

#include <random>

namespace dad_bot {

void on_slash_command(const dpp::slashcommand_t& event)
{
   if (event.command.get_command_name() == dad_bot::dad_joke_command) {
      static std::random_device rdev;
      static std::mt19937 mt19937(rdev());
      static std::uniform_int_distribution<unsigned int> dist(0, dad_bot::dad_jokes::jokes.size()-1);
      event.reply(dad_bot::dad_jokes::jokes.at(dist(mt19937)));
   }
}

}  // namespace dad_bot