#include        <sys/types.h>   /* basic system data types */
#include        <sys/socket.h>  /* basic socket definitions */
#include        <sys/time.h>    /* timeval{} for select() */
#include        <time.h>                /* timespec{} for pselect() */
#include        <netinet/in.h>  /* sockaddr_in{} and other Internet defns */
#include        <arpa/inet.h>   /* inet(3) functions */
#include        <errno.h>
#include        <fcntl.h>               /* for nonblocking */
#include        <netdb.h>
#include        <signal.h>
#include        <stdio.h>
#include        <stdlib.h>
#include        <string.h>
#include <sys/utsname.h>
#define MAXLINE 1024
#define SA struct sockaddr
#undef	MAXLINE
#define	MAXLINE 65507

char* generate_system(char entity);
char nodeName[40];
char oid[20];

const char* run_catalog(char *ptr){

	struct utsname buf;
	int ret;
	ret = uname(&buf);

      	if (strcmp(ptr,".1.3.6.1.2.1.1.1") == 0){
	if(!ret){ 	
	strcpy(nodeName,"OperatingSystemName: ");
	strcat(nodeName, buf.sysname);
	}
  }

	else if (strcmp(ptr,".1.3.6.1.2.1.1.2") == 0){
        if(!ret){
        strcpy(nodeName,"Node(Host)Name: ");
        strcat(nodeName, buf.nodename);
        }
  }

	else if(strcmp(ptr,".1.3.6.1.2.1.1.3") == 0){
        if(!ret){
        strcpy(nodeName,"KernelReleaseVersion: ");
        strcat(nodeName, buf.release);
        }
  }
	else if(strcmp(ptr,".1.3.6.1.2.1.1.4") == 0){
        if(!ret){
        strcpy(nodeName,"OsVersion: ");
        strcat(nodeName, buf.version);
        }
  }
	else if(strcmp(ptr,".1.3.6.1.2.1.1.5") == 0){
        if(!ret){
        strcpy(nodeName,"Hardware: ");
        strcat(nodeName, buf.machine);
        }
}
	else{
        if(!ret){
        strcpy(nodeName,"NODE NOT FOUND, OID IS WRONG");
        }

  }

  return nodeName;
}

void transform_oid(){
	 char lastNr = oid[strlen(oid)-1]; 
         oid[strlen(oid)-1] = '\0';
	 int nr = (int) lastNr;
	 int newNr = nr + 1;
	 char nrToInset = (char) newNr;
	 strncat(oid,&nrToInset,1);
}

void
dg_echo(int sockfd, SA *pcliaddr, socklen_t clilen)
{
	int		n;
	socklen_t	len;
	char		mesg[MAXLINE],recvline[MAXLINE];
	char		str[INET6_ADDRSTRLEN+1];
	time_t		ticks;

	struct sockaddr_in6*	 cliaddr;
	struct sockaddr_in*	 cliaddrv4;
        
	cliaddr = (struct sockaddr_in6*) pcliaddr;

	fprintf(stderr,"Waiting for clients ... \n");
	for ( ; ; ) {
		len = clilen;

		if( (n = recvfrom(sockfd, recvline, MAXLINE, 0, pcliaddr, &len)) < 0 ){
                	fprintf(stderr,"recvfrom error : %s\n", strerror(errno));
			exit(1);		    
		}

		bzero(str, sizeof(str));
				
		if( pcliaddr->sa_family == AF_INET6 ){
		      cliaddr = (struct sockaddr_in6*) pcliaddr;
		      inet_ntop(AF_INET6,  (struct sockaddr  *) &cliaddr->sin6_addr,  str, sizeof(str));
		}
          
		else{
		      cliaddrv4 = (struct sockaddr_in*) pcliaddr;
		      inet_ntop(AF_INET, (struct sockaddr  *) &cliaddrv4->sin_addr,  str, sizeof(str));
		}
		printf("Connection from %s\n", str);
                ticks = time(NULL);
                
		char code=recvline[0];
		fflush(stdout);

		printf("\n Operation Code (GET-3, GET Next-4, Get Bulk-5): %c \n",code);
			
		for (int i=2;i<n-1;i++){
		oid[i-2]=recvline[i];
		}
    
		switch (code) {
		case '3':
			printf("\n CHOSEN GET METHOD \n");
			const char* ptr=run_catalog(oid);
			snprintf(mesg, sizeof(mesg),"%s",ptr);
			break;
		case '4':
			printf(" \n CHOSEN GET NEXT METHOD \n");
			transform_oid();
			const char* ptrs = run_catalog(oid);
                        snprintf(mesg, sizeof(mesg),"%s",ptrs);
			break;
		case '5':
			printf(" \n CHOSEN GET BULK METHOD \n");
			break;
		default:
			printf("\n WRONG CODE \n");
			break;
		}

		if( sendto(sockfd, mesg, strlen(mesg), 0, pcliaddr, len) < 0 ) {
            fprintf(stderr,"sendto error : %s\n", strerror(errno));
			exit(1);		    
		}

	}
}

	

int
main(int argc, char **argv)
{
	int				sockfd, connfd;
	socklen_t			len;
	char				buff[MAXLINE], str[INET6_ADDRSTRLEN+1];
	time_t				ticks;
	struct sockaddr_in6	servaddr, cliaddr;

	if ( (sockfd = socket(AF_INET6, SOCK_DGRAM, 0)) < 0){
			fprintf(stderr,"socket error : %s\n", strerror(errno));
			return 1;
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin6_family = AF_INET6;
	servaddr.sin6_addr   = in6addr_any;
	servaddr.sin6_port   = htons(13);	/* daytime server */

	if ( bind( sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){
			fprintf(stderr,"bind error : %s\n", strerror(errno));
			return 1;
	}

	dg_echo(sockfd, (SA *) &cliaddr, sizeof(cliaddr));        
}
