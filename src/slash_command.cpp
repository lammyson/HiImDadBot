#include "slash_command.hpp"

#include <random>

#include "dad_jokes.hpp"

namespace dad_bot::slash_command {

void on_slash_command(const dpp::slashcommand_t& event) {
   // Reply with a random dad joke
   if (event.command.get_command_name() == dad_bot::slash_command::dad_joke_command) {
      static std::random_device rdev;
      static std::mt19937 mt19937(rdev());
      static std::uniform_int_distribution<unsigned int> dist(0, dad_bot::dad_jokes::jokes.size() - 1);
      event.reply(dad_bot::dad_jokes::jokes.at(dist(mt19937)));
   }
}

} // namespace dad_bot::slash_command
