BUILDDIR ?= build
CFG      ?= default
NAME     ?= c4
SRCDIR   ?= src

Q ?= @

BINDIR := $(BUILDDIR)/$(CFG)
BIN    := $(BINDIR)/$(NAME)
SRC    := $(sort $(wildcard $(SRCDIR)/*.cc))
OBJ    := $(SRC:$(SRCDIR)/%.cc=$(BINDIR)/%.o)
DEP    := $(OBJ:%.o=%.d)

CFLAGS   += -Wall -W -Werror
CXXFLAGS += $(CFLAGS) -std=c++11

DUMMY := $(shell mkdir -p $(sort $(dir $(OBJ))))

.PHONY: all clean

all: $(BIN)

-include $(CFG).cfg

-include $(DEP)

clean:
	@echo "===> CLEAN"
	$(Q)rm -fr $(BINDIR)

$(BIN): $(OBJ)
	@echo "===> LD $@"
	$(Q)$(CXX) -o $(BIN) $(OBJ)

$(BINDIR)/%.o: $(SRCDIR)/%.cc
	@echo "===> CXX $<"
	$(Q)$(CXX) $(CXXFLAGS) -MMD -c -o $@ $<
