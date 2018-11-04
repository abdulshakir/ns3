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
void read()
{
	char fn[]="dictionary";
	ifstream f(fn);
	if(!f)
		return;
	string s;
	while(getline(f,s)&&s!="")
	{
		string k;
		getline(f,k);
		dict[s]=k;
	}
	f.close();

}
void write()
{
	char fn[]="dictionary";
	ofstream f(fn);
	if(!f)
		return;
	for(auto& kv:dict)
	{
		f<<kv.first<<endl;
		f<<kv.second<<endl;
	}
	f.close();	
}
int main()
{
read();
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

for(int i=0;i<3;i++)
{
	char w[500];
	if(recv(csock,w,sizeof(w),0)<=0)
		break;
	string s(w);
	cout<<"Question received="<<s<<endl;
	if(dict.find(s)!=dict.end())
	{
		s=dict[s];
		strcpy(w,s.c_str());
		int rep=1;
		send(csock,&rep,sizeof(rep),0);
		send(csock,w,sizeof(w),0);
	}	
	else
	{
		int rep=-1;
		char p[500];
		strcpy(p,"Invalid question please try again");
		send(csock,&rep,sizeof(rep),0);
		send(csock,p,sizeof(p),0);
		
	}
}


close(ssock);









}
