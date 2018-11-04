#include<bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
using namespace std;
string Gen="11000000000000101";
string crc(string x)
{
	int n=x.length();
	int m=Gen.length(),i=0;
	for(i=0;i+m<=n;i++)
	{
		if(x[i]=='1')
		{
			for(int j=0;j<m;j++)
			{
				x[i+j]='0'+((x[i+j]-'0')^(Gen[j]-'0'));
			}
		}
	}
	string ans="";
	for(;i<n;i++)
		ans=ans+x[i];
	return ans; 
}
bool check(string s)
{
	for(int i=0;i<s.length();i++)
		if(s[i]!='0')
			return false;	
	return true;
}
int Get(string x)
{
	int ans=0;
for(int i=0;i<8;i++)
{
	ans*=2;
ans+=(x[i]-'0');
}
return ans;
}
string convert(string x)
{
	string ans="";
	for(int i=0;i<x.length();i+=8)
	{
		int y=Get(x.substr(i,8));
		char u=y;
		string t="";
		t=t+u;
		ans=ans+t;
	}
	return ans;
	
}
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
int l;
recv(csock,&l,sizeof(l),0);
char c[l+2];
recv(csock,c,sizeof(c),0);
string message(c);
cout<<"received data="<<message<<endl;
string rem=crc(message);
if(check(rem))
{
	cout<<"Message is valid"<<endl;
	message=message.substr(0,message.length()-16);
	message=convert(message);
	cout<<"Received message="<<message<<endl;
}
else
{
	cout<<"Invalid message"<<endl;
	cout<<"Remainder="<<rem<<endl;
}
close(ssock);
}
