/*gcc -ansi -pedantic func_diary.c userDiary.c -o userDiary.out*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AD.h"
#include "meeting.h"

#define LOG_OUT_APPOINTMENTS '5'
#define TRUE 0
#define FALSE 1
int main(void)
{
	enum Error result;
	int size=2;
	int block_size=4;
	char index_diary='0';
	float start_meet,end_meet,_findStartMeeting;
	int room;
	int result_2;
	char nameFile[40] = ";";
	AD *ptr_ad=dynamic_AD_array_create(size,block_size);
	meeting *ptr_meeting=NULL;
	printf("Welcome to an appointment calendar\n");
	
	while(index_diary != LOG_OUT_APPOINTMENTS)
	{
		printf("Enter number: \n 1-To insert a meeting. \n 2-Print all appointments in a diary.\n 3-Find an existing appointment in the diary.\n 4-Remove appointment.\n 5-Log out appointments.\n 6- save the diary\n 7- copy diary save\n");
		scanf(" %c", &index_diary );
		switch(index_diary)
		{
			case '1':
					printf("Enter time start meeting:\n");
					scanf("%f", &start_meet );
					printf("Enter time end meeting:\n");
					scanf("%f", &end_meet);
					printf("Enter room meeting:\n");
					scanf("%d",&room);
					ptr_meeting= createMeeting(start_meet,end_meet,room);
					if(ptr_meeting != NULL)
					{
						result=insertMeeting(ptr_meeting,ptr_ad);
						if(result == OVERFLOW )
						{
							MeetingDestroy(ptr_meeting);
							printf("Dairy full\n");
							break;
						}
						else if(result == OK)
						{
							printf("Insert meeting succeeded\n");
							break;
						}
						else if(result == THE_TIME_NOT_GOOD)
						{
							MeetingDestroy(ptr_meeting);
							printf("Insert time between 0 antil 23.99\n");
							break;
						}
						else if(result == THE_DIARY_BUSY)
						{
							MeetingDestroy(ptr_meeting);
							printf("The diary is busy try leater\n");
							break;
						}
					}
					MeetingDestroy(ptr_meeting);
					printf("Failed to create meeting - please try again\n");
					break;
			case '2':
					AdPrint(ptr_ad);
					break;
			case '3':
					printf("Insert the time start to you want find\n");
					scanf("%f", &_findStartMeeting);
					result_2=FindAppointementInAD(ptr_ad,_findStartMeeting);
					if(result_2 == FALSE)
					{
						printf("NOT Find Meeting Try again\n");
					}
					printf("Find meeting\n");
					break;
			case '4':
					printf("Insert the time start to you want remove\n");
					scanf("%f", &_findStartMeeting);
					result=RemoveMeeting(ptr_ad,_findStartMeeting);
					if(result == UNDERFLOW )
					{
						printf("Not have meeting in diary\n");
						break;
					}
					else if(result == PARAMERET_NOT_GOOD)
					{
						printf("The time to start not good try angain\n");
						break;
					}
					else if(result == OK)
					{
						printf("The meeting remove\n");
						break;
					}
					printf("not succeeded remove meeting try again\n");
					
			case '5':
					printf("you sure you want destroy diary? if yes-1 if not-2\n");					
					scanf("%d",&result_2);
					if(result == 1)
					{
						AdDestroy(ptr_ad);
						printf("Destroy the diary\n");
					}
					break;
			case '6':
					printf("Enter name file you want\n");
					scanf(" %s",nameFile);
					result_2=SaveDiary(ptr_ad,nameFile);
					if(result_2 == FALSE)
					{
						printf("not sucsses to save\n");
					}
					printf("sucsses to save\n");
					break;
			case '7':
					printf("warring if you want not save cant delet your diary now\n if you want to contiue 1 else 2\n");					
					scanf("%d",&result_2);
					if(result == 1)
					{
						printf("Enter name file you want copy\n");
						scanf(" %s",nameFile);
						result_2=loadDiary(ptr_ad,nameFile);
						if(result_2 == FALSE)
						{
							printf("not sucsses to copy\n");
						}
						printf("sucsses to copy\n");
					}
					default:printf("The number entered is incorrect - re-type\n");

		}

	}




}
