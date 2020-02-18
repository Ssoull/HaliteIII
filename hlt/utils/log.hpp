#pragma once

#include <string>

namespace custom_logger
{
void open(int bot_id);
void log(const std::string &message);
} // namespace custom_logger
