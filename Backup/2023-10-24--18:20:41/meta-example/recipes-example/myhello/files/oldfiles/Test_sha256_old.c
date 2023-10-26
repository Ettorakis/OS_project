#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./Sha256_library.h"

int main(){
char input[10]="ciao\0";
char output[65]="";
int exit_value;

exit_value= sha256_algorithm(input, strlen(input), output);

printf("input:%s\n", input);
printf("output:%s\n", output);
printf("exitcode:%d\n",exit_value);


return 0;

}