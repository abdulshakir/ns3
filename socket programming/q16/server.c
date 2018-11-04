#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

void main()
{

	int ssock,csock;       // creating server and clinet socket discriptor
	
	unsigned int len;

	struct sockaddr_in server,client;   // creating server & client socket object

	if((ssock=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("socket: is not created");
		exit(-1);
	}

	server.sin_family=AF_INET;
	server.sin_port=htons(10000);       // initializing server socket parameters..
	server.sin_addr.s_addr=INADDR_ANY;
	//inet_addr("127.0.0.1");
	bzero(&server.sin_zero,0); //appending 8 byte zeroes to 'struct sockaddr_in', to make it equal in size with 'struct sockaddr'.. 


	len=sizeof(struct sockaddr_in);
	
	if((bind(ssock,(struct sockaddr *)&server,len))==-1)
	{  	// binding port & IP  
		perror("bind: ");
		exit(-1);
	}

	if((listen(ssock,5))==-1)
	{	// listening for client
		perror("listen: ");                     
		exit(-1);
	}


	if((csock=accept(ssock,(struct sockaddr *)&client,&len))==-1)
	{	// accepting connectn
		perror("accept: ");                         
		exit(-1);
	}
	char pass[]="Password";
	char rec[512];
	recv(csock,rec,sizeof(rec),0);
	if(strcmp(rec,pass)!=0)
	{
		int v=-1;
		send(csock,&v,sizeof(v),0);
		printf("Wrong password. Expected '%s' received '%s'\n",pass,rec);		
	}
	else
	{
		int v=1;
		send(csock,&v,sizeof(v),0);
		printf("Password verified. Waiting for a hi\n");
		recv(csock,rec,sizeof(rec),0);
		if(strcmp(rec,"Hi")==0)
		{
			strcpy(rec,"Hello");
			printf("Hello sent\n");
			
		}
		else
		{
			printf("Unexpected string '%s' received instead of 'Hi'\n",rec);			
			strcpy(rec,"Please follow the instructions next time");
			
		}
		send(csock,rec,sizeof(rec),0);
	}
	close(ssock);

}
