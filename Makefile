LIB				:= ncconf

SRCS			:= $(wildcard src/*.cpp)
OBJS			:= $(SRCS:.cpp=.o)

CXXFLAGS		+= -std=c++11 -Wall -Wextra -pedantic-errors
CXXFLAGS		+= -g
CXXFLAGS		+= -fPIC

# Include headers
CXXFLAGS		+= -Iinclude

# Shared library by default
TARGET			:= lib/lib$(LIB).so

# Test
TEST_SRCS		:= $(wildcard test/*.cpp)
TEST_OBJS		:= $(TEST_SRCS:.cpp=.o)
TEST_TARGET		:= test/test_ncconf
TEST_LDFLAGS	:= -Llib
TEST_LDLIBS		:= -lncconf -Wl,-rpath=../lib

.PHONY: all
all: $(TARGET)

.PHONY: test
test: all $(TEST_TARGET)

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET) $(OBJS:.o=.d)
	rm -f $(TEST_OBJS) $(TEST_TARGET) $(TEST_OBJS:.o=.d)

.PHONY: $(TARGET)
$(TARGET): $(OBJS)
	$(CXX) $^ $(LDFLAGS) -o $(TARGET) -shared $(LDLIBS)

.PHONY: $(TEST_TARGET)
$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $^ $(LDFLAGS) $(TEST_LDFLAGS) -o $(TEST_TARGET) $(LDLIBS) $(TEST_LDLIBS)

CXXFLAGS	+= -MMD
-include $(OBJS:.o=.d)