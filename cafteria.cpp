#include<iostream>
using namespace std;
void list();
void signture();
const int maxsize=100;
class student 
{ 
	int studentID , numberBUYitems;
    double average;
    string studentName;                             
	public:
	student()
	{
	studentID =0;
	numberBUYitems =rand()%4;
	studentName ="Empty";
	average=rand()%100;
	}
	student(int sid,int nbi,double avg,string sname)//constructor with parameters
	{
	studentID=sid;
	numberBUYitems =nbi;
	average=avg;
	studentName =sname;
	}		
//================----------------------->setters<-----------------------================	
	void setSID(int sid)
	{
	studentID=sid;
	}
	void setNBI(int nbi)
	{
	numberBUYitems =nbi;
	}
	void setAVG(double avg)
	{
	average=avg;
	}
	void setSNAME(string sname)
	{
	studentName =sname;
	}
//================----------------------->getters<-----------------------================	
	int getSID()
	{
	return studentID;
	}
	int getNBI()
	{
	return numberBUYitems;
	}
	double getAVG()
	{
	return average;
	}
    string getSNAME()
	{
	return studentName;
	}
		
	void operator=(student s)
	{
	 setSID(s.getSID());
	 setNBI(s.getNBI());
	 setAVG(s.getAVG());
	 setSNAME(s.getSNAME());
     }
	 
	};
	
class queue
{
		int front,rear,count;
		student students[maxsize];
		int items;
		int c;
		public:
		queue()
		{
		c=0;
		count=0;
		front=0;
		rear=maxsize-1;
	    items=rand()%100;//(rand()%200)(0-199)<=================================================================
		}
		bool empty()
		{
		return(count==0);
		}
		bool ItemsNo()
		{
			int x;
			x = items-students[rear].getNBI();
			if( x >=0 && students[rear].getNBI()<=items && items!=0)
			{	
			items-=students[rear].getNBI();
			return 1;
			}
			else 
			return 0;
			
		}
		bool append(int sid, int nbi,double avg,string sname)
	    {
	  	if(count==maxsize)
	    return 0;
	  	rear=(rear+1)%maxsize;
	  	students[rear].setSID(sid);
	    students[rear].setNBI(nbi);
	    students[rear].setAVG(avg);
	    students[rear].setSNAME(sname);
	  	count++;
		  return 1;
		}
		bool append2(student s)
	    {
	    	
	  if(count==maxsize)return 0;
	  if(ItemsNo()==1)
	  {
		rear=(rear+1)%maxsize;
	  students[rear]=s;
	  count++;return 1;
	  }
	  else return 0;
		}
		bool append3(student s)
	    {
	  if(count==maxsize)return 0;
		rear=(rear+1)%maxsize;
	  students[rear]=s;
	  count++;return 1;
		}
		bool serve()
		{
		if(empty())return 0;
		front=(front+1)%maxsize;
		count--;
		return 1;
		}	
		bool retrieve(student &item)
		{
		if(empty())return 0;
		item=students[front];
		return 1;
		}
	    
	 
};		
bool CheckingID(queue unsorted,int sid)
{
	student temp;
	while(!unsorted.empty())
	{
	unsorted.retrieve(temp);
	if(temp.getSID()==sid) 
	return 1;
	unsorted.serve();
	}
	return 0;
	
}

void fillUnsorted(queue &unsorted,queue &q)
{
string sname;
int sid;
int nos=5;//number of students(rand()%100) <=======================================================================
for(int i=0;i<nos;i++)
{
student s;
cout<<endl<<"please!! enter student id : ";
cin>>sid;
while(CheckingID(unsorted,sid)==1)
{
cout<<"\n ERROR ID please enter valid (not used before)ID : ";
cin>>sid;
cout<<endl;
}
cout<<"please!! enter student name : ";cin>>sname;
s.setSID(sid);
s.setSNAME(sname);
unsorted.append2(s);
q.append3(s);	
}
}

int TheTotalSells(queue priorityQ)
{
	int total=0,sells1=0,sells2=0,items;student s;
	while(!priorityQ.empty())
		{
	priorityQ.retrieve(s);
	if(s.getAVG()>=90);// there no adding on total sells becasue they get there items for free
	else if(s.getAVG()<89 && s.getAVG()>60 )//between the 89 and 60 there are one item for free so -1 on the (nbi)
	{items =s.getNBI()-1;if(items>0) sells1+=items*10;}
	else{sells2+=s.getNBI()*10;}
	priorityQ.serve();
		}
	total=sells1+sells2;
	return total;
}
int CountSItem(queue priorityQ)
{
 student s;int count=0;
 while(!priorityQ.empty()){priorityQ.retrieve(s);if(s.getNBI()==0){count++;}priorityQ.serve();}
 return count;
}
void finshingItemsCounter(student s,queue q)//find who's student buy 
{	
	while(!q.empty())
	{	q.retrieve(s);
		if(q.ItemsNo()==0)
		{	
		cout<<"Student id       ===> "<<s.getSID()<<endl;
		cout<<"---------------------------------------------------"<<endl;
		cout<<"Student name       ===> "<< s.getSNAME()<<endl;
		cout<<"---------------------------------------------------"<<endl;
		cout<<"# of student items   ===> "<<s.getNBI()<<endl;
		cout<<"---------------------------------------------------"<<endl;
		cout<<"Average of the student ===> "<<s.getAVG()<<endl<<endl<<endl;
		}
		else 
	cout<<"students with flase conditions"<<endl;
	q.serve();
	}
		
			
}

	
			
	


void removemax(queue &unsorted, student s)// Find the max average student to delete it from waiting queue and move it to PQueue
{
	student stu;queue q;
	while(!unsorted.empty())
		{
		unsorted.retrieve(stu);
		if(s.getSID()==stu.getSID())
			{
			unsorted.serve();
			}
		if(unsorted.retrieve(stu)==1)
			{
			q.append2(stu);
			unsorted.serve();
			}
		
		}
	while(!q.empty())
		{
		q.retrieve(stu);
		unsorted.append2(stu);
		q.serve();
		}

}
student MaxAverage(queue unsorted)
{
	student smax;
	unsorted.retrieve(smax);
	student max;
	max=smax;
	while(!unsorted.empty())
	{
	unsorted.retrieve(smax);
	if(smax.getAVG()>max.getAVG())
	max=smax;
	unsorted.serve();
	}
	return max;	
}
void fill(queue &unsorted , queue &priorityQ)
{
	student ps;
	while(!unsorted.empty())
	{
	ps=MaxAverage(unsorted);
	priorityQ.append2(ps);
	removemax(unsorted,ps);	
	}
}
void print(queue priorityQ)
{
	student s;
	while(!priorityQ.empty())
	{

	priorityQ.retrieve(s);
	cout<<"Student id       ===> "<<s.getSID()<<endl;
	cout<<"---------------------------------------------------"<<endl;
	cout<<"Student name       ===> "<< s.getSNAME()<<endl;
	cout<<"---------------------------------------------------"<<endl;
	cout<<"# of student items   ===> "<<s.getNBI()<<endl;
	cout<<"---------------------------------------------------"<<endl;
	cout<<"Average of the student ===> "<<s.getAVG()<<endl<<endl<<endl;
	
	
	priorityQ.serve();	
	}
}
main()
{
	queue priorityQ,unsorted,q;
		int choice;
		student s;
		fillUnsorted(unsorted,q);
    do{
       list();
       cin>>choice;
       cout<<endl;
       if(choice==1)
	   	{
       cout<<"*************************************************\n"<<endl;
       	fill(unsorted,priorityQ);print(priorityQ);
       cout<<"\n*************************************************\n"<<endl;
		}
       else if(choice==2)
		{
		cout<<"*************************************************\n"<<endl;
		cout<<TheTotalSells(priorityQ)<<endl;
		cout<<"\n*************************************************\n"<<endl;
		}
       else if(choice==3)
		{
		cout<<"*************************************************\n"<<endl;
		cout<<CountSItem(priorityQ)<<endl;
		cout<<"\n*************************************************\n"<<endl;
		}
	   else if(choice==4)
	   {
		cout<<"*************************************************\n"<<endl;
		finshingItemsCounter(s,q);
		cout<<"\n*************************************************\n"<<endl;
		}
		else if(choice==5)
	   {
		cout<<"*************************************************\n"<<endl;
		signture();
		cout<<"\n*************************************************\n"<<endl;
		}
  }while(choice!=6);
}
void list()
{
		cout<<"1- Print the students in the priority queue ."<<endl;
		cout<<"2- Print the total amount of money that the cafeteria sell."<<endl;
		cout<<"3- Print the number of students that don't buying any item."<<endl;
		cout<<"4- Find if there is a student that buying some of his items and the others are not."<<endl;
		cout<<"5- APPLICATION Signture"<<endl;
		cout<<"6- Exit"<<endl;	
		cout<<"HELLO!! i am ANANi (*___*) HOW i Can serve You : ";
	
}
void signture()
{
	cout<<"\n\n\n";
		cout<<"\t\t\t\t  *************************************************"<<endl;
		cout<<"\t\t\t\t  ****||Thx for using the app (| 8> __ <8 |) ||****"<<endl;
		cout<<"\t\t\t\t  *************************************************"<<endl;
		cout<<"\t\t\t\t  *************************************************"<<endl;
		cout<<"\t\t\t\t  ******||=> Mohammad Adeeb younes Anani <=||******"<<endl;
		cout<<"\t\t\t\t  *************************************************"<<endl;
		cout<<"\n\n\n";
		cout<<endl;
}