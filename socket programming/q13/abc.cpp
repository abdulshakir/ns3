#include<bits/stdc++.h>
using namespace std; 
string conv(char x)
{
	int u=x;
	string ans="";
	for(int i=0;i<8;i++)
	{
		int h=u%2;
		char t=h+'0';
		string y=""+t;
		ans=y+ans;
		u/=2;
	}
	return ans;
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
			string hj=""+ty;
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
	string x;
	cin>>x;
	cout<<Generate(x)<<endl;
}
