CXX := g++
FLAGS := -std=c++11 -O3

.PHONY: clean all

all: data random multiples line 
	$(CXX) $(FLAGS) small.cc -o small.mio
	$(CXX) $(FLAGS) large.cc -o large.mio
	./small.mio < data/small1.in > small.out
	./large.mio < data/small1.in > large.out
	diff small.out large.out
	./small.mio < data/small2.in > small.out
	./large.mio < data/small2.in > large.out
	diff small.out large.out
	./small.mio < data/small3.in > small.out
	./large.mio < data/small3.in > large.out
	diff small.out large.out
	./large.mio < data/small1.in > data/small1.out
	./large.mio < data/small2.in > data/small2.out
	./large.mio < data/small3.in > data/small3.out
	./large.mio < data/large1.in > data/large1.out
	./large.mio < data/large2.in > data/large2.out
	./large.mio < data/large3.in > data/large3.out
	rm ./*.mio
	rm ./*.out
	tar zcvf data.tar.gz -C data .

data:
	mkdir -p data

random: gen_random.cc
	$(CXX) $(FLAGS) gen_random.cc -o random.mio
	./random.mio 0 > data/small1.in
	./random.mio 1 > data/large1.in
	rm random.mio

multiples: gen_multiples.cc
	$(CXX) $(FLAGS) gen_multiples.cc -o multiples.mio
	./multiples.mio 0 > data/small2.in
	./multiples.mio 1 > data/large2.in
	rm multiples.mio

line: gen_line.cc
	$(CXX) $(FLAGS) gen_line.cc -o line.mio
	./line.mio 0 > data/small3.in
	./line.mio 1 > data/large3.in
	rm line.mio

clean:
	rm -rf data
