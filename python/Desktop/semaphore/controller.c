#include"sema.h"

main()
{
int semid;

semid=semGet(256, 1);
printf("Process Master: Got semaphore %d\n", semid);
setVal(semid, 0, 1);
printf("Process Master: Set value 1 to semaphore %d\n", semid);


}
