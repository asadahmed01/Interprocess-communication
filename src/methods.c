#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "../inc/header.h"


void runServerMachine() {

	printf("inside the main loop....\n"); 
	sleep(3);
	printf("...still inside main loop\n");
	sleep(2);
	printf("...END of main loop\n");
	
}
