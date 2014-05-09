#include <string.h>
#include <iostream>
#include "Disk_File.h"
using namespace std;int main()    
{ 
    string registro="pablo clavo un clavito|pablo clavo un clavito|pablo clavo un clavito|pablo clavo un clavito|pablo clavo un clavito|";
    string m2="lalalala/lalalala/lalalala/lalalala/lalalala/lalalala/lalalala/lalalala/lalalala/lalalala/lalalala/lalalala/lalalala/lalalala/";
    string header="trabalenguas >D";
    cout << "inicializando  " << endl;
    Disk_File file1= Disk_File(" hello world ", "lol");
    file1.init(200);
    cout << "escribiendo  " << endl;
    file1.writeHeader(header);
    file1.write(registro, 1, 2, 5);
    
    cout << " leyeno"<< endl;
    
    cout << file1.readHeader() << endl;
    cout << file1.read(1,2, registro.size(), 5) << endl;
    cout << "termino" << endl;
    
    cout << "archivo 2" << endl;
        Disk_File file=Disk_File("hi world ","file1");
        file.init(128);
        file.writeHeader(header);
        file.write(registro, 0, 0 , 5);
        file.write(m2, 0, registro.size(), 5);
        file.write(registro, 2, 0,5);
        file.write(m2, 3, 0,5);
        cout <<file.read(2, 0, registro.size(),5)<<endl;
        cout <<file.readHeader()<< " Header  1"  <<endl<< endl;
        
    
}
