#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include "../inc/header.h"

#define MSG_SIZE 1000

void runServerMachine(int messageID) {
	int returnCode;
	char tmp[10];
	char logMessage[100] = "DC-";

	MSGCODES 	message; // new variable of type msgCODES STRUCT

	//start receiving the messae here
	msgrcv(messageID, (void*)&message, sizeof(message), 80, 0);
	//if(returnCode == -1) {printf("error occurred"); }
	returnCode = message.processID;
	sprintf(tmp, "%d", returnCode);
	int statusCode = message.statusCode;
	strcat(logMessage, "01");
	strcat(logMessage,tmp);
	logger(logMessage);
	printf("processID: %d\n", message.processID);
	printf("processID: %d\n", message.statusCode);
	
	
}


void logger (char* message) {
	char timeStamp[100];
	struct tm* t;
	time_t now;
	now = time(0); //get the current time
	t = localtime(&now); //struct of the time

	strftime(timeStamp, 100, "[%Y-%d-%d  %H:%M:%S] : ", t);

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
