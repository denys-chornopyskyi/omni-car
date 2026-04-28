#include <string>

namespace Response {
inline std::string ok(std::string cmd) { return std::string("ok: ") + cmd; }

inline std::string err(std::string cmd) { return std::string("unknown: ") + cmd; }
} 