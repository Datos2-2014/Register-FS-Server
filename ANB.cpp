/* 
 * File:   ANB.cpp
 * Author: jeremy
 * 
 * Created on 8 de mayo de 2014, 02:22 AM
 */

#include "ANB.h"
#include <string>

using namespace std;

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
 * @param pName Nombre para el archivo
 * @param pPath Direccion donde se encuentra el archivo
 * @return Puntero hacia un arreglo de caracteres que contiene el fileDescriptor
 */
string ANB::newFile(char pClientDescriptor[17], char pName[65], char pPath[]) {
    SLLNode* tmp = root;
    
    char* folderActual = strtok(pPath, "/");
    
    if (folderActual==NULL) {
        Disk_File* file = new Disk_File(pClientDescriptor, pName);
        root->getFolder()->insert(file, pName);
    }
    else {
        tmp = searchFolder(pPath);
        if(tmp==NULL) {
            cout << "Ubicación incorrecta" << endl;
            return NULL;
        }
        else {
            Disk_File* file = new Disk_File(pClientDescriptor, pName);
            tmp->getFolder()->insert(file, pName);
            
            string peerDesc = file->getPeerDescriptor();
            return peerDesc;
        }
    }
}

/**
 * Función auxiliar. Busca un nodo en el arbol a partir del nombre de su direccion.
 * @param pPath Caracter de la direccion de la carpeta
 * @return Puntero hacia el nodo de la lista donde se encuentra
 */
SLLNode* ANB::searchFolder(char pPath[]) {
    SLLNode* tmp = root;
    SLL* listaActual = tmp->getFolder();
    
    char* folderActual = strtok(pPath, "/");
    while(folderActual!=NULL) {
        for(tmp = listaActual->getFirst(); tmp!=NULL; tmp = tmp->getNext()) {
            std::string foldAct_str(folderActual);
            if((tmp->getFlag()==0)&&(foldAct_str.compare(tmp->getName()) == 0)) {
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

/**
 * Crea el esquema para los registros  de los archivos
 * @param pFileDesc File descriptor del archivo al cual se le va a definir el esquema
 * @param pCol cadena con las columnas y el nombre de cada una, de la forma: {<column1Name>,<column1Type>,<column1Size>},{<column2Name>,<column2Type>,<column2Size>},..,{<columnNName>,<columnNType>,<columnNSize>}
 * @return 1-Si la operacion no fue exitosa, 0-si lo fue
 */
int ANB::createSchema(char pFileDesc[33], string pCol) {
    SLL* folder_archivo = searchFile(pFileDesc, root->getFolder());
    
    SLLNode* archivo = folder_archivo->searchFile(pFileDesc);
    if (archivo==NULL) {
        return 1;
    }
    else {
        archivo->getFile()->setSchema(pCol);
        return 0;
    }
}

/**
 * Recibe un file descriptor(array de caracteres de 32 posiciones) y elimina el archivo representado por este.
 * @param pFileDesc File descriptor necesario para buscar el archivo a borrar dentero del arbol n-ario
 */
void ANB::deleteFile(char pFileDesc[33]) {
    SLL* contentFolder = root->getFolder();
    
    if(contentFolder == NULL) {
        cout << "El archivo no existe" << endl;
    }
    else {
        SLL* listaArchivo = searchFile(pFileDesc, contentFolder);
        if(listaArchivo == NULL) {
            cout << "El archivo no existe" << endl;
        }
        else {
            listaArchivo->removeFile(pFileDesc);
        }
    }
}
/**
 * Método auxiliar. Busca un archivo en el arbol n-ario de forrma recursiva, a partir de su filedecriptor.
 * @param pFileDesc FileDescriptor necesario para buscar el archivo.
 * @param pFolder Es la carpeta en la cual se busca el archivo.
 * @return Retorna la carpeta donde se encuentra el archivo.
 */
SLL* ANB::searchFile(char pFileDesc[33], SLL* pFolder) {
    SLL* contentFolder = pFolder;
    if(contentFolder == NULL) {
        return NULL;
    }    
    else {
        SLLNode* tmp = contentFolder->getFirst();
        while(tmp!=NULL) {
            if(tmp->getFlag() == 1) {
                if(tmp->getFile()->getPeerDescriptor().compare(pFileDesc)==0) { //Cambiar getFileName por getFileDesc
                    return contentFolder;
                }
                else {
                    tmp = tmp->getNext();
                }
            }
            else {
                return searchFile(pFileDesc,tmp->getFolder());
            }
        }
        return NULL;
    }
}

/**
 * Elimina una carpeta del arbol del sistema de archivos, la operacion no se puede realizar
 * si dicha carpeta tiene algún contenido.
 * @param pPath Direccion donde se encuentra la carpeta.
 */
void ANB::deleteFolder(char pPath[]) {
    char* folderActual = strtok(pPath, "/");
    char* folderAnt;
    string folderAnt_str;
    while(folderActual != NULL) {
        folderAnt = folderActual;
        folderActual = strtok(0, "/");
        std::string foldAnt_str(folderAnt);
        folderAnt_str = foldAnt_str;        
    }
    
    SLL* folder = searchSLLFolder(pPath);
    if(folder != NULL) {
        folder->removeFolder(folderAnt_str);
    }
}
/**
 * Función auxiliar que busca una lista donde se encuentra la carpeta pasada como parámetro
 * @param pPath Direccion de la carpeta a buscar.
 * @return Lista donde se encuentra dicha carpeta para después borrarla.
 */
SLL* ANB::searchSLLFolder(char pPath[]) {
    SLLNode* tmp = root;
    SLL* listaActual = tmp->getFolder();
    SLL* lista;
    
    char* folderActual = strtok(pPath, "/");
    while(folderActual!=NULL) {
        for(tmp = listaActual->getFirst(); tmp!=NULL; tmp = tmp->getNext()) {
            std::string foldAct_str(folderActual);
            if((tmp->getFlag()==0)&&(foldAct_str.compare(tmp->getName()) == 0)) {
                lista = listaActual;
                listaActual = tmp->getFolder();
                break;
            }
        }
        if(tmp==NULL) {
            cout << "Ubicación incorrecta" << endl;
            return NULL;
        }
        else {
            folderActual = strtok(0, "/");
        }
    }
    if(listaActual->getFirst() == NULL) {
        return lista;
    }
    else {
        cout << "La carpeta no se puede borrar porque contiene archivos" << endl;
        return NULL;
    }
}

/**
 * Consulta un contenedor para mostrar su contenido en consola.
 * @param Direccion donde se encuentra el contenedor, incorpora la carpeta a buscar.
 */
void ANB::queryFolder(char pPath[]) {
    SLLNode* cont = searchFolder(pPath);
    
    SLL* folder = cont->getFolder();
    
    SLLNode* tmp = folder->getFirst();
    while(tmp != NULL) {
        if(tmp->getFlag() == 0) {
            cout << tmp->getName() << endl;
        }
        else {
            string name = tmp->getFile()->getName();
            string fileDesc = tmp->getFile()->getClientDescriptor();
            cout << name << " - " << fileDesc << endl;
        }
    }
}

/**
 * Obtiene el esquema de registro de un archivo especificado por 
 * su fileDescriptor pasado como parámetro.
 * @param pFileDesc FileDescriptor del archivo al que se le desea crear el nuevo esquema de registro.
 * @return Puntero hacia el objeto esquema respectivo del archivo.
 */
schema* ANB::getSchema(char pFileDesc[]) {
    SLL* folder_archivo = searchFile(pFileDesc, root->getFolder());
    SLLNode* archivo = folder_archivo->searchFile(pFileDesc);
    
    if(archivo == NULL) {
        return NULL;
    }
    else {
        return archivo->getFile()->getSchema();
    }
}

/**
 * Crea un nuevo registro y lo añade al archivo especificado por su
 * fileDescriptor pasado como parámetro.
 * @param pFileDesc Descriptor del archivo para encontrar el archivo al que se le desea crear el nuevo registro de datos.
 * @param pValores Cadena de valores pasados por el usuario, contiene tanto el nombre de la columna como su vaor respectivo.
 * @return Una cadena de caracteres que contiene el número de registro y su posición dentro del archivo.
 */
string ANB::addRegister(char pFileDesc[33], string pValores) {
    SLL* folder_archivo = searchFile(pFileDesc, root->getFolder());
    SLLNode* archivo = folder_archivo->searchFile(pFileDesc);
    Disk_File* file = archivo->getFile();
    
    string nomb;
    string value;
    
    int tipo_dato = 1;
    int n = 3;
    
    while(n < pValores.size()-2) {
        int i = n;
        int j = n;
        
        while(pValores[j] != '>') {
            j++;
        }
        string dato = pValores.substr(i,i+j-1);
        
        if(tipo_dato == 1) {
            nomb = dato;
            tipo_dato++;
            n=j+3;
        }
        else {
            value = dato;
            tipo_dato = 1;
            n = j+5;
            file->write(value, file->getRegisterFree(), file->getSchema()->getDesplazamiento(nomb), file->getSchema()->getConst(nomb), file->getSchema()->getColTam(nomb));
        }
    }
    return to_string(file->getRegisterFree());
}
