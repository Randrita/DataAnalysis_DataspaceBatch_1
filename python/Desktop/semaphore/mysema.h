/*---------------------------------------------------------------------
* File Name: sema.h
* Functions:
*
*    int semGet(key_t semkey, int mem_no);
*    int removeSem(int semid);
*    int setVal(int semid, int semnum, int semval);
*    int getVal(int semid, int semnum);
*    void lock(int semid, int semnum);
*    void unlock(int semid, int semnum);
*
*--------------------------------------------------------------------*/
#ifndef SEMA_H
#define SEMA_H

#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>

#define SEMKEY 150
#define PERM 0666

union semun
{
int val;
struct semid_ds *buf;
ushort *array;
};

/*---------------------------------------------------------------------
* Function Name: semGet
* Objective: creates a semaphore array
* In Parameters: 1. semaphore key (key_t [int])
*                2. number of members in the semaphore array (int)
* Return Values: semaphore id (int)
*                -1 -> failure
* Other Variables Changed or Used: None
*
* Warning (To be taken into account when modifying): None
*--------------------------------------------------------------------*/

int semGet(key_t semkey, int mem_no)
{
    int semid;

    if((semid=semget(semkey, mem_no, IPC_CREAT|PERM))==-1)
    {
        //printf("\ncan't get semaphore (key = %d)",SEMKEY);
        //fflush(stdout);
    }
    else
    {
        //printf("\ngot semaphore successfully (id = %d)",semid);
        //fflush(stdout);
    }
    return(semid);
}

/*---------------------------------------------------------------------
* Function Name: removeSem
* Objective: removes a semaphore array
* In Parameters: 1. semaphore id (int)
* Return Values: -1 -> failure
*                 1 -> success
* Other Variables Changed or Used: None
*
* Warning (To be taken into account when modifying): None
*--------------------------------------------------------------------*/

int removeSem(int semid)
{
    int retval;

    if((retval=semctl(semid, 0, IPC_RMID, 0))==-1)
    {
        //printf("\ncan't remove semaphore");
        //fflush(stdout);
    }
    else
    {
        //printf("\nsemaphore (id = %d) removed successfully",semid);
        //fflush(stdout);
    }
    return(retval);
}

/*---------------------------------------------------------------------
* Function Name: setVal
* Objective: sets value to a semaphore
* In Parameters: 1. semaphore id (int)
*                2. semaphore number within the array (int)
*                3. the value (int)
* Return Values: 1 -> success
*               -1 -> failure
* Other Variables Changed or Used: None
*
* Warning (To be taken into account when modifying): None
*--------------------------------------------------------------------*/

int setVal(int semid, int semnum, int semval)
{
    int retval;
    union semun arg;

    arg.val=semval;
    if((retval=semctl(semid, semnum, SETVAL, arg))==-1)
    {
        /*
        printf("\ncan't set %dth memeber of semaphore set (id = %d) 
                           to %d",semnum, semid, semval);
        fflush(stdout);
        */
    }
    else
    {
        /*
        printf("\nset %dth memeber of semaphore set (id = %d) to %d",
                                     semnum, semid, semval);
        fflush(stdout);
        */
    }
    return(retval);
}

/*---------------------------------------------------------------------
* Function Name: getVal
* Last Modified:
* Objective: read the value of a semaphore
* In Parameters: 1. semaphore id
*                2. semaphore number within the semaphore array
* Return Values: semaphore value (int)
* Other Variables Changed or Used: None
*
* Warning (To be taken into account when modifying): None
*--------------------------------------------------------------------*/

int getVal(int semid, int semnum)
{
    int retval;
    union semun arg;
    if((retval=semctl(semid, semnum, GETVAL, 0))==-1)
    {
        /*
        printf("\ncan't get value of %dth member of semaphore set 
                                          (id = %d)", semnum, semid);
        fflush(stdout);
        */
    }
    else
    {
        /*
        printf("\nvalue of %dth member of semaphore set (
                             id = %d) = %d", semnum, semid, retval);
        fflush(stdout);
        */
    }
    return(retval);
}

/*---------------------------------------------------------------------
* Function Name: lock
* Objective: decrement a semaphore value, the calling process blocks
*            if the semaphore value cannot be decremented
* In Parameters: 1. semaphore id (int)
*                2. semaphore number (int)
* Return Values: None
* Other Variables Changed or Used: None
*
* Warning (To be taken into account when modifying): None
*--------------------------------------------------------------------*/

void lock(int semid, int semnum)
{
    struct sembuf semoparray[1];

    semoparray[0].sem_num=semnum;
    semoparray[0].sem_op=-1;
    semoparray[0].sem_flg=0;

    semop(semid, semoparray, 1);
}

/*---------------------------------------------------------------------
* Function Name: unlock 
* Objective: increase the value of a semaphore
* In Parameters: 1. semaphore id
*                2. semaphore number within the semaphore array
* Return Values: None
* Other Variables Changed or Used: None
*
* Warning (To be taken into account when modifying): None
*--------------------------------------------------------------------*/

void unlock(int semid, int semnum)
{
    struct sembuf semoparray[1];

    semoparray[0].sem_num=semnum;
    semoparray[0].sem_op=1;
    semoparray[0].sem_flg=0;

    semop(semid, semoparray, 1);
}

#endif
