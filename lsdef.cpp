#include <iostream>
#include <fstream>
#include <string>

/*
Simplest command-line util for listing contents of BMC Remedy ARS .def files
(c) 2011 Andrey Semenyuk
*/

using namespace std;

ifstream def;

string getname (void)
{
 string line;
 size_t i;

 getline(def, line);
 i=line.find(':');
 i++;
 return line.substr(i, line.length()-i);
}

int main (int nargs, char* args[])
{
 string line;
 size_t i1;
 int container_type=0;

 if(nargs<2)
 {
  cout << "Give me a name of the def-file as a parameter" << endl;
  return 1;
 }

 def.open(args[1], ifstream::in);
 
 while(def.good())
 {
  getline(def, line);
  
  if(line.compare("begin schema") == 0)
  {
   cout << "schema\t";
   cout << getname() << endl;
   do{getline(def, line);}while(line!="end");   
   continue;
  }
  
  if(line.compare("begin container") == 0)
  {
   string name=getname();
   getline(def, line);
   if(line=="   type           : 1") container_type=1;
   if(line=="   type           : 4") container_type=4;
   
   switch(container_type)
   {
    case 1 : cout << "AL guide\t"; break;
	case 4 : cout << "AL guide\t"; break;
	default : cout << "UNKNOWN CONTAINER\t"; break;
   }
   
   container_type=0;
   cout << name << endl;
   continue;
  }
  
  i1=line.find(' ');
  
  string l2=line.substr((size_t)0, i1);
  
  if(l2.compare("begin") == 0)
  {
   cout << line.substr(i1+1, line.length()-i1) + "\t";
   cout << getname() << endl;
   continue;
  }
 }
}
