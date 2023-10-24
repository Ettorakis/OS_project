/*
 * Simulated Device Driver © 2023 by Andrea Bonino, Gabriele Fasolis, Mattia
 * Mattiauda, Ettore Mondino, Federico Tartaglia is licensed under Attribution-
 * NonCommercial 4.0 International. To view a copy of this license, visit 
 * http://creativecommons.org/licenses/by-nc/4.0/
 */

#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

int main() {
        int fd=0;
        uint32_t buff;
        fd=open("/sys/devices/platform/b000000.virt_foo", O_RDONLY);
        if(fd>0){
                printf("File aperto\n");
                if(pread(fd, &buff, sizeof(buff), 0)!=4){
                        printf("Erorre lettura da file test, %x \n", buff);
                }
                else{
                        printf("stampa %x\n",buff);
                }
        }

	return 0;
}
