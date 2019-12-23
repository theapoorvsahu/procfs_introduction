#include<unistd.h>
#include<sys/types.h>
#include<linux/fcntl.h>
#include<stdlib.h>
#include<stdio.h>

int main()
{
   int fd,ret,buf[1024];
   fd = open("/proc/readme",O_RDONLY);
   if(fd<0) { perror("error in opening"); exit(1); }
   printf("value of fd is %d\n", fd); 

   //lseek(fd,0,SEEK_SET);
 
   // Remove the following 'while loop' for getting a good and clean tracing...
   while(1)
   {
	   ret = read(fd,buf,4096);
	   if(ret<0) { perror("error in read"); exit(6); }
	   if(ret==0) break ;

	   printf("the no. characters returned is %d\n", ret);
	   if(ret>0) { write(STDOUT_FILENO,buf,ret); } 
   }
   exit(0);
}
