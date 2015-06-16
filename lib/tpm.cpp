/*
 * tpm.cpp
 * Author: Aven Bross
 * Date: 5/19/2015
 * 
 * Description:
 * Tree Parity Machine neural network implementation.
 * Has one output node and k hidden nodes each with n input nodes.
*/

#ifndef TPM_CPP
#define TPM_CPP

#include "tpm.h"
#include <cstddef>
#include <vector>
#include <string>
#include <random>

// Construct a tree parity machine with given dimensions
TreeParityMachine::TreeParityMachine(std::size_t k, std::size_t n, std::size_t l): _l(l) {
    std::random_device rd;	// Create random device
	std::mt19937 el(rd());	// Use 32 bit mersenne twister
	std::uniform_int_distribution<int> udist(-_l,_l);
	
    for(int i=0; i<k; i++){
        std::vector<int> temp;
        for(int j=0; j<n; j++){
            temp.push_back(udist(el));
        }
        _w.push_back(temp);
    }
}

// Produce output bit from given input vectors
int TreeParityMachine::check(const std::vector<std::vector<int>> & input) const {
    int result = 1;
    for(int i=0; i<_w.size(); i++){
        int temp = 0;
        for(int j=0; j<_w[i].size(); j++){
            temp += input[i][j] * _w[i][j];
        }
        result *= (temp >= 0) ? 1 : -1;
    }
    return result;
}

// Train neural network based on given inputs
void TreeParityMachine::train(const std::vector<std::vector<int>> & input, int val) {
    for(int i=0; i<_w.size(); i++){
        // Calculate output bit of each hidden node
        int temp = 0;
        for(int j=0; j<_w[i].size(); j++){
            temp += input[i][j] * _w[i][j];
        }
        int result = (temp >= 0) ? 1 : -1;
        
        // If ouput bit matches, apply hebian learning
        if(result == val){
            for(int j=0; j<_w[i].size(); j++){
                _w[i][j] += input[i][j];
                if(_w[i][j] > _l) _w[i][j] = _l;
                if(_w[i][j] < (-1)*_l) _w[i][j] = (-1)*_l;
            }
        }
    }
}

// Return the weight vector as a string
std::string TreeParityMachine::value() const {
    std::string result;
    for(int i=0; i<_w.size(); i++){
        for(int j=0; j<_w[i].size(); j++){
            int temp = _w[i][j] + _l;
            result += std::to_string(temp);
            result += " ";
            if(temp<10) result += " ";
        }
        if(i<_w.size()-1) result += "|  ";
    }
    return result;
}

#endif
