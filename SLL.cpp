/* 
 * File:   SLL.cpp
 * Author: jeremy
 * 
 * Created on 19 de marzo de 2014, 08:03 PM
 */

#include <cstdlib>
#include <iostream>
#include "SLL.h"
#include "SLLNode.h"

using namespace std;

SLL::SLL() {
    first = 0;
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
 * Imprime los datos de la lista de manera lineal.
 */
void SLL::print() {
    SLLNode* tmp = first;
    for (tmp; tmp != 0; tmp = tmp->getNext()) {
        cout << tmp->getData() << " - ";
    }
    cout << "\n";
}

/**
 * Inserta un elemento al principio de la lista.
 * @param pData Dato para inserta al nodo a insertar.
 */
void SLL::insertHead(int pData) {
    SLLNode* tmp = new SLLNode(pData);
    
    if(first==0) {
        first = tmp;
        size++;
    }
    
    else {
        tmp->setNext(first);
        setFirst(tmp);
        size++;
    }
}

/**
 * Inserta un elemento al final de la lista.
 * @param pData Dato para el nodo a insertar.
 */
void SLL::insertTail(int pData) {
    SLLNode* tmp = new SLLNode(pData);
    
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
 * Inserta elementos en orden a la lista.
 * Referencia: http://ronnyml.wordpress.com/2009/07/04/listas-enlazadas-clase-lista-en-c/
 * @param pData Dato para el nodo a insertar.
 */
void SLL::insertInOrder(int pData) {
    SLLNode* tmp = new SLLNode (pData);
    SLLNode* tmpF = first;
 
    if (!first) {
        first = tmp;
    } 
    else {
        if (first->getData() > pData) {
            tmp->setNext(first);
            first = tmp;
        } 
        else {
            while ((tmpF->getNext() != 0) && (tmpF->getNext()->getData() < pData)) {
                tmpF = tmpF->getNext();
            }
            tmp->setNext(tmpF->getNext());
            tmpF->setNext(tmp);
        }
    }
    size++;
}

/**
 * Elimina un nodo de lal lista a partir de su elemento.
 * Referencia: http://ronnyml.wordpress.com/2009/07/04/listas-enlazadas-clase-lista-en-c/
 * @param pData Elemento para buscar el nodo a eliminar.
 */
void SLL::remove(int pData) {
    SLLNode* temp = first;
    SLLNode* temp1 = first->getNext();
 
    int cont = 0;
 
    if (first->getData() == pData) {
        first = temp->getNext();
    } 
    else {
        while (temp1) {
            if (temp1->getData() == pData) {
                SLLNode* aux_node = temp1;
                temp->setNext(temp1->getNext());
                delete aux_node;
                cont++;
                size--;
            }
            temp = temp->getNext();
            temp1 = temp1->getNext();
        }
    }
 
    if (cont == 0) {
        cout << "No existe el dato " << endl;
    }
}

/**
 * Busca un nodo en la lista a partir de su parametro y retorna true si lo
 * encuentra y false de lo contrario.
 * @param pData Elemento para buscar el nodo.
 * @return true si encuentra el nodo, false de lo contrario.
 */
bool SLL::search(int pData) {
    SLLNode* tmp = first;
    
    while(tmp) {
        if(tmp->getData() == pData) {
            return true;
        }
        tmp = tmp->getNext();
    }
    return false;
}

/**
 * Combina 2 listas de manera ordenada ascendentemente.
 * @param pList Lista para concatenar.
 * @return Puntero a la nueva lista formada por los elementos de las dos.
 */
SLL* SLL::merge(SLL &pList) {
    SLL* newList = new SLL();
    
    SLLNode* tmp2 = first;
    while(tmp2) {
        newList->insertInOrder(tmp2->getData());
        tmp2 = tmp2->getNext();
    }
    
    SLLNode* tmp1 = pList.getFirst();
    while(tmp1) {
        newList->insertInOrder(tmp1->getData());
        tmp1 = tmp1->getNext();
    }
    
    return newList;
}

/**
 * Forma una nueva lista con los elemento que se repiten en ambas.
 * @param Lista para comprobar elementos repetidos.
 * @return Puntero a la nueva lista.
 */
SLL* SLL::intersection(SLL& pList) {
    SLL* newList = new SLL();
    
    SLLNode* tmp1 = first;
    SLLNode* tmp2;
    
    while(tmp1) {
        tmp2 = pList.getFirst();
        int elem = tmp1->getData();
        while(tmp2) {
            if(elem == tmp2->getData()) {
                newList->insertHead(elem);
                break;
            }
            else {
                tmp2 = tmp2->getNext();
            }
        }
        tmp1 = tmp1->getNext();
    }
    return newList;
}

/**
 * Incierte la lista, el ultimo elemento quedaria de primero en ella.
 * Referencia: http://ronnyml.wordpress.com/2009/07/04/listas-enlazadas-clase-lista-en-c/
 */
void SLL::invert() {
    SLLNode* prev = NULL;
    SLLNode* next = NULL;
    SLLNode* temp = first;
 
    while (temp) {
        next = temp->getNext();
        temp->setNext(prev);
        prev = temp;
        temp = next;
    }
    first = prev;
}

void SLL::insertRandom(int pNum) {
    if(pNum == 0) {
        
    }
    else {
        for(int i = pNum; i>0; i++) {
            int randomInt = rand()%5001;
            insertHead(randomInt);
        }
    }
}