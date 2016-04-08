# util
This library provides useful utils.

---
## Modules
* [`check`](check.h)
* [`commandline_flag`](commandline_flag.h)
* [`io`](io.h)
* [`logging`](logging.h)
* [`stream`](stream)
* [`string`](string.h)

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
