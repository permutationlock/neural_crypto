/*
 * neural_crypto.cpp
 * Author: Aven Bross
 * Date: 5/19/2015
 * 
 * Description:
 * Uses two Tree Parity Machines to generate private keys
 *   over a public network.
 * Each TPM neural network evaluates an input vector and 
 *   then the networks are trained only if each tpm 
 *   produces the same output bit.
 */
 
#include "lib/tpm.h"
#include "lib/stats.h"
#include <vector>
#include <string>
#include <random>
#include <iostream>
#include <map>

using std::vector;
using std::map;
using std::string;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::cout;


const int L = 2;
const int K = 16;
const int N = 16;

const int rounds = 1000;
 
int main(){
    random_device rd;
    mt19937 el(rd());
    uniform_int_distribution<int> udist(0,1);
    
    // Records drinks taken
    vector<int> standard_records;
    vector<int> attack_records;
    
    for(int i=0; i<rounds; i++){
        TreeParityMachine tpm1(K,N,L);
        TreeParityMachine tpm2(K,N,L);
        
        TreeParityMachine atk(K,N,L);
        
        bool done = false;
        bool attack_done = false;
        int iterations = 0;
        int attack_iterations = 0;
        while(!attack_done){
            vector<vector<int>> input;
        
            for(int r=0; r<K; r++){
                std::vector<int> temp;
                for(int c=0; c<N; c++){
                    temp.push_back(udist(el)*2-1);
                }
                input.push_back(temp);
            }
            for(int i=0; i<input.size(); i++){
                for(int j=0; j<input[i].size(); j++){
                    int temp = input[i][j];
                }
            }
            int val = tpm1.check(input);
            if(val == tpm2.check(input)){
                tpm1.train(input, val);
                tpm2.train(input, val);
                atk.train(input, val);
            }
            if((tpm1.value().compare(tpm2.value()) == 0)){
                done = true;
            }
            if(done && (atk.value().compare(tpm2.value()) == 0)){
                attack_done = true;
            }
            if(!done) iterations++;
            attack_iterations++;
        }
        standard_records.push_back(iterations);
        attack_records.push_back(attack_iterations);
    }
    cout << "Test Parameters:\n";
    cout << "    L = " << L << "\n";
    cout << "    K = " << K << "\n";
    cout << "    N = " << N << "\n\n";
    cout << "Standard Users:\n";
    oneVarStats(standard_records);
    cout << "\n\nAttacker:\n";
    oneVarStats(attack_records);
}
