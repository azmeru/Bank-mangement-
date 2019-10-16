#include<iostream>
#include<iomanip>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include<ctime>
#include<windows.h>
float rate=0.05;
using namespace std;
class admin
{
 protected:
    double orginal;
    double amount;
	double interes;
 	double totalTime;
	char fname[20];
	char lname[20];
	char gender[10];
	char acctype[50];
	char branch[50];
	char nationality[30];
    int year;
	int date;
	int hour;
	int month;
	int phonenum;
	int accnum;
public:
	    int setid();//to generate random account number
		int calInterest();     //to calculate interest 
        double update();//to update an account
	    int RetAccNo();// to hold account number
		void create_account();//function to get data from user
		void update_account();//function to update new data
		void report() ;//function to show all the customers data in tabular format
};
class customer:public admin
  {
  	public:
  		void group_members();
  		void show_account() ; //fuction to show data
		void depo(double);//function to deposit money
	    void withdraw(double);//function to withdraw money
	    void transfer_money(int,int,double);// to transfer money to other
	    
	    void write_account();	//function to write record to file
        void display_sp(int);	//function to display account details given by user from file
        void modify_account(int);	//function to modify record of file
        void delete_account(int);	//function to delete record of file
        void display_all();		//function to display all account details
        //file
        void deposit(int,double );// function to desposit amount for given account to file
        void with(int,double); // function to withdraw amount for given account to file
};
void customer::group_members()
  {
	cout<<"this program is made by IT department\n";
	cout<<"   \n group 1 students\n\n";
	cout <<"first name"<<setw(16)<<"last name"<<setw(15)<<"id no\n";
	cout <<"abel"<<setw(15)<<"desta"<<setw(25)<<"mit/ur/072/09\n";
	cout <<"alene"<<setw(16)<<"A/tsion"<<setw(23)<<"mit/ur/027/09\n";
	cout <<"azmeru"<<setw(14)<<"g/abzgi"<<setw(24)<<"mit/ur/121/09\n";
	cout <<"aida"<<setw(15)<<"milaw"<<setw(25)<<"mit/ur/073/09\n";
	cout<<"bahre"<<setw(15)<<"fissha"<<setw(20)<<"mit/ur//09";
	return;
  }  
  int admin::RetAccNo()
  {
	return accnum;
  }

int admin::setid()

  {
   fstream File;
   File.open("bank.dat",ios::in|ios::binary);
   File.seekg(0);
   again:
   srand(time(NULL));
   int x=(rand()%3000)+1;
   while(File)
    {
        File.read(reinterpret_cast<char*>(this),sizeof(this));
        if(this->RetAccNo()==x)
         {
            goto again;
         }
        else
            return x;
    }
  }
  

void admin::create_account()

  {
	cout<<"\n your account Number . :";
	accnum=setid();
	cout<<accnum;
	cout<<"\n\nEnter first name:\t ";
	cin>>fname;
	cout<<"\n\nEnter last name :\t ";
	cin>>lname;
	cout<<"\n\nEnter gender:\t\t";
	cin>>gender;
	cout<<"\n\nEnter phone number:\t";
	cin>>phonenum;
	cout<<"\n\nEnter country:\t";
	cin.ignore();
	cin.getline(nationality,50);
	cout<<"\nEnter the branch name of the bank :\t" ;
 	cin.ignore();
	cin.getline(branch,50);
	cout<<"\nchoose Type of The account(current or saving account):\t";
	cin>>acctype;
	cout<<"\nEnter The Initial amount>=50:"<<endl;
	cin>>amount;
	if(amount<50)
	{
	cout<<"\nIt is impossible to save less than 50 ";
     }
	cout<<"\n date of registration"<<endl;
    time_t t = time(NULL);
    tm* timePtr = localtime(&t);
    cout << "Date" <<(timePtr->tm_mday)<<"/"<< (timePtr->tm_mon)+1 <<"/"<< (timePtr->tm_year)+1900<< endl;
    cout << "Time" << (timePtr->tm_hour)<<":"<< (timePtr->tm_min)<<":"<< (timePtr->tm_sec) << endl;
    month=(timePtr->tm_mon)+1;
    year=(timePtr->tm_year)+1900;
    hour=(timePtr->tm_hour);
    date=(timePtr->tm_mday);
    totalTime=(year*365)+(hour/24)+(date)+(month*30);
    orginal= amount;
     
	cout<<"\n\n\nAccount Created..";
  }
 
void admin::update_account()
  { 
	cout<<endl<<"\n update first name of the account holder  : \t";
	cin>>fname;
	cout<<endl<<"\n update last name of the account holder  : ";
	cin>>lname;
	cout<<"\n update gender :";
	cin>>gender;
	cout<<"\nupdate phone number:";
	cin>>phonenum;
	cout<<"\nupdate nationality:";
	cin.ignore();
	cin.getline(nationality,50);
  }
void admin::report() 

    {
     cout<<accnum<<setw(8)<<"    "<<fname<<setw(8)<<"     "<<lname<<setw(10)<<"    "<<acctype<<setw(10)<<"  "<<amount<<setw(10)<<"   "<<gender<<endl;
    }

   void customer::show_account() 
   
   {
	cout<<"\nAccount No. :\t "<<accnum;
	cout<<"\nFirst Name : \t"<<fname;
	cout<<"\nLast name :\t"<<lname;
	cout<<"\nBalance: \t"<<amount;
	cout<<"\nType of Account : \t"<<acctype;
   }
void customer::depo(double x)

  {
	amount=amount+x;
	orginal=amount;
  }
  
void customer::withdraw(double x)

   {
	if(x>amount)
	
	 {
	cout<<"\n your balance is insufficient can not withdraw balance!";
	
	 }
	else
	  {
	amount=amount-x;
	orginal=amount;
      }
   }
void customer::write_account()//function to write to a file

  {
	ofstream outFile;
	outFile.open("bank.dat",ios::binary|ios::app|ios::out);
	create_account();
	outFile.write(reinterpret_cast<char*>(this), sizeof(*this));
	outFile.close();
  }
  
void customer::transfer_money(int x,int y,double am) //To transfer money

  {
	int a=0,b=0;
	fstream File;
	File.open("bank.dat",ios::binary|ios::in|ios::out);
	if(!File)
	  {
	   cout<<"File could not be open !! Press any Key...";
		return;
	  }
	  
	while(!File.eof())
	   {
		File.read(reinterpret_cast<char*> (this), sizeof(*this));
		if(accnum==x)
		a=1;
		if(accnum==y)
		b=1;
	   }
	 if(a==1&&b==1)
	  {
	 if(am>amount)
		cout<<"\nBalance is insufficient";
		else
		 {
			with(x,am);
			deposit(y,am);
		 }
	  }
		  else
		cout<<"You entered a wrong account number";
  }
void customer:: display_sp(int x)//fuction to display a specfic account afrom a file
  {
	bool found=false;
	ifstream inFile;
	inFile.open("bank.dat",ios::binary|ios::in);
	if(!inFile)
	 { 
		cout<<"File could not be open !! Press any Key...";
		return;
	 } 
	cout<<"\nACCOUNT DETAILS\n";
	while(!inFile.eof() && found==false)
	 {
	inFile.read(reinterpret_cast<char *> (this),sizeof(*this));
		if(accnum==x)
		{
			show_account();
			found=true;
		}
	 } 
	inFile.close();
	if(found==false)
		cout<<"\n\nAccount number does not exist";
	}
	
void customer::modify_account(int x) //function to modify the account
	{
	bool found=false;
	fstream File;
	File.open("bank.dat",ios::binary|ios::in|ios::out);
	if(!File)
	 {
	   cout<<"File could not be open !! Press any Key...";
		return;
	 }
		while(!File.eof()&&found==false )
	     { 
		  File.read(reinterpret_cast<char *> (this), sizeof(*this));
		if(accnum==x)
		   {
	        show_account();
			cout<<"\n\nEnter The New Details of account"<<endl;
			update_account();
			int pos=(-1)*static_cast<int>(sizeof(*this));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (this), sizeof(*this));
			cout<<"\n\n\t Account Updated";
			found=true;
			cout<<"\n date of update";
			time_t t = time(NULL);
            tm* timePtr = localtime(&t);
            cout << "Date     " <<(timePtr->tm_mday)<<"/"<< (timePtr->tm_mon)+1 <<"/"<< (timePtr->tm_year)+1900<< endl;
            cout << "Time     " << (timePtr->tm_hour)<<":"<< (timePtr->tm_min)<<":"<< (timePtr->tm_sec) << endl;
		  }
	    }
	File.close();
	if(found==false)
	   cout<<"\n\n Record Not Found ";
   }
void customer:: delete_account(int x)//to delete an account from file
   {
	ifstream inFile;
	ofstream outFile;
	inFile.open("bank.dat",ios::binary);
	if(!inFile)
	  {
		cout<<"File could not be open !! Press any Key...";
		return;
	  }
	outFile.open("Tem.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (this), sizeof(*this)))
	  {
		if(accnum!=x)
		  {
			outFile.write(reinterpret_cast<char *> (this), sizeof(*this));
		  }
	  }
	inFile.close();
	outFile.close();
	remove("bank.dat");
	rename("Tem.dat","bank.dat");
	cout<<"\n\n\t account Deleted ..";
   }
   
int admin::calInterest()

   {
	fstream File;
	time_t t = time(NULL);
    tm* timePtr = localtime(&t);
    int mm=(timePtr->tm_mon)+1;
    int  yy=(timePtr->tm_year)+1900;
    int dd=(timePtr->tm_mday);
    int hh=(timePtr->tm_hour);
    double tot=(mm*30)+(hh/24)+(dd)+(yy*365);
    
	File.open("bank.dat",ios::binary|ios::in|ios::out);
		while(File.read(reinterpret_cast<char *> (this), sizeof(*this)))
	     {
			interes=(orginal*rate)/365;
		    amount=orginal+((tot-totalTime)*interes);
			int pos=(-1)*static_cast<int>(sizeof(*this));
			File.seekp(pos,ios::cur);			
			File.write(reinterpret_cast<char *> (this), sizeof(*this));
         }
    File.close();
    return 0;  
   }
   
void customer::display_all()
   { 
	ifstream inFile;
	inFile.open("bank.dat",ios::binary|ios::in);
	if(!inFile)
	 {
		cout<<"File could not be open !! Press any Key...";
		return;
	 }
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"=============================================================================\n";
	cout<<"Accno   FIRSTNAME     LastName   accType       Balance          gender\n";
	cout<<"=============================================================================\n";
	while(inFile.read(reinterpret_cast<char *> (this), sizeof(*this)))
	 {
		report();
	 }
	inFile.close();
   }
   
void customer::deposit(int n,double am) //function to deposit amount

   {
	bool found=false;
	fstream File;
		File.open("bank.dat", ios::binary|ios::in|ios::out);
	if(!File)
	   {
		cout<<"File could not be open !! Press any Key...";
		return;
	   }
	while(!File.eof() && found==false)
	   {
		File.read(reinterpret_cast<char *> (this), sizeof(*this));
		if(accnum==n)
		  {
			show_account();
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				depo(am);
	    	int pos=(-1)*static_cast<int>(sizeof(*this));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (this), sizeof(*this));
			cout<<"\n\n\t balance updated";
			cout<<"\n\nyour balalnce is now"<<endl;
			cout<<amount;
			cout<<"\ndate of deposit";
			time_t t = time(NULL);
           tm* timePtr = localtime(&t);
           cout << "Date     " <<(timePtr->tm_mday)<<"/"<< (timePtr->tm_mon)+1 <<"/"<< (timePtr->tm_year)+1900<< endl;
           cout << "Time     " << (timePtr->tm_hour)<<":"<< (timePtr->tm_min)<<":"<< (timePtr->tm_sec) << endl;
			found=true;
	      }
       }
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
    }

  
void customer:: with(int n ,double am)   //fuction to withdraw amount
  {
	double wi;
	bool found=false;
	fstream File;
	File.open("bank.dat", ios::binary|ios::in|ios::out);
	if(!File)
	  {
		cout<<"File could not be open !! Press any Key...";
		return;
	  }
	while(!File.eof() && found==false)
	  {
		File.read(reinterpret_cast<char *> (this), sizeof(*this));
		if(accnum==n)
		  {
			show_account();
			cout<<"\n\n\tTO WITHDRAW AMOUNT ";
			withdraw(am);
	    	int pos=(-1)*static_cast<int>(sizeof(*this));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (this), sizeof(*this));
			cout<<"\n\n\t balance updated";
			cout<<"\n\nyour balalnce is now\n\t\t"<<endl;
			cout<<amount;
			cout<<"\n\ndate of withdraw \n";
			time_t t = time(NULL);
       tm* timePtr = localtime(&t);
       cout << "Date     " <<(timePtr->tm_mday)<<"/"<< (timePtr->tm_mon)+1 <<"/"<< (timePtr->tm_year)+1900<< endl;
       cout << "Time     " << (timePtr->tm_hour)<<":"<< (timePtr->tm_min)<<":"<< (timePtr->tm_sec) << endl;
			found=true;
	       }
       }
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
   }


int main()
  { 
  void intro();   
    system("color  2");
	customer cu;
	cu.calInterest();
	intro(); //intoduction
	int num1,num;//account number
  double money;
  	int n;
  
  	while(1)
	{
		system("cls");
		cout<<"\n\t================";
		cout<<"\n\n\tBANK MENU";
		cout<<"\n\t=================";
		cout<<"\n\n\t <1> ADMINISTRATOR";
		cout<<"\n\n\t <2> CUSTOMER";
	    cout<<"\n\n\t <3> EXIT";
	    cout<<"\n\n\t <4>about this app";
		cout<<"\n\t=====================";
		cout<<"\n\n\tSelect Your choice \t";
		cin>>n;
		system("cls");
		switch(n)
		{
		case 1:
	    cout<<"\n\t=====================";
		cout<<"\n\t MENUS OF ADMINSTRATER";
		cout<<"\n\t========================";
		cout<<"\n\n\t <1> Register new account";
		cout<<"\n\n\t <2> All account holder list";
		cout<<"\n\n\t <3> to delete an account ";
		cout<<"\n\n\t <4> to Modifay an account";
		cout<<"\n\n\t <5> Exit ";
        cout<<"\n\t=============================";
		cout<<"\n\n\tSelect Your choice \t";
		cin>>n;
		switch(n)
		{
	case 1:
		cu.write_account();
		break;
		
	case 2:
		cu.display_all();
		break;
		
	case 3:
		 cout<<"\n\n\tEnter The account No. : ";
		 cin>>num;
		cu.delete_account(num);
		 break;
		
	case 4:
		cout<<"\n\n\tEnter The account No. : ";
		cin>>num;
		cu.modify_account(num);
		break;

	case 5:
	    cout<<"thank you for using our bank system";
	    break;
	    
	default:
		cout<<"\n\n\t we have no more option";
        }
          break;
case 2:
	   cout<<"\n\t======================";
	   cout<<"\n\tMENUS FOR CUSTOMER";
	   cout<<"\n\t===================";
        cout<<"\n\n\t <1>. Deposit amount";
		cout<<"\n\n\t <2>. Withdraw amount";
		cout<<"\n\n\t <3>. TO see information about your account  ";
		cout<<"\n\n\t <4>.Transfer money";
		cout<<"\n\n\t <5>. Exit";
		cout<<"\n\t=============================================";
		cout<<"\n\n\tSelect Your choose\t";
		cin>>n;
        switch(n)
        {
    case 1:
		cout<<"\n\n\t Enter the account number\t";
		cin>>num;
		cout<<"\nEnter the amount of money to deposit\t";
		cin>>money;
		cu.deposit(num,money);
		 break;
		 
    case 2:
		cout<<"\n\n\t Enter the account number\t";
		cin>>num;
		cout<<"\nEnter the amount of money to withdraw\t";
		cin>>money;
		cu.with(num,money);
		 break;
		 
    case 3:
		cout<<"\n\n\t Enter the account number\t"	;
		cin>>num;
		cu.display_sp(num);
		break;
	
	case 4:
			cout<<"\n\n\t Enter the account No\t";
			cin>>num;
			cout<<"\nEnter the account number of reciver\t";
			cin>>num1;
			cout<<"\nEnter the amount of money\t";
			cin>>money;
			cu.transfer_money(num,num1,money);
			break;
			
	case 5:
			cout<<"\n\n\tThanks for using this bank ";
			break;
			
	default:
		    cout<<"\n\n\t ...... please enter a correct number";
		}
		break;
		
case 3:
	cout<<"\n\t Thanks for using this bank system";
   exit(0);
case 4:
	cu.group_members();
	}
	cin.ignore();
	cin.get();
}
}
void intro()
{
	cout<<"\n\t\t\t    WELL COME";
	cout<<"\n\t\t\t ===============";
	cout<<"\n\t\t\t   TO OUR BANK";
	cout<<"\n\t\t\t ==============";
	cout<<"\n\n\t\t\t RECORED SYSTEM";
	cout<<"\n\t\t\t =================";
	cout<<"\n\n\t\t\t Press any key to continue....";
    cin.get();
}
