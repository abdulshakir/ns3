#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
char names[][100]={"Liam","Noah","Mason","Elijah","Oliver","Jacob","Lucas","Michael","Alexander","Ethan"};
int marks[10][4];

void main()
{
	for(int i=0;i<10;i++)
		for(int j=0;j<4;j++)
			marks[i][j]=rand()%100+1;

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
	int arr[]={3,3,7,15,27};
	while(1)
	{
		int n;
		if(recv(csock,&n,sizeof(n),0)<=0)
			break;

		printf("Received roll no=%d\n",n);
		n--;
		int l=sizeof(names[n]);
		send(csock,&l,sizeof(l),0);
		send(csock,names[n],sizeof(names[n]),0);
		printf("Sent name=%s\n",names[n]);
		for(int i=0;i<4;i++)
		{
			send(csock,&marks[n][i],sizeof(marks[0][0]),0);
			printf("Marks sent=%d\n",marks[n][i]);
		}				
	}
	close(ssock);

}
