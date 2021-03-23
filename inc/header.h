

#define TRUE  1
#define FALSE 0

#define M_TYPE	80

#define SEND	1
#define RECEIVE	2


void runServerMachine(int messageID);
void logger (char* message);
/*
 * note: our client and server must agree upon this structure!
 */


typedef struct msgCODES
{
	long mtype;
	pid_t processID; 
	int statusCode;	
	
	
} MSGCODES;





