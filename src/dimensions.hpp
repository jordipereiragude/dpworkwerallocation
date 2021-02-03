#pragma once

#include <limits>
#include <string>

typedef double Time;
const Time inf_time = std::numeric_limits<Time>::max();

inline std::string tostring(const Time& t) { return (t<inf_time?std::to_string(t):"inf"); }
