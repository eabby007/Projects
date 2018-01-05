//write a program that converts a number into its word equivalent e.g 132 = one hundred thirty two 

#include<iostream>
#include<cstdio>
#include<string>

using namespace std;


class NumToWord{
	int _data;
	NumToWord(){}
	public:
		NumToWord(int data):_data(data){}
		string ToWord();
		string toString();
		
};


//converting a integer to string equvalent
string NumToWord::toString()
{
	int n=_data,count=0,j,i;
	static string s;
	char arr[10];
	while(n!=0)
	{
		arr[count++]=((n%10)+'0');
		n/=10;
	}
	arr[count]=0;
	i=0;
	j=count-1;
	char temp=0;
	while(i<j)
	{
		temp=arr[i];
		arr[i++]=arr[j];
		arr[j--]=temp;
	}
	return (s=arr);	
}


string NumToWord::ToWord()
{
	string s=toString();
	return s;

	
}

int main(int agrc, char **agrv)
{
	NumToWord n(120);
	//n.ToWord(120);
	printf("string %s\n",n.ToWord().c_str());
	return 0;
	
}
