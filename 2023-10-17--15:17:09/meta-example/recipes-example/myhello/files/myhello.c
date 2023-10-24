/*
 * Simulated Device Driver © 2023 by Andrea Bonino, Gabriele Fasolis, Mattia
 * Mattiauda, Ettore Mondino, Federico Tartaglia is licensed under Attribution-
 * NonCommercial 4.0 International. To view a copy of this license, visit 
 * http://creativecommons.org/licenses/by-nc/4.0/
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
/*
int main() {

	int fd = open ("/dev/LM_module",O_RDWR	);
	if (fd < 0) {
		perror ("Unable to open device");
	}

	unsigned int arg;
	long r =  ioctl(fd, 0x01 , &arg);

	if (r < 0) {
		perror ("Unable to open device");
	}

	int buf;
	r = read (fd, &buf, sizeof(int));

	write (fd, &buf, sizeof(int));	

	close(fd);

}
*/
int main(){
	printf("Hrllo andre\n");
	return 0;
}
