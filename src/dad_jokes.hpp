#pragma once

#include <array>
#include <string_view>

namespace dad_bot::dad_jokes {

using namespace std::string_view_literals;
constexpr std::array jokes = {
    "Dad: Anytime we're driving and I see a bunch of cows I always say: Look a flock of cows!\n"sv
    "Kid: Herd of cows dad\n"sv
    "Dad: Of course I've heard of them, there's a flock of them right over there!"sv,

    "(Driving past a graveyard)\n"sv
    "Dad: Look it's the dead centre of town. People are just dying to get in there. But did you know nobody who lives around here is allowed to be buried there?\n"sv
    "Kid: Why?\n"sv
    "Dad: Because you aren't allowed to bury people who are still living"sv,

    "How do you know when your clock is still hungry?\n"sv
    "It goes back four seconds"sv};
}  // namespace dad_bot::dad_jokes
