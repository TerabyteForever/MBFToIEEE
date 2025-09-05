/*
    This code converts single-precision Microsoft Binary Format to the IEEE 754 format.

    Note that you will have to also convert the bit mode if necessary; for instance, Computrac/Metastock file system holds its data on big endian form.
    
    Copyright (c) 2024 - Terabyte Forever

    Updates:
        - 1.9.2025: Encapsulated the distributed functions to single library.
*/
#include <iostream>
#include <cstdint>

namespace TF{
    //This was made in order to process the same float in hex manners.
    union mbf_t {
        uint32_t int_;
        float fp_;
    };
    class MBF{
        public:
            MBF();
            static float mbf_to_ieee(const mbf_t& mbf_hex) noexcept;
            static mbf_t ieee_to_mbf(const float& ieee_hex) noexcept;          
            ~MBF();
    };
};
/// @brief Converts MBF to IEEE 754.
/// @param mbf_hex MBF float in hexadecimal.
/// @return IEEE 754 representation of the given value.
float TF::MBF::mbf_to_ieee(const TF::mbf_t& mbf_hex) noexcept {
    TF::mbf_t u;
    uint8_t exponent = ((mbf_hex.int_ & 0xFF000000) >> 24) - 2; //2 is removed for bias sake. Thinking bitwisely, this thing removes that bias bit.
    uint8_t sign_bit = ((mbf_hex.int_ & 0x800000) >> 23);
    u.int_ = (sign_bit << 31) | (exponent << 23) | (mbf_hex.int_ & 0x7FFFFF);
    return u.fp_;
}
/// @brief Converts IEEE float to MBF.
/// @param ieee_hex IEEE float in hexadecimal.
/// @return MBF representation of the given value.
TF::mbf_t TF::MBF::ieee_to_mbf(const float& ieee_hex) noexcept {
    TF::mbf_t u;
    TF::mbf_t temp;
    temp.fp_ = ieee_hex;
    uint8_t sign_bit = ((temp.int_ & 0x80000000) >> 31);
    uint8_t exponent = ((temp.int_ & 0x7F800000) >> 23) + 2; //Add that goddamn bias again.
    u.int_ = (exponent << 24) | (sign_bit << 23) | (temp.int_ & 0x7FFFFF); 
    return u;
}