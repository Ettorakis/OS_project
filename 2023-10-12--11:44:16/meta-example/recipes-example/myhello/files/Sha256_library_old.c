//
// Created by andre on 03/10/2023.
//

#include "./Sha256_library.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//aggiungere bit di controllo sulla disponibilità della sha256


int sha256_algorithm(char* input,int n, char* output){
    int return_value;
    return_value=sha256_inizialize();
    while(!sha256_check_avaiability()){
        usleep(100);                    //attesa di 100 millisecondi in attesa della liberazione del hardware
    }
    if(return_value==0){
        return_value=sha256_request(input,n);
    }
    usleep(200);
    if(return_value==0) {
        sha256_get_output(output);
    }
    return return_value;
}
int sha256_inizialize(){
    printf("Inizializzazione sha256\n");
    return 0;
}       //????


int sha256_request(const char* input, int n){
    FILE* console_pointer;
	//char command_sha256[4]="ls\n";
    char prefix_command[55]="cd /sys/devices/platform/b040000.virt_shame;echo ";
    char postfix_command[30]=" > input; echo 1 > cmd\n";
    char command_sha256[100]="";
	FILE* ret_fopen;
	char str_read[65]="";
    if(n>10){
        printf("Errore, driver memory dimension of input must be at maximum 100 character. Abort!\n");
        return (-2);

    }
	
    //costruzione comando (append echo+input)
	printf("1\n");
	strcat(command_sha256,prefix_command);
	strcat(command_sha256,input);
	strcat(command_sha256,postfix_command);
   
    //	command_sha256[99]='\0';
	
//	printf("stringa Comando: %s\n",command_sha256);
//	printf("2\n");   
	console_pointer=popen(command_sha256,"w");
    if (console_pointer==NULL){
        return (-1);
    }
    printf("Input inviato al driver!\n");
    pclose(console_pointer);
//    printf("After pclose in request\n");
	ret_fopen=fopen("/sys/devices/platform/b040000.virt_shame/output", "r");
	fgets(str_read,65,ret_fopen);
	printf("Dal file output ho letto: %s\n",str_read);
  return 0;
}

int sha256_get_output(char* output){
    char output_sha256[265];
    FILE* console_pointer;
	
    console_pointer=popen("cd /sys/devices/platform/b040000.virt_shame; cat output\n","r");
    if (console_pointer==NULL){
        return (-1);
    }
	printf("After popen in get_output\n");
    fgets(output_sha256, sizeof(output_sha256), console_pointer);
    output_sha256[64]='\0';
    printf("Ricevuto output sha256:\n %s\n",output_sha256);
    pclose(console_pointer);

    strcpy(output,output_sha256);
    return (1);

}

int sha256_check_avaiability(){
    //funzione per andare a leggere il flag se il dispositivo è occupato
    return 1;

}
