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
	int 		retCode;

	//obtain the message key
	message_key = ftok (".", 8555);
	//check if the key was generated
	if (message_key == -1) 
	{ 
		return 1;
	}


	//check if there is message queue id

	if ((messageID = msgget(message_key, 0)) == -1) 
	{

		//if not, Create a new message queue

		messageID = msgget (message_key, IPC_CREAT | 0660);
		if (messageID == -1) 
		{
			return 2;
		}
	}


	printf ("(SEVER) Our message queue ID is %d\n", messageID);
	
	//start allocating a shared memory for the masterlist

	int shmID = allocateSharedMemory();
	//attach to the allocated shared memory block
	masterlist = (MasterList *)shmat(shmID, NULL, 0);
	//check if attachment was successfull
	if (masterlist == NULL) 
	{
	  exit(1);
	}

	printf("aaatttaaacheeeed\n");

	///// ********************** ///////
	//reset all the spots in the master to empty 
	for(int i= 0; i < MAX_DC_ROLES; i++)
	{
		masterlist->dc[i].dcProcessID = 0;
	}
	printf("sleep before the main loop\n");
	//sleep 15 seconds before the main loop
	sleep(15);
	printf("just  woke up");
	while(1)
	{
		
		printf("calling the func now\n");
	 	retCode = runServerMachine(messageID, masterlist);
	 	if(retCode == 1)
	 	{
	 		break;
	 	}
		printf("...breaking out of the loop...\n\n");
	  
	}

	
	printf ("(SERVER) Exiting ... removing msgQ and leaving ...\n");
	//clear the message queue
	msgctl (messageID, IPC_RMID, (struct msqid_ds *)NULL);
	//free shared memory
	shmctl(shmID, IPC_RMID, 0);


return 0;
}



