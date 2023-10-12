//
// Created by andre on 03/10/2023.
//

#ifndef SAFEREGISTRATION_SHA256_LIBRARY_H
#define SAFEREGISTRATION_SHA256_LIBRARY_H


//funzione che comunica con il dispositivo, effettua la scrittura
int sha256_algorithm(char* input,int n, char* output);
int sha256_inizialize();        //????
int sha256_request(const char* input, int n);
int sha256_get_output(char* output);
int sha256_check_avaiability();


#endif //SAFEREGISTRATION_SHA256_LIBRARY_H
