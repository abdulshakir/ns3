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
int max=20;
int arr[max+1][3];
for(int i=0;i<=max;i++)
{	for(int j=0;j<2;j++)
		arr[i][j]=(rand())%15;
	arr[i][2]=rand()%10;
	if(arr[i][1]<=arr[i][2])
	{
		arr[i][2]-=arr[i][1];
		arr[i][1]=0;
	}
	else
	{
		arr[i][1]-=arr[i][2];
		arr[i][2]=0;
	}
}
	
int ssock,csock;       // creating server and clinet socket discriptor

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

while(1)
{
	int n,l;
	char c[500];
	if(recv(csock,&n,sizeof(n),0)<=0)
	break;
	if(recv(csock,&l,sizeof(l),0)<=0)
	break;
	if(n>max||n<1)
	{
		strcpy(c,"Invalid employee id!");
	}
	else if(arr[n][2]!=0)
	{
		string x="You cannot take more leaves as you have already taken "+to_string(arr[n][2])+" extra leaves";
		strcpy(c,x.c_str());
	}
	else if(arr[n][1]<l)
	{
		string x="Your leave cannot be sanctioned as you can take only "+to_string(arr[n][1])+" more leaves";
		strcpy(c,x.c_str());
	}
	else
	{
		string x="You leave can be sanctioned as your available leave balance is "+to_string(arr[n][1]);
		strcpy(c,x.c_str());	
	}
	
	send(csock,&c,sizeof(c),0);
	printf("Sent=%s\n",c);
}


close(ssock);









}
