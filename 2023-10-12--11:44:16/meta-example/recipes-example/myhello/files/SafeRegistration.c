#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define path_user_file  "./user.txt"
#define path_crypted_credential_file "./crypted_credential.txt"
#define path_crypted_phone_number_file "./crypted_phone.txt"
#define path_tmp_file "./tmp_file.txt"
#include "Sha256_library.h"

int input_funzionality(char* returned_char){
    char user_input[5];
    char CharInput;

    scanf("%s", user_input);
    CharInput=user_input[0];
    if ((int) CharInput > 96) {
        CharInput = (char) (CharInput - 32);
    }
    if (CharInput == 'L' || CharInput == 'R' || CharInput == 'E' || CharInput == 'F') {
        *returned_char=CharInput;
        return 1;
    }
    else return 0;
}

int check_Username(FILE* user_file,const char* Username, int* entry_number){
    char read_line[20];

    *entry_number=0;
    while (!feof(user_file)) {
        fscanf(user_file,"%s",read_line);
        *entry_number = *entry_number + 1;
        if (strcmp(read_line, Username) == 0) {
            return 1;
        }
    }
    return 0;
}

int check_sha256( FILE* sha_file,const char* string,const int entry_number) {
    int counter=0;
    char read_line[65];
    while (!feof(sha_file)) {
        counter += 1;
        fscanf(sha_file,"%s",read_line);
        if (counter == entry_number) {
            if (strcmp(string, read_line) == 0) return 1;
            else return 0;
        }
    }
    return 0;
}

int sha256_input1_input2(char* input1, char* input2, char* output){
    char input_sha256[50];
    //costruzione sha256 input
    input_sha256[0]='\0';
    strcat(input_sha256,input1);
    strcat(input_sha256,input2);

    //esecuzione sha256
    if(sha256_algorithm(input_sha256,(int)strlen(input_sha256),output)!=0){
        printf("Error while using sha256 algorithm with user and password\n");
        return (-2);
    }
    return (0);
}


int main() {
    int valid, user_found, valid_credential, valid_phone_number;
    char CharInput = ' ';
    int commandExit = 0;
    FILE *user_file;
    FILE *credential_file;
    FILE *phone_file;
    FILE *tmp_file;
    char Username[20];
    char Phone_number[20];
    char Password[20];
    int entry_number = 0, counter = 0;
    char output_sha256[65];
    char tmp_credential[65];
    char comando[35];

    while (!commandExit) {
        printf("Welcome to SafeRegistration.c\n"
               "Enter L to login in \n"
               "Enter R to register\n"
               "Enter F to recover your password\n"
               "Enter E to exit\n\n"
        );
        valid=0;
        while (!valid) {
            printf("Input:");
            valid=input_funzionality(&CharInput);
        }
        switch (CharInput) {
            case 'L':
                user_file = fopen(path_user_file, "r");
                if (user_file == NULL) {
                    printf("Errore: file utenti mancante\n");
                    return (-1);
                }
                printf("Username:\n");
                scanf("%s", Username);

                user_found=check_Username(user_file, Username, &entry_number);

                if (user_found) {
                    credential_file = fopen(path_crypted_credential_file, "r");
                    if (credential_file == NULL) {
                        printf("Errore: file credenziali mancante\n");
                        return (-1);
                    }

                    printf("Password:\n");
                    scanf("%s", Password);

                    if(sha256_input1_input2(Username,Password,output_sha256)!=0){
                        return -2;
                    }
                    valid_credential=check_sha256(credential_file, output_sha256,entry_number);

                    if(valid_credential){
                        printf("You have successfully log in. Have a nice day!\n");
                    }
                    else {
                        printf("Username and password are incorrect. Try again.\n");
                    }
                    fclose(credential_file);
                }
                else {
                    printf("Username unknown or incorrect. Check you have typed it correctly or make a registration\n");
                }
                fclose(user_file);
                break;
                
            case 'R':
                user_file = fopen(path_user_file, "r");
                if (user_file == NULL) {
                    printf("Errore: file utenti mancante\n");
                    return (-1);
                }
                printf("Username:\n");
                scanf("%s", Username);

                user_found=check_Username(user_file, Username, &entry_number);
                fclose(user_file);

                if (!user_found) {
                    printf("Password:\n");
                    scanf("%s", Password);
                    printf("Phone Number (will be used to password recovery):\n");
                    scanf("%s", Phone_number);

                    user_file = fopen(path_user_file, "a");
                    fprintf(user_file,"%s\n",Username);
                    fclose(user_file);
                    credential_file= fopen(path_crypted_credential_file,"a");
                    if (credential_file == NULL) {
                        printf("Errore: file credenziali mancante\n");
                        return (-1);
                    }

                    if(sha256_input1_input2(Username,Password,output_sha256)){
                        return -2;
                    }

                    fprintf(credential_file,"%s\n",output_sha256);
                    fclose(credential_file);

                    phone_file=fopen(path_crypted_phone_number_file,"a");
                    if (phone_file == NULL) {
                        printf("Errore: file phone_number mancante\n");
                        return (-1);
                    }

                    if(sha256_input1_input2(Username,Phone_number,output_sha256)!=0){
                        return -2;
                    }

                    fprintf(phone_file,"%s\n",output_sha256);
                    fclose(phone_file);

                } else {
                    printf("Your username is already registered. Use another one. If it's your user, log in or recover your password");
                }
                break;

            case 'F':
                user_file = fopen(path_user_file, "r");
                if (user_file == NULL) {
                    printf("Errore: file utenti mancante\n");
                    return (-1);
                }
                printf("Enter your Username\n");
                scanf("%s", Username);
                user_found=check_Username(user_file, Username, &entry_number);
                fclose(user_file);
                if (user_found){
                    phone_file=fopen(path_crypted_phone_number_file,"r");

                    if (phone_file == NULL) {
                        printf("Errore: file phone_number mancante\n");
                        return (-1);
                    }

                    printf("Enter your telephone number\n");
                    scanf("%s",Phone_number);


                    if(sha256_input1_input2(Username,Phone_number,output_sha256)!=0){
                        return -2;
                    }

                    valid_phone_number=check_sha256(phone_file,output_sha256,entry_number);

                    fclose(phone_file);

                    if (valid_phone_number){
                        credential_file=fopen(path_crypted_credential_file,"r");
                        tmp_file=fopen(path_tmp_file,"w");

                        if (credential_file == NULL) {
                            printf("Errore: file crededial mancante\n");
                            return (-1);
                        }

                        printf("We are going to reset your password. Type a new password\n");
                        printf("Password:\n");
                        scanf("%s", Password);

                        if(sha256_input1_input2(Username,Password,output_sha256)!=0){
                            return -2;
                        }
                        counter=0;
                        while(fscanf(credential_file,"%s",tmp_credential)!=EOF){
                            counter+=1;
                            if(counter==entry_number){
                                fprintf(tmp_file,"%s\n",output_sha256);
                            }
                            else{
                                fprintf(tmp_file,"%s\n",tmp_credential);
                            }
                        }
                        fclose(credential_file);
                        fclose(tmp_file);

                        comando[0]='\0';
                        strcat(comando,"rm ");
                        strcat(comando,path_crypted_credential_file);
                        strcat(comando,"\0");
                        system(comando);

                        rename("./tmp_file.txt","./crypted_credential.txt");
                        printf("Thank you the new password is now registered and safe!\n");
                    }
                    else{
                        printf("Sorry, you have typed a phone number that is not associated with your username. Try again\n");
                    }
                }
                else{
                    printf("No match in our database, please register yourself\n");

                }

                break;
            default:;
        }
        if (CharInput == 'E') {
            commandExit = 1;
        }
    }
    printf("SafeRegistration will terminate. Have a nice day!\n");
}


