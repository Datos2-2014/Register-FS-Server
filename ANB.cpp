/* 
 * File:   ANB.cpp
 * Author: jeremy
 * 
 * Created on 8 de mayo de 2014, 02:22 AM
 */

#include "ANB.h"
#include <string>
#include "Jzon.h"
#include <iostream>
#include "RegisterPointer.h"

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
int ANB::newFolder(string pName, string pPath, string pUsername, string pPassword){
    SLLNode* tmp = root;
    
    char* a = strdup(pPath.c_str());
    char* folderActual = strtok(a, "/");
    
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
string ANB::newFile(string pClientDescriptor, string pName, string pPath, string pUsername, string pPassword) {
    SLLNode* tmp = root;
    
    char* a = strdup(pPath.c_str());
    char* folderActual = strtok(a, "/");
    
    if (folderActual==NULL) {
        Disk_File* file = new Disk_File(pClientDescriptor, pName);
        root->getFolder()->insert(file, pName);
    }
    else {
        tmp = searchFolder(pPath);
        if(tmp==NULL) {
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
SLLNode* ANB::searchFolder(string pPath) {
    SLLNode* tmp = root;
    SLL* listaActual = tmp->getFolder();
    
    char* a = strdup(pPath.c_str());
    char* folderActual = strtok(a, "/");
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
int ANB::createSchema(string pFileDesc, string pCol, string pUsername, string pPassword) {
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
void ANB::deleteFile(string pFileDesc, string pUsername, string pPassword) {
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
SLL* ANB::searchFile(string pFileDesc, SLL* pFolder) {
    SLL* contentFolder = pFolder;
    if(contentFolder == NULL) {
        return NULL;
    }    
    else {
        SLLNode* tmp = contentFolder->getFirst();
        while(tmp!=NULL) {
            if(tmp->getFlag() == 1) {
                if(tmp->getFile()->getFileDescriptor().compare(pFileDesc)==0) {
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
void ANB::deleteFolder(string pPath, string pUsername, string pPassword) {
    char* a = strdup(pPath.c_str());
    char* folderActual = strtok(a, "/");
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
SLL* ANB::searchSLLFolder(string pPath) {
    SLLNode* tmp = root;
    SLL* listaActual = tmp->getFolder();
    SLL* lista;
    
    char* a = strdup(pPath.c_str());
    char* folderActual = strtok(a, "/");
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
void ANB::queryFolder(string pPath, string pUsername, string pPassword) {
    SLLNode* cont = searchFolder(pPath);
    
    SLL* folder = cont->getFolder();
    
    SLLNode* tmp = folder->getFirst();
    while(tmp != NULL) {
        if(tmp->getFlag() == 0) {
            cout << tmp->getName() << endl;
        }
        else {
            string name = tmp->getFile()->getName();
            string fileDesc = tmp->getFile()->getFileDescriptor();
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
string ANB::getSchema(string pFileDesc) {
    SLL* folder_archivo = searchFile(pFileDesc, root->getFolder());
    SLLNode* archivo = folder_archivo->searchFile(pFileDesc);
    
    if(archivo == NULL) {
        return NULL;
    }
    else {
//        return archivo->getFile()->getSchema();
        schema* sc = archivo->getFile()->getSchema();
        Jzon::Object root;
        Jzon::Array schema;
        
        int count = 1;
        list<string>::iterator it_nombre = sc->get_nombre().begin();
        while(it_nombre != sc->get_nombre().end()) {
            string s_nomb = *it_nombre;
            Jzon::Object nod_nomb;
            nod_nomb.Add("Nombre", s_nomb);
            
            list<string>::iterator it_tamanyo = sc->get_tamanyo().begin();
            int tmp_tam = 1;
            while(tmp_tam!=count) {
                it_tamanyo++;
                tmp_tam++;
            }
            string s_tam = *it_tamanyo;
            nod_nomb.Add("Tamaño", s_tam);
            
            list<string>::iterator it_tipo = sc->get_tipo().begin();
            int tmp_tipo = 1;
            while(tmp_tipo!=count) {
                it_tipo++;
                tmp_tipo++;
            }
            string s_tipo = *it_tipo;
            nod_nomb.Add("Tamaño", s_tipo);
            
            it_nombre++;
            count++;
            schema.Add(nod_nomb);
         }
        root.Add("schema", schema);

        Jzon::Writer writer(root, Jzon::StandardFormat);
        writer.Write();
        std::string result = writer.GetResult();
        
        return result;
    }
}

/**
 * Crea un nuevo registro y lo añade al archivo especificado por su
 * fileDescriptor pasado como parámetro.
 * @param pFileDesc Descriptor del archivo para encontrar el archivo al que se le desea crear el nuevo registro de datos.
 * @param pValores Cadena de valores pasados por el usuario, contiene tanto el nombre de la columna como su vaor respectivo.
 * @return Una cadena de caracteres que contiene el número de registro y su posición dentro del archivo.
 */
int ANB::addRegister(string pFileDesc, string pValores, string pUsername, string pPassword) {
    SLL* folder_archivo = searchFile(pFileDesc, root->getFolder());
    if(folder_archivo == NULL) {
        return NULL;
    }
    SLLNode* archivo = folder_archivo->searchFile(pFileDesc);
    Disk_File* file = archivo->getFile();
    
    return file->addReg(pValores);
    
    
//    string nomb;
//    string value;
//    
//    int tipo_dato = 1;
//    int n = 3;
//    
//    while(n < pValores.size()-2) {
//        int i = n;
//        int j = n;
//        
//        while(pValores[j] != '>') {
//            j++;
//        }
//        string dato = pValores.substr(i,j);
//        
//        if(tipo_dato == 1) {
//            nomb = dato;
//            tipo_dato++;
//            n=j+3;
//        }
//        else {
//            value = dato;
//            tipo_dato = 1;
//            n = j+5;
//            int registLibre = file->getRegisterFree();
//            file->write(value, registLibre, file->getSchema()->getDesplazamiento(nomb), file->getSchema()->getConst(nomb), file->getSchema()->getColTam(nomb));
//        }
//    }
//    return to_string(file->getRegisterFree());
}

/**
 * Obtiene un registro a partir, ya sea de su número de registro, o de su desplazamiento
 * dentro del archivo(definido por pFlag). El archivo es definido po pFileDesc.
 * @param pColummns Columnas que se desean recuperar(* si son todas, o se definen).
 * @param pFlag Bandera que indica cual es el modo de busqueda del registro
 * 1-si es por numero de registro, 0-si es por desplazamiento dentro del archivo
 * @param pFileDesc FileDescriptor que representa al archivo donde se encuentra
 * el registro para mostrar.
 * @param pDeplaz Desplazamiento del registro a mostrar, dentro de su archivo.
 * @param pRegisterNumber Número de registro dentro del archivo.
 * @return Una cadena de caracteres que contiene los datos de las columnas consulatadas
 */
string ANB::getRegister(string pFileDesc, int pFlag, int pRegisterNumber_Desp, string pColummns, string pUsername, string pPassword) {
    SLL* folder_archivo = searchFile(pFileDesc, root->getFolder());
    SLLNode* archivo = folder_archivo->searchFile(pFileDesc);
    Disk_File* file = archivo->getFile();
    
    void* reg;
    if(pFlag == 1) {
        reg = file->readR(pRegisterNumber_Desp);
    }    else {
        reg = file->readO(pRegisterNumber_Desp);
    }
    
    string result = "";
    if (pColummns == "{*}") {
        int tam = file->getSchema()->get_nombre().size();
        int count = 0;
        int tmp = 0;
        while(count<tam) {
            string nomb = file->getSchema()->getName(count);
            string tipoDato = file->getSchema()->getTipo(nomb);
            
            if(tipoDato=="Byte") {
                char* value = (char*) (reg+tmp);
                tmp += 1;
                    
                std::string value_std(value);
                result.append("<"+nomb+":"+value_std+">");
            }
            else if(tipoDato=="Short") {
                short* value = (short*) (reg+tmp);
                tmp += 2;
                
                ostringstream ss;
                ss << value;
                    
                
                result.append("<"+nomb+":"+ss.str()+">");
            }
            else if(tipoDato=="Int") {
                int* value = (int*) (reg+tmp);
                tmp += 4;
                
                ostringstream ss;
                ss << value;
                
                
                result.append("<"+nomb+":"+ss.str()+">");
            }
            else if(tipoDato=="float") {
                float* value = (float*) (reg+tmp);
                tmp += 4;
                
                ostringstream ss;
                ss << value;
               
                result.append("<"+nomb+":"+ss.str()+">");
            }
            else if(tipoDato=="BigInt") {
                int tamDato = file->getSchema()->getColTam(nomb);
                int punteroTmp=tmp;
                string bigIntData;
                while(punteroTmp!=tamDato) {
                    int* value = (int*)(reg+tmp);
                    
                    ostringstream ss;
                    ss << value;
                    
                    bigIntData.append(ss.str());
                    tmp += 4;
                    punteroTmp += 4;
                }
                result.append("<"+nomb+":"+bigIntData+">");
            }
            else {
                int tamDato = file->getSchema()->getColTam(nomb);
                int punteroTmp=tmp;
                string bigIntData;
                while(punteroTmp!=tamDato) {
                    char* value = (char*)(reg+tmp);
                    
                    std::string value_std(value);
                    
                    bigIntData.append(value_std);
                    tmp += 1;
                    punteroTmp += 1;
                }
                result.append("<"+nomb+":"+bigIntData+">");
            }
        }
        return result;
    }
    else {
        int pos = 1;
        while(pos < pColummns.size()-1){
            int i = pos;
            int j = 0;
            while(pColummns[pos]!= ',' || pColummns[pos]!= '}') {
                pos++;
                j++;
            }
            string nomb = pColummns.substr(i,j);
            int desp = file->getSchema()->getDesplazamiento(nomb);
            
            string tipoDato = file->getSchema()->getTipo(nomb);
            if(tipoDato=="Byte") {
                char* value = (char*) (reg+desp);
                    
                std::string value_std(value);
                result.append("<"+nomb+":"+value_std+">");
            }
            else if(tipoDato=="Short") {
                short* value = (short*) (reg+desp);
                
                ostringstream ss;
                ss << value;
                    
                result.append("<"+nomb+":"+ss.str()+">");
            }
            else if(tipoDato=="Int") {
                int* value = (int*) (reg+desp);
                
                ostringstream ss;
                ss << value;
                
                result.append("<"+nomb+":"+ss.str()+">");
            }
            else if(tipoDato=="float") {
                float* value = (float*) (reg+desp);
                
                ostringstream ss;
                ss << value;
                
                result.append("<"+nomb+":"+ss.str()+">");
            }
            else if(tipoDato=="BigInt") {
                int tamDato = file->getSchema()->getColTam(nomb);
                int punteroTmp=desp;
                string bigIntData;
                while(punteroTmp!=tamDato) {
                    int* value = (int*)(reg+desp);
                    
                    ostringstream ss;
                    ss << value;

                    bigIntData.append(ss.str());
                    desp += 4;
                    punteroTmp += 4;
                }
                result.append("<"+nomb+":"+bigIntData+">");
            }
            else {
                int tamDato = file->getSchema()->getColTam(nomb);
                int punteroTmp=desp;
                string bigIntData;
                while(punteroTmp!=tamDato) {
                    char* value = (char*) (reg+desp);
                    
                   std::string value_std(value);
                    
                    bigIntData.append(value_std);
                    desp += 1;
                    punteroTmp += 1;
                }
                result.append("<"+nomb+":"+bigIntData+">");
            }
            pos++;
        }
        return result;
    }
    
    
//    string result = "";
//    
//    if (pFlag == 1) {
//        if (pColummns == "{*}") {
//            int tam = file->getSchema()->get_nombre().size();
//            int count = 0;
//            
//            while(count<tam) {
//                string nomb = file->getSchema()->getName(count);
//                string valor = file->read(pRegisterNumber_Desp, file->getSchema()->getDesplazamiento(nomb), file->getSchema()->getTam(nomb), file->getSchema()->getConst(nomb));
//                
//                result.append("<"+nomb+":"+valor+">");
//                
//                count++;
//            }
//            return result;
//        }
//        else {
//            int pos = 1;
//            while(pos < pColummns.size()-1){
//                int i = pos;
//                int j = pos;
//                while(pColummns[j]!= ',' || pColummns[j]!= '}') {
//                    j++;
//                }
//                string nomb = pColummns.substr(i,j);
//                string valor = file->read(pRegisterNumber_Desp, file->getSchema()->getDesplazamiento(nomb), file->getSchema()->getTam(nomb), file->getSchema()->getConst(nomb));
//                
//                result.append("<"+nomb+":"+valor+">");
//                
//                pos = j+1;
//            }
//            return result;
//        }
//    }
//    else {
//        // FALTA REALIZAR
//    }
}

/**
 * Elimina un registro específico.
 * @param pFileDesc File descriptor que identifica al archivo donde se localiza el registro
 * @param pFlag Bandera que indica cual es el modo de busqueda del registro
 * 1-si es por numero de registro, 0-si es por desplazamiento dentro del archivo.
 * @param pRegisterNumber_Desp Determina ya sea el número de registro o el desplazamiento
 * dentro del archivo, dependiendo de la bandera.
 * @return 0-Si la operación fue exitosa, 1-Si no lo fue
 */
int ANB::deleteRegister(string pFileDesc, int pFlag, int pRegisterNumber_Desp) {
    SLL* folder_archivo = searchFile(pFileDesc, root->getFolder());
    SLLNode* archivo = folder_archivo->searchFile(pFileDesc);
    Disk_File* file = archivo->getFile();
    
//    if(pFlag == 1) {
//        return file->deleteR(pRegisterNumber_Desp);
//    }
//    else {
//        return file->deleteO(pRegisterNumber_Desp);
//    }
}

/**
 * Consulta un archivo e imprime el ID y desplazamiento de cada registro del mismo.
 * @param pFileDesc File descriptor para buscar el archivo.
 */
void ANB::checkFile(string pFileDesc, string pUsername, string pPassword) {
    SLL* folder_archivo = searchFile(pFileDesc, root->getFolder());
    SLLNode* archivo = folder_archivo->searchFile(pFileDesc);
    Disk_File* file = archivo->getFile();
    
    RegisterPointer lista = file->getUsedRecords();
    RegisterPointerNode* tmp = lista.GetHead();
    for(tmp; tmp!=NULL; tmp = tmp->GetNext()) {
        cout << tmp->GetActual() << endl;
        //Imprimir desplazamiento.
    }
}

/**
 * Modifica un registro específico dentro del archivo especificado por el parametro pFileDesc
 * @param pFileDesc Descriptor que representa el archivo a consultar
 * @param pFlag Bandera que indica cual es el modo de busqueda del registro
 * 1-si es por numero de registro, 0-si es por desplazamiento dentro del archivo.
 * @param pRegisterNumber_Desp Desplazamiento del registro a mostrar, dentro de su archivo. O numero de registro
 * Dependiendo de la bandera.
 * @param pColummns Columnas que se desean modificar junto con su valor
 */
void ANB::modifyReg(string pFileDesc, int pFlag, int pRegisterNumber_Desp, string pColumns, string pUsername, string pPassword) {
    SLL* folder_archivo = searchFile(pFileDesc, root->getFolder());
    SLLNode* archivo = folder_archivo->searchFile(pFileDesc);
    Disk_File* file = archivo->getFile();
    
    string datos = "";
    
    int tipo_dato = 1;
    int n = 3;
    
    while(n < pColumns.size()-2) {
        int i = n;
        int j = 0;
        
        while(pColumns[i] != '>') {
            i++;
            j++;
        }
        string dato = pColumns.substr(n,j);
        if(tipo_dato == 1) {
            if(datos=="") {
                datos.append(dato);
            }
            else {
                datos.append(","+dato);
            }
            tipo_dato++;
            n=i+3;
        }
        else {
            datos.append(","+dato);
            
            tipo_dato = 1;
            n = i+5;
        }
    }
    
    if(pFlag==0) {
        file->modifyR(datos, pRegisterNumber_Desp);
    }
    else {
        file->modifyO(datos, pRegisterNumber_Desp);
    }
}
