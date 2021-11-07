#ifndef __meeting_h__
#define __meeting_h__
#define MAGICNUM 205984834
typedef struct meeting 
{
	float meeting_start;
	float meeting_end; 
	int meeting_room;
	int meeting_magic_num; 
}meeting;


/*
Discription:The function receives data from the user and checks if the data is good, and in addition returns a pointer to the meeting.
Input:void.
Output:Pointer to meeting.
Error:If the user did not enter a good start and end time and if no space was allocated for metting you will return NULL.
*/
/*meeting *createMeeting();*/
meeting *createMeeting(float start_meet,float end_meet,int room);




/*
Discription:free meeting to not insert to diary.
Input:pointer to meeting.
Output:NANE.
Error:NANE.
*/
void MeetingDestroy(meeting *ptr_meeting);




#endif /*#ifndef __meeting_h__ */
