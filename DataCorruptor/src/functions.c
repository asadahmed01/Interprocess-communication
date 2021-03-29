/*
* FILE           : functions.c
* PROGRAMMERs    : Mohammed Abusultan && Asad ahmad
* FIRST VERSION  : 2021 - 03 - 27
* DESCRIPTION    : this file contains all the functions that are responsible of DX application .
*                
* 
*/
/*Credit to(Sean Clarke) 	: this code has been altered and edited to follow the assignment requirements. */

#include "../inc/dataCorruptor.h"


/*	Name	:  startDX()
*  Purpose  :  this function is used to start the Data Corruptor application. it gets the secret key for shared memory and 
*			   then it checks if it;s exists or not, and it detache this application to that memory location. after that
*			   it generates random codes 0-20 and based on that it decides to kill process or delete msgQ, do nothing.
*  Inputs	:	Nothing
*  Outputs	:	NONE
*  Returns	:	0 Success, 1 Fail
*/
int startDX()
{
	/*valriables */
	int 		done = 0;
	int 		shmid;		//shared memory ID
	key_t 		shmem_key;  //secret key 
	key_t	 	message_key;//msgQ ID
	MasterList *mList;
	int 		messageId;
	int 		count = 0;
	int			counter = 0;
	int 		randCode = 0;
	pid_t 		result = 0;
	char logMessage[1000] = "WOD Action ";
	char test [100] = "DX detected that msgQ is gone - assuming DR/DCs done";
	char deletionMsg[100] = "DX deleted the msQ - the DR/DC's can't talk anymore - exiting";
	char delMsg [100] = "";
	int status ;
	char testing [100]= "";

	/* get the secret key_code to the area of shared memory we will allocate */	
	shmem_key = ftok (".", KEY);// key is : 16535

	//check if it's succeed 
	if (shmem_key == -1) 
	{ 
	  printf ("Cannot allocate key\n");
	  return 1;
	}
	message_key = ftok(".", PID);//PID 8555
	
	//check if shared memory id exits if it is not sleep for 10 seconds
	while((shmid = shmget (shmem_key, sizeof (MasterList), 0)) == -1) 
	{
		
		counter++;
		printf ("sleeping for 10 sec...\n");
		sleep(TEN);//sleep for 10 seconds
		if(counter == 100)
		{
			return done =1;
		
		}
		
	}

	//attach to the shared memory location
	mList = (MasterList *)shmat(shmid, NULL, 0);

	while(!done)
	{
		//here we use the time to seed rnad() dunction
		srand(time(0));	

		//generate random number of seconds between 10-30						
		count = rand() % TWENTY + TEN;			
		sleep(count);
		
		//check for msgQ existance
		if((messageId = msgget (message_key, 0)) == -1)
		{
			if(!shmid)
			{
				break;
			}
			
			//free shared memory
			shmctl(shmid, IPC_RMID, 0);
			
			//log the event to text file
			snprintf("", sizeof(logMessage), "%s", test);
			logger(logMessage);
	
			return done=1;
		}
		else
		{	
		
			//here we use the time to seed rnad() dunction
			srand(time(0));	

			//generate random number 0-20
			randCode =rand() % TWENTY;
			randCode = 1;
			//if the random number 0 , 8 , 19
			if(randCode == 0 || randCode == EIGHT || randCode == NINETEEN)
			{
				//do nothing
			}
			//if the random number 1 , 4 , 11 (kill DC-01)
			else if(randCode == 1 || randCode == FOUR || randCode == ELEVEN)
			{
			
				//call function to get the process id 
				result = getProcessId(0,mList);
				
				//if process ID is grater than 0 that means the process is there
				if(result > 0)
				{
					//check if the process exists before killing it 
					if((getpgid(result) != -1) &&  (status = kill(result,9)) == -1)
					{
						//when kill() fails exit
						return done = 1;
					
					}
					//when kill() succeed
					if(status == 0)
						{
							//format then log the event into text file
							snprintf(testing, sizeof(logMessage), "WOD Action %d DC-01 [%d] TERMINATED",randCode, result);
							logger(testing);
						}
				}
				else
				{
					//do nothing
					
				}
		
			}
			//if the random number 3 , 6 , 13 (kill DC-02)
			else if(randCode == THREE || randCode == SIX || randCode == THIRTEEN)
			{
				//call function to get the process id 
				result = getProcessId(1,mList);
				
				//if process ID is grater than 0 that means the process is there
				if(result > 0)
				{
					//check if the process exists before killing it
					if((getpgid(result) != -1) &&  (status = kill(result,9)) == -1)
					{
						//when kill() fails exit
						return done=1;
					
					}
					//when kill() succeed
					if(status == 0)
					{
						//format then log the event into text file
						snprintf(logMessage, sizeof(logMessage), " %d DC-02 [%d] TERMINATED",randCode, result);
						logger(logMessage);
					}
				}
				else
				{
					//do nothing
					
				}
			}
			//if the random number 2 , 5 , 15 (kill DC-03)
			else if(randCode == TWO || randCode == FIVE || randCode == FIFTEEN)
			{
				//call function to get the process id 
				result = getProcessId(TWO,mList);
				
				//if process ID is grater than 0 that means the process is there
				if(result > 0)
				{
					//check if the process exists before killing it
					if((getpgid(result) != -1) &&  (status = kill(result,9)) == -1)
					{
						//when kill() fails exit
						return done=1;
					
					}
					//when kill() succeed
					if(status == 0)
					{
						//format then log the event into text file
						snprintf(logMessage, sizeof(logMessage), " %d DC-03 [%d] TERMINATED",randCode, result);
						logger(logMessage);
					}
				}
				else
				{
					//do nothing
					
				}
			}
			//if the random number 7 (kill DC-04)
			else if(randCode == SEVEN)
			{
				//call function to get the process id 
				result = getProcessId(THREE,mList);
				
				//if process ID is grater than 0 that means the process is there
				if(result > 0)
				{
				
					//check if the process exists before killing it
					if((getpgid(result) != -1) &&  (status = kill(result,9)) == -1)
					{
						//when kill() fails exit
						return done=1;
					
					}
					//when kill() succeed
					if(status == 0)
					{
						//format then log the event into text file
						snprintf(logMessage, sizeof(logMessage), " %d DC-04 [%d] TERMINATED",randCode, result);
						logger(logMessage);
					}
				}
				else
				{
					//do nothing
					
				}
			}
			//if the random number 9 (kill DC-05)
			else if(randCode == NINE)
			{
				//call function to get the process id 
				result = getProcessId(FOUR,mList);
				
				//if process ID is grater than 0 that means the process is there
				if(result > 0)
				{
				
					//check if the process exists before killing it
					if((getpgid(result) != -1) &&  (status = kill(result,9)) == -1)
					{
						//when kill() fails exit
						return done=1;
					
					}
					//when kill() succeed
					if(status == 0)
					{
						//format then log the event into text file
						snprintf(logMessage, sizeof(logMessage), " %d DC-05 [%d] TERMINATED",randCode, result);
						logger(logMessage);
					}
				}
				else
				{
					//do nothing
					
				}
			}
			//if the random number 12 (kill DC-06)
			else if(randCode ==TWELVE)
			{
				//call function to get the process id 
				result = getProcessId(FIVE,mList);

				//if process ID is grater than 0 that means the process is there
				if(result > 0)
				{
				
					//check if the process exists before killing it
					if((getpgid(result) != -1) &&  (status = kill(result,9)) == -1)
					{
						//when kill() fails exit
						return done=1;
					
					}
					//when kill() succeed
					if(status == 0)
					{
						//format then log the event into text file
						snprintf(logMessage, sizeof(logMessage), "%d DC-06 [%d] TERMINATED",randCode, result);
						logger(logMessage);
					}
				}
				else
				{
					//do nothing
					
				}
			}
			//if the random number 14 (kill DC-07)
			else if(randCode ==FOURTEEN)
			{
				//call function to get the process id 
				result = getProcessId(SIX,mList);
				
				//if process ID is grater than 0 that means the process is there
				if(result > 0)
				{

					//check if the process exists before killing it
					if((getpgid(result) != -1) &&  (status = kill(result,9)) == -1)
					{
						//when kill() fails exit
						return done=1;
					
					}
					//when kill() succeed
					if(status == 0)
					{
						//format then log the event into text file
						snprintf(logMessage, sizeof(logMessage), "%d DC-07 [%d] TERMINATED",randCode, result);
						logger(logMessage);
					}
				}
				else
				{
					//do nothing
					
				}
			}
			//if the random number 16 (kill DC-08)
			else if(randCode == SIXTEEN)
			{
				//call function to get the process id 
				result = getProcessId(SEVEN,mList);
				
				//if process ID is grater than 0 that means the process is there
				if(result > 0)
				{
				
					//check if the process exists before killing it
					if((getpgid(result) != -1) &&  (status = kill(result,9)) == -1)
					{
						//when kill() fails exit
						return done=1;
					
					}
					//when kill() succeed
					if(status == 0)
					{
						//format then log the event into text file
						snprintf(logMessage, sizeof(logMessage), "%d DC-08 [%d] TERMINATED", randCode, result);
						logger(logMessage);
					}
				}
				else
				{
					//do nothing
					 
				}
			}
			//if the random number 18 (kill DC-09)
			else if(randCode == EIGHTEEN)
			{
				//call function to get the process id 
				result = getProcessId(EIGHT,mList);
				
				//if process ID is grater than 0 that means the process is there
				if(result > 0)
				{
				
					//check if the process exists before killing it
					if((getpgid(result) != -1) &&  (status = kill(result,9)) == -1)
					{
						//when kill() fails exit
						return done=1;
					
					}
					//when kill() succeed
					if(status == 0)
					{
						//format then log the event into text file
						snprintf(logMessage, sizeof(logMessage), "%d DC-09 [%d] TERMINATED", randCode, result);
						logger(logMessage);
					}
				}
				else
				{
					//do nothing
					
				}
			}
			//if the random number 20 (kill DC-10)
			else if(randCode == TWENTY)
			{
				//call function to get the process id 
				result = getProcessId(NINE,mList);


				//if process ID is grater than 0 that means the process is there
				if(result > 0)
				{
				
					//check if the process exists before killing it
					if((getpgid(result) != -1) &&  (status = kill(result,9)) == -1)
					{
						//when kill() fails exit
						return done=1;
					
					}
					//when kill() succeed
					if(status == 0)
					{
						//format then log the event into text file
						snprintf(logMessage, sizeof(logMessage), "%d DC-10 [%d] TERMINATED",randCode, result);
						logger(logMessage);
					}
				}
				else
				{
					//do nothing
					
				}
			
				
			}
			//if the random number 10 , 17 delete msgQ
			else if(randCode == TEN || randCode == SEVENTEEN)
			{
				//delet msgQ and check it it succeed
				if(msgctl(messageId, IPC_RMID, (struct msqid_ds *)NULL) == -1)
				{
					
						printf("Error DELETE QUEUE\n");
						return done=1;
				}
				else
				{
					//format string and log the event to the text file
					snprintf(delMsg, sizeof(logMessage), " %s", deletionMsg);
					logger(delMsg);
				
				}

			}
		}
	
	}
	
	return 0;

}


/*	Name	:  pid_t getProcessId()
*  Purpose  :  this function is used to check if the DC process exists.
*  Inputs	:	int pIndex, MasterList *pID
*  Outputs	:	Nothing
*  Returns	:	it returns the process ID if it is exists, 0 otherwise.
*/
pid_t getProcessId(int pIndex, MasterList *pID)
{

	pid_t process = 0 ;
		
	//check the the process at the given index
	if(pID->dc[pIndex].dcProcessID != 0)
	{
		
		process = pID->dc[pIndex].dcProcessID;// get the process ID
		return process;//return it 
	}
	else
	{
		return process; //does not exisit
	}
		
}


////// ** ////////
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
	fp = fopen("/tmp/dataCorruptor.log", "a+");
	if(fp == NULL){
		printf("Cannot create logger file");
		exit(1);
		
	}
	
	//write the message to the log file
	fprintf(fp, "%s %s \n", timeStamp, message);
	//close the file
	fclose(fp);

}
