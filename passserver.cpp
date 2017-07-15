#include"passserver.h"
#include<string>
#include<fstream>
PassServer::PassServer(size_t size): Server(size) {}
PassServer::~PassServer(){

}



bool PassServer::load(const char * filename){
  ifstream infile;
  string key; 
  string password; 
  infile.open(filename);
  
if (!infile){
    cout<<"Wrong file name";
    return false;
}

while (infile >> key){
  if (infile >> password)
    Server.insert(make_pair(key, encrypt(password)));
 }

return true;
}



bool PassServer::addUser(std::pair<string,  string> & kv){

  kv.second=encrypt(kv.second);
  
  if(Server.insert(kv)){
    cout<<"User"<<" "<<kv.first<<" "<<"inserted"<<endl;
    return true;
  }
}

bool PassServer::addUser(std::pair<string, string> && kv){

     kv.second=encrypt(kv.second);
 
  if(Server.insert(kv)){
    cout<<"User"<<" "<<kv.first<<" "<<"inserted"<<endl;
    return true;
  }
}
bool PassServer::removeUser(const string & k){
  if(!(Server.remove(k))){
    cout<<"*****Error: User not found. Could not delete user"<<endl; 
    return false;
  }

  
  Server.remove(k);
  cout<<"User"<<" "<<k<<" "<<"deleted"<<endl;
  return true;
}


bool PassServer::changePassword(const pair<string, string> &p, const string & newpassword){

  if((!Server.contains(p.first)) ||(Server.match(make_pair(p.first,encrypt(newpassword))))){ 
    cout<<"*****Error: Could not change user password"<<endl; 
     return false;
  }
  
  if(Server.match(make_pair(p.first, encrypt(p.second)))){
    Server.insert(make_pair(p.first, encrypt(newpassword)));
  cout<< "Password changed for user denyse"<<p.first<<endl; 

    return true;
  }
}

bool PassServer::find(const string & user){
return Server.contains(user); 
}

void PassServer::dump(){
  Server.dump(); 
}    

size_t PassServer::size(){
  return Server.Hsize(); 
}

bool PassServer::write_to_file(const char *filename){
  return Server.write_to_file(filename); 
}

string PassServer::encrypt(const string & str){


  char salt[]=  "$1$########";

  char * password = new char [300];
  
   strcpy(password,crypt(str.c_str(),salt)); 

   return password; 
}


   
