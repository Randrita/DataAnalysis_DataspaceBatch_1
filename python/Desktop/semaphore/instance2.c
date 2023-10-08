#include"sema.h"

main()
{
int semid;

semid=semGet(256, 1);
printf("Process B: Got semaphore %d\n", semid);

while(1)
{
printf("Process B: Trying to enter into <CS>\n");
lock(semid, 0);
printf("Process B: Sucessfully entered into <CS>\n");
printf("Process B: I am in critical section\n");
sleep(15);
printf("Process B: Trying to exit from <CS>\n");
unlock(semid, 0);
printf("Process B: Successfully exited from <CS>\n");
printf("Process B: I am in <RS>\n");
sleep(5);
}

}
