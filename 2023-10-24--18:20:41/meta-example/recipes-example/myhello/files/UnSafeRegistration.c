#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define path_user_file "./user.txt"
#define path_credential_file "./credential.txt"
#define path_phone_number_file "./phone.txt"
#define path_tmp_file "./tmp_file.txt"

// Function for reading user input and returning a validated character
int input_funzionality(char* returned_char){
    char user_input[5];
    char CharInput;

    // Read user input as a string
    scanf("%s", user_input);

   // Take the first character from the input
    CharInput=user_input[0];

    // Convert lowercase character to uppercase if needed
    if ((int) CharInput > 96) {
        CharInput = (char) (CharInput - 32);
    }
    // Check if the character is 'L', 'R', 'E', or 'F'
    if (CharInput == 'L' || CharInput == 'R' || CharInput == 'E' || CharInput == 'F') {
        *returned_char=CharInput;
        return 1;	 // Valid input
    }
    else return 0;	// Invalid input
}


// Function to check if a username exists in a user file and get its entry number
int check_Username(FILE* user_file,const char* input_username, int* entry_number){
    char Username[30];

    *entry_number=0;		// Initialize the entry number


    // Loop through the user file to search for the given username
    while (!feof(user_file)) {
        fscanf(user_file,"%s",Username);
        *entry_number = *entry_number + 1;
	// Check if the read username matches the provided username
        if (strcmp(Username, input_username) == 0) {
            return 1; // Username found
        }
    }
    return 0;	// Username not found
}

// Function to check if password of user is correct 
int check_password(FILE* credential_file, const char* input_password, const int entry_number){
    int counter=0;
    char Password[30];

	// Loop through the password file
    while (!feof(credential_file)) {
        counter += 1;

        fscanf(credential_file,"%s",Password);

	// Check if the current line corresponds to the specified entry number
        if (counter == entry_number) {
	    // Check if the read password matches the provided password
            if (strcmp(input_password, Password) == 0) return 1; // correct Password
            else return 0;  // wrong Password 
        }
    }
    return 0;  // Wrong password
}

// Function to check if phone number of user is correct 
int check_phone(FILE* phone_file, const char* input_phone, const int entry_number){
    int counter=0;
    char Phone[30];
	// Loop through the phone file
    while (!feof(phone_file)) {
        counter += 1;
        fscanf(phone_file,"%s",Phone);

	// Check if the current line corresponds to the specified entry number
        if (counter == entry_number) {
		// Check if the read phone matches the provided phone number
            if (strcmp(input_phone, Phone) == 0) return 1;  // correct Password
            else return 0;  // wrong Password 
        }
    }
    return 0; // wrong Password 
}

int main() {
    // Declare variables to track validation and user information
    int valid, user_found, valid_credential, valid_phone_number;
    char CharInput = ' ';
    int commandExit = 0;
 
    // Declare file pointers for data files
    FILE *user_file;
    FILE *credential_file;
    FILE *phone_file;
    FILE *tmp_file;
    FILE *creazione_file;

    // Declare character arrays to store user input and processed data
    char Username[30];
    char Phone_number[30];
    char Password[30];
    int entry_number = 0, counter = 0;
    char tmp_credential[60];
    char comando[35];

    if (access(path_user_file, F_OK) != 0) { // file doesn't exist
        creazione_file=fopen(path_user_file,"w");   //file is created
        fclose(creazione_file);
    }


    if (access(path_credential_file, F_OK) != 0) { // file doesn't exist
        creazione_file=fopen(path_credential_file,"w");   //file is created
        fclose(creazione_file);
    }

    if (access(path_phone_number_file, F_OK) != 0) { // file doesn't exist
        creazione_file=fopen(path_phone_number_file,"w");   //file is created
        fclose(creazione_file);
    }

    // Start an infinite loop for user interactions
    while (!commandExit) {
        printf("Welcome to UnSafeRegistration.c\n"
               "Enter L to login in \n"
               "Enter R to register\n"
               "Enter F to recover your password\n"
               "Enter E to exit\n\n"
        );
        valid=0;
	// Loop until valid input is received
        while (!valid) {
            printf("Input:");
            valid=input_funzionality(&CharInput);
        }
	// Process user input based on the chosen option
        switch (CharInput) {
            case 'L':
		// Open the user file for reading
                user_file = fopen(path_user_file, "r");

		// Check if the user file exists
                if (user_file == NULL) {
                    printf("Error: missing users file\n");
                    return (-1);
                }
                printf("Username:\n");
                scanf("%s", Username);

		// Check if the entered username exists in the user file
                user_found=check_Username(user_file, Username, &entry_number);
                fclose(user_file);

                if (user_found) {
		    // Open the credential file for reading
                    credential_file=fopen(path_credential_file,"r");

		     // Check if the credential file exists
                    if (credential_file == NULL) {
                        printf("Error: missing credential file \n");
                        return (-1);
                    }


                    printf("Password:\n");
                    scanf("%s", Password);
	
		    // Check if the calculated hash exists in the credential file
                    valid_credential= check_password(credential_file,Password,entry_number);

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
                break;

            case 'R':
		// Open the user file for reading
                user_file = fopen(path_user_file, "r");

		// Check if the user file exists
                if (user_file == NULL) {
                    printf("Error: missing user file\n");
                    return (-1);
                }
                printf("Username:\n");
                scanf("%s", Username);

		// Check if the entered username exists in the user file
                user_found=check_Username(user_file, Username, &entry_number);
                fclose(user_file);

                if (!user_found) {
                    printf("Password:\n");
                    scanf("%s", Password);
                    printf("Phone Number (will be used to password recovery):\n");
                    scanf("%s", Phone_number);


		    // Open the user file for appending and add the new username
                    user_file = fopen(path_user_file, "a");
                    fprintf(user_file,"%s\n",Username);
                    fclose(user_file);

		    // Open the credential file for appending
                    credential_file= fopen(path_credential_file,"a");

		    // Check if the credential file exists
                    if (credential_file == NULL) {
                        printf("Errore: missing credential file\n");
                        return (-1);
                    }

		    // Append to the credential file
                    fprintf(credential_file,"%s\n",Password);
                    fclose(credential_file);

		    // Open the phone file for appending
                    phone_file=fopen(path_phone_number_file,"a");
	
		     // Check if the phone file exists
                    if (phone_file == NULL) {
                        printf("Error: missing phone_number file\n");
                        return (-1);
                    }


		     // Append the phone file
                    fprintf(phone_file,"%s\n",Phone_number);
                    fclose(phone_file);

                } else {
                    printf("Your username is already registered. Use another one. If it's your user, log in or recover your password");
                }
                break;

            case 'F':
		// Open the user file for reading
                user_file = fopen(path_user_file, "r");

		// Check if the user file exists
                if (user_file == NULL) {
                    printf("Error:missing users file\n");
                    return (-1);
                }
                printf("Enter your Username\n");
                scanf("%s", Username);
                user_found=check_Username(user_file, Username, &entry_number);
                fclose(user_file);
                if (user_found){
		   // Open the phone file for reading
                    phone_file=fopen(path_phone_number_file,"r");

		    // Check if the phone file exists
                    if (phone_file == NULL) {
                        printf("Error: missing phone_number file\n");
                        return (-1);
                    }

                    printf("Enter your telephone number\n");
                    scanf("%s",Phone_number);

		    // Check if the phone number is correct in the phone file
                    valid_phone_number=check_phone(phone_file,Phone_number,entry_number);

                    fclose(phone_file);

                    if (valid_phone_number){

			// Open the credential file for reading and a temporary file for writing
                        credential_file=fopen(path_credential_file,"r");
                        tmp_file=fopen(path_tmp_file,"w");

			// Check if the credential file exists
                        if (credential_file == NULL) {
                            printf("Error: missing credential file\n");
                            return (-1);
                        }

                        printf("We are going to reset your password. Type a new password\n");
                        printf("Password:\n");
                        scanf("%s", Password);

                        counter=0;

			// Iterate through the credential file, updating the password hash
                        while(fscanf(credential_file,"%s",tmp_credential)!=EOF){
                            counter+=1;
                            if(counter==entry_number){
                                fprintf(tmp_file,"%s\n",Password);
                            }
                            else{
                                fprintf(tmp_file,"%s\n",tmp_credential);
                            }
                        }
                        fclose(credential_file);
                        fclose(tmp_file);


			// Create a command to remove the original credential file
                        comando[0]='\0';
                        strcat(comando,"rm ");
                        strcat(comando,path_credential_file);
                        strcat(comando,"\0");

			// Execute the command to remove the original credential file
                        system(comando);

			// Rename the temporary file to replace the original credential file
                        rename("./tmp_file.txt","./credential.txt");
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


	// Check if the user chose to exit the program
        if (CharInput == 'E') {
            commandExit = 1;
        }
    }
	 // Display a closing message when the program terminates
    printf("UnSafeRegistration will terminate. Have a nice day!\n");
}


