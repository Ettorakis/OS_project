//
// Created by andre on 03/10/2023.
//

#ifndef SAFEREGISTRATION_SHA256_LIBRARY_H
#define SAFEREGISTRATION_SHA256_LIBRARY_H


//funzione che comunica con il dispositivo, effettua la scrittura
int sha256_algorithm(char* input,int n, char* output);	//gloabal function which recall sha256_check_busy, sha256_request and sha256_get_output
int sha256_inizialize();        // Function to initialize SHA-256 hardware.
int sha256_request(const char* input, int n);	// Function to elaborate the request for SHA-256 calculation.
int sha256_get_output(char* output);	// Function to retrieve the output of SHA-256 calculation.
int sha256_check_busy();	// Poll for the availability of SHA-256 hardware, explaining the busy polling loop.


#endif //SAFEREGISTRATION_SHA256_LIBRARY_H
