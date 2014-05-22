#include <string.h>
#include <iostream>
#include "Disk_File.h"
#include <list>
#include <string>
#include <cstdlib>
#include "Jzon.h"
#include "ANB.h"

using namespace std;

int main(int argc, char** argv)    
{        
    ANB* File_System = new ANB();
    
    string pru;
    getline(cin,pru);
    int j=0;
    while (pru[j]!= '<'){
        j++;
    }
    string dato=pru.substr(0,j);
    cout <<dato;
    if(dato=="touch"){
        /*Separación de los parámetros del comando*/
        int punt1 = j+1;
        while (pru[punt1] != '>'){
            punt1++;
        }
        string param1 = pru.substr(j+1,punt1);
        
        int punt2 = punt1+2;
        while (pru[punt2] != '>'){
            punt2++;
        }
        string param2= pru.substr(punt1+2,punt2);
        
        int punt3 = punt2+2;
        while (pru[punt3] != '>'){
            punt3++;
        }
        string param3 = pru.substr(punt2+2,punt3);
        
        /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
        string ret = File_System->newFile(param2, param1, param3);
        
        /*Parse y envío en formato json */
        Jzon::Object root;                              //Creación del objeto para parsear el contenido
        root.Add("Peer descriptor", ret);               //Añade una etiqueta con el valor correspondiente
        
        Jzon::Writer writer(root, Jzon::StandardFormat);//Escribe la etiqueta en el formato estándar
        writer.Write();                                 //Escribe el nodo
        std::string result = writer.GetResult();        //Almacena en una variable string el formato json creado
        
        //Enviar "result" al cliente
        
        cout << result << endl;
        cout << "touch Finalizado" << endl;
    }
    else if(dato=="mkcont"){
        /*Separación de los parámetros del comando*/
        int punt1 = j+1;
        while (pru[punt1] != '>'){
            punt1++;
        }
        string param1 = pru.substr(j+1,punt1);
        
        int punt2 = punt1+2;
        while (pru[punt2] != '>'){
            punt2++;
        }
        string param2 = pru.substr(punt1+2,punt2);
        
        /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
        int ret = File_System->newFolder(param2, param1);
        
        /*Parse y envío en formato json */
        Jzon::Object root;                              //Creación del objeto para parsear el contenido
        root.Add("Operacion No Exitosa", ret);          //Añade una etiqueta con el valor correspondiente
        
        Jzon::Writer writer(root, Jzon::StandardFormat);//Escribe la etiqueta en el formato estándar
        writer.Write();                                 //Escribe el nodo
        std::string result = writer.GetResult();        //Almacena en una variable string el formato json creado
        
        //Enviar "result" al cliente
        
        cout << result << endl;
        cout << "mkcont Finalizado" << endl;
    }
    else if(dato=="mkschema"){
        /*Separación de los parámetros del comando*/
        int punt1 = j+1;
        while (pru[punt1] != '>'){
            punt1++;
        }
        string param1 = pru.substr(j+1,punt1);
        
        int punt2 = punt1+1;
        bool flag = false;
        while(!flag) {
            if((pru[punt2]=='}') && (pru[punt2+1]=='}')) {
                flag = true;
            }
            else {
                punt2++;
            }
        }
        string param2 = pru.substr(punt1+1,punt2+2);
        
        /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
        int ret = File_System->createSchema(param1, param2);
        
        /*Parse y envío en formato json */
        Jzon::Object root;                              //Creación del objeto para parsear el contenido
        root.Add("Operacion No Exitosa", ret);          //Añade una etiqueta con el valor correspondiente
        
        Jzon::Writer writer(root, Jzon::StandardFormat);//Escribe la etiqueta en el formato estándar
        writer.Write();                                 //Escribe el nodo
        std::string result = writer.GetResult();        //Almacena en una variable string el formato json creado
        
        //Enviar "result" al cliente
        
        cout << result << endl;
        cout << "mkschema Finalizado" << endl;
    }
    else if(dato=="add-reg"){
        /*Separación de los parámetros del comando*/
        int punt1 = j+1;
        while (pru[punt1] != '>'){
            punt1++;
        }
        string param1 = pru.substr(j+1,punt1);
        
        int punt2 = punt1+1;
        bool flag = false;
        while(!flag) {
            if(pru[punt2]=='}' && pru[punt2+1]=='}') {
                flag = true;
            }
            else {
                punt2++;
            }
        }
        string param2 = pru.substr(punt1+1,punt2+2);
        
        /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
        string ret = File_System->addRegister(param1, param2);
        
        /*Parse y envío en formato json */
        Jzon::Object root;                              //Creación del objeto para parsear el contenido
        root.Add("Número de registro", ret);            //Añade una etiqueta con el valor correspondiente
        
        Jzon::Writer writer(root, Jzon::StandardFormat);//Escribe la etiqueta en el formato estándar
        writer.Write();                                 //Escribe el nodo
        std::string result = writer.GetResult();        //Almacena en una variable string el formato json creado
        
        //Enviar "result" al cliente
        
        cout << result << endl;
        cout << "add-reg Finalizado" << endl;
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
        /*Separación de los parámetros del comando*/
        int punt1 = j+1;
        while (pru[punt1] != '>'){
            punt1++;
        }
        string param1 = pru.substr(j+1,punt1);
        
        /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
        File_System->deleteFile(param1);
        
        cout << "del-file Finalizado" << endl;
    }
    else if(dato=="del-cont"){
        /*Separación de los parámetros del comando*/
        int punt1 = j+1;
        while (pru[punt1] != '>'){
            punt1++;
        }
        string param1 = pru.substr(j+1,punt1);
        
        /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
        File_System->deleteFolder(param1);
        
        cout << "del-cont Finalizado" << endl;
    }
    else if(dato=="get-schema"){
        /*Separación de los parámetros del comando*/
        int punt1 = j+1;
        while (pru[punt1] != '>'){
            punt1++;
        }
        string param1 = pru.substr(j+1,punt1);
        
        /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
        string ret = File_System->getSchema(param1);
        
        //Enviar result al cliente
        
        cout << ret << endl;
        cout << "get-schema Finalizado" << endl;
    }
    else if(dato=="ls-cont"){
        /*Separación de los parámetros del comando*/
        int punt1 = j+1;
        while (pru[punt1] != '>'){
            punt1++;
        }
        string param1 = pru.substr(j+1,punt1);
        
        /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
        File_System->queryFolder(param1);
        
        cout << "ls-cont Finalizado" << endl;
    }
    else if(dato=="cat-file"){
        cout << "cat-file";
    }
    else{
        cout <<"se ha digitado un comando invalido";        
    }    
}