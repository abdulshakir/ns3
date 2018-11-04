#include<bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include<sys/stat.h>
using namespace std;
int main()
{
	
int ssock,csock;       // creating server and clinet socket discriptor

unsigned int len;

struct sockaddr_in server,client;   // creating server & client socket object

if((ssock=socket(AF_INET,SOCK_STREAM,0))==-1){
	perror("socket: is not created");
	exit(-1);
}

server.sin_family=AF_INET;
server.sin_port=htons(8982);       // initializing server socket parameters..
server.sin_addr.s_addr=inet_addr("127.0.0.2");
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
char fn[500];
recv(csock,fn,sizeof(fn),0);
struct stat res;

if(stat(fn,&res)!=0)
{
	cout<<"Invalid filename"<<endl;
	int v=-1;
	send(csock,&v,sizeof(v),0);
}
else
{
	ifstream f(fn,ios::in|ios::binary);
	cout<<"file opened"<<endl;
	int sz=res.st_size;
	cout<<"File size="<<sz<<" bytes"<<endl;
	int v=1;	
	send(csock,&v,sizeof(v),0);
	char buf[sz];
	f.read(buf,sz);
	send(csock,&sz,sizeof(sz),0);
	send(csock,buf,sizeof(buf),0);
	cout<<"File sent"<<endl;	
}



close(ssock);








}
