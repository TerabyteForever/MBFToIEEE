/*
    This code converts single-precision Microsoft Binary Format to the IEEE 754 format.
    
    Copyright (c) 2024 - Terabyte Forever
*/

#include <iostream>
#include <cstdint>

//This was made in order to process the same float in hex manners.
union FloatType {
    uint32_t int_;
    float fp_;
};


/// @brief Converts MBF to IEEE 754.
/// @param mbf_hex MBF float in hexadecimal.
/// @return IEEE 754 representation of the given value.
inline FloatType mbf_to_ieee(const FloatType& mbf_hex) noexcept {
    FloatType u;
    uint8_t exponent = ((mbf_hex.int_ & 0xFF000000) >> 24) - 2; //2 is removed for bias sake. Thinking bitwisely, this thing removes that bias bit.
    uint8_t sign_bit = ((mbf_hex.int_ & 0x800000) >> 23);
    u.int_ = (sign_bit << 31) | (exponent << 23) | (mbf_hex.int_ & 0x7FFFFF);
    return u;
}

/// @brief Converts IEEE float to MBF.
/// @param ieee_hex IEEE float in hexadecimal.
/// @return MBF representation of the given value.
inline FloatType ieee_to_mbf(const FloatType& ieee_hex) noexcept {
    FloatType u;
    uint8_t sign_bit = ((ieee_hex.int_ & 0x80000000) >> 31);
    uint8_t exponent = ((ieee_hex.int_ & 0x7F800000) >> 23) + 2; //Add that goddamn bias again.
    u.int_ = (exponent << 24) | (sign_bit << 23) | (ieee_hex.int_ & 0x7FFFFF); 
    return u;
}

int main(int argc, char** argv){
    FloatType mbf, ieee;
    mbf.int_ = 0x8676AF91;
    ieee = mbf_to_ieee(mbf);
    std::cout<<std::hex<<ieee.int_<<'\n'<<ieee.fp_<<std::endl<<std::endl;
    mbf = ieee_to_mbf(ieee);
    std::cout<<std::hex<<mbf.int_<<'\n'<<mbf.fp_<<std::endl;
    return 0;
}