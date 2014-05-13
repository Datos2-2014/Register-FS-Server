/* 
 * File:   SLL.h
 * Author: jeremy
 *
 * Created on 19 de marzo de 2014, 08:03 PM
 */
#ifndef SLL_H
#define	SLL_H
#include "SLLNode.h"

using namespace std;
class SLLNode;
class SLL {
    public:
        SLL();
        SLL(const SLL& orig);
        virtual ~SLL();
        
        SLLNode* getFirst(); //Obtiene el primer nodo de la lista
        void setFirst(SLLNode*); //Establece un puntero para el primer nodo de la lista
        int getSize(); //Obtiene el tamaño total actual de la lista
        
        void insert(Disk_File*, string); //Inserta un nodo a la lista
        void removeFile(string); //Remueve un nodo de la lista
        void removeFolder(string); //Remueve una carpeta de una lista simple
    
    private:
        SLLNode *first; //Primer nodo de la lista
        int size; //Tamaño actual de la lista
};

#endif	/* SLL_H */

