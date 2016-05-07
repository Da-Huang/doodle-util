GXX = g++
INCLUDES = -I.
CXXFLAGS = \
-std=c++11 -Wall $(INCLUDES) -march=native -funroll-loops -O3
LDFLAGS = -rdynamic -pthread
CXX = $(GXX)
LD = $(GXX)

SOURCE_DIR = util util/iterator util/stream util/string util/thread
SOURCE_FILES = \
$(wildcard *.cc) $(foreach dir,$(SOURCE_DIR),$(wildcard $(dir)/*.cc))
SOURCE_TESTS = \
$(wildcard *test.cc) $(foreach dir,$(SOURCE_DIR),$(wildcard $(dir)/*test.cc))
SOURCE_MAINS = \
$(wildcard *main.cc) $(foreach dir,$(SOURCE_DIR),$(wildcard $(dir)/*main.cc))
SOURCE_LIBS = $(filter-out $(SOURCE_TESTS) $(SOURCE_MAINS),$(SOURCE_FILES))

LIB_OBJS = $(SOURCE_LIBS:.cc=.o)
DEPS = $(SOURCE_FILES:.cc=.d)
TESTS = $(SOURCE_TESTS:.cc=)
MAINS = $(SOURCE_MAINS:.cc=)

EXISTED_DEPS = \
$(wildcard *.d) $(foreach dir,$(SOURCE_DIR),$(wildcard $(dir)/*.d))
EXISTED_OBJS = \
$(wildcard *.o) $(foreach dir,$(SOURCE_DIR),$(wildcard $(dir)/*.o))
EXISTED_LIBS = \
$(wildcard *.a) $(foreach dir,$(SOURCE_DIR),$(wildcard $(dir)/*.a))
EXISTED_TESTS = \
$(wildcard *test) $(foreach dir,$(SOURCE_DIR),$(wildcard $(dir)/*test))
EXISTED_MAINS = \
$(wildcard *main) $(foreach dir,$(SOURCE_DIR),$(wildcard $(dir)/*main))

all: lib main test

LIB = util-lib.a

lib: $(LIB)

main: $(MAINS)

test: $(TESTS)

%.o: %.cc
	@echo Compiling $< and Generating its Dependencies ...
	$(CXX) -c $(CXXFLAGS) -MMD -o $@ $<

%.a: $(LIB_OBJS)
	@echo Linking Static Library: $@ ...
	ar rcs $@ $^
	@echo Library $@ Done.

%main: %main.o $(LIB)
	@echo Generating Main: $@ ...
	$(LD) -o $@ $^ $(LDFLAGS)
	@echo Main $@ Done.

%test: %test.o $(LIB)
	@echo Generating Test: $@ ...
	$(LD) -o $@ $^ $(LDFLAGS)
	@echo Test $@ Done.

-include $(DEPS)

clean:
	@echo Removing Mains.
	@$(RM) $(EXISTED_MAINS)
	@echo Removing Tests.
	@$(RM) $(EXISTED_TESTS)
	@echo Removing Libraries.
	@$(RM) $(EXISTED_LIBS)
	@echo Removing Objects.
	@$(RM) $(EXISTED_OBJS)
	@echo Removing Dependencies.
	@$(RM) $(EXISTED_DEPS)
	@echo All Clean.

.PHONY: all clean main test
.SECONDARY: $(EXISTED_OBJS)
