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
#include        <unistd.h>
#include        <regex.h>

char oid[] = ".1.3.6.1.2.1.1.1";
#define MAXLINE 1024
#define SA      struct sockaddr

//#define M_ALARM
#ifdef M_ALARM

void sig_alarm(int signo)
{
   printf("Received SIGALARM = %d\n", signo);
}

int m_signal(int signum, void handler(int)){
    struct sigaction new_action, old_action;

  /* Set up the structure to specify the new action. */
    new_action.sa_handler = handler;
    sigemptyset (&new_action.sa_mask);
    new_action.sa_flags = 0;

    if( sigaction (signum, &new_action, &old_action) < 0 ){
          fprintf(stderr,"sigaction error : %s\n", strerror(errno));
          return 1;
    }
    return 0;
}
#endif

int
dt_cli(int sockfd, const SA *pservaddr, socklen_t servlen,char code[])
{
	int		n, i;
	char		sendline[MAXLINE], recvline[MAXLINE+1];
	socklen_t	len;
	struct sockaddr	*preply_addr;
	char		str[INET6_ADDRSTRLEN+1];
	struct sockaddr_in6*	 cliaddr;
	struct sockaddr_in*	 cliaddrv4;
	struct timeval delay;

	if( (preply_addr = malloc(servlen)) == NULL ){
		perror("malloc error");
		exit(1);
	}

	bzero( sendline, sizeof(sendline));

#ifndef M_ALARM

	delay.tv_sec = 3;  //opóŸnienie na gnieŸdzie
	delay.tv_usec = 1; 
	len = sizeof(delay);
	if( setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &delay, len) == -1 ){
		fprintf(stderr,"SO_RCVTIMEO setsockopt error : %s\n", strerror(errno));
		return -1;
	}
#else
	m_signal(SIGALRM, sig_alarm);
#endif

	len = servlen;
	for(i=0; i < 3 ; i++ ){
               
               char *foo = malloc(strlen(oid)+strlen(oid)+2);
	       strcpy(foo,code);
	       strcat(foo," ");
	       strcat(foo,oid);
                snprintf(sendline,sizeof(sendline),"%s\n",foo);
		free(foo);

		if( sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen) < 0 ){
			perror("sendto error");
			free(preply_addr);
			exit(1);
		}
#ifdef M_ALARM
		alarm(3);
#endif

		if( (n = recvfrom(sockfd, recvline, MAXLINE, 0, preply_addr, &len) ) < 0 ){
			printf("errno = %d\n", errno);
			perror("recfrom error");
			if( ((errno == EAGAIN) || (errno ==  EINTR)) && (i < 2) )
				continue;
			else{
				free(preply_addr);
				return(1);
			}
		}else
#ifdef M_ALARM
		        alarm(0);
#endif
			break;
	}

	bzero(str, sizeof(str));

	if( preply_addr->sa_family == AF_INET6 ){
		cliaddr = (struct sockaddr_in6*) preply_addr;
		inet_ntop(AF_INET6, (struct sockaddr  *) &cliaddr->sin6_addr,  str, sizeof(str));
	}
	else{
		cliaddrv4 = (struct sockaddr_in*) preply_addr;
		inet_ntop(AF_INET, (struct sockaddr  *) &cliaddrv4->sin_addr,  str, sizeof(str));
	}

	if (len != servlen || memcmp(pservaddr, preply_addr, len) != 0) {
		printf("\n");
	}

	recvline[n] = 0;	/* null terminate */
	if (fputs(recvline, stdout) == EOF){
		fprintf(stderr,"fputs error : %s\n", strerror(errno));
		free(preply_addr);
		exit(1);
	}
	free(preply_addr);
	return 0;
}

	void
dt_cli_connect(int sockfd, const SA *pservaddr, socklen_t servlen)
{
	int		n;
	char	sendline[MAXLINE], recvline[MAXLINE + 1];
	char		str[INET6_ADDRSTRLEN+1];

	bzero(str, sizeof(str));
	if( connect(sockfd, (SA *) pservaddr, servlen) < 0 ){
		perror("connect error");
		exit(1);
	}

//	if( write(sockfd, sendline, strlen(sendline)+1) < 0 ){
	if( write(sockfd, sendline, 0) < 0 ){
		perror("write error");
		exit(1);
	}

	if( (n = read(sockfd, recvline, MAXLINE)) < 0 ){
		perror("read error");
		exit(1);
	}

	recvline[n] = 0;	/* null terminate */
	if (fputs(recvline, stdout) == EOF){
		fprintf(stderr,"fputs error : %s\n", strerror(errno));
		exit(1);
	}
}

void display_current_oid()
{
	printf("\n");
	printf("Current OID: %s",oid);
        printf("\n");
        sleep(4);	
}

int userInput()
 {
    int choice;

    printf("\n===========================\n");
    printf("(1). Display current OID   \n");
    printf("(2). Set new OID           \n");
    printf("(3). GET                   \n");
    printf("(4). GET Next              \n");
    printf("(5). GET Bulk              \n");
    printf("(0). Exit                  \n");
    printf("===========================\n\n");

    printf("Enter your choice, please\n");
    scanf("%d", &choice);

    return choice;
 }

void display_menu(){
	int userInput();

	printf("\n#########################\n");
        printf("                         \n");
        printf(" WELCOME IN SNMP CLIENT!\n ");
        printf("                         \n");
        printf("#########################\n");
        printf("                         \n");
	printf("    CHOOSE YOUR OPTION   \n");
	printf("                         \n");
}


void setOid(char new_oid[])
{
   strcpy(oid,new_oid);
   display_current_oid();
}

void transform_oid(){
	char lastNr = oid[strlen(oid)-1];
	oid[strlen(oid)-1] = '\0';
	int nr = (int) lastNr;
	int newNr = nr + 1;
	char nrToInset = (char) newNr;
	strncat(oid,&nrToInset,1);
}


	int
main(int argc, char **argv)
{
	int					sockfd, n, delay;
	struct sockaddr_in6	servaddr;
	char				recvline[MAXLINE + 1];

	if (argc != 2){
		fprintf(stderr, "usage: a.out <IPaddress> \n");
		return 1;
	}
	if ( (sockfd = socket(AF_INET6, SOCK_DGRAM, 0)) < 0){
		fprintf(stderr,"socket error : %s\n", strerror(errno));
		return 1;
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin6_family = AF_INET6;
	servaddr.sin6_port   = htons(13);	/* daytime server */
	if (inet_pton(AF_INET6, argv[1], &servaddr.sin6_addr) <= 0){
		fprintf(stderr,"inet_pton error for %s : %s \n", argv[1], strerror(errno));
		return 1;
	}

	// dt_cli( sockfd, (SA *) &servaddr, sizeof(servaddr)); tutaj uruchamia sie wyslanie
	display_menu();
	
	int sel = 1; //select number for menu


    while(userInput)
    {
      sel = userInput();
      switch(sel)
      {
    case 1 :
      	printf("\n");
	display_current_oid();    
	continue;
    
    case 2 :
	printf("\n");
        printf("Please remember that OID is valid when it's like .1.3.6.1.2.1.X.Y.Z ");		
	printf("\n");
	printf("Enter OID that you want to set: ");
        char newOid[50];
	scanf("%s",newOid);
	setOid(newOid);
     	sleep(2);
	continue;

    case 3 :
	dt_cli( sockfd, (SA *) &servaddr, sizeof(servaddr),"3");
      	continue;

    case 4 :
	dt_cli( sockfd, (SA *) &servaddr, sizeof(servaddr),"4");
	transform_oid();
      	continue;
    
    case 5 :
	dt_cli( sockfd, (SA *) &servaddr, sizeof(servaddr),"5");
	continue;
    case 0 :
	printf("\n koncze dzialanie programu");
      	exit(0);

    default :
	break;
      }
      break;
    }
	
	fflush(stdout);
	sleep(2);	
	exit(0);
}
