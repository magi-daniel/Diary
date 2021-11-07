#include "meeting.h"
#define MAGICNUM 205984834

typedef struct AD 
{
	meeting **ad_ptr_meeting;
	int ad_size;
	int ad_block_size; 
	int ad_num_of_elements;
	int ad_magic_num; 
	int ad_status_meeting;
}AD;

enum Error
{
	OK,
	PARAMERET_NOT_GOOD,
	THE_TIME_NOT_GOOD,
	POINTER_NOT_INTIALIZED,
	RECALOC_FAILE,
	UNDERFLOW,
	OVERFLOW,
	THE_DIARY_BUSY
};
/*
Discription:The function gets space to allocate and also how much it is willing to allocate each time and it allocates the AD.
Input:size, block size
Output:The function returns an assigned AD
Error:The function returns NULL if we did not get proper parameters or if we could not assign the array.
*/
AD *dynamic_AD_array_create(int size, int block_size);




/*
Discription:the function get diary and receives a meeting and insert to diary.
Input:meeting and AD
Output:if the meeting insert return OK
Error:if not have a place in AD return OVERFLOW.
	if not succeeded to do realloc return RECALOC_FAILE.
	if the time the meeting not good return THE_TIME_NOT_GOOD.
	if pointer not good return POINTER_NOT_INTIALIZED.
	if have a meeting in diary not Checkered return THE_DIARY_BUSY
*/
/*int insertMeeting(meeting *ptr_meeting, AD *ptr_ad);*/
enum Error insertMeeting(meeting *ptr_meeting, AD *ptr_ad);

/*
Discription:free the pointers to diary.
Input:get pointer to diary.
Output:NANE.
Error:NANE.
*/
void AdDestroy(AD *ptr_ad);

/*
Discription:print all the meting in this day.
Input:get pointer to diary.
Output:NANE.
Error:NANE.
*/
void AdPrint(AD *ptr_ad);



/*
Discription:the func return TRUE if find meeting or FALSE withe the time start meeting.
Input:get a diary and time start meeting
Output:TRUE if find the meeting
Error:FALSE if not have a meeting in day and this start meeting not find.
	if the time to start not good return FALSE
	if pointer to AD NULL return FALSE.
*/
int FindAppointementInAD(AD *ptr_ad, float _findStartMeeting);





/*
Discription:remove the meeting in the time the user get.
Input:get a diary and time start meeting.
Output:return OK if succeeded.
Error:if the time entr not good return PARAMERET_NOT_GOOD.
if pointer to AD NULL return POINTER_NOT_INTIALIZED.
if not have meeting return UNDERFLOW.
if not have this meeting in a diary return THE_TIME_NOT_GOOD.
*/
enum Error RemoveMeeting(AD *ptr_ad,float _findStartMeeting);




/*
Discription:save the meeting white file.
Input:get a diary white meeting and name.
Output:to do file white save the meeting
Error:if the open not sucsses return FALSE;
*/
int SaveDiary(AD *ptr_ad,char* nameFile);




/*
load distroy all the diary you not save.
Discription:get name the file and copy to user.
Input:name file and diary.
Output:NANE.
Error:if open not sucsses return false and if not can to insert the meeting return FALSE.
*/
int loadDiary(AD *ptr_ad,char* nameFile);




/*
Discription:print the n line to end 
Input:n line to print.
Output:NANE.
Error:if open not sucsses return false.
*/
int PrintTail(int n);
