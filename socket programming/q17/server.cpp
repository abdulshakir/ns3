#include<bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>

using namespace std;
int id,q,pr,qty;
void read()
{
	string s=to_string(id);
	ifstream f(s.c_str());
	if(!f)
		return;
	f>>qty>>pr;
	f.close();
}
void write()
{
	string s=to_string(id);
	ofstream f(s.c_str());
	f<<qty<<endl;
	f<<pr<<endl;
	f.close();
}
int main()
{

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
server.sin_addr.s_addr=inet_addr("127.0.0.1");
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
recv(csock,&id,sizeof(id),0);
recv(csock,&q,sizeof(q),0);
string ans="";
read();

if(id<1||id>2)
{
	ans="Invalid id";
}
else if(q<0)
{
	ans="Invalid quantity";
}
else if(qty==0)
{
	ans="Requested product out of stock";
}
else if(q>qty)
{
	ans="Only "+to_string(qty)+" units available for this product";
}
else
{
	
	qty-=q;
	int b=q*pr;
	ans="Item sold amount="+to_string(b);
	write();
}
char w[500];
strcpy(w,ans.c_str());
send(csock,w,sizeof(w),0);



close(ssock);









}
