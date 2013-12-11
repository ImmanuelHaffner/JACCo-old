.SUFFIXES:
	%:: SCCS/s.%
	%:: RCS/%
	%:: RCS/%,v
	%:: %,v
	%:: s.%

BUILDDIR		?= build
CFG					?= default
NAME				?= c4
SRCDIR			?= src
TESTDIR			?= test/cppunit
DOCSDIR			?= doc

CPPUNIT_PATH	?= /usr/lib/
CPPUNIT_INCLUDE	?= /usr/include/cppunit/

Q						?= @

BINDIR			:= $(BUILDDIR)/$(CFG)
TESTBINDIR	:= $(TESTDIR)/$(CFG)

BIN					:= $(BINDIR)/$(NAME)
TESTBIN			:= $(TESTBINDIR)/$(NAME)

PWD					:= $(shell pwd)

SRC					:= $(sort $(subst $(PWD), ".", $(shell find $(SRCDIR)/ -name '*.cc')))
OBJ					:= $(SRC:$(SRCDIR)/%.cc=$(BINDIR)/%.o)
DEP					:= $(OBJ:%.o=%.d)

TEST_SRC		:= $(sort $(subst $(PWD), ".", $(shell find $(TESTDIR)/ -name '*.cc')))
TEST_SRC2		:= $(shell echo $(SRC) | sed 's/src\/main.cc/ /')
TEST_OBJ		:= $(TEST_SRC:$(TESTDIR)/%.cc=$(TESTBINDIR)/%.o)
TEST_OBJ2		:= $(TEST_SRC2:$(SRCDIR)/%.cc=$(BINDIR)/%.o)
#TEST_SRC		+= $(TEST_SRC2)
TEST_OBJ		+= $(TEST_OBJ2)
TEST_DEP		:= $(TEST_OBJ:%.o=%.d)

DUMMY				:= $(shell mkdir -p $(sort $(dir $(OBJ))))
DUMMY				:= $(shell mkdir -p $(sort $(dir $(TEST_OBJ))))

#DEBUG				?= 1

ifeq ($(DEBUG), 1)
	CFLAGS	+= -g -DDEBUG
else
	CFLAGS	?= -O2
endif

ifeq ($(VERBOSE), 1)
	CXXFLAGS	+= -v
endif

CFLAGS			+= -Wall -W -pedantic# -Werror
CXXFLAGS		+= $(CFLAGS) -std=c++11


.PHONY: all check check-printer check-all clean cleanall doxy

all: $(BIN)

-include $(CFG).cfg

-include $(DEP)

check: $(TESTBIN)
	-	$(TESTBIN)

-include $(TEST_DEP)

check-printer: all
	@echo ""
	@cd test/;\
	./test-printer.sh;\
	cd ..

check-all: all check
	@echo ""
	@cd test/;\
	./test-tokenize.sh;\
	./test-printer.sh;\
	cd ..

clean:
	@echo "===> CLEAN"
	$(Q)rm -fr $(BINDIR)/
	$(Q)rm -fr $(TESTBINDIR)

cleanall: clean
	@echo "===> CLEANALL"
	$(Q)rm -fr $(DOCSDIR)/

doxy:
	@echo "===> DOXYGEN"
	$(Q)doxygen

$(BIN): $(OBJ)
	@echo "===> LD $@"
	$(Q)$(CXX) $(CXXFLAGS) -o $(BIN) $^

$(TESTBIN): $(TEST_OBJ)
	@echo "===> LD $@"
	$(Q)$(CXX) $(CXXFLAGS) -o $(TESTBIN) $^ -L${CPPUNIT_PATH}/lib -lstdc++ -lcppunit -ldl

$(BINDIR)/%.o: $(SRCDIR)/%.cc
	@echo "===> $(CXX) $<   ->   $@"
	$(Q)$(CXX) $(CXXFLAGS) -MMD -c -o $@ $<

$(TESTBINDIR)/%.o: $(TESTDIR)/%.cc
	@echo "===> $(CXX) $<   ->   $@"
	$(Q)$(CXX) $(CXXFLAGS) -MMD -c -o $@ $< -I${CPPUNIT_INCLUDE}
