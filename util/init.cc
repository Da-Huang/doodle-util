#include "init.h"

#include <cstdlib>
#include <string>
#include <unordered_map>

#include "util/check.h"
#include "util/commandline_flag.h"

DEFINE_bool(help, false, "Show help information.");

namespace util {

void Init(const char* name, int argc, char** argv) {
  // Builds flag map.
  std::unordered_map<std::string, AbstractCommandlineFlag*> flag_map;
  for (AbstractCommandlineFlag* flag :
       *AbstractCommandlineFlag::mutable_flags()) {
    flag_map[flag->name()] = flag;
  }

  int i = 1;
  while (i < argc) {
    CHECK(argv[i][0] == '-' && argv[i][1] == '-')
        << "Error at " << i << "-th item: argument '" << argv[i]
        << "' should start with '--'.";

    std::string item = argv[i];

    // Gets argument's name.
    std::string name, value;
    size_t index = item.find("=");
    if (index == std::string::npos) {
      name = item.substr(2);
    } else {
      name = item.substr(2, index - 2);
    }

    // Checks whether argument exists.
    auto it = flag_map.find(name);
    CHECK(it != flag_map.end()) << "Error at " << i << "-th item: argument '"
                                << name << "' not found.";
    AbstractCommandlineFlag* flag = it->second;

    // Gets argument's value.
    if (index == std::string::npos) {
      // '=' is not contained.
      if (dynamic_cast<CommandlineFlag<bool>*>(flag)) {
        // Flag is bool type. Makes a smart judgement on whether next item is
        // value.
        if (i + 1 >= argc || argv[i + 1][0] == '-') {
          value = "true";
        } else {
          value = argv[++i];
        }
      } else {
        // Flag is not bool type. Value should be next item.
        value = argv[++i];
      }
    } else {
      // '=' is not contained.
      value = item.substr(index + 1);
    }

    it->second->set_value(value);
    ++i;
  }

  if (FLAG_help) {
    for (const AbstractCommandlineFlag* flag :
         *AbstractCommandlineFlag::mutable_flags()) {
      std::cerr << flag->ToString() << std::endl;
    }
    std::exit(EXIT_SUCCESS);
  }
}

}  // namespace util
