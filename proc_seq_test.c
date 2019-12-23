#include<unistd.h>
#include<sys/types.h>
#include<linux/fcntl.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
   int fd,ret,buf[1024];

   fd = open("/proc/proc_test/readme",O_RDONLY);
   if(fd<0) { perror("error in opening"); exit(1); }

   lseek(fd,22,SEEK_SET);
 
   ret = read(fd,buf,4096);
   if(ret<0) { perror("error in read"); exit(6); }
   if(ret==0) ;
   if(ret>0) { write(STDOUT_FILENO,buf,ret); } 

   exit(0);
}
