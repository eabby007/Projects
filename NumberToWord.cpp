//write a program that converts a number into its word equivalent e.g 132 = one hundred thirty two 

#include<iostream>
#include<cstdio>
#include<string>
#include<utility>
using namespace std;

//class for conversion
class NumToWord{
	int _data;  // data that is converted 
	
	NumToWord(){}  //private constructor so that object can't be instantiated without parameter
	
	string toString(); //converts a number to string equivalent
	
	string wordstore(pair <string,int* > ); // converts number to word format 
	
	int toDigit(string );   // converts a string to number for switch .i.e. in wordstore
	public:
		
		NumToWord(int data):_data(data){}   // public constructor
		
		string ToWord();                    //member function used for conversion
};

//converts a string to integer
int NumToWord::toDigit(string s)
{
	int num=0;
	int count=1;
	for(auto it=s.rbegin();it!=s.rend();++it)  //traversing in reverse order using reverse ITERATORS (rbegin() & rend()
	{
		num=num+(*it-'0')*count;    //starting from units place and adding subsequent digits for integer 
		count*=10; 
	}
	
	return num;
}


//converting a integer to string equvalent
string NumToWord::toString()
{
	int n=_data,count=0,j,i;
	
	static string facevalue =""; //SINCE local string variable has to be returned so it must be declared STATIC 

	char arr[10];  // Buffer for storing digits as character from the given integer
	
	while(n!=0)   // constructing equivalent array from integer but in reverse order .i.e. if input is 123(integer) array becomes 321(chars)
	{
		arr[count++]=((n%10)+'0');   //conversion from int to char adding '0'
		n/=10;
	}
	arr[count]=0;
	i=0;
	j=count-1;
	char temp=0;
	while(i<j)     // obtaining correct order .i.e. from 321 from previous to 123 
	{
		temp=arr[i];
		arr[i++]=arr[j];
		arr[j--]=temp;
	}
	return (facevalue =arr);  // creating STL string from c-string by assinging c-string array to STL String and then returning the string	
}

// wordstore to convert a integer to its word equivalent step wise
string NumToWord::wordstore(pair<string,int* > p)  // takes a pair of string and (pointer to length inorder to find its placevalue)
{
	string placevalue="";
	string facevalue="";
	int x;
	
	// LOGIC is simple behind this .. take pen and paper and it can easily be understood by dry running a test case
	
	if(*(p.second)==2 ||*(p.second)==5 ||*(p.second)==7 || *(p.second)== 9)  
		{
			x=toDigit(p.first.substr(0,2));  //to integer
			if(x>0)
			{
				if(x<=20)
				{
					switch(*(p.second))
					{
						case 5: placevalue="thousand ";break;
						case 7: placevalue="lakh ";break;
						case 9: placevalue="crore ";break;
					}
				}
				else
					{
						*(p.second)+=1;
						x=(x-(x%10));
					}
	
			}
			*(p.second)-=2;	
		}
		
	else if(*(p.second)==1 || *(p.second)== 3 || *(p.second)==4 || *(p.second)==6 ||*(p.second)==8)
		{
			x=toDigit(p.first.substr(0,1));
			if(x>0)
			switch(*(p.second))
			{
				case 8: placevalue="crore ";break;
				case 6: placevalue="lakh ";break;
				case 4: placevalue="thousand ";break;
				case 3: placevalue="hundred ";break;
			}
			*(p.second)-=1;
		}
			
	switch(x)
	{
		case 1:facevalue = "one "; break;
		case 2:facevalue = "two "; break;
		case 3:facevalue = "three "; break;
		case 4:facevalue = "four "; break;
		case 5:facevalue = "five "; break;
		case 6:facevalue = "six "; break;
		case 7:facevalue = "seven "; break;
		case 8:facevalue = "eight "; break;
		case 9:facevalue = "nine "; break;
		case 10:facevalue = "ten "; break;
		case 11:facevalue = "eleven "; break;
		case 12:facevalue = "twelve "; break;
		case 13:facevalue = "thirteen "; break;
		case 14:facevalue = "fourteen "; break;
		case 15:facevalue = "fifteen "; break;
		case 16:facevalue = "sixteen "; break;
		case 17:facevalue = "seventeen "; break;
		case 18:facevalue = "eighteen "; break;
		case 19:facevalue = "nineteen "; break;
		case 20:facevalue = "twenty "; break;
		case 30:facevalue = "thirty "; break;
		case 40:facevalue = "forty "; break;
		case 50:facevalue = "fifty "; break;
		case 60:facevalue = "sixty "; break;
		case 70:facevalue = "seventy "; break;
		case 80:facevalue = "eighty "; break;
		case 90:facevalue = "ninety "; break;
	}
	return (facevalue +placevalue); //returning value
	
}


//function to be called on a object of NumToWord for conversion
string NumToWord::ToWord()
{
	string sdata=toString();   //convert input integer to string for further processing
	
	int len=sdata.length();   //obtaining length of string
	
	int length=len;          //IMPORTANT variable needed
	
	static string result=" ";  //STATIC since that variable is to be returned 
	
	result.erase();  //each call has to re-initialise the variable result , since static is initialsed only once so data must be erased 
			// each time in order to get a new string each time or else data from previous invocation is retained

	int i=0;
	
	pair<string,int *> p; //declaring a pair variable
	
	while(len!=0)   // len variable is updated since its pointer is passed in the pair variable and subsequently becomes 0
	{
		p={sdata,&len};    // create pair value for passing  to wordstore member function
		result+=wordstore(p);  // string is concatnated for each invocation of wordstore to create full string in order to return
		
		sdata=sdata.substr(length-len);  // update string in each iteration e.g if previous was 123 it might become
						// 23 depends on the above logic
		
		length=sdata.length();  // update length variable in order to create proper substring in above statement in next iteration 
	}
	result.at(0)^=32;  // make the first alphabet to upper case

	return result;  
	
}

int main(int agrc, char **agrv)
{

	bool cont =false;
	//MENU 
	do
	{
		puts("Enter any integer (at max 9 digits long & positive integers) ");
		int num;
		scanf("%d",&num);
		if(num<=0)
		cout<<"Zero"<<endl;
		else
		{
			NumToWord *obj=new NumToWord(num);
			printf("%d in Words :\n%s\n",num,(obj->ToWord()).c_str());
			delete obj; //avoid memory leak
		}
		puts("do you want to continue: ");
		char choice;
		cin>>choice;
		if((choice | 32) =='y')
			cont=true;
		else
			cont=false;

	}while(cont);
	return 0;
	
}
