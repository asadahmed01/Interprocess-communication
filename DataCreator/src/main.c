/*
* FILE           : main.c
* PROGRAMMERs    : Mohammed Abusultan && Asad ahmad
* FIRST VERSION  : 2021 - 03 - 27
* DESCRIPTION    : this program is used to act like client and send random codes to server. each codes indecates the status of the machine.
*		   after sending a message the program is going to sleep for a number of seconds between 10 - 30. 
*                
*  
*/

#include "../inc/dataCreator.h"

int main (void)
{
	//calling function to establish connection
	establishCon();
	return 0;
}
