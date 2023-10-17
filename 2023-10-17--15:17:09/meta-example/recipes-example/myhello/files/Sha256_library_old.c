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

    while(sha256_check_busy()){		//polling sulla disponibilità dell'hardware
        usleep(100);                    //if hardware is busy, this process sleep for 100 milliseconds, then it tries again to see aviability
	printf("Waiting for check busy\n");
    }
    return_value=sha256_request(input,n);	//input request of executing sha256 (it passes the input)

    usleep(200);				//wait for sha256's output calcolation
    if(return_value==0) {
        sha256_get_output(output);		//gets of sha256's output
    }
    return return_value;
}


int sha256_inizialize(){
    printf("Inizializzazione sha256\n");
    return 0;
}


int sha256_request(const char* input, int n){
    FILE* sha256_input_file;
    FILE* sha256_cmd_file;
    //char command_sha256[4]="pwd\n";
//    char prefix_command[55]="cd /sys/devices/platform/b040000.virt-sha-nodename;echo ";
//    char postfix_command[30]=" > input; echo 1 > cmd\n";	
//    char command_sha256[200]="";

    if(n>100){
        printf("Errore, driver memory dimension of input must be at maximum 100 character. Abort!\n");
        return (-2);

    }

    sha256_input_file=fopen("/sys/devices/platform/b040000.virt-sha-nodename/input", "w");
    if (sha256_input_file==NULL){
        return (-1);
    }

    fprintf(sha256_input_file,"%s",input);
    fclose(sha256_input_file);


    sha256_cmd_file=fopen("/sys/devices/platform/b040000.virt-sha-nodename/cmd", "w");
    if (sha256_cmd_file==NULL){
        return (-1);
    }

    fprintf(sha256_cmd_file,"%d",1);
    fclose(sha256_cmd_file);


    return 0;
}

int sha256_get_output(char* output){
    char output_sha256[265];
    FILE* sha256_output_file;

    sha256_output_file=fopen("/sys/devices/platform/b040000.virt-sha-nodename/output", "r");
    if (sha256_output_file==NULL){
        return (-1);
    }
    fgets(output_sha256,65,sha256_output_file);
    fclose(sha256_output_file);

    //output_sha256[64]='\0';
//    printf("Ricevuto output sha256:\n %s\n",output_sha256);

    strcpy(output,output_sha256);
    return (1);

}

int sha256_check_busy(){
    //funzione per andare a leggere il flag se il dispositivo è occupato
    FILE* busy_attribute;
    int busy_read;
    busy_attribute=fopen("/sys/devices/platform/b040000.virt-sha-nodename/busy","r");
    if (busy_attribute==NULL){
	printf("Non apro attributo\n");
        return (-1);
    }
    busy_read=fgetc(busy_attribute);
    if(busy_read==-1){
	printf("Non leggo\n");
	return -1;
    }else{
//	printf("Busy_read 0=%d\n",busy_read);
	busy_read=busy_read-'0';
    }
    fclose(busy_attribute);
//    printf("Busy_read=%d\n",busy_read);
    return busy_read;
}
