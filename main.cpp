#include <string.h>
#include <iostream>
#include "Disk_File.h"
#include <list>
#include <string>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv)    
{
    string pru;
    getline(cin,pru);
    int j=0;
    while (pru[j]!= '<'){
        j++;
    }
    string dato=pru.substr(0,j);
    cout <<dato;
    if(dato=="touch"){
        cout << "touch";
    }
    else if(dato=="mkcont"){
        cout << "mkcont";
    }
    else if(dato=="mkschema"){
        cout << "mkschema";
    }
    else if(dato=="add-reg"){
        cout << "add-reg";
    }
    else if(dato=="get-reg"){
        cout << "get-reg";
    }
    else if(dato=="del-reg"){
        cout << "del-reg";
    }
    else if(dato=="mod-reg"){
        cout << "mod-reg";
    }
    else if(dato=="del-file"){
        cout << "del-file";
    }
    else if(dato=="del-cont"){
        cout << "del-cont";
    }
    else if(dato=="get-schema"){
        cout << "get-schema";
    }
    else if(dato=="ls-cont"){
        cout << "ls-reg";
    }
    else if(dato=="cat-file"){
        cout << "cat-file";
    }
    else{
        cout <<"se ha digitado un comando invalido";        
    }
    
    return 0;
    
//    string registro="pablo clavo un clavito|pablo clavo un clavito|pablo clavo un clavito|pablo clavo un clavito|pablo clavo un clavito|";
//    string m2="lalalala/lalalala/lalalala/lalalala/lalalala/lalalala/lalalala/lalalala/lalalala/lalalala/lalalala/lalalala/lalalala/lalalala/";
//    string header="trabalenguas >D";
//    cout << "inicializando  " << endl;
//    Disk_File file1= Disk_File(" hello world ", "lol");
//    file1.init(200);
//    cout << "escribiendo  " << endl;
//    file1.writeHeader(header);
//    file1.write(registro, 1, 2, 5);
//    
//    cout << " leyeno"<< endl;
//    
//    cout << file1.readHeader() << endl;
//    cout << file1.read(1,2, registro.size(), 5) << endl;
//    cout << "termino" << endl;
//    
//    cout << "archivo 2" << endl;
//        Disk_File file=Disk_File("hi world ","file1");
//        file.init(128);
//        file.writeHeader(header);
//        file.write(registro, 0, 0 , 5);
//        file.write(m2, 0, registro.size(), 5);
//        file.write(registro, 2, 0,5);
//        file.write(m2, 3, 0,5);
//        cout <<file.read(2, 0, registro.size(),5)<<endl;
//        cout <<file.readHeader()<< " Header  1"  <<endl<< endl;
  
//    string pru="hola";
//    int n=pru.size();
//    cout<<n << endl;
//    string prueba=pru.substr(0,3);
//    cout << prueba <<endl;
    
//    char path[] = "/jere/fotos/myPhotos/";
//    
//    cout << path << endl;
//    char* folderActual = strtok(path, "/");
//    char* folderAnt;
//    cout << folderActual << endl;
//    string fA;
//    
//    while(folderActual!=NULL) {
//        folderAnt = folderActual;
//        folderActual = strtok(0, "/");
//        cout << "folderAnt "<<folderAnt << endl;
////        cout << "fa" << folderActual << endl;
//        std::string fAstr(folderAnt);
//        fA = fAstr;
//    }
//    
//    cout << "salio " << fA;
    
    
//    list<string> nombre;
//    nombre.push_front("1");
//    nombre.push_front("2");
//    int b = 0;
//    
//    list<string>::iterator it = nombre.begin();
//    while(it != nombre.end()) {
//        string s = *it;
//        int a = atoi(s.c_str());
//        b += a;
//        it++;
//    }
//    cout << b;
}