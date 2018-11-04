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
	x=x+"0000000000000000";
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

string Generate(string m)
{
	string ans="";
	for(int i=0;i<m.length();i++)
	{
		int u=m[i];
		string h;
		for(int j=0;j<8;j++)
		{
			int yy=u%2;
			char ty='0'+yy;
			string hj="";
			hj=hj+(char)ty;
			h=hj+h;
			u/=2;
		}
		cout<<h<<endl;
		ans=ans+h;
	}
	return ans;
}
int main()
{


int sock;      // client socket discriptor
unsigned int len;
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
string message;
cout<<"Enter the message to be sent"<<endl;
cin>>message;
message=Generate(message);
cout<<"Data word="<<message<<endl;
string rem=crc(message);
cout<<"Remainder obtained="<<rem<<endl;
message=message+rem;
cout<<"Obtained Code word="<<message<<endl;
cout<<"Enter the position of the bit to be flipped(from left,indexing starts from 0) or -1 if no flipping"<<endl;
int yy;
cin>>yy;
if(yy!=-1)
{
	message[yy]='0'+'1'-message[yy];	
}
int l=message.length();
char c[l+2];
strcpy(c,message.c_str());
//l=sizeof(c);
send(sock,&l,sizeof(l),0);
send(sock,c,sizeof(c),0);
close(sock);
return 0;
}
