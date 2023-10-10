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

    while(!sha256_check_avaiability()){		//polling sulla disponibilità dell'hardware
        usleep(100);                    //if hardware is busy, this process sleep for 100 milliseconds, then it tries again to see aviability
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
    FILE* console_pointer;
    char command_sha256[4]="pwd\n";
    //char prefix_command[55]="cd /sys/devices/platform/b040000.virt_shame;echo ";
    //char postfix_command[30]=" > input; echo 1 > cmd\n";	
    //char command_sha256[200]="";

    if(n>100){
        printf("Errore, driver memory dimension of input must be at maximum 100 character. Abort!\n");
        return (-2);

    }
	
    //costruzione comando (append echo+input)
	//strcat(command_sha256,prefix_command);
	//strcat(command_sha256,input);
	//strcat(command_sha256,postfix_command);
   
	console_pointer=popen(command_sha256,"w");

    if (console_pointer==NULL){
        return (-1);
    }
    printf("Input inviato al driver!\n");
    pclose(console_pointer);
    return 0;
}

int sha256_get_output(char* output){
    char output_sha256[265];
    FILE* console_pointer;
    FILE* sha256_output_file;
	
    //console_pointer=popen("cd /sys/devices/platform/b040000.virt_shame; cat output > output_sha256.txt\n","r");
    console_pointer=popen("pwd > output_sha256.txt\n","r");
    if (console_pointer==NULL){
        return (-1);
    }
    pclose(console_pointer);
    //sha256_output_file=fopen("/sys/devices/platform/b040000.virt_shame/output_sha256.txt", "r");
    sha256_output_file=fopen("./output_sha256.txt", "r");
    if (sha256_output_file==NULL){
        return (-1);
    }
    fscanf(sha256_output_file, "%s", output_sha256);
    fclose(sha256_output_file);

    
    //console_pointer=popen("rm /sys/devices/platform/b040000.virt_shame/output_sha256.txt","r");
    console_pointer=popen("rm ./output_sha256.txt", "r");
    if (console_pointer==NULL){
        return (-1);
    }
    pclose(console_pointer);

    //output_sha256[64]='\0';
    printf("Ricevuto output sha256:\n %s\n",output_sha256);

    strcpy(output,output_sha256);
    return (1);

}

int sha256_check_avaiability(){
    //funzione per andare a leggere il flag se il dispositivo è occupato
    return 1;

}
