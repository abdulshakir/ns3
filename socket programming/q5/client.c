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
	while(1)
	{
		int n;
		printf("Enter n\n");
		scanf("%d",&n);
		send(sock,&n,sizeof(n),0);
		char f;
		while(recv(sock,&f,sizeof(f),0)&&f!=0)
			printf("%c",f);
		
		printf("Press Y to continue or any other key to exit\n");
		char ch1;		
		scanf("%c%c",&ch1,&ch1);
		if(ch1!='Y')
		{
			close(sock);
			exit(0);
		}

	}
}


