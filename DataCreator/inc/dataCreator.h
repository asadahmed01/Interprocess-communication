/*
* FILE           : dataCreator.h
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

//struct
typedef struct msgCODES
{
	long mtype;
	pid_t processID; 
	int statusCode;	
		
	
} MSGCODES;

//functions prototypes
int sendMsg(pid_t processId, int messageId, int code);
int establishCon();
void logger (char* message);

//conestants
#define PID 8555
#define OKAY 0
#define HYDRAULIC_PRESSURE_FAIL 1
#define SAFTEY_BTN_FAIL 2
#define NO_RAW_MATERIAL_IN_PROCESS 3
#define OPERATING_OUT_OF_RANG 4
#define OPERATOR_ERROR 5
#define OFFLINE 6
#define SIX 6
#define TYPE_NUM 80


