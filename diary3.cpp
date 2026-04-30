#include <iostream>
#include <fstream>   
#include <string>
#include <cstdio>    
#include <cstdlib>   
using namespace std;

class DiaryEntry 
{
public:
    string date;
    string text;

    void createEntry();
    void displayEntries();
    void editEntry();
    void deleteEntry();
};

void login() 
{
    string pass;
    cout<<"============================\n";
    cout<<"   DIGITAL DIARY LOGIN\n";
    cout<<"Enter Password: ";
    cin>>pass;

    if (pass!="1102") {
        cout<<"Incorrect Password! Access Denied.\n";
        exit(0);
    }
    cout<<"Successfully logged in!\n";
}

void DiaryEntry::createEntry()
 {
    ofstream file("diary.txt", ios::app);

    cout<<"\nEnter Date (DD/MM/YYYY): ";
    cin>>date;
    cin.ignore();

    cout<<"Enter your Diary Content:\n";
    getline(cin, text);

    file<<date<<"|"<<text<<endl;
    file.close();

    cout<<"Diary Entry Added Successfully!\n";
}

void DiaryEntry::displayEntries() 
{
    ifstream file("diary.txt");
    string line;

    cout<<"\n------STORED DIARY ENTRIES ------\n";
    while (getline(file, line))
     {
        cout<<line<<endl;
    }
    file.close();
}

void DiaryEntry::editEntry() 
{
    ifstream file("diary.txt");
    ofstream tempfile("temp.txt");
    string searchDate, line;
    bool found=false;

    cout<<"Enter date to update (DD/MM/YYYY): ";
    cin>>searchDate;
    cin.ignore();

    while (getline(file, line)) 
    {
        if (line.find(searchDate)==0) 
        {
            found=true;
            cout<<"Enter updated diary content:\n";
            getline(cin, text);
            tempfile<<searchDate<<"|"<<text<<endl;
        } 
        else 
        {
            tempfile<<line<<endl;
        }
    }

    file.close();
    tempfile.close();

    remove("diary.txt");
    rename("temp.txt", "diary.txt");

    if(found)
        cout<<"Diary Entry is Updated Successfully!\n";
    else
        cout<<"No Matching Entry found!\n";
}

void DiaryEntry::deleteEntry() 
{
    ifstream file("diary.txt");
    ofstream tempfile("temp.txt");
    string searchDate, line;
    bool found=false;

    cout<<"Enter date to delete (DD/MM/YYYY): ";
    cin>>searchDate;

    while (getline(file, line))
     {
        if (line.find(searchDate)==0) 
        {
            found=true;
            continue;
        }
        tempfile<<line<<endl;
    }

    file.close();
    tempfile.close();

    remove("diary.txt");
    rename("temp.txt", "diary.txt");

    if(found)
        cout << "Diary Entry Successfully Deleted!\n";
    else
        cout << "Matching Entry not found!\n";
}

int main() 
{
    login();
    DiaryEntry manager;
    int option;

    while(true) 
    {
        cout<<"\n============================\n";
        cout<<"   DIGITAL DIARY MENU\n";
        cout<<"============================\n";
        cout<<"1. Add a New Entry\n";
        cout<<"2. View All Entries\n";
        cout<<"3. Edit an Entry\n";
        cout<<"4. Delete an Entry\n";
        cout<<"5. Exit\n";
        cout<<"Enter your choice: ";
        cin>>option;

        switch(option)
         {
        case 1:
            manager.createEntry();
            break;
        case 2:
            manager.displayEntries();
            break;
        case 3:
           manager.editEntry();
            break;
        case 4:
           manager.deleteEntry();
            break;
        case 5:
            cout<<"Thank you for using Digital Diary!\n";
            exit(0);
        default:
            cout<<"Invalid Choice! Please Try Again.\n";
        }
    }
   

    return 0;
}

