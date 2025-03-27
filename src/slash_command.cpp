#include "slash_command.hpp"

#include <random>
#include <variant>

#include "dad_jokes.hpp"

namespace dad_bot::slash_command {

namespace {
constexpr auto all_dad_jokes_formatted() -> std::string {
   std::string string;
   for (std::size_t i = 0; i < dad_bot::dad_jokes::jokes.size(); ++i)
   {
      string += std::to_string(i) + std::string(dad_bot::dad_jokes::jokes.at(i)) + '\n';
   }
   return string;
}
}

void on_slash_command(const dpp::slashcommand_t& event) {
   event.from->creator->log(dpp::loglevel::ll_debug, "on_slash_command='" + event.command.get_command_name() + "'");

   // Reply with a random dad joke
   if (event.command.get_command_name() == dad_bot::slash_command::dad_joke_command) {
      // Provides a random number when selecting a random dad joke
      static std::random_device rdev;
      static std::mt19937 mt19937(rdev());
      static std::uniform_int_distribution<unsigned int> dist(0, dad_bot::dad_jokes::jokes.size() - 1);

      // Get all parameters
      const auto index_variant = event.get_parameter("index");
      const auto print_all_variant = event.get_parameter("all");

      // No parameters so just reply with a random dad joke
      if (std::holds_alternative<std::monostate>(index_variant) && std::holds_alternative<std::monostate>(print_all_variant)) {
         event.reply(dad_bot::dad_jokes::jokes.at(dist(mt19937)));
         return;
      }

      // Reply with a specific dad joke if the index subcommand exists
      if (std::holds_alternative<int64_t>(index_variant)) {
         event.reply(dad_bot::dad_jokes::jokes.at(std::get<int64_t>(index_variant)));
      }

      // Reply with all dad joke if the all subcommand exists and matches "all"
      if (std::holds_alternative<std::string>(print_all_variant) && std::get<std::string>(print_all_variant) == "all") {
         event.reply(all_dad_jokes_formatted());
      }
   }
}

} // namespace dad_bot::slash_command
