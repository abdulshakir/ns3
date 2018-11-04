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
int main()
{


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
client.sin_port=htons(10000);        // initializing  socket  parameters 
client.sin_addr.s_addr=INADDR_ANY;
//inet_addr("127.0.0.1");
bzero(&client.sin_zero,0); //appending 8 byte zeroes to 'struct sockaddr_in', to make it equal in size with 'struct sockaddr'.. 


len=sizeof(struct sockaddr_in);
if((connect(sock,(struct sockaddr *)&client,len))==-1){  //conneting to client
perror("connect: ");
exit(-1);
}
for(int i=0;i<3;i++)
{
	
	char w[500];
	cout<<"Enter a question"<<endl;
	string s="";
		while(s=="")
			getline(cin,s);
	strcpy(w,s.c_str());
	send(sock,w,sizeof(w),0);
	int rep;
	recv(sock,&rep,sizeof(rep),0);
	if(rep!=1&&rep!=-1)
	break;
	recv(sock,w,sizeof(w),0);
	printf("%s\n",w);
	
	char ch1;
	if(i==2)
		break;
	printf("Press Y to continue or any other key to exit\n");
	cin>>ch1;
		if(ch1!='Y')
			break; 
}
close(sock);
exit(0);
}


