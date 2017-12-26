/*Problem statement is to design a event query app in order to get a price quote for a particular event in particular date*/
//COMPILE USING C++11 STD 
// or else many featurs will not run
//just trial 

#include<iostream>
#include<string>
#include<cstdlib>
#include<cstdio>

using namespace std;

//abstract event class
class event{
	protected:
		string type;
		int nog;
		static int eventno;
		string eid;
		string date;
		const double dc=40.0;
	public:
		//just for practicing friend function
		friend string converter(event *ptr,int value);
		
		string idcreator(event *ptr){
			eventno++;
			return converter(ptr,eventno);
		}
		
		;
		virtual double cost()=0;
		virtual void setdate(string date)=0;
		virtual void setnog(int guests )=0;
		virtual void print(){
			cout<<"DETAILS : "<<endl;
			cout <<"event type : "<<type<<" on date : "<<date<<endl;
			cout<<" with no. of guests is: "<<nog<<"  and event id :"<<eid<<endl;
			cout<<" total cost is(in ruppees) : "<<cost()<<endl;
		}
};


//creating a unique event id for further booking 
string converter(event *ptr,int value)
{
	string s="\0";
	if(ptr->type=="wedding")
	{
		
		s=to_string(value);
		s="W-"+s;
	}
	else if(ptr->type=="Birthday")
	{
		s=to_string(value);
		s="B-"+s;
	}
	return s;
}

//initialising static variable
int event::eventno=0;

//wedding class implementing event abstract class
class wedding:public event{
	private :
		const double cst=60;
	public:
		wedding(){
			type="wedding";
			eid=idcreator(this);//craeting id .. calling superclass method inherited with this object
			
		}
		double cost(){
			return dc+nog*cst+200;
		}
		void print()
		{
			cout<<endl;
			event::print();
			cout<<endl;
		}
		void setnog(int guest){nog=guest;}
		void setdate(string date){this->date=date;}
};

//birthday class inherting abstract event class
class birthday:public event{
	private: 
		const double  cst=50;
		
	public:
		birthday(){
			type="Birthday";
			eid=idcreator(this);
			
		}
		double cost(){
			return dc+nog*cst;
		}
		void print(){
			cout<<endl;
			event::print();	
			cout<<endl;
		}
		void setnog(int guest){nog=guest;}
		void setdate(string date){this->date=date;}
};

//craeting factory for getting proper objects
class eventfactory{
	event *e;
	public:
		event *create (string type)
		{
			if(type=="wedding")
				e=new wedding();
			else if(type=="Birthday")
				e=new birthday();
			return e;
		}
	
};

//for storing inputs taken from main()
class input{
	public:
		int nog;
		string date;
		string type;
		string name;
		input(int n,string d,string t,string na):nog(n),date(d),type(t),name(na){}
};

//all i-o operations in one global method to be used by main()
input * menu()
{	
	int nog;
	int choice;
	string name;
	string date;
	string type;
	cout<<"Welcome to kathie's catering"<<endl;
	cout<<"enter your name"<<endl;
	
	getline(cin,name);
	cout<<"type of event\n1.wedding\n2.birthday"<<endl;
	cin>>choice;
	cout<<"no. of guest : ";
	cin>>nog;
	cout<<"enter date (dd-mnth-year): ";
	cin>>date;
	if(choice==1)
		type="wedding";
	else
		type="Birthday";
	//input i(nog,date,type,name);
	return(new input(nog,date,type,name)); 
}



int main()
{
	char choice;
	eventfactory *ef=new eventfactory;//instiating a factory object
	event *e=NULL;
	input *i=NULL;
	do{	//repeating till user says no
		
		i=menu();
		e=ef->create(i->type);
		e->setnog(i->nog);
		e->setdate(i->date);
		cout<<"Hi.. "<<i->name<<" details of your query are: "<<endl;
		e->print();
		cout<<"do u want another one ? y/n"<<endl;
		cin >>choice;
		cin.ignore();
		delete e;
		delete i;
	}while(choice=='y');	
	return 0;
	delete ef;
}
