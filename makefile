all: neural_crypto

neural_crypto: tpm.o neural_crypto.o
	g++ tpm.o neural_crypto.o -std=c++11 -o neural_crypto

neural_crypto.o: neural_crypto.cpp
	g++ -c neural_crypto.cpp -std=c++11 -O3

tpm.o: lib/tpm.cpp
	g++ -c lib/tpm.cpp -std=c++11 -O3

clean:
	rm *.o neural_crypto

