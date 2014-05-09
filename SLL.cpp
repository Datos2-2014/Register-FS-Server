/* 
 * File:   SLL.cpp
 * Author: jeremy
 * 
 * Created on 19 de marzo de 2014, 08:03 PM
 */
#include <iostream>
#include "SLL.h"
#include "Disk_File.h"

SLL::SLL() {
    first = NULL;
    size = 0;
}

SLL::SLL(const SLL& orig) {
}

SLL::~SLL() {
}

/**
 * Obtiene el primer nodo de la lista.
 * @return Primer nodo de la lista
 */
SLLNode* SLL::getFirst() {
    return first;
}

/**
 * Establece el nodo para el apuntador al primer nodo de la lista.
 * @param pFirst puntero para el primer nodo.
 */
void SLL::setFirst(SLLNode* pFirst) {
    this->first = pFirst;
}

/**
 * Obtiene el tamaño de la lista.
 * @return Cantidad de datos de la lista.
 */
int SLL::getSize() {
    return size;
}

/**
 * Inserta un elemento al final de la lista.
 * @param pData Dato para el nodo a insertar.
 */
void SLL::insert(Disk_File* pFile, string pFolderName) {
    SLLNode* tmp = new SLLNode(pFile,pFolderName);
    
    if(first==0) {
        first = tmp;
        size++;
    }
    
    else {
        int i = 0;
        SLLNode* tmp1 = first;
        while(i<size-1) {
            tmp1 = first->getNext();
            i++;
        }
        tmp1->setNext(tmp);
        size++;
    }
}


/**
 * Elimina un nodo de lal lista a partir de su elemento.
 * Referencia: http://ronnyml.wordpress.com/2009/07/04/listas-enlazadas-clase-lista-en-c/
 * @param pData Elemento para buscar el nodo a eliminar.
 */
void SLL::removeFile(string pFileDesc) {
    SLLNode* tmp1 = first;
    SLLNode* tmp2 = first->getNext();
    
    if((first->getFlag() == 1) && (first->getFile()->getFileName().compare(pFileDesc))) {
            first = first->getNext();
            delete tmp1;
    }
    
    else {
        while(tmp2) {
            if((tmp2->getFlag() == 1) && (tmp2->getFile()->getFileName().compare(pFileDesc))) {
                tmp1->setNext(tmp2->getNext());
                delete tmp2;
                size --;
                return;
            }
            else {
                tmp1 = tmp1->getNext();
                tmp2 = tmp2->getNext();
            }
        }
        cout << "El archivo no existe" << endl;
    }
}