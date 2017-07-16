/* Litte program which shows the use of ARM NEON functions on 8-Bit integers
 *
 * Author: Konstantin Luebeck (University of Tuebingen, Chair for Embedded Systems)
 */

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
    uint8_t result_x2[32];

    uint16_t data_uint16[8];
    uint16_t result_uint16[8];

    // vectorized data
    uint8x16_t vector_data0, vector_data1, vector_data2;
    uint16x8_t vector_data_uint16x8, vector_result_uint16x8;
    uint8x16x2_t vector_result_uint8x16x2;


    // ------------------------------------------------------------------------
    printf("\n");
    printf("Addition 8-Bit Unsinged Integer (x16):\n");

    // load input data
    // v: vector
    // ld1: load one array
    // q: 128-bit registers
    // u8: 8-bit integers
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

    // v: vector
    // add: addition
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data0 = vector_data0 + vector_data1
    vector_data0 = vaddq_u8(vector_data1, vector_data0);

    // v: vector
    // st1: store
    // q: 128-bit registers
    // u8: 8-bit integer
    // result = vector_data0
    vst1q_u8(result, vector_data0);

    for(i = 0; i < 16; i++) {
        printf("%u + %u = %u\n", data0[i], data1[i], result[i]);
    }


    // ------------------------------------------------------------------------
    printf("\n");
    printf("Addition with Halving (truncation) 8-Bit Unsinged Integer (x16):\n");

    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = i;
        data1[i] = i+16;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);
    
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


    // ------------------------------------------------------------------------
    printf("\n");
    printf("Addition with Halving (rounding) 8-Bit Unsinged Integer (x16):\n");
     
    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = i;
        data1[i] = i+16;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);
    
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


    // ------------------------------------------------------------------------
    printf("\n");
    printf("Addition with Saturation 8-Bit Unsinged Integer (x16):\n");

    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = i;
        data1[i] = i+16;
    }
    data0[15] = 250;
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

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

   
    // ------------------------------------------------------------------------
    printf("\n");
    printf("Multiplication 8-Bit Unsinged Integer (x16):\n");

    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = (i % 3) + 2;
        data1[i] = i+16;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

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


    // ------------------------------------------------------------------------
    printf("\n");
    printf("Multiply-Accumulate 8-Bit Unsinged Integer (x16):\n");

    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = (i % 3) + 2;
        data1[i] = i+16;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);
    vector_data2 = vld1q_u8(data2);

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

    
    // ------------------------------------------------------------------------
    printf("\n");
    printf("Multiply-Subtract 8-Bit Unsinged Integer (x16):\n");

    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = (i % 2) + 1;
        data1[i] = (i % 3) + 2;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);
    vector_data2 = vld1q_u8(data2);

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


    // ------------------------------------------------------------------------
    printf("\n");
    printf("Subtract 8-Bit Unsinged Integer (x16):\n");
    
    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = i+1;
        data1[i] = i*2+1;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

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


    // ------------------------------------------------------------------------
    printf("\n");
    printf("Subtract with Halving 8-Bit Unsinged Integer (x16):\n");

    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = i+1;
        data1[i] = i*4+1;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);
    
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


    // ------------------------------------------------------------------------
    printf("\n");
    printf("Subtract with Saturation 8-Bit Unsinged Integer (x16):\n");
   
    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = i+3 % 5;
        data1[i] = i*2+1;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

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


    // ------------------------------------------------------------------------
    printf("\n");
    printf("Compare equal 8-Bit Unsinged Integer (x16):\n");
   
    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = i+3 % 5;
        data1[i] = i*2+1;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

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


    // ------------------------------------------------------------------------
    printf("\n");
    printf("Compare greater-than or equal 8-Bit Unsinged Integer (x16):\n");

    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = i+3 % 5;
        data1[i] = i*2+1;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);
    
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

    
    // ------------------------------------------------------------------------
    printf("\n");
    printf("Compare less-than or equal 8-Bit Unsinged Integer (x16):\n");
   
    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = i+3 % 5;
        data1[i] = i*2+1;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

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


    // ------------------------------------------------------------------------
    printf("\n");
    printf("Compare greater-than 8-Bit Unsinged Integer (x16):\n");
    
    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = i+3 % 5;
        data1[i] = i*2+1;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

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


    // ------------------------------------------------------------------------
    printf("\n");
    printf("Compare less-than 8-Bit Unsinged Integer (x16):\n");

    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = i+3 % 5;
        data1[i] = i*2+1;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

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


    // ------------------------------------------------------------------------
    printf("\n");
    printf("Test Bits 8-Bit Unsinged Integer (x16):\n");
   
    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = i+3 % 5;
        data1[i] = i*2+1;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

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


    // ------------------------------------------------------------------------
    printf("\n");
    printf("Absolute Difference 8-Bit Unsinged Integer (x16):\n");

    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = i+3 % 5;
        data1[i] = i*2+1;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);
    
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

    
    // ------------------------------------------------------------------------
    printf("\n");
    printf("Maximum 8-Bit Unsinged Integer (x16):\n");
    
    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = i+3 % 5;
        data1[i] = i*2+1;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

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


    // ------------------------------------------------------------------------
    printf("\n");
    printf("Pairwise Addition 8-Bit Unsinged Integer (x16):\n");

    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = i;
    }
    vector_data0 = vld1q_u8(data0);

    // v: vector
    // paddl: pairwise addition
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data0 = vector_data0[i*2] + vector_data0[i*2+1]
    vector_result_uint16x8 = vpaddlq_u8(vector_data0);

    // see above (addition)
    vst1q_u16(result_uint16, vector_result_uint16x8);

    for(i = 0; i < 8; i++) {
        printf("%u + %u = %u\n", data0[i*2], data0[i*2+1], result_uint16[i]);
    }


    // ------------------------------------------------------------------------
    printf("\n");
    printf("Pairwise Addition with Accumulate 8-Bit Unsinged Integer (x16):\n");

    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = i;
    }
    vector_data0 = vld1q_u8(data0);

    for(i = 0; i < 8; i++) {
        data_uint16[i] = i;
    }
    vector_data_uint16x8 = vld1q_u16(data_uint16);

    // v: vector
    // padal: pairwise addition with accumulate
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data0 = vector_data0[i*2] + vector_data0[i*2+1] + vector_data_uint16x8[i]
    vector_result_uint16x8 = vpadalq_u8(vector_data_uint16x8, vector_data0);

    // see above (addition)
    vst1q_u16(result_uint16, vector_result_uint16x8);

    for(i = 0; i < 8; i++) {
        printf("%u + %u + %u = %u\n", data0[i*2], data0[i*2+1], data_uint16[i], result_uint16[i]);
    }


    // ------------------------------------------------------------------------
    printf("\n");
    printf("Shift Left 8-Bit Unsinged Integer (x16):\n");

    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = i;
        data1[i] = i % 4;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

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

    
    // ------------------------------------------------------------------------
    printf("\n");
    printf("Shift Left with Rounding 8-Bit Unsinged Integer (x16):\n");

    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = i;
        data1[i] = i % 4;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

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


    // ------------------------------------------------------------------------
    printf("\n");
    printf("Shift Left with Saturation 8-Bit Unsinged Integer (x16):\n");

    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = i;
        data1[i] = i % 6;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

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


    // ------------------------------------------------------------------------
    printf("\n");
    printf("Shift Left with Saturation and Rounding 8-Bit Unsinged Integer (x16):\n");

    for(i = 0; i < 16; i++) {
        data0[i] = i;
        data1[i] = i % 6;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

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


    // ------------------------------------------------------------------------
    printf("\n");
    printf("Bitwise Not 8-Bit Unsinged Integer (x16):\n");

    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = i;
    }
    vector_data0 = vld1q_u8(data0);

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
    

    // ------------------------------------------------------------------------
    printf("\n");
    printf("Count leading zeros 8-Bit Unsinged Integer (x16):\n");

    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = i;
    }
    vector_data0 = vld1q_u8(data0);

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

    
    // ------------------------------------------------------------------------
    printf("\n");
    printf("Count set bits 8-Bit Unsinged Integer (x16):\n");

    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = i;
    }
    vector_data0 = vld1q_u8(data0);

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


    // ------------------------------------------------------------------------
    printf("\n");
    printf("Vector Extract 8-Bit Unsinged Integer (x16):\n");

    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = i;
        data1[i] = i+16;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

    // v: vector
    // ext: vector extract
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data2 = takes the 7 first elements from vector_data0 and puts it
    // at the end and fills the rest with elements from vector_data1 from
    // postion 8 on an puts it in the front
    vector_data2 = vextq_u8(vector_data1, vector_data0, 7);

    // see above (addition)
    vst1q_u8(result, vector_data2);

    printf("data0:  ");
    for(i = 0; i < 16; i++) {
        printf("%3u ", data0[i]);
    }
    printf("\n");

    printf("data1:  ");
    for(i = 0; i < 16; i++) {
        printf("%3u ", data1[i]);
    }
    printf("\n");

    printf("result: ");
    for(i = 0; i < 16; i++) {
        printf("%3u ", result[i]);
    }
    printf("\n");


    // ------------------------------------------------------------------------
    printf("\n");
    printf("Reverse 64 8-Bit Unsinged Integer (x16):\n");

    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = i;
    }
    vector_data0 = vld1q_u8(data0);

    // v: vector
    // rev 64: reverses the elements within an 64-bit block
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data1 = reverses the elements within an 64-bit block in vector_data0
    vector_data1 = vrev64q_u8(vector_data0);

    // see above (addition)
    vst1q_u8(result, vector_data1);

    printf("data0:  ");
    for(i = 0; i < 16; i++) {
        printf("%3u ", data0[i]);
    }
    printf("\n");

    printf("result: ");
    for(i = 0; i < 16; i++) {
        printf("%3u ", result[i]);
    }
    printf("\n");


    // ------------------------------------------------------------------------
    printf("\n");
    printf("Reverse 32 8-Bit Unsinged Integer (x16):\n");

    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = i;
    }
    vector_data0 = vld1q_u8(data0);

    // v: vector
    // rev32: reverse 32
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data1 = reverses the elements within an 32-bit block in vector_data0
    vector_data1 = vrev32q_u8(vector_data0);

    // see above (addition)
    vst1q_u8(result, vector_data1);

    printf("data0:  ");
    for(i = 0; i < 16; i++) {
        printf("%3u ", data0[i]);
    }
    printf("\n");

    printf("result: ");
    for(i = 0; i < 16; i++) {
        printf("%3u ", result[i]);
    }
    printf("\n");

    
    // ------------------------------------------------------------------------
    printf("\n");
    printf("Reverse 16 8-Bit Unsinged Integer (x16):\n");

    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = i;
    }
    vector_data0 = vld1q_u8(data0);

    // v: vector
    // rev32: reverse 16
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data1 = reverses the elements within an 16-bit block in vector_data0
    vector_data1 = vrev16q_u8(vector_data0);

    // see above (addition)
    vst1q_u8(result, vector_data1);

    printf("data0:  ");
    for(i = 0; i < 16; i++) {
        printf("%3u ", data0[i]);
    }
    printf("\n");

    printf("result: ");
    for(i = 0; i < 16; i++) {
        printf("%3u ", result[i]);
    }
    printf("\n");


    // ------------------------------------------------------------------------
    printf("\n");
    printf("Bit select 8-Bit Unsinged Integer (x16):\n");

    // load input data
    for(i = 2; i < 16; i++) {
        data0[i] = i;
        data1[i] = i+8;
        data2[i] = i % 2;
    }

    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);
    vector_data2 = vld1q_u8(data2);

    // v: vector
    // bsl: bit select
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data2 = each bit is selected either from vector_data0 or
    // vector_data1 if the vector_data2 bit is 0 or 1
    // 0: select bit from vector_data0
    // 1: select bit from vector_data1
    vector_data2 = vbslq_u8(vector_data2, vector_data1, vector_data0);

    // see above (addition)
    vst1q_u8(result, vector_data2);

    printf("data0:  ");
    for(i = 0; i < 16; i++) {
        printf("0x%02x ", data0[i]);
    }
    printf("\n");

    printf("data1:  ");
    for(i = 0; i < 16; i++) {
        printf("0x%02x ", data1[i]);
    }
    printf("\n");

    printf("data2:  ");
    for(i = 0; i < 16; i++) {
        printf("0x%02x ", data2[i]);
    }
    printf("\n");

    printf("result: ");
    for(i = 0; i < 16; i++) {
        printf("0x%02x ", result[i]);
    }
    printf("\n");

    
    // ------------------------------------------------------------------------
    printf("\n");
    printf("Transpose 8-Bit Unsinged Integer (x16):\n");

    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = i;
        data1[i] = i+16;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

    // v: vector
    // trn: transpose
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // the data in vector_data1 and vector_data0 are interpreted as elements of
    // a 2x2 matrix which will be transposed and stored in
    // vector_result_uint8x16x2 which is a 8x16x2 vector
    // http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0489e/CIHDJAEA.html
    vector_result_uint8x16x2 = vtrnq_u8(vector_data1, vector_data0);

    // see above (addition)
    vst2q_u8(result_x2, vector_result_uint8x16x2);
    
    printf("data1 data0\n");
    for(i = 0; i < 8; i++) {
        printf("%3d %3d   ", data1[i*2], data0[i*2]);
    }
    printf("\n");
    for(i = 0; i < 8; i++) {
        printf("%3d %3d   ", data1[i*2+1], data0[i*2+1]);
    }
    printf("\n");

    printf("result\n");
    for(i = 0; i < 8; i++) {
        printf("%3d %3d   ", result_x2[i*4], result_x2[i*4+1]);
    }
    printf("\n");
    for(i = 0; i < 8; i++) {
        printf("%3d %3d   ", result_x2[i*4+2], result_x2[i*4+3]);
    }
    printf("\n");


    for(i = 0; i < 16; i++) {
        data0[i] = i;
        data1[i] = i+16;
    }


    // ------------------------------------------------------------------------
    printf("\n");
    printf("Zip 8-Bit Unsinged Integer (x16):\n");

    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = i;
        data1[i] = i+16;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

    // v: vector
    // zip: zip
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // interleaves the elements of vector_data0 and vector_data1 and stores it
    // in vector_result_uint8x16x2 which is a 8x16x2 vector
    // http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0489e/CIHDJAEA.html
    vector_result_uint8x16x2 = vzipq_u8(vector_data0, vector_data1);

    // see above (addition)
    vst2q_u8(result_x2, vector_result_uint8x16x2);
 
    printf("data0:  ");
    for(i = 0; i < 16; i++) {
        printf("%3d ", data0[i]);
    }
    printf("\n");

    printf("data1:  ");
    for(i = 0; i < 16; i++) {
        printf("%3d ", data1[i]);
    }
    printf("\n");

    printf("result: ");
    for(i = 0; i < 16; i++) {
        printf("%3d ", result_x2[i]);
    }
    printf("\n");

    printf("        ");
    for(i = 16; i < 32; i++) {
        printf("%3d ", result_x2[i]);
    }
    printf("\n");
    
    
    // ------------------------------------------------------------------------
    printf("\n");
    printf("Unzip 8-Bit Unsinged Integer (x16):\n");

    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = i;
        data1[i] = i+16;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

    // v: vector
    // uzp: unzip
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // deinterleaves the elements of vector_data0 and vector_data1 and stores it
    // in vector_result_uint8x16x2 which is a 8x16x2 vector (seems not to work)
    // http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0489e/CIHDJAEA.html
    vector_result_uint8x16x2 = vuzpq_u8(vector_data0, vector_data1);

    // see above (addition)
    vst2q_u8(result_x2, vector_result_uint8x16x2);
 
    printf("data0:  ");
    for(i = 0; i < 16; i++) {
        printf("%3d ", data0[i]);
    }
    printf("\n");

    printf("data1:  ");
    for(i = 0; i < 16; i++) {
        printf("%3d ", data1[i]);
    }
    printf("\n");

    printf("result: ");
    for(i = 0; i < 16; i++) {
        printf("%3d ", result_x2[i]);
    }
    printf("\n");

    printf("        ");
    for(i = 16; i < 32; i++) {
        printf("%3d ", result_x2[i]);
    }
    printf("\n");


    // ------------------------------------------------------------------------
    printf("\n");
    printf("Logical AND 8-Bit Unsinged Integer (x16):\n");

    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = i;
        data1[i] = i+16;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

    // v: vector
    // and: and
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data0 = vector_data0 & vector_data1
    vector_data0 = vandq_u8(vector_data1, vector_data0);

    // see above (addition)
    vst1q_u8(result, vector_data0);

    for(i = 0; i < 16; i++) {
        printf("0x%02x & 0x%02x = 0x%02x\n", data0[i], data1[i], result[i]);
    }

    
    // ------------------------------------------------------------------------
    printf("\n");
    printf("Logical OR 8-Bit Unsinged Integer (x16):\n");

    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = i;
        data1[i] = i+16;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

    // v: vector
    // orr: or
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data0 = vector_data0 | vector_data1
    vector_data0 = vorrq_u8(vector_data1, vector_data0);

    // see above (addition)
    vst1q_u8(result, vector_data0);

    for(i = 0; i < 16; i++) {
        printf("0x%02x | 0x%02x = 0x%02x\n", data0[i], data1[i], result[i]);
    }


    // ------------------------------------------------------------------------
    printf("\n");
    printf("Logical XOR 8-Bit Unsinged Integer (x16):\n");

    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = i;
        data1[i] = i+16;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

    // v: vector
    // eor: xor
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data0 = vector_data0 ^ vector_data1
    vector_data0 = veorq_u8(vector_data1, vector_data0);

    // see above (addition)
    vst1q_u8(result, vector_data0);

    for(i = 0; i < 16; i++) {
        printf("0x%02x ^ 0x%02x = 0x%02x\n", data0[i], data1[i], result[i]);
    }

    
    // ------------------------------------------------------------------------
    printf("\n");
    printf("Logical AND-NOT (bit clear) 8-Bit Unsinged Integer (x16):\n");

    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = i;
        data1[i] = i+16;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

    // v: vector
    // bic: and-not (bit clear)
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data0 = ~vector_data0 & vector_data1
    vector_data0 = vbicq_u8(vector_data1, vector_data0);

    // see above (addition)
    vst1q_u8(result, vector_data0);

    for(i = 0; i < 16; i++) {
        printf("~0x%02x & 0x%02x = 0x%02x\n", data0[i], data1[i], result[i]);
    }


    // ------------------------------------------------------------------------
    printf("\n");
    printf("Logical OR-NOT 8-Bit Unsinged Integer (x16):\n");

    // load input data
    for(i = 0; i < 16; i++) {
        data0[i] = i;
        data1[i] = i+16;
    }
    vector_data0 = vld1q_u8(data0);
    vector_data1 = vld1q_u8(data1);

    // v: vector // orn: or-not
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer 
    // vector_data0 = ~vector_data0 | vector_data1
    vector_data0 = vornq_u8(vector_data1, vector_data0);

    // see above (addition)
    vst1q_u8(result, vector_data0);

    for(i = 0; i < 16; i++) {
        printf("~0x%02x | 0x%02x = 0x%02x\n", data0[i], data1[i], result[i]);
    }


    // ------------------------------------------------------------------------
    printf("\n");
    printf("Cast 32-Bit Unsigned Integer (x4) to 8-Bit Unsinged Integer (x16):\n");

    uint32_t data_uint32[] = {1,2,3,4};
    uint32x4_t vector_data_uint32x4;

    vector_data_uint32x4 = vld1q_u32(data_uint32);

    // v: vector
    // reinterpret: cast
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer
    // u32: 32-bit unsigned integer
    vector_data0 = vreinterpretq_u8_u32(vector_data_uint32x4);

    // see above (addition)
    vst1q_u8(result, vector_data0);

    printf("data uint32: ");
    for(i = 0; i < 4; i++) {
        printf("%3d ", data_uint32[i]);
        printf("    ");
        printf("    ");
        printf("    ");
    }
    printf("\n");
    printf("result:      ");
    for(i = 0; i < 16; i++) {
        printf("%3d ", result[i]);
    }
    printf("\n");
    

    // ------------------------------------------------------------------------
    printf("\n");
    printf("Cast 16-Bit Unsigned Integer (x8) to 8-Bit Unsinged Integer (x16):\n");

    for(i = 0; i < 8; i++) {
        data_uint16[i] = i+1;
    }

    vector_data_uint16x8 = vld1q_u16(data_uint16);

    // v: vector
    // reinterpret: cast
    // q: 128-bit registers (8x16 = 128)
    // u8: 8-bit unsigned integer
    // u32: 32-bit unsigned integer
    vector_data0 = vreinterpretq_u8_u16(vector_data_uint16x8);

    // see above (addition)
    vst1q_u8(result, vector_data0);

    printf("data uint16: ");
    for(i = 0; i < 8; i++) {
        printf("%3d ", data_uint16[i]);
        printf("    ");
    }
    printf("\n");
    printf("result:      ");
    for(i = 0; i < 16; i++) {
        printf("%3d ", result[i]);
    }
    printf("\n");

    return 0;
}
