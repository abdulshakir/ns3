#include<bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
using namespace std;
map<string,string> dict;
int main(int argc, char *argv[])
{
if(argc!=5)
{
	cout<<"Invalid arguments "<<endl;
	return 0;
}

int sock;      // client socket discriptor
int a,b,c,i;
unsigned int len;
char ch[3]="no";
char ch1[3];

struct sockaddr_in client;
if((sock=socket(AF_INET,SOCK_STREAM,0))==-1){  // client socket is created..
perror("socket: ");
exit(-1);
}

client.sin_family=AF_INET;
string prt(argv[2]);

client.sin_port=htons(stoi(prt));        // initializing  socket  parameters 
client.sin_addr.s_addr=inet_addr(argv[1]);
bzero(&client.sin_zero,0); //appending 8 byte zeroes to 'struct sockaddr_in', to make it equal in size with 'struct sockaddr'.. 


len=sizeof(struct sockaddr_in);
if((connect(sock,(struct sockaddr *)&client,len))==-1){  //conneting to client
perror("connect: ");
exit(-1);
}
	
char w[500];
int id=stoi(argv[3]),q=stoi(argv[4]);
send(sock,&id,sizeof(id),0);
send(sock,&q,sizeof(q),0);
recv(sock,w,sizeof(w),0);
printf("%s\n",w);	
	
close(sock);
exit(0);
}


