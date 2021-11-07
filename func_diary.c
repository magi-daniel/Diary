#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AD.h"
#include "meeting.h"
#define MAGICNUM 205984834
#define MINIMUN_TIME_FOR_MEETING 0.01
#define START_DAY 0
#define END_DAY 23.99
#define NOT_HAVE_A_PLACE_IN_THIS_TIME -1
#define NOT_HAVE_THIS_MEETING -1
#define TRUE 0
#define FALSE 1
#define NOT_AVAILABLE 0 
#define AVAILABLE 1
#define SIZE_LINE 100
/*help func*/
enum Error cheak_parameter_AD_create(int size, int block_size);
enum Error cheak_parameter_createMeeting(float start_meet,float end_meet);
enum Error cheak_parameter_insert(meeting *ptr_meeting, AD *ptr_ad);
enum Error increase(AD *ptr_ad);
int sort(meeting *ptr_meeting, AD *ptr_ad);
enum Error shiftRigth( AD *ptr_ad,int index);
int CheakParameterFind(AD *ptr_ad, float _findStartMeeting);
enum Error CheakParameterRemove(AD *ptr_ad, float _findStartMeeting);
int FindIndexMeeting(AD *ptr_ad, float _findStartMeeting);
enum Error shiftToLeft( AD *ptr_ad,int index);
enum Error getMagicNum(AD *ptr_ad,int *magicNum);
enum Error getNumberOfElement(AD *ptr_ad,int *numberOfElement);

AD *dynamic_AD_array_create(int size, int block_size)
{
	meeting **ptr_meeting=NULL;
	AD *ptr_ad_struct=NULL;
	if(cheak_parameter_AD_create(size,block_size)!=OK)
	{	
		return NULL;
	}

	ptr_ad_struct =(AD*)malloc(sizeof(AD));
	if(ptr_ad_struct == NULL)
	{
		return NULL;
	} 
	ptr_meeting=(meeting**)malloc(size* sizeof(meeting*));
	if(ptr_meeting == NULL)
	{
		free(ptr_ad_struct);
		return NULL;
	}	
	ptr_ad_struct -> ad_ptr_meeting= ptr_meeting;
	ptr_ad_struct -> ad_size = size;
	ptr_ad_struct -> ad_num_of_elements = 0;
	ptr_ad_struct -> ad_block_size = block_size;
	ptr_ad_struct -> ad_magic_num = MAGICNUM;
	ptr_ad_struct -> ad_status_meeting=AVAILABLE;
	return ptr_ad_struct;
}

/*meeting *createMeeting()*/
meeting *createMeeting(float start_meet,float end_meet,int room )
{
	meeting *ptr_meeting=NULL;
	if(cheak_parameter_createMeeting(start_meet,end_meet) != OK)
	{
		return NULL;
	}
	ptr_meeting =(meeting*)malloc(sizeof(meeting));
	if(ptr_meeting == NULL)
	{
		return NULL;
	}
	ptr_meeting -> meeting_start = start_meet;
	ptr_meeting -> meeting_end = end_meet;
	ptr_meeting -> meeting_room = room;
	return ptr_meeting;
} 

enum Error insertMeeting(meeting *ptr_meeting, AD *ptr_ad)
{
	int index;
	enum Error result;
	if(ptr_ad ->ad_status_meeting == NOT_AVAILABLE)
	{
		return THE_DIARY_BUSY;
	}
	ptr_ad ->ad_status_meeting=NOT_AVAILABLE;
	if((result=cheak_parameter_insert(ptr_meeting, ptr_ad)) != OK) /*cheak parameter */
	{
		ptr_ad ->ad_status_meeting=AVAILABLE;		
		return result;
	}
	if((ptr_ad -> ad_size) == (ptr_ad -> ad_num_of_elements)) /*if not have a place*/
	{
		if ((result = increase(ptr_ad)) != OK) 
		{			
			ptr_ad ->ad_status_meeting=AVAILABLE;			
			return result;
		}
	}
	
	if((ptr_ad -> ad_num_of_elements) != 0)
	{
		index=sort(ptr_meeting,ptr_ad);/*sort*/
		if (index < 0)
		{		
			ptr_ad ->ad_status_meeting=AVAILABLE;
			return THE_TIME_NOT_GOOD;
		}		
		shiftRigth(ptr_ad,index);	/*shiftRigth*/	
	}
	else
	{
		index=0; /*if not have a element in diary*/
	}
	(ptr_ad -> ad_ptr_meeting[index])=(ptr_meeting); /*enter,insert*/
	(ptr_ad -> ad_num_of_elements)++;
	ptr_ad ->ad_status_meeting=AVAILABLE;
	return OK;
}

void AdDestroy(AD *ptr_ad)
{
	int i;
	if(( ptr_ad != NULL) && (MAGICNUM == (ptr_ad -> ad_magic_num)))
	{
		for(i=0; i < ptr_ad -> ad_num_of_elements; i++)
		{
			if(ptr_ad -> ad_ptr_meeting[i] != NULL)
			{
				free(ptr_ad -> ad_ptr_meeting[i]);	
			}
		}
		(ptr_ad -> ad_magic_num) =0;
		free(ptr_ad);
	}
}

void AdPrint(AD *ptr_ad)
{
	int i;
	if( ptr_ad != NULL)
	{
		if(0 == ptr_ad -> ad_num_of_elements)
		{
			printf("not have a meeting in this day\n");
		}
		else
		{
			for(i=0; i < ptr_ad -> ad_num_of_elements; i++)
			{
				printf("MEETING: %d \n", i);
				printf("Start meeting: %.2f\n", ptr_ad -> ad_ptr_meeting[i] -> meeting_start);
				printf("End meeting: %.2f\n", ptr_ad -> ad_ptr_meeting[i] -> meeting_end);
				printf("Room meeting: %d\n", ptr_ad -> ad_ptr_meeting[i] -> meeting_room);
			}
		}
		
	}
}


int FindAppointementInAD(AD *ptr_ad, float _findStartMeeting)
{
	int i;
	if(CheakParameterFind(ptr_ad, _findStartMeeting) == FALSE)
	{
		return FALSE;
	}			
	for(i=0; i < ptr_ad -> ad_num_of_elements; i++)
	{	
		if(_findStartMeeting == (ptr_ad -> ad_ptr_meeting[i] -> meeting_start))
		{
			return TRUE;
		}
	}
	return FALSE;
}

enum Error RemoveMeeting(AD *ptr_ad,float _findStartMeeting)
{
	int i;
	int index;
	enum Error result=CheakParameterRemove(ptr_ad, _findStartMeeting);
	if(OK != result)
	{
		return result;
	}	
	index=FindIndexMeeting(ptr_ad, _findStartMeeting);
	if (0 > index)
	{
		return THE_TIME_NOT_GOOD;
	}
	shiftToLeft(ptr_ad, index);
	(ptr_ad -> ad_num_of_elements)--;
	return OK;	
}



void MeetingDestroy(meeting *ptr_meeting)
{
	int i;
	if( ptr_meeting == NULL || ptr_meeting -> meeting_magic_num != MAGICNUM)
	{
		return;
	}
	free(ptr_meeting);
}


/*help func*/

enum Error cheak_parameter_AD_create(int size, int block_size)
{
	if (size <= 0 || block_size < 0 )
	{
		return PARAMERET_NOT_GOOD;
	}
	if(size == 0 && block_size == 0)
	{
		return PARAMERET_NOT_GOOD;
	}
	return OK;
}


enum Error cheak_parameter_createMeeting(float start_meet,float end_meet)
{
	if(start_meet < START_DAY)
	{
		return THE_TIME_NOT_GOOD;
	}
	if(end_meet > END_DAY)
	{
		return THE_TIME_NOT_GOOD;
	}
	if(start_meet > end_meet)
	{	
		return THE_TIME_NOT_GOOD;
	}
	if((end_meet - start_meet) < MINIMUN_TIME_FOR_MEETING)
	{
		return THE_TIME_NOT_GOOD;
	}
	return OK;
	
}

enum Error cheak_parameter_insert(meeting *ptr_meeting, AD *ptr_ad)
{
	if(ptr_meeting == NULL)
	{
		return POINTER_NOT_INTIALIZED;
	}
	if(ptr_ad == NULL || (ptr_ad -> ad_ptr_meeting) == NULL)
	{
		return POINTER_NOT_INTIALIZED;
	}
	if((ptr_ad -> ad_size) < 0 || (ptr_ad -> ad_num_of_elements) < 0 )
	{	
		return PARAMERET_NOT_GOOD;
	}
	if((ptr_ad -> ad_size) < (ptr_ad -> ad_num_of_elements))
	{
		return PARAMERET_NOT_GOOD;
	}
	return OK;
}

enum Error increase(AD *ptr_ad)
{
	meeting **temp;
	if((ptr_ad -> ad_block_size) <= 0)
	{
		return OVERFLOW;
	}
	/*realloc*/
	temp=realloc((ptr_ad -> ad_ptr_meeting),((ptr_ad -> ad_size)+(ptr_ad -> ad_block_size))*(sizeof(meeting*))); 
	if(temp == NULL)
	{
		return RECALOC_FAILE;
	}
	(ptr_ad -> ad_size)=((ptr_ad -> ad_size)+(ptr_ad -> ad_block_size));
	(ptr_ad -> ad_ptr_meeting)=temp;		
	return OK;
}

int sort(meeting *ptr_meeting, AD *ptr_ad)
{	
	int i;
	int index;
	if ((ptr_ad -> ad_ptr_meeting[(ptr_ad -> ad_num_of_elements)-1] -> meeting_end) < (ptr_meeting -> meeting_start)) /*if in end*/
	{
		index= (ptr_ad -> ad_num_of_elements);	
		return index;
	}
	if((ptr_meeting -> meeting_end) < (ptr_ad -> ad_ptr_meeting[0] -> meeting_start))/*if in first, start*/
	{
		index =0;
		return index;
	}		

	for(i=0;i<((ptr_ad -> ad_num_of_elements)-1);i++)
	{
		if ((ptr_ad -> ad_ptr_meeting[i] -> meeting_end) < (ptr_meeting -> meeting_start))
		{
			if((ptr_meeting -> meeting_end) < (ptr_ad -> ad_ptr_meeting[i+1] -> meeting_start) )
			{
				index= i+1;
				return index;
			}
		}
	}
	return NOT_HAVE_A_PLACE_IN_THIS_TIME;
}

enum Error shiftRigth( AD *ptr_ad,int index)
{
	int i;
	for(i=(ptr_ad -> ad_num_of_elements);i>index;i--)
	{
		(ptr_ad -> ad_ptr_meeting[i])=(ptr_ad -> ad_ptr_meeting[i-1]);
		return OK;
	}
}


int CheakParameterFind(AD *ptr_ad, float _findStartMeeting)
{
	if(ptr_ad == NULL)
	{
		return FALSE;	
	}
	if(START_DAY > _findStartMeeting && END_DAY < _findStartMeeting )
	{
		return FALSE;
	}
	return TRUE;
}

enum Error CheakParameterRemove(AD *ptr_ad, float _findStartMeeting)
{
	if(ptr_ad == NULL)
	{
		return POINTER_NOT_INTIALIZED;	
	}
	if(START_DAY > _findStartMeeting && END_DAY < _findStartMeeting )
	{
		return PARAMERET_NOT_GOOD;
	}
	if(0 >= ptr_ad -> ad_num_of_elements)
	{
		return UNDERFLOW;
	}
	return OK;
}


int FindIndexMeeting(AD *ptr_ad, float _findStartMeeting)
{
	int i;
	for(i=0; i < ptr_ad -> ad_num_of_elements; i++)
	{	
		if(_findStartMeeting == (ptr_ad -> ad_ptr_meeting[i] -> meeting_start))
		{
			return i;
		}
	}
	return NOT_HAVE_THIS_MEETING;
}

enum Error shiftToLeft( AD *ptr_ad,int index)
{
	int i;
	for(i=index; i<(ptr_ad -> ad_num_of_elements)-1; i++)
	{
		(ptr_ad -> ad_ptr_meeting[i])=(ptr_ad -> ad_ptr_meeting[i+1]);
		return OK;
	}
}


enum Error getMagicNum(AD *ptr_ad,int *magicNum)
{
	*magicNum= ptr_ad -> ad_magic_num;
	return OK;
}

enum Error getNumberOfElement(AD *ptr_ad,int *numberOfElement)
{
	*numberOfElement= ptr_ad -> ad_num_of_elements;
	return OK;
}




int SaveDiary(AD *ptr_ad, char* nameFile)
{
	int i;
	FILE *fp;
	fp=fopen( nameFile,"w");
	if(fp == NULL)
	{
		return FALSE;
	}
	for(i=0; i<ptr_ad -> ad_num_of_elements; i++)
	{
		fprintf(fp,"%f %f %d \n", ptr_ad -> ad_ptr_meeting[i] -> meeting_start, ptr_ad -> ad_ptr_meeting[i] -> meeting_end, ptr_ad -> ad_ptr_meeting[i] -> meeting_room);
	}
	fclose(fp);
}

int loadDiary(AD *ptr_ad,char* nameFile)
{
	int i;
	float start_meet;
	float end_meet;	
	int room;
	FILE *fp1;
	meeting *ptr_meeting=NULL;
	enum Error result;
	fp1=fopen( nameFile,"r");
	if(fp1 == NULL)
	{
		return FALSE;
	}
	fscanf(fp1,"%f%f%d",&start_meet,&end_meet,&room);
	while(!feof(fp1))
	{
		ptr_meeting=createMeeting(start_meet,end_meet,room );
		result=insertMeeting(ptr_meeting,ptr_ad);
		if(result != OK)
		{
			return FALSE;
			fclose(fp1);
		}
		fscanf(fp1,"%f%f%d",&start_meet,&end_meet,&room);
	}
	fclose(fp1);
}

int PrintTail(int n)
{
	char string[1000];
	int count=0;
	int temp;
	FILE *fp1;
	fp1=fopen( "AD.h","r");
	if(fp1 == NULL)
	{
		return FALSE;
	}
	fseek(fp1,0, SEEK_END);
	temp=0;
	while(ftell(fp1) != 0 && count < n+1)
	{
		fseek(fp1,temp--, SEEK_END);
		if(fgetc(fp1) == '\n')
		{
			count++;
		}
	}
	fgets(string,1001,fp1);
	while(!feof(fp1))
	{
		/*puts(string);	*/
		printf("%s",string);		
		fgets(string,1001,fp1);
		
	}
	fclose(fp1);
}
/*
int PrintTailNew(int n)
{
	int i=0;
	char string[1000];
	int count=0;
	int *arr=(size_t*)malloc(n*sizeof(size_t));
	int temp= (n*SIZE_LINE)*(2);
	FILE *fp1;
	fp1=fopen( "AD.h","r");
	if(fp1 == NULL)
	{
		return FALSE;
	}
	fseek(fp1,-temp, SEEK_END);
	while(!feof(fp1))
	{
		fgets(fp1/*todo*/ 
/*		i=(i+1)/n; /*todo arr tikli*/
/*		arr[i]=
		count++;
	}
	if(count == n)
	{
		arr[n-1]/*print*/
/*	} 
	
	fgets(string,1001,fp1);
	while(!feof(fp1))
	{
		/*puts(string);	*/
/*		printf("%s",string);		
		fgets(string,1001,fp1);
		
	}
	fclose(fp1);
}

*/













