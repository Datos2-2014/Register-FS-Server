/* 
 * File:   SLLNode.h
 * Author: jeremy
 *
 * Created on 19 de marzo de 2014, 08:05 PM
 */
#ifndef SLLNODE_H
#define	SLLNODE_H
#include "Disk_File.h"
#include "SLL.h"

using namespace std;

class SLL;
class SLLNode {
    public:
        SLLNode(Disk_File*, string);
        SLLNode(const SLLNode& orig);
        virtual ~SLLNode();
        
        Disk_File* getFile(); //Obtiene el archivo almacenado en el nodo
        SLLNode* getNext(); //Obtiene un puntero hacia el siguiente nodo
        void setNext(SLLNode*); //Establece el puntero hacia un nodo siguiente
        int getFlag(); //Bandera que representa si el contenido del nodo es o no archivo
        string getName(); //Devuelve el nombre de la carpeta
        SLL* getFolder(); //Devuelve el contenido de una carpeta
        
    private:
        SLLNode* next; //Nodo siguiente
        
        int flag; //1:Archivo; 0:Carpeta
        
        Disk_File* file; //Archivo
        
        SLL* folder; //Carpeta; lista de su contenido
        string name; //Nombre para la carpeta
};

#endif	/* SLLNODE_H */

