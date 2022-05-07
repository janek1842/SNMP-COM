 #include<stdio.h>
#include<sys/utsname.h>

int main()
{
 int ret;
 struct utsname buf;
 ret = uname(&buf);
 if(!ret) {
  char sysName[] = buf.sysname;
  char nodeName[] = buf.nodename;
  printf("Kernel Release Version: %s\n",buf.release);
  printf("OS Version: %s\n",buf.version);
  printf("Hardware: %s\n",buf.machine);
 }
 else {
  printf("Error in the System call");
  return -1;
 }
return 0;
}
