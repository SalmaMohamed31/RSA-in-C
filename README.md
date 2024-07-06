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


