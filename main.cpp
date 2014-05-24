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
        if(param1.size()>64) {
            cout << "Numero de caracteres excedido en file name" << endl; //Añadir error
        }
        else {
            int punt2 = punt1+2;
            while (pru[punt2] != '>'){
                punt2++;
            }
            string param2 = pru.substr(punt1+2,punt2);
            if(param2.size()>64) {
                cout << "Numero de caracteres excedido en client descriptor" << endl; //Añadir error
            }
            else {
                int punt3 = punt2+2;
                while (pru[punt3] != '>'){
                    punt3++;
                }
                string param3 = pru.substr(punt2+2,punt3);

                /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
                string ret = File_System->newFile(param2, param1, param3);
                if(ret=="") {
                    cout << "Ubicacion incorrecta" << endl; //Añadir error
                }
                else {
                    /*Parse y envío en formato json */
                    Jzon::Object root;                              //Creación del objeto para parsear el contenido
                    root.Add("Peer descriptor", ret);               //Añade una etiqueta con el valor correspondiente

                    Jzon::Writer writer(root, Jzon::StandardFormat);//Escribe la etiqueta en el formato estándar
                    writer.Write();                                 //Escribe el nodo
                    std::string result = writer.GetResult();        //Almacena en una variable string el formato json creado
                    cout << result << endl;

                    //Enviar "result" al cliente
                }
            }
        }
        
        cout << "touch Finalizado" << endl;
    }
    
    else if(dato=="mkcont"){
        /*Separación de los parámetros del comando*/
        int punt1 = j+1;
        while (pru[punt1] != '>'){
            punt1++;
        }
        string param1 = pru.substr(j+1,punt1);
        if(param1.size()>64) {
                cout << "Numero de caracteres excedido en container name" << endl; //Añadir error
        }
        else {
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
            
        }
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
        if(ret=="") {
            cout << "Archivo no encontrado" << endl; //Añadir error
        }
        else {
            /*Parse y envío en formato json */
            Jzon::Object root;                              //Creación del objeto para parsear el contenido
            root.Add("Número de registro", ret);            //Añade una etiqueta con el valor correspondiente

            Jzon::Writer writer(root, Jzon::StandardFormat);//Escribe la etiqueta en el formato estándar
            writer.Write();                                 //Escribe el nodo
            std::string result = writer.GetResult();        //Almacena en una variable string el formato json creado

            //Enviar "result" al cliente

            cout << result << endl;
        }
        cout << "add-reg Finalizado" << endl;
    }
    
    else if(dato=="get-reg"){
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
        int param2_int = atoi(param2.c_str());
        
        int punt3 = punt2+2;
        while (pru[punt3] != '>'){
            punt3++;
        }
        string param3 = pru.substr(punt2+2,punt3);
        int param3_int = atoi(param3.c_str());
        
        int punt4 = punt3+2;
        while (pru[punt4] != '>'){
            punt4++;
        }
        string param4 = pru.substr(punt2+2,punt3);

        /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
        string ret = File_System->getRegister(param1, param2_int, param3_int, param4);
        
        /*Parse y envío en formato json */
        Jzon::Object root;                              //Creación del objeto para parsear el contenido
        
        int pos = 1;
        while(pos < ret.size()-1) {
            int i = pos;
            int j = pos;
        
            while(ret[j]!=':') {
                j++;
            }
            string nodNomb = ret.substr(i,j);
            j += 1;
            int k = j;
            while(ret[k]!='>') {
                k++;
            }
            string nodVal = ret.substr(j,k);
            
            root.Add(nodNomb, nodVal);                  //Añade una etiqueta con el valor correspondiente
            
            pos = k+2;
        }
        
        Jzon::Writer writer(root, Jzon::StandardFormat);//Escribe la etiqueta en el formato estándar
        writer.Write();                                 //Escribe el nodo
        std::string result = writer.GetResult();        //Almacena en una variable string el formato json creado
        cout << result << endl;

        //Enviar "result" al cliente
        
        cout << "get-reg Finalizado";
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
        /*Separación de los parámetros del comando*/
        int punt1 = j+1;
        while (pru[punt1] != '>'){
            punt1++;
        }
        string param1 = pru.substr(j+1,punt1);
        
        /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
        File_System->checkFile(param1);
        
        cout << "cat-file Finalizado";
    }
    
    else{
        cout <<"se ha digitado un comando invalido";      //Añadir error  
    }    
}