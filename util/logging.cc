#include "logging.h"

#include <cstdlib>
#include <cxxabi.h>
#include <execinfo.h>
#include <iostream>
#include <sstream>
#include <string>

#include "util/commandline_flag.h"

DEFINE_int(backtrace_buffer_size, 100, "The buffer size for backtrace.");

DEFINE_int(v, ::util::Logger::Level::INFO, "Log level.");

namespace util {
namespace {

std::string DemangleLine(const std::string& line) {
  size_t start = line.find("(");
  if (start == std::string::npos) {
    return line;
  }
  ++start;
  size_t end = line.find("+", start);
  if (end == std::string::npos) {
    return line;
  }
  std::string name = line.substr(start, end - start);

  std::string ans;
  int status;
  char* real_name =
      abi::__cxa_demangle(name.c_str(), nullptr, nullptr, &status);
  if (status == 0 && real_name) {
    ans = line.substr(0, start) + real_name + line.substr(end);
  } else {
    ans = line;
  }

  if (real_name) {
    std::free(real_name);
  }
  return ans;
}

}  // namespace

Logger::~Logger() {
  if (!should_log_ || level_ > FLAG_v) return;

  // Uses an ostringstream as buffer to output in order to print consistently
  // under multithreading.
  std::ostringstream oss;

  // Indents by 2.
  std::istringstream iss(ostr_.str());
  std::string line;
  std::getline(iss, line);
  oss << line << std::endl;
  while (std::getline(iss, line)) {
    oss << "  " << line << std::endl;
  }

  // Handles FATAL to output backtrace.
  if (level_ == Level::FATAL) {
    void* backtrace_buffer[FLAG_backtrace_buffer_size];
    size_t size = backtrace(backtrace_buffer, FLAG_backtrace_buffer_size);
    char** backtrace_msgs = backtrace_symbols(backtrace_buffer, size);
    if (backtrace_msgs == nullptr) {
      oss << " Failed to backtrace." << std::endl;
      return;
    }
    for (size_t i = 0; i < size; ++i) {
      oss << "  " << DemangleLine(backtrace_msgs[i]) << std::endl;
    }
    std::free(backtrace_msgs);
    std::cerr << oss.str();
    std::exit(EXIT_FAILURE);
  } else {
    std::cerr << oss.str();
  }
}

}  // namespace util
