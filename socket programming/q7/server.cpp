#include<bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
using namespace std;
int main(){

int ssock,csock;       // creating server and clinet socket discriptor
int a,b,c;
unsigned int len;

struct sockaddr_in server,client;   // creating server & client socket object

if((ssock=socket(AF_INET,SOCK_STREAM,0))==-1){
	perror("socket: is not created");
	exit(-1);
}

server.sin_family=AF_INET;
server.sin_port=htons(10000);       // initializing server socket parameters..
server.sin_addr.s_addr=INADDR_ANY;
//inet_addr("127.0.0.1");
bzero(&server.sin_zero,0); //appending 8 byte zeroes to 'struct sockaddr_in', to make it equal in size with 'struct sockaddr'.. 


len=sizeof(struct sockaddr_in);

if((bind(ssock,(struct sockaddr *)&server,len))==-1){  // binding port & IP  
	perror("bind: ");
	exit(-1);
}

if((listen(ssock,5))==-1){     // listening for client
	perror("listen: ");                     
	exit(-1);
}


if((csock=accept(ssock,(struct sockaddr *)&client,&len))==-1){  // accepting connectn
	perror("accept: ");                         
	exit(-1);
}
int arr[]={3,3,7,15,27};
while(1)
{
	int n;
	if(recv(csock,&n,sizeof(n),0)<=0)
	break;
	printf("Received i=%d\n",n);
	int x=2;
	while(n>1)
	{
		while(n%x==0)
		{
			int v=1;
			send(csock,&v,sizeof(v),0);
			send(csock,&x,sizeof(x),0);
			printf("Sent %d\n",x);
			n/=x;
		}
		x++;
	}
	n=0;
	send(csock,&n,sizeof(n),0);
}


close(ssock);









}
