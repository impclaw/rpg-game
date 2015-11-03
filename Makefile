#########################
# customise these
CFILES := $(wildcard gui/*.cpp) $(wildcard states/*.cpp) $(wildcard *.cpp)
PROG := game
CXXFLAGS := -Wall -Wextra -g -std=c++11 -pedantic -Wno-unused-variable -Wno-unused-parameter -Wno-unused-private-field
LDFLAGS := -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio -llua5.2 -ldl
########################

# -MMD generates dependencies while compiling
CFLAGS += -MMD
CC := clang++
CXX := clang++

OBJFILES := $(CFILES:.cpp=.o)
DEPFILES := $(CFILES:.cpp=.d)

$(PROG) : $(OBJFILES)
	@$(LINK.o) $(LDFLAGS) -o $@ $^

clean :
	rm -f $(PROG) $(OBJFILES) $(DEPFILES)

data: 
	-zip -j -r -0 data.pk3 res/*

-include $(DEPFILES)
