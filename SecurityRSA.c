#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

#define MAX_32_BIT 4294967295UL
#define MAX_64_BIT 18446744073709551615UL

bool is_prime(uint32_t n) {
    if (n <= 1) {
        return false;
    }
    if (n <= 3) {
        return true;
    }
    if (n % 2 == 0 || n % 3 == 0) {
        return false;
    }
    for (uint32_t i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}


// function to convert decimal to binary
uint64_t convert(uint64_t n) {

  // variable to store the result
  uint64_t bin = 0;

  int rem, i = 1;

  // loop to convert to binary
  while (n != 0) {
    
    // get remainder of n divided by 2
    rem = n % 2;
    
    // divide n by 2
    n /= 2;
    
    // multiply remainder by i
    // add the product to bin
    bin += rem * i;
    
    // multiply i by 10
    i *= 10;
  }

  return bin;
}


//plaintext, b,n
uint64_t mod_exp(uint64_t plaintext, uint64_t b, uint64_t n) 
{
    uint64_t result = 1;
    plaintext = plaintext% n;
    while (b > 0) {
        if (b & 1) { // Check if the least significant bit is set
            result = (result * plaintext) % n;
        }
        b >>= 1; // Right shift exponent by 1 bit
        plaintext = (plaintext * plaintext) % n;
    }
    return result;

}

// Extended Euclidean Algorithm to find gcd and coefficients x, y
uint64_t extended_gcd(uint64_t a, uint64_t b, int64_t *x, int64_t *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }

    int64_t x1, y1;
    uint64_t gcd = extended_gcd(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}

// Function to calculate the modular inverse using Extended Euclidean Algorithm
uint64_t mod_inv(uint64_t b, uint64_t m) {
    int64_t x, y;
    uint64_t phi = m;
    int64_t gcd = extended_gcd(b, m, &x, &y);

    // If gcd is not 1, modular inverse does not exist
    if (gcd != 1) {
        fprintf(stderr, "Modular inverse does not exist\n");
        return 0; // Error code
    }

    // Ensure the result is positive
    return (x % phi + phi) % phi;
}


uint64_t encrypt(uint64_t plaintext, uint64_t n, uint64_t e) {
   /* if (plaintext >= n) {
        fprintf(stderr, "Plaintext too large for key size\n");
        return -1; // Error 
    }*/
    return mod_exp(plaintext, e, n);
}

uint64_t decrypt(uint64_t ciphertext, uint64_t n, uint64_t d) {
    return mod_exp(ciphertext, d, n);
}

bool is_integer(const char *str) {
    // Check if the string is empty
    if (*str == '\0') {
        return false;
    }

    // Check if the first character is a plus (+) or minus (-) sign
    if (*str == '+' || *str == '-') {
        str++; // Move to the next character
    }

    // Check each character of the string
    while (*str) {
        // If any character is not a digit, return false
        if (*str < '0' || *str > '9') {
            return false;
        }
        str++;
    }

    // All characters are digits, so it's an integer
    return true;
}
// Function to map two-letter combinations to unique integer values
uint64_t map_to_integer(const char *text) {
    return ((uint64_t)text[0] << 8) | text[1];
}

// Function to map integer values back to their corresponding two-letter combinations
void map_to_text(uint64_t value, char *text) {
    text[0] = (value >> 8) & 0xFF;
    text[1] = value & 0xFF;
    text[2] = '\0'; // Null-terminate the string
}

int main() {
    
    uint32_t p = 1;
    uint32_t q = 1;
    uint64_t n = 1;
    uint32_t b = 1;
    uint64_t a = 1;
    const char *plaintext_text="";//= "aa";
  
   
    // p and q should be prime numbers less than 2^32
    if (!is_prime(p) || !is_prime(q)) {
        fprintf(stderr, "p and q must be prime numbers\n");
        return 1;
    }
    
    if(((uint64_t)p * q) != n){
        printf("n is incorrect\n");
        return 1;
    }
    
    // n should be less than 2^64
    if (n > MAX_64_BIT) {
        fprintf(stderr, "n exceeds 64-bit limit\n");
        return 1;
    }

    
    
    // Generate public and private keys
    // In practice, the private key should be kept secret
    uint64_t phi = ((uint64_t)p - 1) * ((uint64_t)q - 1);
     
    if((b*a)% phi !=1 ){
        printf("public or private key incorrect\n");
        return 1;
    }

  
    
    

    uint64_t plaintext ;

    if (strlen(plaintext_text) > 20) {  // Maximum 20 characters for 64-bit number
        printf("plaintext more than 64 bits\n");
        return 1;
    }

    // Check if input is an integer or a string
    if (is_integer(plaintext_text) && strlen(plaintext_text) <= 20 ) {
        // Input is an integer
        plaintext = strtoull(plaintext_text, NULL, 10);
    } else {
        // Input is a string, convert it to an integer using binary representation
        size_t len = strlen(plaintext_text);
        if (len > 8 * sizeof(uint64_t)) {
            // String length exceeds the maximum size for a 64-bit integer
            fprintf(stderr, "String length exceeds maximum size\n");
            return 1;
        }
        plaintext = 0;
        for (size_t i = 0; i < len; i++) {
            plaintext |= ((uint64_t)plaintext_text[i]) << (8 * (len - 1 - i));
        }
    }
    //printf("this is the inv : %llu",mod_inv(35,15));
    //printf("this is the square : %llu",mod_exp(17,22,21));
    
    char ciphertext_text[64];
    
    size_t plaintext_len = strlen(plaintext_text);

    // Define maximum block size based on n
    size_t max_block_size = sizeof(uint64_t);

    printf("Original: %llu\n", plaintext);

  
    FILE *file;
    char filename[] = "input.txt";

    // Open the file in write mode
    file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }


    
if(is_integer(plaintext_text)){
        printf("ciphertext = %llu", encrypt(plaintext, n,b));
        fprintf(file, "%llu\n", encrypt(plaintext, n,b));
}else{
printf("Ciphertext: ");
    for (size_t i = 0; i < plaintext_len; i += 2) {
        uint64_t plaintext_block = map_to_integer(&plaintext_text[i]);
        uint64_t ciphertext_block = encrypt(plaintext_block, n, b);
        printf("%llu ", ciphertext_block);
        char text[3];
        map_to_text(ciphertext_block, text);
        printf("%s ", text);
        fprintf(file, "%s\n", text);
    }
    printf("\n");
}




    // Close the file
    fclose(file);
    
    //uint64_t decrypted_text = decrypt(ciphertext, n, a);

   // printf("Decrypted: %llu\n", decrypted_text);
    return 0;
}
