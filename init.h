// This file specifies interfaces for initializing a project.

#ifndef UTIL_INIT_H_
#define UTIL_INIT_H_

namespace util {

// Initializes a project. Should be called at the very beginning of main.
// E.g.
//   Init(argv[0], argc, argv);
void Init(const char* name, int argc, char** argv);

}  // namespace util

#endif  // UTIL_INIT_H_
