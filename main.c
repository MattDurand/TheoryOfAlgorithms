/*
  Matthew Durand
  g00346987@gmit.ie
*/

// Library imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

// Function to rotate x left c bits
#define LEFT_ROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))


// These vars will contain the hash
uint32_t a, b, c, d;

// Adapted From: https://gist.github.com/creationix/4710780

// Method to hash string input
void md5_hash_string(uint8_t *initial_message) {
    // The amount of bit shifts for each round
    const uint32_t s[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                          5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
                          4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                          6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

// Pre-defined hash values used for transform rounds 1, 2, 3, and 4

// How to get the Constants in K[i]
//    for (i = 0; i <= 64)
//        K[i] = floor(2^32 * abs(sin(i+1)))

    const uint32_t k[64] = {
            0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
            0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
            0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
            0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
            0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
            0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
            0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
            0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
            0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
            0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
            0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
            0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
            0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
            0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
            0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
            0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

    // calculates the length of the message
    size_t initial_length = strlen((char *) initial_message);

    uint8_t *message = NULL;

    // Initializing earlier vars with hash values
    a = 0x67452301;
    b = 0xefcdab89;
    c = 0x98badcfe;
    d = 0x10325476;

    // Append single "1" bit to input message
    int new_length = ((((initial_length + 8) / 64) + 1) * 64) - 8;

    // calloc is used to allocate memory
    // Append "0" bits until the resulting length is 448, modulo 512
    message = calloc(new_length + 64, 1);

    // memcpy is a built in method that creates a copy of a memory block
    memcpy(message, initial_message, initial_length);

    // append the 1 bit to the message
    message[initial_length] = 128;

    // Append the length of the message to 512 bits by adding a representation of the original message in 64-bits
    uint32_t bit_length = 8 * initial_length;
    memcpy(message + new_length, &bit_length, 4);

    // Process Message in 16-word blocks
    // for each 512 bits
    for (int i = 0; i < new_length; i += 64) {
        // each 512 bits break it into 16, 32-bit words
        uint32_t *m = (uint32_t *) (message + i);

        // Variables for buffer
        uint32_t aa = a;
        uint32_t bb = b;
        uint32_t cc = c;
        uint32_t dd = d;

        int32_t j;
        for (j = 0; j < 64; j++) {

            uint32_t f, g;

            // Adapted from: https://www.ietf.org/rfc/rfc1321.txt
            if (j < 16) {
                f = (bb & cc) | ((~bb) & dd);
                g = j;
            } else if (j < 32) {
                f = (dd & bb) | ((~dd) & cc);
                g = (5 * j + 1) % 16;
            } else if (j < 48) {
                f = bb ^ cc ^ dd;
                g = (3 * j + 5) % 16;
            } else {
                f = cc ^ (bb | (~dd));
                g = (7 * j) % 16;
            }

            // temp to hold dd while rotation occurs
            uint32_t temp = dd;
            dd = cc;
            cc = bb;
            bb = bb + LEFT_ROTATE((aa + f + k[j] + m[g]), s[j]);
            aa = temp;
        }

        // Adding the output hash from the loop to the result
        a += aa;
        b += bb;
        c += cc;
        d += dd;

    }

}//MD5_HASH_STRING

int main(int argc, char **argv) {
    char *msg = argv[1];

    uint8_t *digest;


    printf("The Hash Output of this Input is: \n");
    digest = (uint8_t *) &a;
    printf("%2.2x%2.2x%2.2x%2.2x", digest[0], digest[1], digest[2], digest[3], a);
    digest = (uint8_t *) &b;
    printf("%2.2x%2.2x%2.2x%2.2x", digest[0], digest[1], digest[2], digest[3], b);
    digest = (uint8_t *) &c;
    printf("%2.2x%2.2x%2.2x%2.2x", digest[0], digest[1], digest[2], digest[3], c);
    digest = (uint8_t *) &d;
    printf("%2.2x%2.2x%2.2x%2.2x", digest[0], digest[1], digest[2], digest[3], d);
    printf("\n");

}
