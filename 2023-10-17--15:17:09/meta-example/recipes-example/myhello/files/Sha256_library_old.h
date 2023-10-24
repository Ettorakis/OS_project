/*
 * Simulated Device Driver © 2023 by Andrea Bonino, Gabriele Fasolis, Mattia
 * Mattiauda, Ettore Mondino, Federico Tartaglia is licensed under Attribution-
 * NonCommercial 4.0 International. To view a copy of this license, visit 
 * http://creativecommons.org/licenses/by-nc/4.0/
 */

// Created by andre on 03/10/2023.

#ifndef SAFEREGISTRATION_SHA256_LIBRARY_H
#define SAFEREGISTRATION_SHA256_LIBRARY_H


//funzione che comunica con il dispositivo, effettua la scrittura
int sha256_algorithm(char* input,int n, char* output);
int sha256_inizialize();        //????
int sha256_request(const char* input, int n);
int sha256_get_output(char* output);
int sha256_check_avaiability();


#endif //SAFEREGISTRATION_SHA256_LIBRARY_H
