#include<iostream>
#include<fstream>
#include<exception>
#include<stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "err.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

using namespace std;

// count how many occurance a word(Lower&Upper) in a file, input must be a lowercase number
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
  //http://www.cplusplus.com/forum/general/245501/
    key_t key = 0;
    int shm_id;
    shm_id = shmget(key, 26*sizeof(int), 0666 | IPC_CREAT);
    int* occ = (int*)shmat(shm_id, NULL, 0);
  //
  //int* occ=new int[26];               
  pid_t pid;  
  pid=fork();
  for(int i=97;i<97+26;i++)
  {
       
    if(pid==0)
    {
      occ[i-97]=count(i,filename);
      exit;
    }else if (pid<0)
    {
      cout<<"fork error\n";
      exit;
    } 
    
  }
  
  if (pid>0)
  { 
  wait(NULL);
    for (int i=0;i<26;i++)
    {
      char Lletter=i+97;
      char Uletter=Lletter-32;
      cout<<Uletter<<"/"<<Lletter<<" ";
      cout<<occ[i]<<endl;
    }
  }
  
  return 0;
}
