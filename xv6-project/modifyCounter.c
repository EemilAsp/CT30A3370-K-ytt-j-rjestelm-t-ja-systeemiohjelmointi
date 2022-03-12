#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])//take the number of syscall wanted to be tracked as input
{

resetCount();//reseting the counter first
int i = atoi(argv[1]);//argv[1] is the number between 1-24
setCounter(i);//setting up the counter to count the exact systemcall
printf(1,"The new systemcall that is tracked is number: %d\n", i);//printing the number 
printf(1,"The counter has been now reseted. and the count is %d\n", getnumb());//showing that the count is reseted.
exit();
}
