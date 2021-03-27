#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/types.h>
#include "../inc/header.h"

/*
* FILE           : functions.c
* PROGRAMMERs    : Mohammed Abusultan && Asad ahmad
* FIRST VERSION  : 2021 - 03 - 27
* DESCRIPTION    : this file contains all the functions that are resposible for receiving messages and establishing connection
*				   between client and server.
*                
*  
*/

int main (void){

	int 		exitServer = 1;
	int counter = 0;
	key_t 		message_key;

	int 		messageID ; // message ID
	int 		returnCode;	// return code from message processing
	MasterList* masterlist;
	char		buffer[100];
	

	//obtain the message key
	message_key = ftok (".", 8555);
	printf("message key %d", message_key);
	if (message_key == -1) 
	{ 
		printf ("(SERVER) Cannot allocate key\n");
		return 1;
	}	/* endif */


	/*
	 * if message queue exists, use it, or
	 * allocate a new one
	 */

	if ((messageID = msgget(message_key, 0)) == -1) 
	{
		printf ("(SERVER) No queue available, creating NOW......!\n");

		//Create a new message queue

		messageID = msgget (message_key, IPC_CREAT | 0660);
		if (messageID == -1) 
		{
			printf ("(SERVER) Cannot allocate a new queue!\n");
			return 2;
		}
	}


	printf ("(SEVER) Our message queue ID is %d\n", messageID);
	

	/*
	 * our server is done, so shut down the queue
	 */
	
	//start allocating a shared memory for the masterlist

	int shmID = allocateSharedMemory();
	//attach to the allocated shared memory block
	masterlist = (MasterList *)shmat(shmID, NULL, 0);
	if (masterlist == NULL) 
	{
	  printf ("Cannot attach to shared memory block!\n");
	  exit(1);
	}

	printf("aaatttaaacheeeed\n");

	///// ********************** ///////
	for(int i= 0; i < 10; i++)
	{
		masterlist->dc[i].dcProcessID = 0;
	}
	printf("sleep before the main loop\n");
	sleep(5);
	printf("just  woke up");
	while(1)
	{
		
		printf("calling the func now\n");
	 	runServerMachine(messageID, masterlist);
		printf("...breaking out of the loop...\n\n");
		sleep(3);
		//logger("Updated in the master list");
		//break;
	  
	}

	
	printf ("(SERVER) Exiting ... removing msgQ and leaving ...\n");
	msgctl (messageID, IPC_RMID, (struct msqid_ds *)NULL);
	//free shared memory
	shmctl(shmID, IPC_RMID, 0);


return 0;
}



