/*
 * tpm.h
 * Author: Aven Bross
 * Date: 5/19/2015
 * 
 * Description:
 * Tree Parity Machine neural network implementation.
 * Has one output node and k hidden nodes each with n input nodes.
*/

#ifndef TPM_H
#define TPM_H

#include <cstddef>
#include <vector>
#include <string>

class TreeParityMachine {
public:
    // Construct a tree parity machine with given dimensions
    TreeParityMachine(std::size_t k, std::size_t n, std::size_t l);
    
    // Produce output bit from given input vectors
    int check(const std::vector<std::vector<int>> & input) const;
    
    // Train neural network based on given inputs and training value
    void train(const std::vector<std::vector<int>> & input, int val);
    
    // Return the weight vector as a string
    std::string value() const;
    
private:
    // Weight vector
    std::vector<std::vector<int>> _w;
    // Weight range
    int _l;
};

#endif
