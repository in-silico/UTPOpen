CXX := g++
FLAGS := -std=c++11 -O3

.PHONY: clean all

all: data random
	$(CXX) $(FLAGS) solution.cc -o sol.mio
	./sol.mio < sample.in > output.mio
	diff sample.out output.mio
	./sol.mio < data/input > data/output
	rm ./*.mio
	rm -f ./*.tar.gz
	tar zcvf data.tar.gz -C data .

data:
	mkdir -p data

random: generator.cc
	$(CXX) $(FLAGS) generator.cc -o random.mio
	./random.mio > data/input
	cat sample.in >> data/input
	rm random.mio


clean:
	rm -rf data
