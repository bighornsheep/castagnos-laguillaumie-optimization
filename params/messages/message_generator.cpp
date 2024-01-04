/**
 
 @author Parthasarathi Das
 @desc   Generates messages of a given bit length
 
 */


#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <gmp.h>

int main(int argc, char** argv)
{
    // check input(s)
    if (argc != 2) {
        std::cout << "Error: Check the number of input(s)" << std::endl;
        std::cout << "Usage: Message size in bits" << std::endl;
        exit(0);
    }
    
    
    // 
    int count = 1000; // number of messages that is to be generated
    int bits = strtol(argv[1], NULL, 10); // size of message in bits as user input
    char filename[PATH_MAX];
    size_t buffer;
    FILE *file_ptr;
    mpz_t message;
    gmp_randstate_t rands;
    
    mpz_inits (message, NULL);
    gmp_randinit_default (rands);
    
    
    
    // set output file
    snprintf(filename, PATH_MAX, "%d.txt", bits);
    file_ptr = fopen(filename, "w");
    
    
    // generate messages
    for (int i = 0; i < count; i++) {
        mpz_urandomb(message, rands, bits);
        buffer = mpz_out_str(file_ptr, 16, message); // 16 = hex base
        fprintf(file_ptr, "\n");
    }
    
    
    // close output file
    fclose(file_ptr);
    
    // clear local variables
    mpz_clears(message, NULL);
    gmp_randclear(rands);
    
    return 0;
}
