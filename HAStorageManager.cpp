///* 
// * File:   HAStorageManager.cpp
// * Author: jeremy
// * 
// * Created on 5 de junio de 2014, 09:23 PM
// */
//
//#include "HAStorageManager.h"
//
//HAStorageManager::HAStorageManager() {
//    CMarkup xml;
//    int i = 1;
//    while(xml.Load("Arbol"+to_string(i)+".xml")){
//        i++;
//        
//        ANB* FS = new ANB();
//        SLLNode* tmp = FS->getRoot();
//        
//        xml.FindElem();
//        xml.IntoElem();
//        while(xml.FindElem("Folder")) {
//            SLL* folder = tmp->getFolder();
//            folder->insert(NULL, xml.GetAttrib("Name"));
//            
//        }
//    }
//}
//
//HAStorageManager::HAStorageManager(const HAStorageManager& orig) {
//}
//
//HAStorageManager::~HAStorageManager() {
//}
//
///**
// * Recive el comando ya convertirdo a string pasado por el cliente
// * para ejecutar la operación correcta
// * @param comando Comando del cliente
// */
//void HAStorageManager::command_listener(string comando) {
//    int j=0;
//    while (comando[j]!= '<'){
//        j++;
//    }
//    string dato=comando.substr(0,j);
//    //cout <<dato;
//    if(dato=="touch"){
//        /*Separación de los parámetros del comando*/
//        int punt1 = j+1;
//        int aux1=0;
//        while (comando[punt1] != '>'){
//            punt1++;
//            aux1++;
//        }
//        string param1 = comando.substr(j+1,aux1);
//        cout<< "Filename: "<<param1<<endl;
//        if(param1.size()>64) {
//            cout << "Numero de caracteres excedido en file name" << endl; //Añadir error
//        }
//        else {;
//            int punt2 = punt1+2;
//            int aux2=0;
//            while (comando[punt2] != '>'){
//                punt2++;
//                aux2++;
//            }
//            string param2 = comando.substr(punt1+2,aux2);
//            cout<< "client descriptor: "<<param2<<endl;
//            if(param2.size()>64) {
//                cout << "Numero de caracteres excedido en client descriptor" << endl; //Añadir error
//            }
//            else {
//                int punt3 = punt2+2;
//                int aux3=0;
//                while (comando[punt3] != '>'){
//                    punt3++;
//                    aux3++;
//                }
//                string param3 = comando.substr(punt2+2,aux3);
//                cout<< "Path: "<<param3<<endl;
//
//                int punt4 = punt3+2;
//                int aux4=0;
//                while (comando[punt4] != '>'){
//                    punt4++;
//                    aux4++;
//                }
//                int punt5 = punt4+2;
//                int aux5=0;
//                while (comando[punt5] != '>'){
//                    punt5++;
//                    aux5++;
//                }
//                int punt6 = punt5+2;
//                int aux6=0;
//                while (comando[punt6] != '>'){
//                    punt6++;
//                    aux6++;
//                }
//                string usr = comando.substr(punt5+2,aux6);
//                nt punt7 = punt6+2;
//                int aux7=0;
//                while (comando[punt7] != '>'){
//                    punt7++;
//                    aux7++;
//                }
//                string pass = comando.substr(punt6+2,aux7);
//                arbol(storageID).autorizacion(usr, pass);
//
//                /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
//                string ret = File_System->newFile(param2, param1, param3);
//                if(ret=="") {
//                    cout << "Ubicacion incorrecta" << endl; //Añadir error
//                }
//                else {
//                    /*Parse y envío en formato json */
//                    Jzon::Object root;                              //Creación del objeto para parsear el contenido
//                    root.Add("Peer descriptor", ret);               //Añade una etiqueta con el valor correspondiente
//
//                    Jzon::Writer writer(root, Jzon::StandardFormat);//Escribe la etiqueta en el formato estándar
//                    writer.Write();                                 //Escribe el nodo
//                    std::string result = writer.GetResult();        //Almacena en una variable string el formato json creado
//                    cout << result << endl;
//
//                    //Enviar "result" al cliente
//                }
//            }
//        }
//
//        cout << "touch Finalizado" << endl;
//    }
//
//    else if(dato=="mkcont"){
//        /*Separación de los parámetros del comando*/
//        int punt1 = j+1;
//        int aux1=0;
//        while (comando[punt1] != '>'){
//            punt1++;
//            aux1++;
//        }
//        string param1 = comando.substr(j+1,aux1);
//        cout<< "Container name: "<<param1<<endl;
//        
//        if(param1.size()>64) {
//                cout << "Numero de caracteres excedido en container name" << endl; //Añadir error
//        }
//        else {
//            int punt2 = punt1+2;
//            int aux2=0;
//            while (comando[punt2] != '>'){
//                punt2++;
//                aux2++;
//            }
//            string param2 = comando.substr(punt1+2,aux2);
//            cout<< "path: "<<param2<<endl;
//
//            /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
//            int ret = File_System->newFolder(param2, param1);
//
//            /*Parse y envío en formato json */
//            Jzon::Object root;                              //Creación del objeto para parsear el contenido
//            root.Add("Operacion No Exitosa", ret);          //Añade una etiqueta con el valor correspondiente
//
//            Jzon::Writer writer(root, Jzon::StandardFormat);//Escribe la etiqueta en el formato estándar
//            writer.Write();                                 //Escribe el nodo
//            std::string result = writer.GetResult();        //Almacena en una variable string el formato json creado
//
//            //Enviar "result" al cliente
//
//            cout << result << endl;
//
//        }
//        cout << "mkcont Finalizado" << endl;
//    }
//
//    else if(dato=="mkschema"){
//        /*Separación de los parámetros del comando*/
//        int punt1 = j+1;
//        int aux1=0;
//        while (comando[punt1] != '>'){
//            punt1++;
//            aux1++;
//        }
//        string param1 = comando.substr(j+1,aux1);
//        cout<<"file descriptor: "<<param1<<endl;
//
//        int punt2 = punt1+1;
//        int aux2=0;
//        bool flag = false;
//        while(!flag) {
//            if((comando[punt2]=='}') && (comando[punt2+1]=='}')) {
//                flag = true;
//                aux2+=2;
//            }
//            else {
//                punt2++;
//                aux2++;
//            }
//        }
//        string param2 = comando.substr(punt1+1,aux2);
//        cout<<"Nombres columnas: "<<param2<<endl;
//
//        /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
//        int ret = File_System->createSchema(param1, param2);
//
//        /*Parse y envío en formato json */
//        Jzon::Object root;                              //Creación del objeto para parsear el contenido
//        root.Add("Operacion No Exitosa", ret);          //Añade una etiqueta con el valor correspondiente
//
//        Jzon::Writer writer(root, Jzon::StandardFormat);//Escribe la etiqueta en el formato estándar
//        writer.Write();                                 //Escribe el nodo
//        std::string result = writer.GetResult();        //Almacena en una variable string el formato json creado
//
//        //Enviar "result" al cliente
//
//        cout << result << endl;
//        cout << "mkschema Finalizado" << endl;
//    }
//
//    else if(dato=="add-reg"){
//        /*Separación de los parámetros del comando*/
//        int punt1 = j+1;
//        int aux1=0;
//        while (comando[punt1] != '>'){
//            punt1++;
//            aux1++;
//        }
//        string param1 = comando.substr(j+1,aux1);
//        cout<<"file descriptor: "<<param1<<endl;
//
//        int punt2 = punt1+1;
//        int aux2=0;
//        bool flag = false;
//        while(!flag) {
//            if(comando[punt2]=='}' && comando[punt2+1]=='}') {
//                flag = true;
//                aux2+=2;
//            }
//            else {
//                punt2++;
//                aux2++;
//            }
//        }
//        string param2 = comando.substr(punt1+1,aux2);
//        cout<<"Columnas: "<<param2<<endl;
//        
//
//        /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
//        int ret = File_System->addRegister(param1, param2);
//        std::string ret_str = to_string(ret);
//        if(ret_str=="") {
//            cout << "Archivo no encontrado" << endl; //Añadir error
//        }
//        else {
//            /*Parse y envío en formato json */
//            Jzon::Object root;                              //Creación del objeto para parsear el contenido
//            root.Add("Número de registro", ret_str);        //Añade una etiqueta con el valor correspondiente
//
//            Jzon::Writer writer(root, Jzon::StandardFormat);//Escribe la etiqueta en el formato estándar
//            writer.Write();                                 //Escribe el nodo
//            std::string result = writer.GetResult();        //Almacena en una variable string el formato json creado
//
//            //Enviar "result" al cliente
//
//            cout << result << endl;
//        }
//        cout << "add-reg Finalizado" << endl;
//    }
//
//    else if(dato=="get-reg"){
//        /*Separación de los parámetros del comando*/
//        int punt1 = j+1;
//        int aux1=0;
//        while (comando[punt1] != '>'){
//            punt1++;
//            aux1++;
//        }
//        string param1 = comando.substr(j+1,aux1);
//        cout<<"file descriptor: "<<param1<<endl;
//
//        int punt2 = punt1+2;
//        int aux2=0;
//        while (comando[punt2] != '>'){
//            punt2++;
//            aux2++;
//        }
//        string param2 = comando.substr(punt1+2,aux2);
//        cout<<"Entero 1 o 0: "<<param2<<endl;
//        int param2_int = atoi(param2.c_str());
//
//        int punt3 = punt2+2;
//        int aux3=0;
//        while (comando[punt3] != '>'){
//            punt3++;
//            aux3++;
//        }
//        string param3 = comando.substr(punt2+2,aux3);
//        cout<<"offset or reg num: "<<param3<<endl;
//        int param3_int = atoi(param3.c_str());
//
//        int punt4 = punt3+2;
//        int aux4=0;
//        while (comando[punt4] != '>'){
//            punt4++;
//            aux4++;
//        }
//        string param4 = comando.substr(punt3+2,aux4);
//        cout<<"todo o columnas: "<<param4<<endl;
//
//        /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
//        string ret = File_System->getRegister(param1, param2_int, param3_int, param4);
//
//        /*Parse y envío en formato json */
//        Jzon::Object root;                              //Creación del objeto para parsear el contenido
//
//        int pos = 1;
//        while(pos < ret.size()-1) {
//            int i = pos;
//            int j = pos;
//
//            while(ret[j]!=':') {
//                j++;
//            }
//            string nodNomb = ret.substr(i,j);
//            j += 1;
//            int k = j;
//            while(ret[k]!='>') {
//                k++;
//            }
//            string nodVal = ret.substr(j,k);
//
//            root.Add(nodNomb, nodVal);                  //Añade una etiqueta con el valor correspondiente
//
//            pos = k+2;
//        }
//
//        Jzon::Writer writer(root, Jzon::StandardFormat);//Escribe la etiqueta en el formato estándar
//        writer.Write();                                 //Escribe el nodo
//        std::string result = writer.GetResult();        //Almacena en una variable string el formato json creado
//        cout << result << endl;
//
//        //Enviar "result" al cliente
//
//        cout << "get-reg Finalizado";
//    }
//
//    else if(dato=="del-reg"){
//         /*Separación de los parámetros del comando*/
//        int punt1 = j+1;
//        int aux1=0;
//        while (comando[punt1] != '>'){
//            punt1++;
//            aux1++;
//        }
//        string param1 = comando.substr(j+1,aux1);
//        cout<<"file descriptor: "<<param1<<endl;
//        
//        int punt2 = punt1+2;
//        int aux2=0;
//        while (comando[punt2] != '>'){
//            punt2++;
//            aux2++;
//        }
//        string param2 = comando.substr(punt1+2,aux2);
//        cout<<"1 o 0: "<<param2<<endl;
//        int param2_int = atoi(param2.c_str());
//        int punt3 = punt2+2;
//        int aux3=0;
//        while (comando[punt3] != '>'){
//            punt3++;
//            aux3++;
//        }
//        string param3 = comando.substr(punt2+2,aux3);
//         cout<<"offset o reg num: "<<param3<<endl;
//        int param3_int = atoi(param3.c_str());
//        /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
//        File_System->deleteRegister(param1, param2_int, param3_int);
//
//        cout << "del-reg Finalizado";
//    }
//
//    else if(dato=="mod-reg"){
//        /*Separación de los parámetros del comando*/
//        int punt1 = j+1;
//        int aux1=0;
//        while (comando[punt1] != '>'){
//            punt1++;
//            aux1++;
//        }
//        string param1 = comando.substr(j+1,aux1);
//        cout<<"file descriptor: "<<param1<<endl;
//
//        int punt2 = punt1+2;
//        int aux2=0;
//        while (comando[punt2] != '>'){
//            punt2++;
//            aux2++;
//        }
//        string param2 = comando.substr(punt1+2,aux2);
//        cout<<"1 o 0: "<<param2<<endl;
//        int param2_int = atoi(param2.c_str());
//
//        int punt3 = punt2+2;
//        int aux3=0;
//        while (comando[punt3] != '>'){
//            punt3++;
//            aux3++;
//        }
//        string param3 = comando.substr(punt2+2,aux3);
//        cout<<"offset o regnum: "<<param3<<endl;
//        int param3_int = atoi(param3.c_str());
//
//
//        //
//        int punt4 = punt3+1;
//        int aux4=0;
//        bool flag = false;
//        while(!flag) {
//            if(comando[punt4]=='}' && comando[punt4+1]=='}') {
//                flag = true;
//                aux4+=2;
//            }
//            else {
//                punt4++;
//                aux4++;
//            }
//        }
//        string param4 = comando.substr(punt3+1,aux4);
//        cout<<"Columnas: "<<param4<<endl;
//        
//
//        /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
//        File_System->modifyReg(param1, param2_int, param3_int, param4);
//
//        cout << "mod-reg Finalizado";
//    }
//
//    else if(dato=="del-file"){
//        /*Separación de los parámetros del comando*/
//        int punt1 = j+1;
//        int aux1=0;
//        while (comando[punt1] != '>'){
//            punt1++;
//            aux1++;
//        }
//        string param1 = comando.substr(j+1,aux1);
//        cout<<"file descriptor: "<<param1<<endl;
//
//        /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
//        File_System->deleteFile(param1);
//
//        cout << "del-file Finalizado" << endl;
//    }
//
//    else if(dato=="del-cont"){
//        /*Separación de los parámetros del comando*/
//        int punt1 = j+1;
//        int aux1=0;
//        while (comando[punt1] != '>'){
//            punt1++;
//            aux1++;
//        }
//        string param1 = comando.substr(j+1,aux1);
//        cout<<"path: "<<param1<<endl;
//
//        /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
//        File_System->deleteFolder(param1);
//
//        cout << "del-cont Finalizado" << endl;
//    }
//
//    else if(dato=="get-schema"){
//        /*Separación de los parámetros del comando*/
//        int punt1 = j+1;
//        int aux1=0;
//        while (comando[punt1] != '>'){
//            punt1++;
//            aux1++;
//        }
//        string param1 = comando.substr(j+1,aux1);
//        cout<<"file descriptor: "<<param1<<endl;
//
//        /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
//        string ret = File_System->getSchema(param1);
//
//        //Enviar result al cliente
//
//        cout << ret << endl;
//        cout << "get-schema Finalizado" << endl;
//    }
//
//    else if(dato=="ls-cont"){
//        /*Separación de los parámetros del comando*/
//        int punt1 = j+1;
//        int aux1=0;
//        while (comando[punt1] != '>'){
//            punt1++;
//            aux1++;
//        }
//        string param1 = comando.substr(j+1,aux1);
//        cout<<"path: "<<param1<<endl;
//
//        /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
//        File_System->queryFolder(param1);
//
//        cout << "ls-cont Finalizado" << endl;
//    }
//
//    else if(dato=="cat-file"){
//        /*Separación de los parámetros del comando*/
//        int punt1 = j+1;
//        int aux1=0;
//        while (comando[punt1] != '>'){
//            punt1++;
//            aux1++;
//        }
//        string param1 = comando.substr(j+1,aux1);
//        cout<<"file descriptor: "<<param1<<endl;
//
//        /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
//        File_System->checkFile(param1);
//
//        cout << "cat-file Finalizado";
//    }
//
//    else{
//        cout <<"se ha digitado un comando invalido";     //Añadir error  
//    }
//}//fin de funcion