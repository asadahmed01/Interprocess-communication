/*
* FILE           : functions.c
* PROGRAMMERs    : Mohammed Abusultan && Asad ahmad
* FIRST VERSION  : 2021 - 03 - 27
* DESCRIPTION    : this file contains all the functions that are resposible for receiving messages and establishing connection
*				   between client and server.
*                
*  
*/

#define TRUE  1
#define FALSE 0

#define M_TYPE	80
#define BUFF_SIZE 1000
#define SEND	1
#define RECEIVE	2
#define MAX_DC_ROLES 10
#define FATAL_CODE 6
# define TIME_LIMIT 35.00
#define OKAY 0
#define HYDRAULIC_PRESSURE_FAIL 1
#define SAFTEY_BTN_FAIL 2
#define NO_RAW_MATERIAL_IN_PROCESS 3
#define OPERATING_OUT_OF_RANG 4
#define OPERATOR_ERROR 5
#define OFFLINE 6


typedef struct msgCODES
{
	long mtype;
	pid_t processID; 
	int statusCode;	
	
	
} MSGCODES;


typedef struct {
	pid_t dcProcessID;
	time_t lastTimeHeardFrom;
} DCInfo;


typedef struct  {
	int msgQueueID;
	int numberOfDCs;
	DCInfo dc[MAX_DC_ROLES];
} MasterList;




int runServerMachine(int messageID, MasterList* masterlist);
void logger (char* message);
int allocateSharedMemory();
time_t calculateTime();








