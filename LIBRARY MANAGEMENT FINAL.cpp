 
//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************
#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<iomanip>
using namespace std;
//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************


class book
{
	char bno[6];
	char bname[50];
	char aname[20];
	int isd;
  public:
	void create_book()
	{
		char ch1,ch2;
        cout<<"\nNEW BOOK ENTRY...\n";
        cout<<"\nEnter The book no.";
        cin>>bno;
        cin.get(ch1);
        cout<<"\n\nEnter The Name of The Book ";
        gets(bname);
        cout<<"\n\nEnter The Author's Name ";
        gets(aname);
        cout<<"\n\n\nBook Created..";
        isd=0;
    }

    void show_book()
    {
        cout<<"\nBook no. : "<<bno;
        cout<<"\nBook Name : ";
        puts(bname);
        cout<<"Author Name : ";
        puts(aname);
        
    }

    void modify_book()
    {
        cout<<"\nBook no. : "<<bno;
        cout<<"\nModify Book Name : ";
        gets(bname);
        cout<<"\nModify Author's Name of Book : ";
        gets(aname);
    }

    char* retbno()
    {
        return bno;
    }

    void report()
    {cout<<bno<<setw(30)<<bname<<setw(30)<<aname<<endl;}
    
    int retisd()
    {
    	return isd;
	}
	
	void resetisd()
	{
		isd=0;
	}
	
	void addisd()
	{
		isd=1;
	}


};         //class ends here




class student
{
    char admno[6];
    char name[20];
    char stbno[6];
    int token;
public:
    void create_student()
    {
        char ch;
         cout<<"\nNEW STUDENT ENTRY...\n";
        cout<<"\nEnter The admission no. ";
        cin>>admno;
        cin.get(ch);
        cout<<"\n\nEnter The Name of The Student ";
        gets(name);
        token=0;
        stbno[0]='\0';
        cout<<"\n\nStudent Record Created..";
    }

    void show_student()
    {
        cout<<"\nAdmission no. : "<<admno;
        cout<<"\nStudent Name : ";
        puts(name);
        cout<<"\nNo of Book issued : "<<token;
        if(token==1)
            cout<<"\nBook No "<<stbno;
    }

    void modify_student()
    {
        cout<<"\nAdmission no. : "<<admno;
        cout<<"\nModify Student Name : ";
        gets(name);
    }

    char* retadmno()
    {
        return admno;
    }

    char* retstbno()
    {
        return stbno;
    }

    int rettoken()
    {
        return token;
    }

    void addtoken()
    {token=1;}

    void resettoken()
    {token=0;}

    void getstbno(char t[])
    {
        strcpy(stbno,t);
    }

    void report()
    {cout<<"\t"<<admno<<setw(20)<<name<<setw(10)<<token<<endl;}

};         //class ends here




//***************************************************************
//        global declaration for stream object, object
//****************************************************************

fstream fp,fp1;
ofstream f1;
book bk;
student st;


//***************************************************************
//        function to write in file
//****************************************************************

void write_book()
{
    char ch;
    f1.open("book.dat",ios::out|ios::app);
    do
    {
        
        bk.create_book();
        f1.write((char*)&bk,sizeof(book));
        cout<<"\n\nDo you want to add more record..(y/n?)";
        cin>>ch;
    }while(ch=='y'||ch=='Y');
    f1.close();
}

void write_student()
{
    char ch;
    f1.open("student.dat",ios::out|ios::app);
    do
    {
        st.create_student();
        f1.write((char*)&st,sizeof(student));
        cout<<"\n\ndo you want to add more record..(y/n?)";
        cin>>ch;
    }while(ch=='y'||ch=='Y');
    f1.close();
}


//***************************************************************
//        function to read specific record from file
//****************************************************************


void display_spb(char n[])
{
    cout<<"\nBOOK DETAILS\n";
    int flag=0;
    fp.open("book.dat",ios::in);
    while(fp.read((char*)&bk,sizeof(book)))
    {
        if(strcmpi(bk.retbno(),n)==0)
        {
            bk.show_book();
             flag=1;
        }
    }
    
    fp.close();
    if(flag==0)
        cout<<"\n\nBook does not exist";
    getch();
}

void display_sps(char n[])
{
    cout<<"\nSTUDENT DETAILS\n";
    int flag=0;
    fp.open("student.dat",ios::in);
    while(fp.read((char*)&st,sizeof(student)))
    {
        if((strcmpi(st.retadmno(),n)==0))
        {
            st.show_student();
            flag=1;
        }
    }
    
    fp.close();
    if(flag==0)
            cout<<"\n\nStudent does not exist";
     getch();
}


//***************************************************************
//        function to modify record of file
//****************************************************************


void modify_book()
{
    char n[6];
    int found=0;
    
    cout<<"\n\n\tMODIFY BOOK REOCORD.... ";
    cout<<"\n\n\tEnter The book no. of The book";
    cin>>n;
    fp.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&bk,sizeof(book)) && found==0)
    {
        if(strcmpi(bk.retbno(),n)==0)
        {
            bk.show_book();
            cout<<"\nEnter The New Details of book"<<endl;
            bk.modify_book();
            //int pos=-1*sizeof(bk);
                fp.seekp(-1*sizeof(bk),ios::cur);
                fp.write((char*)&bk,sizeof(book));
                cout<<"\n\n\t Record Updated";
                found=1;
        }
    }

        fp.close();
        if(found==0)
            cout<<"\n\n Record Not Found ";
        getch();
}


void modify_student()
{
    char n[6];
    int found=0;
    
    cout<<"\n\n\tMODIFY STUDENT RECORD... ";
    cout<<"\n\n\tEnter The admission no. of The student";
    cin>>n;
    fp.open("student.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
    {
        if(strcmpi(st.retadmno(),n)==0)
        {
            st.show_student();
            cout<<"\nEnter The New Details of student"<<endl;
            st.modify_student();
            //int pos=-1*sizeof(st);
            fp.seekp(-1*sizeof(st),ios::cur);
            fp.write((char*)&st,sizeof(student));
            cout<<"\n\n\t Record Updated";
            found=1;
        }
    }
    
    fp.close();
    if(found==0)
        cout<<"\n\n Record Not Found ";
    getch();
}

//***************************************************************
//        function to delete record of file
//****************************************************************


void delete_student()
{
    char n[6];
    int flag=0;    
    
        cout<<"\n\n\n\tDELETE STUDENT...";
        cout<<"\n\nEnter The admission no. of the Student You Want To Delete : ";
        cin>>n;
        fp.open("student.dat",ios::in|ios::out);
        fstream fp2;
        fp2.open("Temp.dat",ios::out);
        fp.seekg(0,ios::beg);
        while(fp.read((char*)&st,sizeof(student)))
    {
        if(strcmpi(st.retadmno(),n)!=0)
                 fp2.write((char*)&st,sizeof(student));
        else
               flag=1;
    }
        
    fp2.close();
        fp.close();
        remove("student.dat");
        rename("Temp.dat","student.dat");
        if(flag==1)
             cout<<"\n\n\tRecord Deleted ..";
        else
             cout<<"\n\nRecord not found";
        getch();
}


void delete_book()
{
    char n[6];
    
    cout<<"\n\n\n\tDELETE BOOK ...";
    cout<<"\n\nEnter The Book no. of the Book You Want To Delete : ";
    cin>>n;
    fp.open("book.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&bk,sizeof(book)))
    {
        if(strcmpi(bk.retbno(),n)!=0)  
        {
            fp2.write((char*)&bk,sizeof(book));
        }
    }
        
    fp2.close();
        fp.close();
        remove("book.dat");
        rename("Temp.dat","book.dat");
        cout<<"\n\n\tRecord Deleted ..";
        getch();
}



//***************************************************************
//        function to display all students list
//****************************************************************

void display_alls()
{
    
         fp.open("student.dat",ios::in);
         if(!fp)
         {
               cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
               getch();
               return;
         }

    cout<<"\n\n\t\tSTUDENT LIST\n\n";
    cout<<"==================================================================\n";
    cout<<"\tAdmission No."<<setw(10)<<"Name"<<setw(20)<<"Book Issued\n";
    cout<<"==================================================================\n";

    while(fp.read((char*)&st,sizeof(student)))
    {
        st.report();
    }
         
    fp.close();
    getch();
}


//***************************************************************
//        function to display Books list
//****************************************************************

void display_allb()
{
    
    fp.open("book.dat",ios::in);
    if(!fp)
    {
        cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
               getch();
               return;
         }

    cout<<"\n\n\t\tBook LIST\n\n";
    cout<<"=========================================================================\n";
    cout<<"Book Number"<<setw(20)<<"Book Name"<<setw(25)<<"Author\n";
    cout<<"=========================================================================\n";

    while(fp.read((char*)&bk,sizeof(book)))
    {
        bk.report();
    }
         fp.close();
         getch();
}




//***************************************************************
//        functions and structure for date calculation
//****************************************************************


struct date
{
	int d,m,y;
}datei,dated;
const int month[12]={31,28,31,30,31,30,31,31,30,31,30,31};
int isleapyear(date de)
{
	int year=de.y;
	if(year%100==0)
	{
		if(year%400==0)
		return 1;
		else return 0;
	}
	else if(year%4==0)
	return 1;
	else
	return 0;
}
int isvaliddate(date dt)
{
	    if((dt.m>=1)&&(dt.m<=12))
	    {
		
		if((dt.d<=month[dt.m-1])&&(dt.d>=1))
		return 1;
		else if((dt.m==2)&&(isleapyear(dt))&&(dt.d<=29))
		return 1;
		else 
		return 0;
	}
	else 
	return 0;
	
}
int countleapyear(date dt)
{
	int year=dt.y;
    if(dt.m<=2)
	year--;
	return year/4-year/100+year/400;	
}
long counttotal(date da)
{
	long n=da.y*365+da.d;
	int i;
	for(i=0;i<da.m-1;i++)
	n=n+month[i];
	n=n+countleapyear(da);
	return n;
}
void calculatefine()
{
	long n1,n2,n,f=0;
	n1=counttotal(datei);
	n2=counttotal(dated);
	n=n2-n1;
	if(n>15)
	f=(n-15)*10;
	cout<<"Total number of days book kept: "<<n<<"\n"<<"Fine: Rs"<<f;
}





//***************************************************************
//        function to issue book
//****************************************************************

void book_issue()
{
    char sn[6],bn[6];
    int found=0,flag=0;
    
    cout<<"\n\nBOOK ISSUE ...";
    cout<<"\n\n\tEnter The student's admission no.";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
        fp1.open("book.dat",ios::in|ios::out);
        while(fp.read((char*)&st,sizeof(student)) && found==0)
           {
        if(strcmpi(st.retadmno(),sn)==0)
        {
            found=1;
            if(st.rettoken()==0)
            {
                      cout<<"\n\n\tEnter the book no. ";
                cin>>bn;
                while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
                {
                       if(strcmpi(bk.retbno(),bn)==0)
                    {
                    	if(bk.retisd()==0)
                    	{						
                        bk.show_book();
                        flag=1;
                        st.addtoken();
                        bk.addisd();
                        st.getstbno(bk.retbno());
                               //int pos=-1*sizeof(st);
                        fp.seekp(-1*sizeof(st),ios::cur);
                        fp.write((char*)&st,sizeof(student));
                        do
						{
                        cout<<"Enter date of issue DD \n";
                        cin>>datei.d;
	                    cout<<"Enter month of issue MM \n";
	                    cin>>datei.m;
	                    cout<<"Enter year of issue YYYY \n";
	                    cin>>datei.y;
	                    if(isvaliddate(datei)==0)
	                    cout<<"The date is not valid. Enter a valid date \n";
	                    }while(isvaliddate(datei)==0);
	                    fp1.seekp(-1*sizeof(bk),ios::cur);
                        fp1.write((char*)&bk,sizeof(book));
                        cout<<"\n\nBook issued succesfully \n";
                    }
                    else
                    {
                    		cout<<"Book already issued to someone else \n";
					}
                }
                }
                
                  if(flag==0)
                        cout<<"Book  does not exist";
            }
                else
                  cout<<"You have not returned the last book ";

        }
    }
          if(found==0)
        cout<<"Student record not exist...";
    getch();
      fp.close();
      fp1.close();
}

//***************************************************************
//        function to deposit book
//****************************************************************

void book_deposit()
{
    char sn[6],bn[6];
    int found=0,flag=0,day,fine;
    
    cout<<"\n\nBOOK DEPOSIT ...";
    cout<<"\n\n\tEnter The student's admission no.";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
    fp1.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
       {
        if(strcmpi(st.retadmno(),sn)==0)
        {
            found=1;
            if(st.rettoken()==1)
            {
            while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
            {
               if(strcmpi(bk.retbno(),st.retstbno())==0)
            {
                bk.show_book();
                flag=1;
                long n1=counttotal(datei),n2=0;
                do
                {
				
                cout<<"Enter date of deposit DD \n";
            	cin>>dated.d;
	            cout<<"Enter month of deposit MM \n";
	            cin>>dated.m;
	            cout<<"Enter year of deposit YYYY \n";
           	    cin>>dated.y;
           	    n2=counttotal(dated);
           	    if((isvaliddate(dated)==0)||(n2<n1))
           	    cout<<"Invalid date. Enter a valid date \n";
           	    }while((isvaliddate(dated)==0)||(n2<n1));
                    st.resettoken();
                    bk.resetisd();
                    //int pos=-1*sizeof(st);
                    fp.seekp(-1*sizeof(st),ios::cur);
                    fp.write((char*)&st,sizeof(student));
                    cout<<"\n\n\t Book deposited successfully \n";
                    calculatefine();
                    fp1.seekp(-1*sizeof(bk),ios::cur);
                    fp1.write((char*)&bk,sizeof(book));
            }
            }
          if(flag==0)
            cout<<"Book no does not exist";
              }
         else
            cout<<"No book is issued..please check!!";
        }
       }
      if(found==0)
    cout<<"Student record not exist...";
    getch();
  fp.close();
  fp1.close();
  }




//***************************************************************
//        INTRODUCTION FUNCTION
//****************************************************************

void intro()
{
    
    
    cout<<"LIBRARY MANAGEMENT SYSTEM";
    cout<<"\n\nMADE BY : DIPANWITA & PRERANA";
    cout<<"\n\nSCHOOL : HARIYANA VIDYA MANDIR";
    getch();
}



//***************************************************************
//        ADMINISTRATOR MENU FUNCTION
//****************************************************************

void admin_menu()
{
    
    int ch2;
    cout<<"\n\n\n\tADMINISTRATOR MENU";
    cout<<"\n\n\t1.CREATE STUDENT RECORD";
    cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORD";
    cout<<"\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD ";
    cout<<"\n\n\t4.MODIFY STUDENT RECORD";
    cout<<"\n\n\t5.DELETE STUDENT RECORD";
    cout<<"\n\n\t6.CREATE BOOK ";
    cout<<"\n\n\t7.DISPLAY ALL BOOKS ";
    cout<<"\n\n\t8.DISPLAY SPECIFIC BOOK ";
    cout<<"\n\n\t9.MODIFY BOOK ";
    cout<<"\n\n\t10.DELETE BOOK ";
    cout<<"\n\n\t11.BACK TO MAIN MENU";
    cout<<"\n\n\tPlease Enter Your Choice (1-11) ";
    cin>>ch2;
    switch(ch2)
    {
            case 1: 
                write_student();break;
            case 2: display_alls();break;
            case 3:
                   char num[6];
                   
                   cout<<"\n\n\tPlease Enter The Admission No. ";
                   cin>>num;
                   display_sps(num);
                   break;
              case 4: modify_student();break;
              case 5: delete_student();break;
        case 6: 
            write_book();break;
        case 7: display_allb();break;
        case 8: {
                   char num[6];
                   
                   cout<<"\n\n\tPlease Enter The book No. ";
                   cin>>num;
                   display_spb(num);
                   break;
            }
              case 9: modify_book();break;
              case 10: delete_book();break;
             case 11: return;
              default:cout<<"\a";
       }
       admin_menu();
}


//***************************************************************
//        THE MAIN FUNCTION OF PROGRAM
//****************************************************************


int main()
{
    char ch;
    intro();
    do
    {
        
        cout<<"\n\n\n\tMAIN MENU";
        cout<<"\n\n\t01. BOOK ISSUE";
        cout<<"\n\n\t02. BOOK DEPOSIT";
          cout<<"\n\n\t03. ADMINISTRATOR MENU";
          cout<<"\n\n\t04. EXIT";
          cout<<"\n\n\tPlease Select Your Option (1-4) ";
          ch=getche();
          switch(ch)
          {
            case '1':
                 book_issue();
                    break;
              case '2':book_deposit();
                     break;
              case '3':admin_menu();
                 break;
              case '4':exit(0);
              default :cout<<"\a";
        }
        }while(ch!='4');
        getch();
        return 0;
}

//***************************************************************
//                END OF PROJECT
//***************************************************************

