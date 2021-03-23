#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "../inc/header.h"


int main (void){

	int 		exitServer = 1;

	key_t 		message_key;

	int 		messageID ; // message ID
	int 		returnCode;	// return code from message processing
	
	int		x;
	int 		msgPriority;
	char		buffer[100];
	

	//obtain the message key
	message_key = ftok (".", 8555);
	if (message_key == -1) 
	{ 
		printf ("(SERVER) Cannot allocate key\n");
		return 1;
	}	/* endif */


	/*
	 * if message queue exists, use it, or
	 * allocate a new one
	 */

	if ((messageID = msgget (message_key, 0)) == -1) 
	{
		printf ("(SERVER) No queue available, create!\n");

		/*
		 * nope, let's create one (user/group read/write perms)
		 */

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
	
	printf("sleep before the main loop\n");
	sleep(5);
	printf("just  woke up");
	while(1)
	{
		
		printf("calling the func now\n");
	 	runServerMachine(messageID);
		printf("...breaking out of the loop...\n\n");
		sleep(3);
		//logger("Updated in the master list");
		//break;
	  
	}
	printf ("(SERVER) Exiting ... removing msgQ and leaving ...\n");
	//msgctl (mid, IPC_RMID, (struct msqid_ds *)NULL);

return 0;
}



