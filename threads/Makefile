.PHONY: clean

TARGET=parallel.out
LIB=-lpthread
all: $(TARGET)

naive.out: main.o naive.o naive.hpp constants.hpp
	@echo "making: " $@
	g++ -o naive.out main.o naive.o

parallel.out: main.o parallel.o parallel.hpp constants.hpp
	@echo "making: " $@
	g++ -o parallel.out main.o parallel.o $(LIB)

%.o: %.cpp
	@echo "making: " $@
	g++ -c $<

clean:
	rm -f *.o *.out