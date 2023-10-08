#include"sema.h"

main()
{
int semid;

semid=semGet(256, 1);
printf("Process A: Got semaphore %d\n", semid);


while(1)
{
printf("Process A: Trying to enter into <CS>\n");
lock(semid, 0);
printf("Process A: Sucessfully entered into <CS>\n");
printf("Process A: I am in critical section\n");
sleep(8);
printf("Process A: Trying to exit from <CS>\n");
unlock(semid, 0);
printf("Process A: Successfully exited from <CS>\n");

printf("Process A: I am in <RS>\n");
sleep(4);


}

}
