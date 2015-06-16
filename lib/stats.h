/*
 * stats.h
 * Author: Aven Bross
 * Date: 5/20/2015
 * 
 * Description:
 * Little stats library to do 1 var stats on input vectors
*/

#ifndef STATS_H
#define STATS_H

#include <vector>
#include <map>
#include <iostream>
#include <cmath>

template<typename T>
void oneVarStats(std::vector<T> records){
    double rounds = records.size();
    // Histogram of iteration numbers
    std::map<T,int> histogram;
    
    // Find mean and fill histogram
    double total = 0;
    for(auto iterations : records){
        total += (double)iterations;
        histogram[iterations]+=1;
    }
    double average = total/rounds;
    
    // Find standard deviation
    double total_square = 0;
    for(auto iterations : records){
        total_square += ((double)iterations-average)*((double)iterations-average);
    }
    double sd = std::sqrt(total_square/rounds);
    
    // Print out main stats
    std::cout << "MAIN STATS:\n";
    std::cout << "Rounds: " << rounds << "\n";
    std::cout << "Average: " << average << "\n";
    std::cout << "Standard Deviation: " << sd << "\n\n";
    
    // Print out round data
    std::cout << "ROUND DATA:\n";
    double sum = 0;
    for(const auto cat : histogram){
        sum += cat.second;
        std::cout << "Iterations: " << cat.first << "\tRounds: " << ((double)cat.second) << "\tPDF: " << ((double)cat.second)/rounds  << "\tCDF: " << sum/rounds << "\n";
    }
}

#endif
