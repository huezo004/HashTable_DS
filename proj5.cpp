#include<iostream>
#include"passserver.h"
#include<string>
#include<stdlib.h>

void Menu()
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}

int main(){  
  int num; 
  cout<<"Enter preferred hash table capacity"<<endl;
  cin>>num;

  PassServer server(num);

  cout<<num;  

  char letter;
  string usn;   
  string name;
  string lname;  

  do
  {
  Menu();
  cout<<endl;
  cout<<endl;
  
  cin>>letter;

  switch(letter){
    
  case 'l':
    char fname[200];
    cout<<"Enter password file name to load from"<<endl;
    cin>>fname;
    server.load(fname);
      break;

  case 'a': 
    cout<<"Enter username"<<endl;
    cin>>name;
    cout<<"Enter password"<<endl;
    cin>>lname;
    server.addUser(make_pair(name,lname));
   
    break; 

  case 'r':
    cout<<"Enter username"<<endl;
    cin>>usn;
    server.removeUser(usn); 
      break; 

 case 'c':
    cout<<"Enter username    : "<<endl;
    cin>> name;
    cout<<"Enter password    : "<<endl;
    cin>>lname;
    cout<<endl;
    cout<<"Enter new password: "<<endl;
    cin>>usn;
    server.changePassword(make_pair(name,lname),usn);  
    break;

  case 'f':
    cout<<"Enter username :  "<<endl;
    cin>>usn;

    if(server.find(usn))
      cout<<"User"<< " "<<usn<<" "<< "found"<<endl;
    else
      cout<<"User"<< " "<<usn<<" "<< "not found"<<endl;
        break; 

 case 'd':
    server.dump();
    /* for(int i=0; i<server.size(); ++i){
     cout<<'['<<i<<']'<<";"<<
     
     }*/
     break; 

 case 's':
    cout<<"Size of hashtable:"<<" "<<server.size()<<endl;
     break; 

 case 'w':
    cout<<"Enter password file name to write to: ss"<<endl;
    char str[200];
    cin>> str;
    server.write_to_file(str); 
    break; 

  case 'x':
    exit(1); 

  default:
  cout<<"*****Error: Invalid entry.  Try again."<<endl;
  break;   
  }

  } while(letter!='x'); //end do()

 return 0; 

}
