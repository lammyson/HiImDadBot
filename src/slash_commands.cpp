#include "slash_commands.hpp"

#include "dad_jokes.hpp"

namespace dad_bot {

void on_slash_command(const dpp::slashcommand_t& event)
{
   if (event.command.get_command_name() == dad_bot::dad_joke_command) {
      event.reply(dad_bot::dad_jokes::jokes.at(0));
   }
}

}  // namespace dad_bot