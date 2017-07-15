#include <stdio.h>
#include "arm_neon.h"

int main() {

    printf("ARM NEON Examples\n");

    int i;

    // data
    uint8_t data0[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    uint8_t data1[] = {16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};
    uint8_t data2[] = {32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47};
    uint8_t result[16];

    uint16_t data_uint16[8];
    uint16_t result_uint16[8];

    // vectorized data
    uint8x16_t vector_data0, vector_data1, vector_data2;
    uint16x8_t vector_data_uint16, vector_result_uint16;

    // v: vector
    // ld1: load one array
    // q: 128-bit registers
    // u8: 8-bit integers
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);
    vector_data2 = vld1q_u8(data2);

    printf("Addition 8-Bit Unsinged Integer (x16):\n");

    // v: vector
    // add : addition
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data0 = vector_data0 + vector_data1
    vector_data0 = vaddq_u8(vector_data1, vector_data0);

    // v: vector
    // add: store
    // q: 128-bit registers
    // u8: 8-bit integer
    // result = vector_data0
    vst1q_u8(result, vector_data0);

    for(i = 0; i < 16; i++) {
        printf("%u + %u = %u\n", data0[i], data1[i], result[i]);
    }


    vector_data0 = vld1q_u8(data0);

    printf("Addition with Halving (truncation) 8-Bit Unsinged Integer (x16):\n");
     
    // v: vector
    // h: halving (>> 1)
    // add : addition
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data0 = (vector_data0 + vector_data1) >> 1
    vector_data0 = vhaddq_u8(vector_data1, vector_data0);

    // see above (addition)
    vst1q_u8(result, vector_data0);

    for(i = 0; i < 16; i++) {
        printf("(%u + %u) >> 1 = %u\n", data0[i], data1[i], result[i]);
    }


    vector_data0 = vld1q_u8(data0);

    printf("Addition with Halving (rounding) 8-Bit Unsinged Integer (x16):\n");
     
    // v: vector
    // r: round
    // h: halving (/2)
    // add : addition
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data0 = (vector_data0 + vector_data1)/2
    vector_data0 = vrhaddq_u8(vector_data1, vector_data0);

    // see above (addition)
    vst1q_u8(result, vector_data0);

    for(i = 0; i < 16; i++) {
        printf("(%u + %u)/2 = %u\n", data0[i], data1[i], result[i]);
    }


    data0[15] = 250;
    vector_data0 = vld1q_u8(data0);

    printf("Addition with Saturation 8-Bit Unsinged Integer (x16):\n");
     
    // v: vector
    // q: saturation
    // add : addition
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data0 = max(vector_data0 + vector_data1,UINT8_MAX)
    vector_data0 = vqaddq_u8(vector_data1, vector_data0);

    // see above (addition)
    vst1q_u8(result, vector_data0);

    for(i = 0; i < 16; i++) {
        printf("min(%u + %u, UINT8_MAX) = %u\n", data0[i], data1[i], result[i]);
    }

   
    for(i = 0; i < 16; i++) {
        data0[i] = (i % 3) + 2;
    }
    vector_data0 = vld1q_u8(data0);

    printf("Multiplication 8-Bit Unsinged Integer (x16):\n");
     
    // v: vector
    // mul : multiplication
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data0 = vector_data0 * vector_data1
    vector_data0 = vmulq_u8(vector_data1, vector_data0);

    // see above (addition)
    vst1q_u8(result, vector_data0);

    for(i = 0; i < 16; i++) {
        printf("%u * %u = %u\n", data0[i], data1[i], result[i]);
    }


    for(i = 0; i < 16; i++) {
        data0[i] = (i % 3) + 2;
    }
    vector_data0 = vld1q_u8(data0);

    printf("Multiply-Accumulate 8-Bit Unsinged Integer (x16):\n");
     
    // v: vector
    // mla : multiply-accumulate
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data0 = vector_data0 * vector_data1 + vector_data2
    vector_data0 = vmlaq_u8(vector_data2, vector_data1, vector_data0);

    // see above (addition)
    vst1q_u8(result, vector_data0);

    for(i = 0; i < 16; i++) {
        printf("%u * %u + %u = %u\n", data0[i], data1[i], data2[i], result[i]);
    }

    
    for(i = 0; i < 16; i++) {
        data0[i] = (i % 2) + 1;
        data1[i] = (i % 3) + 2;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

    printf("Multiply-Subtract 8-Bit Unsinged Integer (x16):\n");
     
    // v: vector
    // mls : multiply-subtract
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data0 = vector_data2 - vector_data0 * vector_data1
    vector_data0 = vmlsq_u8(vector_data2, vector_data1, vector_data0);

    // see above (addition)
    vst1q_u8(result, vector_data0);

    for(i = 0; i < 16; i++) {
        printf("%u - %u * %u = %u\n", data2[i], data1[i], data0[i], result[i]);
    }


    for(i = 0; i < 16; i++) {
        data0[i] = i+1;
        data1[i] = i*2+1;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

    printf("Subtract 8-Bit Unsinged Integer (x16):\n");
     
    // v: vector
    // sub : subtract
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data0 = vector_data1 - vector_data0
    vector_data0 = vsubq_u8(vector_data1, vector_data0);

    // see above (addition)
    vst1q_u8(result, vector_data0);

    for(i = 0; i < 16; i++) {
        printf("%u - %u = %u\n", data1[i], data0[i], result[i]);
    }


    for(i = 0; i < 16; i++) {
        data0[i] = i+1;
        data1[i] = i*4+1;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

    printf("Subtract with Halving 8-Bit Unsinged Integer (x16):\n");
     
    // v: vector
    // h: halving
    // sub : subtract
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data0 = (vector_data1 - vector_data0) >> 1
    vector_data0 = vhsubq_u8(vector_data1, vector_data0);

    // see above (addition)
    vst1q_u8(result, vector_data0);

    for(i = 0; i < 16; i++) {
        printf("(%u - %u) >> 1 = %u\n", data1[i], data0[i], result[i]);
    }


    for(i = 0; i < 16; i++) {
        data0[i] = i+3 % 5;
        data1[i] = i*2+1;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

    printf("Subtract with Saturation 8-Bit Unsinged Integer (x16):\n");
     
    // v: vector
    // q: saturation
    // sub : subtract
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data0 = (vector_data1 - vector_data0) >> 1
    vector_data0 = vqsubq_u8(vector_data1, vector_data0);

    // see above (addition)
    vst1q_u8(result, vector_data0);

    for(i = 0; i < 16; i++) {
        printf("min(%u - %u, 0) = %u\n", data1[i], data0[i], result[i]);
    }


    for(i = 0; i < 16; i++) {
        data0[i] = i+3 % 5;
        data1[i] = i*2+1;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

    printf("Compare equal 8-Bit Unsinged Integer (x16):\n");
     
    // v: vector
    // eq: equal
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data0 = vector_data1 == vector_data0
    vector_data0 = vceqq_u8(vector_data1, vector_data0);

    // see above (addition)
    vst1q_u8(result, vector_data0);

    for(i = 0; i < 16; i++) {
        printf("%u == %u = %u\n", data1[i], data0[i], result[i]);
    }


    for(i = 0; i < 16; i++) {
        data0[i] = i+3 % 5;
        data1[i] = i*2+1;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

    printf("Compare greater-than or equal 8-Bit Unsinged Integer (x16):\n");
     
    // v: vector
    // ge: greater-than or equal
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data0 = vector_data1 >= vector_data0
    vector_data0 = vcgeq_u8(vector_data1, vector_data0);

    // see above (addition)
    vst1q_u8(result, vector_data0);

    for(i = 0; i < 16; i++) {
        printf("%u >= %u = %u\n", data1[i], data0[i], result[i]);
    }

    
    for(i = 0; i < 16; i++) {
        data0[i] = i+3 % 5;
        data1[i] = i*2+1;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

    printf("Compare less-than or equal 8-Bit Unsinged Integer (x16):\n");
     
    // v: vector
    // le: less-than or equal
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data0 = vector_data1 <= vector_data0
    vector_data0 = vcleq_u8(vector_data1, vector_data0);

    // see above (addition)
    vst1q_u8(result, vector_data0);

    for(i = 0; i < 16; i++) {
        printf("%u <= %u = %u\n", data1[i], data0[i], result[i]);
    }


    for(i = 0; i < 16; i++) {
        data0[i] = i+3 % 5;
        data1[i] = i*2+1;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

    printf("Compare greater-than 8-Bit Unsinged Integer (x16):\n");
     
    // v: vector
    // gt: greater-than 
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data0 = vector_data1 > vector_data0
    vector_data0 = vcgtq_u8(vector_data1, vector_data0);

    // see above (addition)
    vst1q_u8(result, vector_data0);

    for(i = 0; i < 16; i++) {
        printf("%u > %u = %u\n", data1[i], data0[i], result[i]);
    }


    for(i = 0; i < 16; i++) {
        data0[i] = i+3 % 5;
        data1[i] = i*2+1;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

    printf("Compare less-than 8-Bit Unsinged Integer (x16):\n");
     
    // v: vector
    // gt: less-than 
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data0 = vector_data1 < vector_data0
    vector_data0 = vcltq_u8(vector_data1, vector_data0);

    // see above (addition)
    vst1q_u8(result, vector_data0);

    for(i = 0; i < 16; i++) {
        printf("%u < %u = %u\n", data1[i], data0[i], result[i]);
    }


    for(i = 0; i < 16; i++) {
        data0[i] = i+3 % 5;
        data1[i] = i*2+1;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

    printf("Test Bits 8-Bit Unsinged Integer (x16):\n");
     
    // v: vector
    // tst: test bits
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data0 = (vector_data1 & vector_data0) != 0
    vector_data0 = vtstq_u8(vector_data1, vector_data0);

    // see above (addition)
    vst1q_u8(result, vector_data0);

    for(i = 0; i < 16; i++) {
        printf("(%u & %u) != 0 = %u\n", data1[i], data0[i], result[i]);
    }


    for(i = 0; i < 16; i++) {
        data0[i] = i+3 % 5;
        data1[i] = i*2+1;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

    printf("Absolute Difference 8-Bit Unsinged Integer (x16):\n");
     
    // v: vector
    // abd: absolute difference
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data0 = abs(vector_data1 - vector_data0)
    vector_data0 = vabdq_u8(vector_data1, vector_data0);

    // see above (addition)
    vst1q_u8(result, vector_data0);

    for(i = 0; i < 16; i++) {
        printf("abs(%u - %u) = %u\n", data1[i], data0[i], result[i]);
    }


    for(i = 0; i < 16; i++) {
        data0[i] = i+3 % 5;
        data1[i] = i*2+1;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

    printf("Maximum 8-Bit Unsinged Integer (x16):\n");
     
    // v: vector
    // max: maximum
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data0 = max(vector_data1, vector_data0)
    vector_data0 = vmaxq_u8(vector_data1, vector_data0);

    // see above (addition)
    vst1q_u8(result, vector_data0);

    for(i = 0; i < 16; i++) {
        printf("max(%u, %u) = %u\n", data1[i], data0[i], result[i]);
    }


    for(i = 0; i < 16; i++) {
        data0[i] = i;
    }
    vector_data0 = vld1q_u8(data0);


    printf("Pairwise Addition 8-Bit Unsinged Integer (x16):\n");
     
    // v: vector
    // paddl: pairwise addition
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data0 = vector_data0[i*2] + vector_data0[i*2+1]
    vector_result_uint16 = vpaddlq_u8(vector_data0);

    // see above (addition)
    vst1q_u16(result_uint16, vector_result_uint16);

    for(i = 0; i < 8; i++) {
        printf("%u + %u = %u\n", data0[i*2], data0[i*2+1], result_uint16[i]);
    }


    for(i = 0; i < 16; i++) {
        data0[i] = i;
    }
    vector_data0 = vld1q_u8(data0);

    for(i = 0; i < 8; i++) {
        data_uint16[i] = i;
    }
    vector_data_uint16 = vld1q_u16(data_uint16);

    printf("Pairwise Addition with Accumulate 8-Bit Unsinged Integer (x16):\n");

    // v: vector
    // padal: pairwise addition with accumulate
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data0 = vector_data0[i*2] + vector_data0[i*2+1] + vector_data_uint16[i]
    vector_result_uint16 = vpadalq_u8(vector_data_uint16, vector_data0);

    // see above (addition)
    vst1q_u16(result_uint16, vector_result_uint16);

    for(i = 0; i < 8; i++) {
        printf("%u + %u + %u = %u\n", data0[i*2], data0[i*2+1], data_uint16[i], result_uint16[i]);
    }


    for(i = 0; i < 16; i++) {
        data0[i] = i;
        data1[i] = i % 4;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

    printf("Shift Left 8-Bit Unsinged Integer (x16):\n");

    // v: vector
    // shl: shift left 
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data0 = vector_data0 << vector_data1
    vector_data0 = vshlq_u8(vector_data0, (int8x16_t) vector_data1);

    // see above (addition)
    vst1q_u8(result, vector_data0);

    for(i = 0; i < 16; i++) {
        printf("%u << %u = %u\n", data0[i], data1[i], result[i]);
    }

    
    for(i = 0; i < 16; i++) {
        data0[i] = i;
        data1[i] = i % 4;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

    printf("Shift Left with Rounding 8-Bit Unsinged Integer (x16):\n");

    // v: vector
    // rshl: shift left with rounding
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data0 = vector_data0 << vector_data1
    vector_data0 = vrshlq_u8(vector_data0, (int8x16_t) vector_data1);

    // see above (addition)
    vst1q_u8(result, vector_data0);

    for(i = 0; i < 16; i++) {
        printf("%u << %u = %u\n", data0[i], data1[i], result[i]);
    }


    for(i = 0; i < 16; i++) {
        data0[i] = i;
        data1[i] = i % 6;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

    printf("Shift Left with Saturation 8-Bit Unsinged Integer (x16):\n");

    // v: vector
    // qshl: shift left with saturation
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data0 = max(vector_data0 << vector_data1, UINT8_MAX)
    vector_data0 = vqshlq_u8(vector_data0, (int8x16_t) vector_data1);

    // see above (addition)
    vst1q_u8(result, vector_data0);

    for(i = 0; i < 16; i++) {
        printf("max(%u << %u, UINT8_MAX) = %u\n", data0[i], data1[i], result[i]);
    }


    for(i = 0; i < 16; i++) {
        data0[i] = i;
        data1[i] = i % 6;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

    printf("Shift Left with Saturation and Rounding 8-Bit Unsinged Integer (x16):\n");

    // v: vector
    // qshl: shift left with saturation and rounding
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data0 = max(vector_data0 << vector_data1, UINT8_MAX)
    vector_data0 = vqrshlq_u8(vector_data0, (int8x16_t) vector_data1);

    // see above (addition)
    vst1q_u8(result, vector_data0);

    for(i = 0; i < 16; i++) {
        printf("max(%u << %u, UINT8_MAX) = %u\n", data0[i], data1[i], result[i]);
    }


    for(i = 0; i < 16; i++) {
        data0[i] = i;
    }
    vector_data0 = vld1q_u8(data0);

    printf("Bitwise Not 8-Bit Unsinged Integer (x16):\n");

    // v: vector
    // mvn: bitwise not
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data1 = ~vector_data0
    vector_data1 = vmvnq_u8(vector_data0);

    // see above (addition)
    vst1q_u8(result, vector_data1);

    for(i = 0; i < 16; i++) {
        printf("~%u = %u\n", data0[i], result[i]);
    }
    

    for(i = 0; i < 16; i++) {
        data0[i] = i;
    }
    vector_data0 = vld1q_u8(data0);

    printf("Count leading zeros 8-Bit Unsinged Integer (x16):\n");

    // v: vector
    // clz: count leanding zeros
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data1 = count leading zeros(vector_data0)
    vector_data1 = vclzq_u8(vector_data0);

    // see above (addition)
    vst1q_u8(result, vector_data1);

    for(i = 0; i < 16; i++) {
        printf("leading zeros of %u = %u\n", data0[i], result[i]);
    }

    
    for(i = 0; i < 16; i++) {
        data0[i] = i;
    }
    vector_data0 = vld1q_u8(data0);

    printf("Count set bits 8-Bit Unsinged Integer (x16):\n");

    // v: vector
    // cnt: count set bits
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data1 = count number of bits(vector_data0)
    vector_data1 = vcntq_u8(vector_data0);

    // see above (addition)
    vst1q_u8(result, vector_data1);

    for(i = 0; i < 16; i++) {
        printf("set bits of %u = %u\n", data0[i], result[i]);
    }


    // TODO next vextq_u8 (http://gcc.gnu.org/onlinedocs/gcc-4.8.1/gcc/ARM-NEON-Intrinsics.html)

    return 0;
}
