//
//  select_support.cpp
//  
//
//  Created by Elliott Sloate on 10/22/20.
//

#include "../rank_support/rank_support.hpp"
#include "select_support.hpp"
#include <iostream>
#include <math.h>
#include <map>
#include <typeinfo>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <time.h>
#include <unistd.h>
#include <chrono>
#include <boost/dynamic_bitset.hpp>

using namespace std;
using namespace boost;

select_support::select_support(rank_support * r){
    ranker = r;
}
uint64_t select_support::select1(uint64_t i){
    //input: int i, the ith 1
    //output: uin64_t position, the position in ranker's bitset that contains the ith 1
    dynamic_bitset<> * bitvec = ranker->bitvec;
    //pretending we don't know NS
    int size = bitvec->size();
    //do binary search
    uint64_t l = 0;
    uint64_t r = size-1;
    uint64_t mid = (l + r) / 2;
    bool ranked = false;
    while( l <= r){
        uint64_t rank_val = ranker->rank1(mid);
        if (rank_val == i){
            ranked = true;
            break;
        }
        else if(rank_val > i){
            r = mid - 1;
        }
        else if(rank_val < i){
            l = mid + 1;
        }
        mid = (l + r) / 2;

    }
    
    //we may have rank(mid) = i, but that could be a zero there
    // simply iterate until we find the 1, should only be at most BL iterations?
    if (ranked && (bitvec->test(mid) == true)){
        return mid;
    }
    else if(ranked){
        mid--;
        while(ranker->rank1(mid) == i){
            if(bitvec->test(mid) == true){
                return mid;
            }
            mid--;
        }
    }
    return -1;
}
uint64_t select_support::select0(uint64_t i){
    //input: int i, the ith 1
    //output: uin64_t position, the position in ranker's bitset that contains the ith 1
    dynamic_bitset<> * bitvec = ranker->bitvec;
    //pretending we don't know NS
    int size = bitvec->size();
    //do binary search
    uint64_t l = 0;
    uint64_t r = size-1;
    uint64_t mid = (l + r) / 2;
    bool ranked = false;
    while( l <= r){
        uint64_t rank_val = ranker->rank0(mid);
        if (rank_val == i){
            ranked = true;
            break;
        }
        else if(rank_val > i){
            r = mid - 1;
        }
        else if(rank_val < i){
            l = mid + 1;
        }
        mid = (l + r) / 2;

    }

    //we may have rank0(mid) = i, but that could be a 1 there
    // simply iterate until we find the 0, should only be at most BL iterations?
    if (ranked && (bitvec->test(mid) == 0)){
        return mid;
    }
    else if (ranked){
        mid--;
        while(ranker->rank0(mid) == i){
            if(bitvec->test(mid) == 0){
                return mid;
            }
            mid--;
        }
    }
    return -1;

}
uint64_t select_support::overhead(){
    return uint64_t(sizeof(*this));
}
void select_support::save(string& fname){
    ranker->save(fname);
}
void select_support::load(string& fname){
    ranker->load(fname);
}
/*
int main(){
    //testing for various sizes
    for(int i = 5;i<26;i++){
        unsigned long long int powval = (unsigned long long int) (pow(2,i));
        unsigned long long int bitval = rand() % powval;
        dynamic_bitset<> bv(powval,bitval);
        rank_support r(&bv);
        select_support s(&r);
        uint64_t start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        for (int j = 0; j < 10000;j++){
            s.select1( i / 2);
        }
        
        uint64_t end = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        uint64_t time = end-start;
        cout << powval << "," << s.overhead() << "," << time << endl;
    }
    
    
}*/
