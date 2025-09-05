/*
    This code converts single-precision Microsoft Binary Format to the IEEE 754 format.
    
    Copyright (c) 2024 - Terabyte Forever
*/

#include <iostream>
#include "mbf.hpp"

int main(int argc, char** argv){
    TF::mbf_t mbf{0x8676AF91};
    float ieee = TF::MBF::mbf_to_ieee(mbf);
    std::cout<<ieee<<std::endl;
    return 0;
}