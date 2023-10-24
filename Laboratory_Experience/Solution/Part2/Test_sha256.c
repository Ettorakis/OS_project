/*
 * Simulated Device Driver © 2023 by Andrea Bonino, Gabriele Fasolis, Mattia
 * Mattiauda, Ettore Mondino, Federico Tartaglia is licensed under Attribution-
 * NonCommercial 4.0 International. To view a copy of this license, visit 
 * http://creativecommons.org/licenses/by-nc/4.0/
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./Sha256_library.h"

int main(){
char input[10]="mattia";
char output[65]="";
int exit_value;

exit_value= sha256_algorithm(input, strlen(input), output);

printf("input:%s\n", input);
printf("output:%s\n", output);
printf("exitcode:%d\n",exit_value);


return 0;

}
