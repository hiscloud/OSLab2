#include<iostream>
#include<fstream>
#include<exception>
#include<stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "err.h"
using namespace std;

// count how many occurance a word(L&U) in a file, input must be a lowercase number
// int(a)
// a-32=A a=97
int count(char wordN, string filename)
{
  try
  {
    ifstream infile;
    infile.open(filename);
    char test;
    int counter=0;
    while(infile.good())
    {
      if (test==wordN||test==(wordN-32))
        counter++;
      infile>>test;
  //  cout<<test<<endl;
          
    }
    infile.close();
    return counter;
    
  }catch(const exception& e){
    cout<<"file doens't exist"<<endl;
    
  }  
}


int main(int argc, char* argv[])
{
  if (argc==1)
  {
    cout<<"input file name in command line"<<endl;
    exit(1);
  }
  
  string filename="";
  filename+=argv[1];
  if (argc>2)
    for (int i=2;i<argc;i++)
    {
      filename+=" ";
      filename+=argv[i];
    }
    int occurance;
  for(int i=97;i<97+26;i++)
  {
    pid_t pid;  
    pid=fork();
    if(pid==0)
    {
      char letter=i;
      cout<<letter<<" ";
      occurance=count(i,filename);
      cout<<occurance<<endl;
    }else if (pid<0)
    {
      cout<<"fork error\n";
      exit(-1);
    }
  }
    

  return 0;
}