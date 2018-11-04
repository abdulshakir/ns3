#include<bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/stat.h>
using namespace std;
int main(int argc,char* argv[])
{
if(argc!=5)
{
	cout<<"Invalid command line arguments"<<endl;
	return 0;
}
if(strcmp(argv[3],"put")!=0)
{
	printf("%s is not supported command\n",argv[3]);
}
int sock;      // client socket discriptor

unsigned int len;
char ch[3]="no";
char ch1[3];

struct sockaddr_in client;
if((sock=socket(AF_INET,SOCK_STREAM,0))==-1){  // client socket is created..
perror("socket: ");
exit(-1);
}

client.sin_family=AF_INET;
client.sin_port=htons(stoi(argv[2]));        // initializing  socket  parameters 
client.sin_addr.s_addr=inet_addr(argv[1]);
bzero(&client.sin_zero,0); //appending 8 byte zeroes to 'struct sockaddr_in', to make it equal in size with 'struct sockaddr'.. 


len=sizeof(struct sockaddr_in);
if((connect(sock,(struct sockaddr *)&client,len))==-1){  //conneting to client
perror("connect: ");
exit(-1);
}

char fn[500];
strcpy(fn,argv[4]);
send(sock,fn,sizeof(fn),0);
struct stat res;

if(stat(fn,&res)!=0)
{
	cout<<"Invalid filename"<<endl;
	int v=-1;
	send(sock,&v,sizeof(v),0);
}
else
{
	ifstream f(fn,ios::in|ios::binary);
	cout<<"file opened"<<endl;
	int sz=res.st_size;
	cout<<"File size="<<sz<<" bytes"<<endl;
	int v=1;	
	send(sock,&v,sizeof(v),0);
	char buf[sz];
	f.read(buf,sz);
	send(sock,&sz,sizeof(sz),0);
	send(sock,buf,sizeof(buf),0);
	cout<<"File sent"<<endl;	
}


close(sock);
exit(0);
}


