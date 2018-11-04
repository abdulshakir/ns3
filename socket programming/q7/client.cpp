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
while(1)
{
	cout<<"Enter a composite number to be factorised"<<endl;
	int n;
	cin>>n;
	send(sock,&n,sizeof(n),0);
	vector<int> v;
	int x;
	while(recv(sock,&x,sizeof(x),0)&&x)
	{
		recv(sock,&x,sizeof(x),0);
		v.push_back(x);
	}
	cout<<n<<"=";
	for(int i=0;i<v.size()-1;i++)
		cout<<v[i]<<"*";
	cout<<v[v.size()-1]<<endl;
	char ch1;

	printf("Press Y to continue or any other key to exit\n");
	scanf("%c%c",&ch1,&ch1);
		if(ch1!='Y')
			break; 
}
close(sock);
exit(0);
}


