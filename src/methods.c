#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <sys/shm.h>
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
#define MSG_SIZE 1000
int loopCounter = 0;

/*	Name	:  runServerMachine()
*  Purpose  :  this function is used to receive messages from the client machines and process it.
*			   also, this function is responsible for attaching the struct to the allocated shared memory
*  Inputs	:	messageID, shmID
*  Outputs	:	None
*  Returns	:	None
*/
void runServerMachine(int messageID, MasterList* masterlist) {
	int returnCode;
	//char tmp[10];
	int counter = 1;
	//MasterList* masterlist ;
	char logMessage[100] = "DC-";
	double limit = TIME_LIMIT;
	double diff;
	MSGCODES 	message; // new variable of type msgCODES STRUCT

	//start receiving the messae here
	returnCode = msgrcv(messageID, (void*)&message, sizeof(message), 80, 0);
	if(returnCode == -1) 
	{
		printf("error occurred"); 
		exit(1);
	}
	
	
	
	int statusCode = message.statusCode;
	

	printf("processID: %d\n", message.processID);
	printf("status code: %d\n", message.statusCode);


	masterlist->msgQueueID = messageID;
	
	

	for(int i = 0; i< MAX_DC_ROLES; i++) {
		
		
		if(masterlist->dc[i].dcProcessID != message.processID)
		{
			
				if(counter == MAX_DC_ROLES) {
					masterlist->dc[loopCounter].dcProcessID = message.processID;
					masterlist->dc[loopCounter].lastTimeHeardFrom = calculateTime();
					loopCounter++;
					masterlist->numberOfDCs++;
					
					snprintf(logMessage, sizeof(logMessage), "DC-%02d [%d] added to the masterList -NEW DC- status 0 (Everything is Okay)", loopCounter, message.processID);
						logger(logMessage);
					
					
					
				}
				counter++;
			
		}
		else if(masterlist->dc[i].dcProcessID == message.processID) {
			if(message.statusCode == OKAY)
					{
						snprintf(logMessage, sizeof(logMessage), "DC-%02d [%d] updated the masterList -MSG RECEIVED- status %d (Everything is Okay)", loopCounter, message.processID, message.statusCode);
						logger(logMessage);
					}
					if(message.statusCode == HYDRAULIC_PRESSURE_FAIL)
					{
						snprintf(logMessage, sizeof(logMessage), "DC-%02d [%d] updated the masterList -MSG RECEIVED- status %d (HYDRAULIC PRESSURE FAIL)", loopCounter, message.processID, message.statusCode);
						logger(logMessage);
					}
					if(message.statusCode == SAFTEY_BTN_FAIL)
					{
						snprintf(logMessage, sizeof(logMessage), "DC-%02d [%d] updated the masterList -MSG RECEIVED- status %d (Safety Button Fail)", loopCounter, message.processID, message.statusCode);
						logger(logMessage);
					}
					if(message.statusCode == NO_RAW_MATERIAL_IN_PROCESS)
					{
						snprintf(logMessage, sizeof(logMessage), "DC-%02d [%d] updated the masterList -MSG RECEIVED- status %d (No Raw Material in-process)", loopCounter, message.processID, message.statusCode);
						logger(logMessage);
					}
					if(message.statusCode == OPERATING_OUT_OF_RANG)
					{
						snprintf(logMessage, sizeof(logMessage), "DC-%02d [%d] updated the masterList -MSG RECEIVED- status %d (Operation out of Rang)", loopCounter, message.processID, message.statusCode);
						logger(logMessage);
					}
					if(message.statusCode == OPERATOR_ERROR)
					{
						snprintf(logMessage, sizeof(logMessage), "DC-%02d [%d] updated the masterList -MSG RECEIVED- status %d (Operator Eroor)", loopCounter, message.processID, message.statusCode);
						logger(logMessage);
					}
/*			if(message.statusCode == FATAL_CODE)*/
/*			{*/
/*				*/
/*				*/
/*				for(int j = i; j < MAX_DC_ROLES; j++)*/
/*				{*/
/*					*/
/*					masterlist->dc[j].dcProcessID = masterlist->dc[j+1].dcProcessID;*/
/*					*/
/*				}*/
/*			*/
/*				loopCounter--;*/
/*				masterlist->numberOfDCs--;*/
/*				if(masterlist->numberOfDCs == 0)*/
/*				{*/
/*					break;*/
/*				}*/
/*				snprintf(logMessage, sizeof(logMessage), "DC-%02d [%d] has gone OFFLINE- removing from master-list)", loopCounter, message.processID);*/
/*						logger(logMessage);*/
/*			}*/
			if((difftime(calculateTime(), masterlist->dc[i].lastTimeHeardFrom)) > TIME_LIMIT && getpgid(masterlist->dc[i].dcProcessID) != -1)
			{
				for(int j = i; j < MAX_DC_ROLES; j++)
				{
					
					masterlist->dc[j].dcProcessID = masterlist->dc[j+1].dcProcessID;
					printf("removed %d\n", masterlist->dc[j].dcProcessID);
				
				}
			
				loopCounter--;
				masterlist->numberOfDCs--;
				snprintf(logMessage, sizeof(logMessage), "DC-%02d [%d] has gone OFFLINE- removing from master-list)", loopCounter, message.processID);
						logger(logMessage);
			}
			
		//break; 
		}
	
	}
	
	

	for(int i= 0; i < MAX_DC_ROLES; i++)
	{

		if(masterlist->dc[i].dcProcessID != 0)
		{
			printf("dcProcessID[%d].. %d\n",i,masterlist->dc[i].dcProcessID);
		}
		
		
	}

	

}


////// ********** ////////

/*	Name	:  calculateTime()
*  Purpose  :  this function returns the current time in seconds. this time is used to determine when was the last time heard
*			   from the machines
*  Inputs	:	None
*  Outputs	:	None
*  Returns	:	time in seconds
*/
time_t calculateTime(){

	time_t seconds;

     // Stores time seconds

    time(&seconds);

    //printf("Seconds %ld\n", seconds);
	return seconds;
}


/////// ******** ////////
/*	Name	:  allocateSharedMemory()
*  Purpose  :  this function is used to allocate the shared memory bloc for the masterlist the server maintains.
*  Inputs	:	None
*  Outputs	:	None
*  Returns	:	the shared memory ID (int))
*/
int allocateSharedMemory() {
	
	//MasterList *connectedDCs;
	
	int shmid;
	key_t shmkey;

	/* get the secret key_code to the area of shared memory we will allocate */	
	shmkey = ftok (".", 16535);
	if (shmkey == -1) 
	{ 
	  printf ("(CONSUMER) Cannot allocate key\n");
	  //return 1;
	}

	/*
	 * if shared mem exists, use it, or
	 * allocate a new block
	 */
	shmid = shmget(shmkey, sizeof(MasterList), 0644|IPC_CREAT);

	if (shmid == -1) 
	{
		

		printf ("(CONSUMER) Shared-Memory doesnt exist...\n");
		//return 2;
	}

	printf ("Shared-Memory ID is %d\n", shmid);

	//connectedDCs = (MasterList*)shmat (shmid, NULL, 0);
	return shmid;
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

	strftime(timeStamp, 100, "[%Y-%d-%d  %H:%M:%S]  ", t);

	//strcat(timeStamp, message);
	FILE *fp;
	fp = fopen("/tmp/DataMonitor.log", "a+");
	if(fp == NULL){
		printf("Cannot create logger file");
		exit(1);
		
	}
	
	//write the message to the log file
	fprintf(fp, "%s %s \n", timeStamp, message);
	//close the file
	fclose(fp);

}
