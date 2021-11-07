#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AD.h"
#include "meeting.h"
#define MAGICNUM 205984834
#define TRUE 0
#define FALSE 1

int main(void)
{
	
	/*creat AD*/
	Test_1();
	Test_2();
	Test_3();
	Test_4();
	/*creat Meeting*/
	Test_5();
	Test_6();
	Test_7();
	Test_8();
	Test_9();
	/*destroy*/
	Test_10();
	Test_11();
	Test_12();
	Test_13();
	/*insert*/
	Test_14();
	Test_15();
	Test_16();
	Test_17();
	/*find*/
	Test_18();
	Test_19();
	Test_20();
	Test_21();
	/*remove*/
	Test_22();
	Test_23();
	Test_24();
	Test_25();
	
	PrintTail(7);
}
/*creat AD*/
int Test_1()
{
	/*cheak if creat AD working*/
	int size=2;
	int block_size=4;
	AD *ptr_ad=dynamic_AD_array_create(size,block_size);
	if(NULL != ptr_ad)
	{
		printf("Test 1: PASS\n");
	}
	else
	{
		printf("Test 1: FAIL\n");
	}
	AdDestroy(ptr_ad);
}

int Test_2()
{
	/*cheak if creat AD size =0 and blockSize=0*/
	int size=0;
	int block_size=0;
	AD *ptr_ad=dynamic_AD_array_create(size,block_size);
	if(NULL == ptr_ad)
	{
		printf("Test 2: PASS\n");
	}
	else
	{
		printf("Test 2: FAIL\n");
	}
	AdDestroy(ptr_ad);
}

int Test_3()
{
	/*cheak if creat AD  blockSize<0*/
	int size=3;
	int block_size=-1;
	AD *ptr_ad=dynamic_AD_array_create(size,block_size);
	if(NULL == ptr_ad)
	{
		printf("Test 3: PASS\n");
	}
	else
	{
		printf("Test 3: FAIL\n");
	}
	AdDestroy(ptr_ad);
}
int Test_4()
{
	/*cheak if creat AD size <0 */
	int size=-1;
	int block_size=3;
	AD *ptr_ad=dynamic_AD_array_create(size,block_size);
	if(NULL == ptr_ad)
	{
		printf("Test 4: PASS\n");
	}
	else
	{
		printf("Test 4: FAIL\n");
	}
	AdDestroy(ptr_ad);
}
/*creat meeting*/
int Test_5()
{
	/*cheak if creat meeting working*/
	float start_meet= 12;
	float end_meet=13;
	int room=4;
	AD *ptr_ad=dynamic_AD_array_create(2,4);
	meeting *ptr_meeting= createMeeting(start_meet,end_meet,room);
	if(NULL != ptr_meeting)
	{
		printf("Test 5: PASS\n");
	}
	else
	{
		printf("Test 5: FAIL\n");
	}
	AdDestroy(ptr_ad);
}
int Test_6()
{
	/*cheak if creat meeting start_meet < 0 */	
	float start_meet= -1;
	float end_meet=13;
	int room=4;
	AD *ptr_ad=dynamic_AD_array_create(2,4);
	meeting *ptr_meeting= createMeeting(start_meet,end_meet,room);
	if(NULL == ptr_meeting)
	{
		printf("Test 6: PASS\n");
	}
	else
	{
		printf("Test 6: FAIL\n");
	}
	AdDestroy(ptr_ad);
}

int Test_7()
{
	/*cheak if creat meeting end_meet > 23.99 */	
	float start_meet= 10;
	float end_meet=24;
	int room=4;
	AD *ptr_ad=dynamic_AD_array_create(2,4);
	meeting *ptr_meeting= createMeeting(start_meet,end_meet,room);
	if(NULL == ptr_meeting)
	{
		printf("Test 7: PASS\n");
	}
	else
	{
		printf("Test 7: FAIL\n");
	}
	AdDestroy(ptr_ad);
}

int Test_8()
{
	/*cheak if creat meeting start_meet > end_meet */	
	float start_meet= 13;
	float end_meet=12;
	int room=4;
	AD *ptr_ad=dynamic_AD_array_create(2,4);
	meeting *ptr_meeting= createMeeting(start_meet,end_meet,room);
	if(NULL == ptr_meeting)
	{
		printf("Test 8: PASS\n");
	}
	else
	{
		printf("Test 8: FAIL\n");
	}
	AdDestroy(ptr_ad);
}

int Test_9()
{
	/*cheak if creat meeting end_meet - start_meet) < MINIMUN_TIME_FOR_MEETING */	
	float start_meet= 13;
	float end_meet=13;
	int room=4;
	AD *ptr_ad=dynamic_AD_array_create(2,4);
	meeting *ptr_meeting= createMeeting(start_meet,end_meet,room);
	if(NULL == ptr_meeting)
	{
		printf("Test 9: PASS\n");
	}
	else
	{
		printf("Test 9: FAIL\n");
	}
	AdDestroy(ptr_ad);
}
/*destroy*/
int Test_10()
{
	/*destroy free 1*/
	AD *ptr_ad=dynamic_AD_array_create(2,4);
	meeting *ptr_meeting= createMeeting(10,12,2);
	insertMeeting(ptr_meeting,ptr_ad);
	AdDestroy(ptr_ad);
	printf("test 10: PASS\n");
}

int Test_11()
{
	/*destroy free 2*/
	AD *ptr_ad=dynamic_AD_array_create(2,4);
	meeting *ptr_meeting= createMeeting(10,12,2);
	insertMeeting(ptr_meeting,ptr_ad);
	AdDestroy(ptr_ad);
	AdDestroy(ptr_ad);
	printf("test 11: PASS\n");
}


int Test_12()
{
	/*destroy the magic num*/
	int magicNum;
	AD *ptr_ad=dynamic_AD_array_create(2,4);
	meeting *ptr_meeting= createMeeting(10,12,2);
	insertMeeting(ptr_meeting,ptr_ad);
	AdDestroy(ptr_ad);
	getMagicNum(ptr_ad,&magicNum);
	if(0 != magicNum)
	{
		printf("test 12: FAIL\n");
	}
	else
	{
		printf("test 12: PASS\n");
	}
}
int Test_13()
{
	/*destroy more then one meeting*/
	AD *ptr_ad=dynamic_AD_array_create(2,4);
	meeting *ptr_meeting= createMeeting(10,12,2);
	insertMeeting(ptr_meeting,ptr_ad);
	ptr_meeting= createMeeting(13,14,2);
	insertMeeting(ptr_meeting,ptr_ad);
	ptr_meeting= createMeeting(15,16,2);
	insertMeeting(ptr_meeting,ptr_ad);
	AdDestroy(ptr_ad);
	printf("test 13: PASS\n");
}

/*insert*/
int Test_14()
{
	/*cheak if insert working*/
	enum Error result;
	AD *ptr_ad=dynamic_AD_array_create(2,4);
	meeting *ptr_meeting= createMeeting(10,12,2);
	if(result=insertMeeting(ptr_meeting,ptr_ad) == OK)
	{
		printf("test 14: PASS\n");
	}
	else
	{
		printf("test 14: FAIL\n");
	}
	AdDestroy(ptr_ad);
}

int Test_15()
{
	/*cheak if insert working if block size 0*/
	enum Error result;
	AD *ptr_ad=dynamic_AD_array_create(1,0);
	meeting *ptr_meeting= createMeeting(10,12,2);
	insertMeeting(ptr_meeting,ptr_ad);
	ptr_meeting= createMeeting(13,14,2);
	if(result=insertMeeting(ptr_meeting,ptr_ad) == OVERFLOW)
	{
		printf("test 15: PASS\n");
	}
	else
	{
		printf("test 15: FAIL\n");
	}
	AdDestroy(ptr_ad);
}
int Test_16()
{
	/*insert 2 meeting in indentical time*/
	enum Error result;
	AD *ptr_ad=dynamic_AD_array_create(2,4);
	meeting *ptr_meeting= createMeeting(10,12,2);
	insertMeeting(ptr_meeting,ptr_ad);
	ptr_meeting= createMeeting(10,12,2);
	if(result=insertMeeting(ptr_meeting,ptr_ad) == THE_TIME_NOT_GOOD )
	{
		printf("test 16: PASS\n");
	}
	else
	{
		printf("test 16: FAIL\n");
	}
	MeetingDestroy(ptr_meeting);
	AdDestroy(ptr_ad);
}

int Test_17()
{
	/*insert cheak if insert in good place(left rigth)*/
	enum Error result;
	AD *ptr_ad=dynamic_AD_array_create(2,4);
	meeting *ptr_meeting= createMeeting(10,12,2);
	insertMeeting(ptr_meeting,ptr_ad);
	ptr_meeting= createMeeting(8,9,2);
	if(result=insertMeeting(ptr_meeting,ptr_ad) == OK)
	{
		printf("test 17: PASS\n");
	}
	else
	{
		printf("test 17: FAIL\n");
	}	
	AdDestroy(ptr_ad);
}


/*find*/
int Test_18()
{
	/*if find the meeting*/
	int result;
	AD *ptr_ad=dynamic_AD_array_create(2,4);
	meeting *ptr_meeting= createMeeting(10,12,2);
	insertMeeting(ptr_meeting,ptr_ad);
	if(result=FindAppointementInAD(ptr_ad, 10) == TRUE)
	{
		printf("test 18: PASS\n");
	}
	else
	{
		printf("test 18: FAIL\n");
	}
	AdDestroy(ptr_ad);
}


int Test_19()
{
	/*cheak if find in NULL pointer*/
	int result;
	AD *ptr_ad=dynamic_AD_array_create(2,4);
	meeting *ptr_meeting= createMeeting(10,12,2);
	insertMeeting(ptr_meeting,ptr_ad);
	if(result=FindAppointementInAD(NULL, 10) == FALSE)
	{
		printf("test 19: PASS\n");
	}
	else
	{
		printf("test 19: FAIL\n");
	}
	AdDestroy(ptr_ad);
}

int Test_20()
{
	/*cheak if the time to find good*/
	int result;
	AD *ptr_ad=dynamic_AD_array_create(2,4);
	meeting *ptr_meeting= createMeeting(10,12,2);
	insertMeeting(ptr_meeting,ptr_ad);
	if(result=FindAppointementInAD(ptr_ad, 25) == FALSE)
	{
		printf("test 20: PASS\n");
	}
	else
	{
		printf("test 20: FAIL\n");
	}
	AdDestroy(ptr_ad);
}

int Test_21()
{
	/*cheak if the time to in the AD*/
	int result;
	AD *ptr_ad=dynamic_AD_array_create(2,4);
	meeting *ptr_meeting= createMeeting(10,12,2);
	insertMeeting(ptr_meeting,ptr_ad);
	if(result=FindAppointementInAD(ptr_ad, 12) == FALSE)
	{
		printf("test 21: PASS\n");
	}
	else
	{
		printf("test 21: FAIL\n");
	}
	AdDestroy(ptr_ad);
}

/*remove*/
int Test_22()
{
	/*cheak the numberOfElement in remove is good*/
	int numberOfElement;
	AD *ptr_ad=dynamic_AD_array_create(2,4);
	meeting *ptr_meeting= createMeeting(10,12,2);
	insertMeeting(ptr_meeting,ptr_ad);
	RemoveMeeting(ptr_ad,10);
	numberOfElement=getNumberOfElement(ptr_ad,&numberOfElement);
	if(0 == numberOfElement)
	{
		printf("test 22: PASS\n");
	}
	else
	{
		printf("test 22: FAIL\n");
	}
	AdDestroy(ptr_ad);
}
int Test_23()
{
	/*cheak if the remove working*/
	enum Error result;
	AD *ptr_ad=dynamic_AD_array_create(2,4);
	meeting *ptr_meeting= createMeeting(10,12,2);
	insertMeeting(ptr_meeting,ptr_ad);
	result =RemoveMeeting(ptr_ad,10);
	if(OK == result)
	{
		printf("test 23: PASS\n");
	}
	else
	{
		printf("test 23: FAIL\n");
	}
	AdDestroy(ptr_ad);	
}

int Test_24()
{
	/*cheak if the remove working whit pointer NULL*/
	enum Error result;
	AD *ptr_ad=dynamic_AD_array_create(2,4);
	meeting *ptr_meeting= createMeeting(10,12,2);
	insertMeeting(ptr_meeting,ptr_ad);
	result =RemoveMeeting(NULL,10);
	if(POINTER_NOT_INTIALIZED == result)
	{
		printf("test 24: PASS\n");
	}
	else
	{
		printf("test 24: FAIL\n");
	}	
	AdDestroy(ptr_ad);
}



int Test_25()
{
	/*cheak if not have what to remove */
	enum Error result;
	AD *ptr_ad=dynamic_AD_array_create(2,4);
	result =RemoveMeeting(ptr_ad,10);
	if(UNDERFLOW == result)
	{
		printf("test 25: PASS\n");
	}
	else
	{
		printf("test 25: FAIL\n");
	}
	AdDestroy(ptr_ad);	
}


