# Specify compiler
COMP = clang++ -std=c++1y -O2

# Specify target
all: neural_crypto

# Build executable
neural_crypto: tpm.o neural_crypto.o
	$(COMP) tpm.o neural_crypto.o -o neural_crypto

# Build neurl crypto object
neural_crypto.o: neural_crypto.cpp
	$(COMP) -c neural_crypto.cpp

# Build tree parity machine object
tpm.o: lib/tpm.cpp
	$(COMP) -c lib/tpm.cpp

# Clean build
clean:
	rm *.o neural_crypto

