/* 
 * File:   ANB.cpp
 * Author: jeremy
 * 
 * Created on 8 de mayo de 2014, 02:22 AM
 */

#include "ANB.h"

ANB::ANB() {
    root = new SLLNode(NULL, "/");
}

ANB::ANB(const ANB& orig) {
}

ANB::~ANB() {
}

/**
 * Crea una nueva carpeta y la añade al arbol que estructura el sistema de archivos
 * @param pName Nombre para la carpeta nueva
 * @param pPath Direccion donde va a ser creada
 * @return 0 si la operacion fue exitosa, 1 si no lo fue
 */
int ANB::newFolder(string pName, char pPath[]) {
    SLLNode* tmp = root;
    
    char* folderActual = strtok(pPath, "/");
    
    if (folderActual==NULL) {
        root->getFolder()->insert(NULL, pName);
    }
    
    else {
        tmp = searchFolder(pPath);
        if(tmp==NULL) {
            cout << "Fichero no encontrado" << endl;
            return 1;
        }
        else {
            tmp->getFolder()->insert(NULL, pName);
            return 0;
        }
    }
}

/**
 * Crea un nuevo archivo y lo almacena en la estructura del arbol del sistema de archivos.
 * @param pClientDescriptor ID proporcionado por el usuario.
 * @param 
 * @param 
 * @return 
 */
//char* ANB::newFile(char pClientDescriptor[16], char pName[64], char pPath[]) {
//    SLLNode* tmp = root;
//    
//    char* folderActual = strtok(pPath, "/");
//    
//    if (folderActual==NULL) {
//        Disk_File* file = new Disk_File(pClientDescriptor, pName);
//        root->getFolder()->insert(file, pName);
//    }
//    else {
//        tmp = searchFolder(pPath);
//        if(tmp==NULL) {
//            cout << "Fichero no encontrado" << endl;
//            return NULL;
//        }
//        else {
//            Disk_File* file = new Disk_File(pClientDescriptor, pName);
//            tmp->getFolder()->insert(file, pName);
//            
//            char* peerDesc[16] = file.getPeerDescriptor();
//            return peerDesc;
//        }
//    }
//}

/**
 * Busca un nodo en el arbol a partir del nombre de su archivo o contenedor.
 * @param pName Caracter del nombre de la carpeta o archivo
 * @param pAnterior Carpeta anterior
 * @return Puntero hacia el nodo de la lista donde se encuentra
 */
SLLNode* ANB::searchFolder(char pPath[]) {
    SLLNode* tmp = root;
    SLL* listaActual = tmp->getFolder();
    
    char* folderActual = strtok(pPath, "/");
    while(folderActual!=NULL) {
        for(tmp = listaActual->getFirst(); tmp!=NULL; tmp = tmp->getNext()) {
            std::string foldAct_str(folderActual);
            if((tmp->getFlag()==0)&&(foldAct_str.compare(tmp->getName()))) {
                listaActual = tmp->getFolder();
                break;
            }
        }
        if(tmp==NULL) {
            return NULL;
        }
        else {
            folderActual = strtok(0, "/");
        }
    }
    return tmp;
}
