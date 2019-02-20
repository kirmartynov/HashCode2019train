SRCFILES := $(shell find . -type f -name '*.cpp')
INFILES := $(shell find . -type f -name '*.in')
OUTFILES := $(patsubst %.in,%.out,$(INFILES))

all: main.out dp.out $(OUTFILES)

main.out: $(SRCFILES)
	g++ -std=c++14 -O2 -o main.out main.cpp

dp.out: $(SRCFILES)
	g++ -g -std=c++2a -fconcepts -O3 -o dp.out dp.cpp

%.out: %.in main.out
	./main.out < $< > $@
