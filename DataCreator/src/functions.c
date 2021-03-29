/*
* FILE           : functions.c
* PROGRAMMERs    : Mohammed Abusultan && Asad ahmad
* FIRST VERSION  : 2021 - 03 - 27
* DESCRIPTION    : this file contains all the functions that are resposible for sending messages and establishing connection
*				   between client and server.
*                
*  
*/


#include "../inc/dataCreator.h"

/*	Name	:  establishCon()
*  Purpose  :  this function is used to get the process ID for the client, checking the message queue
*			   then it sends codes continuously to the server.
*  Inputs	:	Nothing
*  Outputs	:	error messages when occur
*  Returns	:	0 Success, 1 Fail
*/
//MSGCODES msgInfo;
int establishCon()
{
	key_t	 	message_key;
	pid_t		myPID;
	pid_t 		processId;
	int 		messageId;
	int 		done = 0;
	int 		count = 0;
	int			counter = 0;
	int			msg = 0;
	int			tmp= 0;
	MSGCODES msgInfo;

	/* this client needs to know their own PID */
	myPID = getpid();

	
	//obtain the message key
	message_key = ftok (".", 8555);
	printf("message key %d", message_key);
	if (message_key == -1) 
	{ 
		printf ("(SERVER) Cannot allocate key\n");
		return 1;
	}	/* endif */
	
	while ((messageId = msgget(message_key, 0)) == -1) 
	{
		
		sleep(10);
		printf("message id %d\n", messageId);
		
	}
	
	printf("message id after first while %d\n", messageId);
	//setting the process ID to the given ID from the machine
	processId = myPID;
	
	
	//check if the message queue exists
/*	while((messageId = msgget (message_key, 0) == -1))*/
/*	{*/
/*		printf("first looop\n");*/
/*		sleep(10);	*/
/*		printf("message ID %d\n", messageId);*/
/*	}*/
	//when the message queue is established,send status 0
	
	//when the status code is not 6
	while ((count = sendMsg(processId, messageId, tmp)) != OFFLINE) 
	{
		srand(time(0));	
		
		//assight statusCode to random number between 1-6
		tmp = rand() % (SIX + 1);	//here we use the time to seed rnad() dunction
		counter = rand() % 20 + 10;				//  calculate number of seconds between 10-30
		printf("sleeping....for: %d\n", counter);//debug
		sleep(counter);						
		printf("result is: %d\n",count);//debug
		printf(" [%d] - MSG SENT - Status %d ()\n", processId, count);//debug
		printf("message id inside main loop %d\n", messageId);
		
	}
	
	return done; //return 0

}

/*	Name	:  sendMsg() 
*  Purpose  :  this function is used to send random codes (2-6) to the server.
*  Inputs	:	pid_t processId, int messageId
*  Outputs	:	Nothing
*  Returns	:	-1 if Fail.
*/
int sendMsg(pid_t processId, int messageId, int code)
{
	int dataSize;	
	MSGCODES msgInfo;// struct of type MSGCODES
	int msg;
	char loggMessage [100] = "";
	dataSize = sizeof(MSGCODES) - sizeof(long);//get the size of the struct
	
	//assign processID (the struct processID) to the actual process ID
	msgInfo.processID = processId;

	
	msgInfo.statusCode = code;

	//set mtype to 80 (this variable is going to let the server see the struct, in order to communicate with this client)
	msgInfo.mtype = TYPE_NUM;
	
	//sending message to server
	msg = msgsnd(messageId, (void *)&msgInfo, dataSize,0);
	if(code == 0)
	{
		snprintf(loggMessage, sizeof(loggMessage), "DC [%d] - MSG SENT - Status %d (EVERY IS OKAY)", msgInfo.processID, code);
		logger(loggMessage);
	}
	if(code == 1)
	{
		snprintf(loggMessage, sizeof(loggMessage), "DC [%d] - MSG SENT - Status %d (Hydraulic Pressure Failure)", msgInfo.processID, code);
		logger(loggMessage);
		
	}
	if(code == 2)
	{
		snprintf(loggMessage, sizeof(loggMessage), "DC [%d] - MSG SENT - Status %d (Safety Button Failure)", msgInfo.processID, code);
		logger(loggMessage);
	}
	if(code == 3)
	{
		snprintf(loggMessage, sizeof(loggMessage), "DC [%d] - MSG SENT - Status %d (No Raw Material in the Process)", msgInfo.processID, code);
		logger(loggMessage);
	}
	if(code == 4)
	{
		snprintf(loggMessage, sizeof(loggMessage), "DC [%d] - MSG SENT - Status %d (Operating Temperature Out of Range)", msgInfo.processID, code);
		logger(loggMessage);
	}
	
	if(code == 5)
	{
		snprintf(loggMessage, sizeof(loggMessage), "DC [%d] - MSG SENT - Status %d (Operator Error)", msgInfo.processID, code);
		logger(loggMessage);
	}
	
	
	//check if the sent code is 6 
	if(msgInfo.statusCode == OFFLINE)
	{
		
	
		snprintf(loggMessage, sizeof(loggMessage), " [%d] - MSG SENT - Status %d (Machine is Off-Line)", msgInfo.processID, code);
		logger(loggMessage);
		return OFFLINE;	//return 6 to go offline
	}
	
	return msg;

}


////// ********** ////////
/*	Name	:  logger()
*  Purpose  :  this function is used to log the messages and the status of the machines to the DC monitor log.
*  Inputs	:	message (char*) the message being logged
*  Outputs	:	None
*  Returns	:	None
*/
void logger (char* message) {
	char timeStamp[100];
	struct tm* t;
	time_t now;
	now = time(0); //get the current time
	t = localtime(&now); //struct of the time

	strftime(timeStamp, 100, "[%Y-%d-%d  %H:%M:%S]  : ", t);

	//strcat(timeStamp, message);
	FILE *fp;
	fp = fopen("/tmp/dataCreator.log", "a+");
	if(fp == NULL){
		printf("Cannot create logger file");
		exit(1);
		
	}
	
	//write the message to the log file
	fprintf(fp, "%s %s \n", timeStamp, message);
	//close the file
	fclose(fp);

}
