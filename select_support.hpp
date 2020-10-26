//
//  select_support.hpp
//  
//
//  Created by Elliott Sloate on 10/22/20.
//

#ifndef select_support_hpp
#define select_support_hpp

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <typeinfo>
#include <fstream>
#include <math.h>
#include <boost/dynamic_bitset.hpp>
#include "../rank_support/rank_support.hpp"

class select_support
{
 
public:
    rank_support * ranker;
    
    select_support(rank_support * r);
     uint64_t select1(uint64_t i);
     uint64_t select0(uint64_t i);
     uint64_t overhead();
     void save(std::string& fname);
     void load(std::string& fname);
};

#endif /* select_support_hpp */
