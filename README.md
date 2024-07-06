# RSA in C
---
Salma Mohamed

## Introduction

RSA (Rivest-Shamir-Adleman) is a public-key cryptosystem widely used for secure data transmission. It's named after its inventors: Ron Rivest, Adi Shamir, and Leonard Adleman, who introduced it in 1977. RSA is based on the practical difficulty of factoring the product of two large prime numbers, the factoring problem.
The security of RSA relies on the difficulty of factoring large composite numbers. As long as it remains computationally infeasible to factor in the product of two large primes, RSA remains secure. It's important to choose large enough primes to ensure security against brute-force attacks.

RSA is widely used in secure communication protocols like SSL (Secure Sockets Layer) and TLS (Transport Layer Security) for securing internet communications, digital signatures, and key exchange.


### Project Scope and Objectives

This project aims to implement the RSA encryption algorithm along with checking the key generation process in a programming environment. By leveraging the principles of modular arithmetic, prime number generation, and efficient exponentiation techniques, the project seeks to demonstrate the practical application of RSA encryption for securing data transmission.

Throughout this project, we will explore the intricacies of RSA encryption, including its mathematical foundations, the generation of secure key pairs, and the encryption and decryption of data using these keys. Additionally, we will investigate optimizations and best practices to enhance the efficiency and security of the RSA encryption process.
Through hands-on implementation and experimentation, this project aims to deepen our understanding of cryptographic techniques, empowering us to appreciate the significance of RSA encryption in safeguarding digital communication and data privacy.


## Algorithm

### 1.	Key Generation:
Choose two distinct prime numbers, 𝑝 and q.
Compute their product 𝑛=𝑝𝑞, which is used as the modulus for both the public and private keys.
Calculate Euler's totient function ϕ(n)=(p−1)(q−1).
Choose an integer 𝑒e such that 1<e<ϕ(n) and e is coprime with 𝜙(𝑛). This is the public exponent.
Compute the private exponent 𝑑 as the modular multiplicative inverse of 𝑒 modulo ϕ(n), i.e., d≡e−1(mod ϕ(n)).
### 2.	Encryption:
To encrypt a message 𝑀, the sender computes 𝐶≡𝑀𝑒(mod 𝑛) and sends 𝐶 to the recipient.
### 3.	Decryption:
To decrypt the ciphertext 𝐶, the recipient computes 𝑀≡𝐶𝑑(mod 𝑛).


## Implementation

![Picture1](https://github.com/SalmaMohamed31/RSA-in-C/assets/121355154/7e92ec7b-a652-4870-b70d-b0de22eea06f)

### 1.	#include <stdio.h>:
This header file provides essential input and output functions, including printf, scanf, fprintf, fscanf, etc., used for reading from and writing to the standard input and output streams.
### 2.	#include <stdint.h>:
This header file defines integer types with specified widths, ensuring portability across different platforms. It includes types like uint8_t, uint16_t, uint32_t, uint64_t, int8_t, int16_t, int32_t, and int64_t, among others.
### 3.	#include <stdbool.h>:
This header file defines the Boolean data type bool, along with the constants true and false. It's used for logical operations where boolean values are required.
### 4.	#include <stdlib.h>:
This header file provides various general-purpose functions, including memory allocation and deallocation (malloc, calloc, realloc, free), pseudo-random number generation (rand, srand), sorting and searching functions (qsort, bsearch), etc.
### 5.	#include <errno.h>:
This header file defines the errno variable and error codes for various runtime errors. It's commonly used in conjunction with functions that set errno to indicate errors, such as fopen, malloc, fread, etc.
### 6.	#include <string.h>:
This header file provides functions for string manipulation, including operations like copying strings (strcpy, strncpy), concatenating strings (strcat, strncat), comparing strings (strcmp, strncmp), searching for characters (strchr, strrchr), etc.
### 7.	#include <ctype.h>:
This header file provides functions for character classification and conversion. It includes functions like isalpha, isdigit, islower, isupper, tolower, toupper, etc., which are used for testing and transforming characters.

### Now, let's discuss the defined macros:
MAX_32_BIT: This macro defines the maximum value that can be represented by a 32-bit unsigned integer (uint32_t). Its value is set to 4294967295UL, which is 232−1232−1, the maximum value for a 32-bit unsigned integer.
MAX_64_BIT: Similarly, this macro defines the maximum value that can be represented by a 64-bit unsigned integer (uint64_t). Its value is set to 18446744073709551615UL, which is 264−1264−1, the maximum value for a 64-bit unsigned integer.


******** image 2

is_prime() function to check whether p and q prime or not.

******** image 3

mod_exp() function implements modular exponentiation using the square-and-multiply algorithm, commonly known as the square multiply algorithm, which is a fundamental operation in cryptography, especially in RSA encryption and decryption.

**** image 4

Here's how it works:

1.	It initializes the result to 1 and reduces the base (plaintext) modulo n to prevent overflow.
2.	It iterates through the bits of the exponent (b) from the most significant bit to the least significant bit.
3.	For each bit in the exponent, it squares the base and reduces it modulo n. If the current bit is 1, it multiplies the result by the updated base and reduces it modulo n.
4.	It continues this process until all bits of the exponent have been processed.
5.	Finally, it returns the computed result, which is the modular exponentiation of the base raised to the power of the exponent modulo n.

This algorithm efficiently calculates modular exponentiation with a complexity of O(log b), where b is the exponent. It is widely used in cryptographic operations due to its efficiency and simplicity.


*** image 5


Encrypt() function from its name, this function will be invoked when all prerequisites are done and its time for encryption.


**** image 6

is_integer() function examines each character in the input string to verify that it consists entirely of digits, optionally preceded by a sign character. If the string meets these criteria, the function concludes that it represents an integer and returns true; otherwise, it returns false.


*** image 7

These two functions, map_to_integer() and map_to_text(), are used for mapping two-letter combinations to unique integer values and vice versa. They facilitate the conversion between textual representations and their corresponding numerical representations.


**** image 8

The first part of the main() function we check several things:
1.	P and q are prime.
2.	P and q smaller than 32 bits.
3.	n = pq
4.	n is smaller than 64 bits


**** image 9

The second part of the main() function, calculating phi and making sure from the public key a≡b−1(mod ϕ(n)), by ba mod n =1
Checking if the plaintext greater than 20 characters (equivalent to 64 bits) and to make sure n is smaller than 64 bits then if it is a string it must be divided to blocks to make sure that the plaintext won’t exceed 64 bits.


*** image 10


Finally, the last part in the main we open a file to output the ciphertext computed.



## Conclusion

RSA encryption is a fundamental cryptographic algorithm that provides secure communication over insecure channels. By leveraging the principles of number theory and modular arithmetic, RSA encryption ensures confidentiality and integrity in data transmission. This documentation serves as a comprehensive guide to understanding and implementing RSA encryption in the C programming language.


## Refrences
-	https://toc.cryptobook.us/
-	https://pd.daffodilvarsity.edu.bd/course/material/book-430/pdf_content
-	https://link.springer.com/book/10.1007/978-3-642-04101-3
