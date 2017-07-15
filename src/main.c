#include <stdio.h>
#include "arm_neon.h"

int main() {

    int i;

    // using uint8x16 instructions
    printf("Addition 8-Bit Integer (x16):\n");

    // data
    const uint8_t data0[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    const uint8_t data1[] = {16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};
    uint8_t result[16];

    // vectorized data
    uint8x16_t vector_data0, vector_data1;

    // v: vector
    // ld1: load one array
    // q: 128-bit registers
    // u8: 8-bit integers
    vector_data0 = vld1q_u8(data0);
    /*
    vector_data1 = vld1q_u8(data1);

    // v: vector
    // add : operation addition
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    vector_data0 = vaddq_u8(vector_data0, vector_data1);

    vst1q_u8(result, vector_data0);

    for(i = 0; i < 8; i++) {
        printf("%u + %u = %u", data0[i], data1[i], result[i]);
    }
    */

    return 0;
}
