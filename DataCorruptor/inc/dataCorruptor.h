/*
* FILE           : dataCorruptor.h
* PROGRAMMERs    : Mohammed Abusultan && Asad ahmad
* FIRST VERSION  : 2021 - 03 - 27
* DESCRIPTION    : this file contains all functions prototypes as well as conestants and includes.
*                
*  
*/

//libraries 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>

#define MAX_DC_ROLES 10

//struct
typedef struct 
{
	pid_t dcProcessID;
	time_t lastTimeHeardFrom;
	
} DCInfo;

typedef struct 
{
	int msgQueueID;
	int numberOfDCs;
	DCInfo dc[MAX_DC_ROLES];
	
} MasterList;

//functions prototypes 
int startDX();
pid_t getProcessId(int pIndex, MasterList *pID);
void logger (char* message);


//conestants
#define PID 8555
#define TYPE_NUM 80
#define KEY 16535
#define TWO 2
#define THREE 3
#define FOUR 4
#define FIVE 5
#define SIX 6
#define SEVEN 7
#define EIGHT 8
#define NINE 9
#define TEN 10
#define ELEVEN 11
#define TWELVE 12
#define THIRTEEN 13
#define FOURTEEN 14
#define FIFTEEN 15
#define SIXTEEN 16
#define SEVENTEEN 17
#define EIGHTEEN 18
#define NINETEEN 19
#define TWENTY 20
