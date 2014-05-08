#include <string.h>
#include <iostream>

using namespace std;

int main()
{
    char pPath[] = "/home/jeremy/new Folder/";
    char * a = strtok(pPath,"/");
    cout << a << endl;
    char* b=a;
    while(b!=NULL){
        b=strtok(0, "/");
        cout << b<< endl;
    }
}