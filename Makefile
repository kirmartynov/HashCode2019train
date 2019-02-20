SRCFILES := $(shell find . -type f -name '*.cpp')
INFILES := $(shell find . -type f -name '*.in')
OUTFILES := $(patsubst %.in,%.out,$(INFILES))

all: main.out $(OUTFILES)

main.out: $(SRCFILES)
	g++ -std=c++14 -O2 -o main.out main.cpp

%.out: %.in main.out
	./main.out < $< > $@
