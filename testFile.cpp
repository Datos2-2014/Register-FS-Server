/* 
 * File:   testFile.cpp
 * Author: malcolm
 *
 * Created on May 23, 2014, 6:44 PM
 */

#include <cstdlib>
#include "Disk_File.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
Disk_File hola=Disk_File("string", "holitas");
    hola.init(9);
    string escribir="digamos que voy a escribir este string";
    string escribir2="en este voy a ver si la lista funciona";
    string escribir3="este es solo para probar";
    string header="me cago todavia tengo que modificar el puto header";
    hola.getHeader()->setSize(header.size());
    cout <<"tamanio header " <<hola.getHeader()->getSize() <<endl;
    hola.writeHeader(header);
    int registroEscribir=hola.getRegisterFree();
    cout << "registro a escribir  " << registroEscribir << endl;
    hola.write(escribir, registroEscribir, 0, caseCharArray, sizeof(escribir));
//    cout << "leyendo registro  "<<registroEscribir<<"   "<<hola.read(registroEscribir, 0, sizeof(escribir), caseCharArray)<< endl;
    registroEscribir=hola.getRegisterFree();
    cout << "registro a escribir  " << registroEscribir << endl;
    hola.write(escribir2, registroEscribir,0, caseCharArray, sizeof(escribir2));
//    cout << "leyendo registro  "<<registroEscribir<<"   "<<hola.read(registroEscribir, 0, sizeof(escribir), caseCharArray)<< endl;
    registroEscribir=hola.getRegisterFree();
    cout << "registro a escribir  " << registroEscribir << endl;
    hola.write(escribir3, registroEscribir, 0, caseCharArray,sizeof(escribir3));
    return 0;
}

