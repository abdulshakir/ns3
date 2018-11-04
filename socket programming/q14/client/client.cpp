#include<bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
using namespace std;
int main(int argc,char* argv[])
{
if(argc!=5)
{
	cout<<"Invalid command line arguments"<<endl;
	return 0;
}
if(strcmp(argv[3],"get")!=0)
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
int rep;
recv(sock,&rep,sizeof(rep),0);
if(rep!=1)
{
	cout<<"Invalid Filename"<<endl;
}
else
{
	cout<<"Receiving File"<<endl;
	ofstream f(fn,ios::out|ios::binary);
	int sz;
	recv(sock,&sz,sizeof(sz),0);
	cout<<"File size="<<sz<<" bytes"<<endl;
	char buf[sz];
	recv(sock,&buf,sizeof(buf),0);
	f.write(buf,sz);
	f.close();
	cout<<"File downloaded"<<endl;
}
close(sock);
exit(0);
}


