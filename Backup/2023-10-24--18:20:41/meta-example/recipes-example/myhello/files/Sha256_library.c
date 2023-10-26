// This file was created by andre on 03/10/2023.

#include "./Sha256_library.h"   // Include a user-defined library for SHA-256.
#include <stdio.h>              // Include the standard input/output library.
#include <stdlib.h>             // Include the standard library for memory allocation and deallocation.
#include <string.h>             // Include the string manipulation library.
#include <unistd.h>             // Include the POSIX library for system calls.


int sha256_algorithm(char* input, int n, char* output) {
    int return_value;

    // Poll for the availability of SHA-256 hardware, explaining the busy polling loop.
    while (sha256_check_busy()) {
        usleep(100); // If hardware is busy, this process sleeps for 100 milliseconds, then retries.
        printf("Waiting for check busy\n");
    }

    // Request to execute the SHA-256 algorithm (it passes the input).
    return_value = sha256_request(input, n);

    // Wait for SHA-256's output calculation for 200 microseconds.
    usleep(200);

    // If return_value is 0, get the SHA-256 output.
    if (return_value == 0) {
        sha256_get_output(output); // Gets the SHA-256 output.
    }

    // Return the final return_value.
    return return_value;
}

// Function to initialize SHA-256 hardware.
int sha256_inizialize() {
    printf("Initialization of SHA-256\n");
    return 0;
}

// Function to elaborate the request for SHA-256 calculation.
int sha256_request(const char* input, int n) {
    FILE* sha256_input_file;
    FILE* sha256_cmd_file;

    // Check if the input size is too large and provide an error message.
    if (n > 100) {
        printf("Error: Driver memory dimension of input must be at a maximum of 100 characters. Abort!\n");
        return (-2);
    }

    // Open the input file.
    sha256_input_file = fopen("/sys/devices/platform/b040000.virt-sha-nodename/input", "w");
    if (sha256_input_file == NULL) {
        return (-1);
    }

    // Write the input data to the file.
    fprintf(sha256_input_file, "%s\n", input);
    fclose(sha256_input_file);

    // Open the command file and set it to 1 to trigger the SHA-256 calculation.
    sha256_cmd_file = fopen("/sys/devices/platform/b040000.virt-sha-nodename/cmd", "w");
    if (sha256_cmd_file == NULL) {
        return (-1);
    }

    fprintf(sha256_cmd_file, "%d", 1);
    fclose(sha256_cmd_file);

    return 0;
}

// Function to retrieve the output of SHA-256 calculation.
int sha256_get_output(char* output) {
    char output_sha256[265];
    FILE* sha256_output_file;

    // Open the output file to read the calculated SHA-256 output.
    sha256_output_file = fopen("/sys/devices/platform/b040000.virt-sha-nodename/output", "r");
    if (sha256_output_file == NULL) {
        return (-1);
    }

    // Read the output data.
    fgets(output_sha256, 65, sha256_output_file);
    fclose(sha256_output_file);

    // Copy the SHA-256 output to the provided output buffer.
    strcpy(output, output_sha256);

    // Return success.
    return (1);
}

// Function to read the flag and check if the device is occupied.
int sha256_check_busy() {
    FILE* busy_attribute;
    int busy_read;

    // Open the attribute file to check the hardware status.
    busy_attribute = fopen("/sys/devices/platform/b040000.virt-sha-nodename/busy", "r");
    if (busy_attribute == NULL) {
        printf("Cannot open attribute\n");
        return (-1);
    }

    // Read the busy attribute and handle any errors.
    busy_read = fgetc(busy_attribute);
    if (busy_read == -1) {
        printf("Cannot read\n");
        return -1;
    } else {
        busy_read = busy_read - '0';
    }
    fclose(busy_attribute);

    // Return the busy status.
    return busy_read;
}
