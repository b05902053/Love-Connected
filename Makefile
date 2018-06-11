.PHONY: clean

TARGET=naive.out

all: $(TARGET)

naive.out: main.o naive.o
	@echo "making: " $@
	g++ -o naive.out main.o naive.o

%.o: %.cpp
	@echo "making: " $@
	g++ -c $<

clean:
	rm -f *.o *.out