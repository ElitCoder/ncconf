LIB			:= ncconf

SRCS		:= $(wildcard src/*.cpp)
OBJS		:= $(SRCS:.cpp=.o)

CXXFLAGS	+= -std=c++11 -Wall -Wextra -pedantic-errors
CXXFLAGS	+= -g
CXXFLAGS	+= -fPIC

# Include headers
CXXFLAGS	+= -Iinclude

# Shared library by default
TARGET		:= lib/lib$(LIB).so

$(info $$var is [${SRCS}])

.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET) $(OBJS:.o=.d)

.PHONY: $(TARGET)
$(TARGET): $(OBJS)
	$(CXX) $^ $(LDFLAGS) -o $(TARGET) -shared $(LDLIBS)

CXXFLAGS	+= -MMD
-include $(OBJS:.o=.d)