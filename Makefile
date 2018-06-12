.PHONY: clean

TARGET=parallel.out
all: $(TARGET)

naive.out: main.o naive.o naive.hpp constants.hpp
	@echo "making: " $@
	g++ -o naive.out main.o naive.o

parallel.out: main.o parallel.o parallel.hpp constants.hpp
	@echo "making: " $@
	g++ -o parallel.out main.o parallel.o

%.o: %.cpp
	@echo "making: " $@
	g++ -c $<

clean:
	rm -f *.o *.out