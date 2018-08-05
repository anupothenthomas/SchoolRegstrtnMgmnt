#include <iostream>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<iomanip>
#include<fstream>
#include<dos.h>

//A DATA STRUCTURE IS A GROUP OF DATA ELEMENTS GROUPED TOGETHER UNDER ONE NAME.
//THESE DATA ELEMENTS, KNOWN AS MEMBERS, CAN HAVE DIFFERENT TYPES AND DIFFERENT LENGTHS
// THE FOLLOWING ARE THE DATA STRUCTURES DECLARED USING STRUCT KEYWORD IN ORDER TO LET THE DEVELOPER STORE A SEPERATE DATA STRUCTURE
//TO STORE THE ATTRIBUTES AND DATA INSIDE THEM

// DATA STRUCTURE STUCT MARKS_CRITERIA
struct marks_criteriaol
{
    int sc_min,com_min,arts_min, seat_sc, seat_com, seat_arts;
}
crit;

// DATA STRUCTURE STUCT ADMINISTRATOR
struct administrator
{
    char user_name[10];
    char password[10];
}
admin;

// DATA STRUCTURE STUCT STUDENT
struct student
{
    char name[20];
    int regno,m_eng,m_math,m_sc,m_sst,m_lang;
    int pref_code, stream; // Sc=1, Com=2; Arts=3;

    //PUBLIC METHOD DECLARATIONS, WHICH ARE ACCESSIBLE TO ALL THE MEMBERS AND METHODS OF THE CLASS
public:
    void new_file();
    void input_data();
    void allot_stream();
    int get_stream();
    void display();
    int show_per()
    {
        return((m_eng+m_math+m_sc+m_sst+m_lang)/5);
    }
};
void welcome();
void menu();
int verify_password();
void assign_user();
void clear();
void input_criteria();
void read_criteria();
void read_student();
void create_eligible_sc();
void create_eligible_com();
void create_eligible_arts();
void read_eligible_sc();
void read_eligible_com();
void read_eligible_arts();
char * stream_name(int strm);
void select_list( char *in_file, char *out_file);
void thanks();
student s;

// USING NAMESPACE STD IS AN ABBREVIATION OF STANDARD.
// STD IS THE STANDARD NAMESPACE.
//COUT, CIN AND A LOT OF OTHER THINGS ARE DEFINED IN IT.
//YOU CAN ALSO CALL THESE FUNCTIONS USING STD::COUT , STD::CIN ETC.
//BUT FOR OUR CONVENIENCE WE DECLARE IT IN THE BEGINNING TO AVOID CALLING FUNCTIONS USING STD::COUT, STD::CIN,
//RATHER WE CAN NOW CALL THEM SIMPLY AS COUT, CIN.......

using namespace std;

// VOID CLRSCR IS A METHOD TO INVOKE CLRSCR(), IF UNABLE TO INVOKE THE METHOD IMPLICITLY,
//( IMPLICIT METHOD INVOKE means - THE COMPILER INVOKES THE METHOD ON IT'S OWN WITHOUT ANY TRIGGER FROM THE USER)
void clrscr()
{
#ifdef WINDOWS
    system("cls");
#endif
#ifdef LINUX
    system("clear");
#endif
}

// THE MAIN METHOD FROM WHERE THE EXECUTION STARTS, IN C AND C++ THE EXECUTION IS IN SEQUENTIAL STEPS SINCE IT IS A PROCEDURAL PROGRAMMING LANGUAGE
int main()
{
    clrscr();
    welcome();
    fstream fin, fout;
    fstream fsc, fcom, farts;
    int opt=1, ch;
// UNTIL OPT OPTION IS NOT EQUAL TO 8, DISPLAY ALL THIS OPERATIONS MENU.... IF OPT==8, GO TO THE END OF THIS WHILE LOOP, IT RETURNS 0
    while(opt!=8)
    {
        // clrscr();
        clear();
        cout<<"\n\t====================== OPERATIONS MENU ======================\n";
        cout<<"\n\n\t[1] CREATE / MODIFY ADMISSION CRITERIA(Administrator only)";
        cout<<"\n\n\t[2] ENTER STUDENT'S DATA ";
        cout<<"\n\n\t[3] ALLOTMENT OF STREAM";
        cout<<"\n\n\t[4] DISPLAY CRITERIA FOR SELECTION";
        cout<<"\n\n\t[5] DISPLAY ALLOTMENT OF STUDENT'S STREAM";
        cout<<"\n\n\t[6] DISPLAY ALL STUDENT'S REGISTERED";
        cout<<"\n\n\t[7] CREATE / DISPLAY MERIT LIST";
        cout<<"\n\n\t[8] QUIT";
        cout<<"\n\t=============================================================\n";
        cout<<"\n\n\t\tEnter your choice : ";
        cin>>opt;

        //IMPORTANT .....!!!  SWITCH CASES ARE USED WHEN WE HAVE FIXED SET OF VALUES, ALSO
        // SWITCH CASE BEGINS, WITH OPT AS THE VARIABLE FOR SELECTION
        switch(opt)
        {

           // CHOICE 1, CHOICE TO CREATE OR MODIFY ADMISSION CRITERIA, ONLY ADMINS CAN,
           //
           // ADMIN USERNAME - RIA
           // ADMIN PASSWORD - RIA
           //
           //
        case 1:
            int p;
            assign_user();
            p=verify_password();
            if(p==0)
            {
                input_criteria();
            }
            else
            {
                cout<<"\n\t YOU ARE AN INVALID USER";
                cout<<"\n\t YOU ARE RESTRICTED FROM CREATING THE QUESTION BANK... (PS: DO NOT TRY TO TRESPASS AGAIN)\n\n";
            }
            break;

        // CHOICE 2, CHOICE TO ENTER STUDENT'S DATA
        case 2:
            int option;
            clrscr();
            cout<<"\nWHAT WOULD YOU LIKE TO DO --\n\n\n\n\n\tPRESS 1 - CREATE A NEW STUDENT INFORMATION FILE \n PRESS 2- APPEND TO THE EXISTING FILE";
            cin>>option;
            if(option==1)
            {
                s.new_file();
            }
            else
            {
                s.input_data();
            }
            break;

            // CHOICE 3, CHOICE TO READ STUDENT'S ALLOTMENT
        case 3:
            clrscr(); //	read_student();
            fin.open("STUDENT",ios::in|ios::out);
            fsc.open("ELIG_SCIENCE",ios::out);
            fcom.open("ELIG_COMMERCE",ios::out);
            farts.open("ELIG_ART",ios::out);
            while(fin.read((char*)& s,sizeof(s)))
            {
                s.allot_stream();
                s.get_stream();   //if(s.get_stream()==0)
                cout<<"\nDUDE YOU ARE NOT ELIGIBLE\n<<APPLICATION REJECTED>>";
                if(s.get_stream()==1)
                    fsc.write((char*)& s,sizeof(s));
                if(s.get_stream()==2)
                    fcom.write((char*)& s,sizeof(s));
                if(s.get_stream()==3)
                    farts.write((char*)& s,sizeof(s));
            }
            fin.close();
            fsc.close();
            fcom.close();
            farts.close();
            cout<<"\n*******************************************";
            cout<<"\n\n\tSTREAM ALLOCATION DONE.";
            cout<<"\n*******************************************";
            break;

             // CHOICE 4, DISPLAY CRITERIAS FOR SELECTION INTO CORRESPONDING STREAMS USING THE METHOD VOID READ_CRITERIA, WHICH HAVE THE CRIT.SC_MIN, CRIT.COM_MIN AND CRIT.ARTS_MIN ATTRIBUTES
        case 4:
            read_criteria();
            //	clear();
            cout<<"\n SCIENCE : "<<crit.sc_min;
            cout<<"\n COMMERCE : "<<crit.com_min;
            cout<<"\n ARTS : "<<crit.arts_min;
            break;

            // CHOICE 5, DISPLAYS ALLOTMENTS MADE FOR STUDENTS IN STREAMS, FROM METHODS : VOID READ_ELIGIBLE_SC(), VOID READ_ELIGIBLE_COM(), VOID READ_ELIGIBLE_ARTS())
        case 5:
            cout<<"\nENTER:\n1.) FOR SCIENCE\n2.) FOR COMMERCE\n3.) FOR ARTS ";
            cin>>ch;

            if (ch==1)
                read_eligible_sc();
            if (ch==2)
                read_eligible_com();
            if (ch==3)
                read_eligible_arts();
            break;

            // CHOICE 6, DISPLAY ALL STUDENT'S REGISTERED, READS THE DATA FROM METHOD: VOID READ_STUDENT();
        case 6:
            clrscr() ;
            read_student();
            break;

            // CHOICE 7,DISPLAYS THE MERIT LIST OF THE CORRESPONDING STREAM
        case 7:
        {
            char c;
            int k=1;
            cout<<"\n****************************************\n";
            cout<<"\n ---------M E R I T   L I S T-----------";
            cout<<"\n\n";
            cout<<"\n\t Enter 1 for MERIT LIST SCIENCE ";
            cout<<"\n\t Enter 2 for MERIT LIST COMMERCE ";
            cout<<"\n\t Enter 3 for MERIT LIST ARTS ";
            cout<<"\n\n";
            cout<<"\n****************************************";
            cout<<"\n\nENTER YOUR CHOICE: ";
            cin>>k;
            if (k==1)
            {
                select_list("ELIG_SCIENCE","SELL_SCIENCE");
                fin.open("SELL_SCIENCE",ios::in);
            }
            if (k==2)
            {
                select_list("ELIG_COMMERCE","SELL_COMMERCE");
                fin.open("SELL_COMMERCE",ios::in);
            }
            if (k==3)
            {
                select_list("ELIG_ART","SELL_ART");
                fin.open("SELL_ART",ios::in);
            }
            if(k>=1 && k<=3)
            {
                while(fin.read((char*)& s,sizeof(s)))
                {
                    s.display();
                    cout<<"\n\t CONTINUE (Y/N)?";
                    cin>>c;
                    if(c=='n')
                        break;
                }
            }
            fin.close();
            fin.close();
            fin.close();
            break;
        }

        // CHOICE 8, OF SWITCH-CASE, RETURNS THE METHOD : VOID THANKS()
        case 8:
            thanks();
            //	cout< <"\nTHANKS BYE ";
            //	exit(0);
            break;
        }
    }
    return 0;
}

// END OF WHILE

// ASSIGNING THE USERNAME AND PASSWORD AS ADMIN TO RIA SANTOSH MATHEW WITH THE FOLLOWING CREDENTIALS

void assign_user()
{
    {
        strcpy(admin.user_name, "ria");
        strcpy(admin.password, "ria");

    }
}

// METHOD TO VERIFY PASSWORD ENTERED BY A USER

int verify_password()
{
    char u_name[10];
    char u_pwd[10],temp[2];
    int x=1;
    cout<<"\n\n ENTER USERNAME:";
    cin>>u_name;
    cout<<"\n\n ENTER PASSWORD:";
    cin>>u_pwd;
    x=strcmp(admin.user_name,u_name);
    if (x==0)
    {
        x=strcmp(admin.password,u_pwd);
    }
    cin.getline(temp,2);
    return(x);
}

// METHOD TO ALLOT THE STREAM TO THE STUDENT WITHOUT ANY RETURN

void student::allot_stream()
{
    int	per=(m_eng+m_math+m_sc+m_sst+m_lang)/5;
    read_criteria();
    switch(pref_code)
    {
    case 1:
        if(per>=crit.sc_min)
            stream=pref_code;
        else
            stream=0;
        break;
    case 2:
        if(per>=crit.com_min)
            stream=pref_code;
        else
            stream=0;
        break;
    case 3:
        if(per>=crit.arts_min)
            stream=pref_code;
        else
            stream=0;
        break;
    }
}

// METHOD TO FETCH THE STREAM OF A PARTICULAR STUDENT; METHOD RETURNS THE STREAM

int student::get_stream()
{
    return(stream);
}

// METHOD TO INPUT THE CRITERIAS [ MARKS & SEATS ] FOR EACH STREAM, METHOD RETURNS NOTHING

void input_criteria()
{
    fstream fout;
    fout.open("CRITERIA",ios::in|ios::out);
    cout<<"\nENTER THE REQUIRED MARKS FOR SCIENCE STREAM(IN PERCENTAGE)";
    cin>>crit.sc_min;
    cout<<"\nENTER NO. OF SEATS FOR SCIENCE STREAM";
    cin>>crit.seat_sc;
    cout<<"\nENTER THE REQUIRED MARKS FOR COMMERCE STREAM(IN PERCENTAGE)";
    cin>>crit.com_min;
    cout<<"\nENTER NO. OF SEATS FOR COMMERCE STREAM";
    cin>>crit.seat_com;
    cout<<"\nENTER THE REQUIRED MARKS FOR ARTS STREAM(IN PERCENTAGE)";
    cin>>crit.arts_min;// END OF WHILE

    cout<<"\nENTER NO. OF SEATS FOR ARTS STREAM";
    cin>>crit.seat_arts;
    fout.write((char*)& crit,sizeof(crit));
    fout.close();
}

// METHOD READS THE CRITERIA THAT HAS BEEN SET BY THE ADMIN, RETURNS NOTHING

void read_criteria()
{
    fstream fin;
    fin.open("CRITERIA",ios::in);
    fin.read((char*)& crit,sizeof(crit));
    fin.close();
}

// METHOD TO INPUT THE DATA OF A STUDENT, THE METHOD DOESN'T RETURN ANYTHING

void student::input_data()
{
    clrscr();
    fstream fin;
    fin.open("STUDENT",ios::app|ios::out);
    char t[2], ans;
    while(1)
    {
        cout<<"\nENTER THE NAME OF THE STUDENT : ";
        gets(name);
        cout<<"\n\nENTER THE ROLL OF THE STUDENT : ";
        cin>>regno;
        cout<<"\n\nENTER MARKS IN ENGLISH : ";
        cin>>m_eng;
        cout<<"\n\nENTER MARKS IN MATHEMATICS : ";
        cin>>m_math;
        cout<<"\n\nENTER MARKS IN SCIENCE : ";
        cin>>m_sc;
        cout<<"\n\nENTER MARKS IN SOCIAL STUDIES : ";
        cin>>m_sst;
        cout<<"\n\nENTER MARKS IN LANGUAGE : ";
        cin>>m_lang;
        cout<<"\n==================WHICH STREAM PREFERED?================ \n";
        cout<<"\t"<<"[1] for SCIENCE\n";
        cout<<"\t"<<"[2] for COMMERCE\n";
        cout<<"\t"<<"[3] for ARTS ";
        cout<<"\n======================================================== \n\tENTER PREFERENCE CODE : ";
        cin>>pref_code;
        stream=-1;
        fin.write((char*)&s,sizeof(s));
        cin.getline(t,2);
        cout<<"\n\tENTER MORE STUDENT ? (Y/N)";
        cin>>ans;
        if (ans=='n')
            break;
    }
    fin.close();
}

// METHOD TO CREATE NEW FILE FOR A STUDENT, THE METHOD RETURNS NOTHING

void student::new_file()
{
    clrscr();
    fstream fin;
    fin.open("STUDENT",ios::out);
    char t[2], ans;
    while(1)
    {
        cout<<"\nENTER THE NAME OF THE STUDENT : ";
        gets(name);
        cout<<"\n\nENTER THE ROLL OF THE STUDENT : ";
        cin>>regno;
        cout<<"\n\nENTER MARKS IN ENGLISH : ";
        cin>>m_eng;
        cout<<"\n\nENTER MARKS IN MATHEMATICS : ";
        cin>>m_math;
        cout<<"\n\nENTER MARKS IN SCIENCE : ";
        cin>>m_sc;
        cout<<"\n\nENTER MARKS IN SOCIAL STUDIES : ";
        cin>>m_sst;
        cout<<"\n\nENTER MARKS IN LANGUAGE : ";
        cin>>m_lang;
        cout<<"==================STREAM PREFERED?================ \n";
        cout<<"\t"<<"[1] for SCIENCE\n";
        cout<<"\t"<<"[2] for COMMERCE\n";
        cout<<"\t"<<"[3] for ARTS ";
        cout<<"\n================================================= \n\tENTER PREFERENCE CODE : ";
        cin>>pref_code;
        stream=-1;
        fin.write((char*)&s,sizeof(s));
        cin.getline(t,2);
        cout<<"\n\tENTER MORE STUDENT ? (Y/N)";
        cin>>ans;
        if (ans=='n')
            break;
    }
    fin.close();
}

// METHOD TO DISPLAY THE DETAILS OF A STUDENT, RETURNS THE DETAILS TO THE USER

void student::display()
{
    cout<<"\n============================================\n";
    cout<<"\n\tNAME	: "<<name;
    cout<<"\n\tREGISTRATION NO.	: "<<regno;
    cout<<"\n\tPERCENTAGE OF MARKS	: "<<((m_eng+m_math+m_sc+m_sst+m_lang)/5)<<"%";
    cout<<"\n\tSTREAM APPLIED FOR	: "<<stream_name(pref_code);
    cout<<"\n============================================\n";
}

// METHOD TO READ FROM THE STUDENT DETAILS

void read_student()
{
    fstream fin;
    char c;
    fin.open("STUDENT", ios::in);
    while(fin.read((char*)& s, sizeof(s)))
    {
        s.display();
        cout<<"\n\tPRESS ANY NO. TO CONTINUE ";
        cin>>c;
        cout<<"\n";
    }
    fin.close();
}

// METHOD TO READ THE ELIGIBILITY CRITERIA OF SCIENCE STREAM

void read_eligible_sc()
{
    char ans;
    fstream fout;
    fout.open("ELIG_SCIENCE",ios::in);
    fout.seekg(0);
    while(fout.read((char*)& s,sizeof(s)))
    {
        s.display();
        cout<<"\n\t CONTINUE (Y/N)? ";
        cin>>ans;
        if (ans=='n')
            break;
    }
    fout.close();
}

// METHOD TO READ THE ELIGIBILITY CRITERIA OF THE COMMERCE

void read_eligible_com()
{
    char ans;
    fstream fout;
    fout.open("ELIG_COMMERCE",ios::in);
    while(fout.read((char*)& s,sizeof(s)))
    {
        s.display();
        cout<<"\n\t CONTINUE (Y/N)? ";
        cin>>ans;
        if (ans=='n')
            break;
    }
    fout.close();
}

// METHOD TO READ THE ELIGIBILITY CRITERIA OF THE ARTS

void read_eligible_arts()
{
    char ans;
    fstream fout;
    fout.open("ELIG_ART",ios::in);
    while(fout.read((char*)& s,sizeof(s)))
    {
        s.display();
        cout<<"\n\t CONTINUE (Y/N)? ";
        cin>>ans;
        if (ans=='n')
            break;
    }
    fout.close();
}

// TEST METHOD TO CLEAR THE VALUES- OPTIONAL

void clear()
{
    //	for(int i=1;i< =24;i++) //	cout<<"\n";
}

// METHOD THAT USES SWITCH-CASE WITH THE HELP OF POINTERS TO THE STREAM_NAME, RETURNS THE MESSAGE CORRESPONDING TO THE INPUT(STRM)
char * stream_name(int strm)
{
    switch(strm)
    {
    case -1:
        return("NOT ASSIGNED"); //	break;
    case 0:
        return("NILL"); //	break;
    case 1:
        return("SCIENCE"); //	break;
    case 2:
        return("COMMERCE"); //	break;
    case 3:
        return("ARTS"); //	break;
    default:
        return("NONE");
    }
}

// METHOD TO SELECT THE LIST USING POINTERS TO IN_FILE AND OUT_FILE

void select_list( char *in_file, char *out_file)
{
    fstream sel, fin;
    int n=0, i,j;
    student sl[100], t;

    sel.open(out_file, ios::out);
    fin.open(in_file,ios::in);

    while(fin.read((char*)& sl[n],sizeof(s)))
    {
        n++;
    }
    cout<<"\nNO OF ELIGIBLE STUDENTS = "<<n<<"\n";
    for(i=0; i<n; i++)
    {

        for(j=i+1; j<=n; j++)
        {

            if(sl[i].show_per()<sl[j].show_per())
            {

                t=sl[j];
                sl[j] = sl[i];
                sl[i] = t;

            }
        }
    }
    for(i=0; i<n; i++)
    {

        sel.write((char*)& sl[i], sizeof(s));
    }
    sel.close();
    fin.close();
}

// METHOD TO DISPLAY THE FRONT MESSAGE ON CONSOLE STARTUP

void welcome()
{

    clrscr();
    int z;
    cout<<"\t  %%      %% ";
    cout<<"\n\t  %%  %%  %% %%%%%%% %%      %%%%%%% %%%%%% %%%% %%%% %%%%%";
    cout<<"\n\t  %%  %%  %% %%      %%      %%      %%  %% %% %%% %% %%";
    cout<<"\n\t  %%  %%  %% %%%%%   %%      %%      %%  %% %% %%% %% %%%%%";
    cout<<"\n\t  %%  %%  %% %%      %%      %%      %%  %% %%     %% %%";
    cout<<"\n\t  %%%%%%%%%% %%%%%%% %%%%%%% %%%%%%% %%%%%% %%     %% %%%%%";
    cout<<"\n";

    cout<<"\n\t--------COMPUTER SCIENCE PROJECT->STREAM ALLOCATION---------";
    cout<<"\n";
    cout<<"\n\t--------------------------- BY -----------------------------";
    cout<<"\n";
    cout<<"\n\t----------------------RIA S. MATHEW XII-B-------------------";
    cout<<"\n";
    cout<<"\n\t--------------------ANUGRAHA MOL BENNY XII-B----------------";
    cout<<"\n";
    cout<<"\n\t--------------------<<>>--<<>>--<<>>--<<>>------------------";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n\t          PRESS ANY NUMBER AND THEN 'ENTER' TO EXIT";
    cout<<"\n";
    cin>>z;

// getch();
}

// METHOD TO DISPLAY THANKS WHEN THE USER IS DONE PERFORMING OPERATIONS

void thanks()
{
    int w;
    clrscr();
    cout<<"\n\n\n\n\t******************  T H A N K   Y O U *********************";
    cout<<"\n\n\t******* PRESS ANY NUMBER AND THEN 'ENTER' TO EXIT **********\n\n";
    cin>>w;
}


//</dos>
//</fstream>
//</iomanip>
//</string>
//</stdio>
//</conio>
//</iostream>

