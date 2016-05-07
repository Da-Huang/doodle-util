# util
This library provides useful utils.

---
## Modules
* [`algorithm`](util/algorithm)
* [`check`](util/check.h)
* [`commandline_flag`](util/commandline_flag.h)
* [`io`](util/io.h)
* [`iterator`](util/iterator)
* [`logging`](util/logging.h)
* [`stream`](util/stream)
* [`string`](util/string)
* [`thread`](util/thread)

---
## Requirements
* `g++ >= 4.8`

---
## Build & Clean
```bash
# Build
make

# Clean
make clean
```

---
## Run All Unit Tests
```bash
# Normal Run
for i in `find -name "*_test"`; do $i; done

# Run with Heapcheck
for i in `find -name "*_test"`; do valgrind --tool=memcheck $i; done
```
