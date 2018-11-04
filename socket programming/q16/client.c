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
	int sock;      // client socket discriptor
	unsigned int len;

	struct sockaddr_in client;
	if((sock=socket(AF_INET,SOCK_STREAM,0))==-1)
	{  	// client socket is created..
		perror("socket: ");
		exit(-1);
	}
	
	client.sin_family=AF_INET;
	client.sin_port=htons(10000);        // initializing  socket  parameters 
	client.sin_addr.s_addr=INADDR_ANY;
	//inet_addr("127.0.0.1");
	bzero(&client.sin_zero,0); //appending 8 byte zeroes to 'struct sockaddr_in', to make it equal in size with 'struct sockaddr'.. 


	len=sizeof(struct sockaddr_in);
	if((connect(sock,(struct sockaddr *)&client,len))==-1)
	{  	//conneting to client
		perror("connect: ");
		exit(-1);
	}
	char pass[512];		
	printf("Enter the password\n");
	scanf("%s",pass);
	send(sock,pass,sizeof(pass),0);
	int rep;
	if(recv(sock,&rep,sizeof(rep),0)&&rep<0)
	{
		printf("Wrong password\n");
		
	}
	else		
	{
		printf("Password verified. Send a 'Hi' to complete authentication.\n");
		scanf("%s",pass);
		send(sock,pass,sizeof(pass),0);
		recv(sock,&pass,sizeof(pass),0);
		printf("%s\n",pass);
		
			
	}
	
	close(sock);
	exit(0);
}


