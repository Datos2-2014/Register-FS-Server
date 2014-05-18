/* 
 * File:   RegisterPointer.cpp
 * Author: jeremy
 * 
 * Created on 16 de mayo de 2014, 02:21 AM
 */

#include "RegisterPointer.h"
#include <iostream>
using namespace std;


RegisterPointer::RegisterPointer() {
    this->_head=NULL;
    this->_tail=NULL;
}

RegisterPointer::RegisterPointer(const RegisterPointer& orig) {
}

RegisterPointer::~RegisterPointer() {
}



void RegisterPointer::SetTail(RegisterPointerNode* _tail) {
    this->_tail = _tail;
}

RegisterPointerNode* RegisterPointer::GetTail() const {
    return _tail;
}

void RegisterPointer::SetHead(RegisterPointerNode* _head) {
    this->_head = _head;
}

RegisterPointerNode* RegisterPointer::GetHead() const {
    return _head;
}

void RegisterPointer::addRegister(int pActual, int pNext){
    RegisterPointerNode* tmp=new RegisterPointerNode(pActual, pNext);
    if(this->_tail!=NULL){
        this->_tail->SetNext(tmp);
        this->_tail=tmp;
    }
    else{
        this->_head=tmp;
        this->_tail=this->_head;
    }
}

/**
 * Elimina un nodo de lal lista a partir de su elemento.
 * Referencia: http://ronnyml.wordpress.com/2009/07/04/listas-enlazadas-clase-lista-en-c/
 * @param pData Elemento para buscar el nodo a eliminar.
 */
void RegisterPointer::remove(int pData) {
    RegisterPointerNode* temp = _head;
    RegisterPointerNode* temp1 = _head->GetNext();
 
    int cont = 0;
 
    if (_head->GetActual() == pData) {
        _head = temp->GetNext();
    } 
    else {
        while (temp1) {
            if (temp1->GetActual() == pData) {
                RegisterPointerNode* aux_node = temp1;
                temp->SetNext(temp1->GetNext());
                delete aux_node;
                cont++;
            }
            temp = temp->GetNext();
            temp1 = temp1->GetNext();
        }
    }
 
    if (cont == 0) {
        cout << "No existe el dato " << endl;
    }
}

/**
 * Busca un nodo de la lista a partir de su elemento.
 * Referencia: http://ronnyml.wordpress.com/2009/07/04/listas-enlazadas-clase-lista-en-c/
 * @param pData Elemento para buscar el nodo a eliminar.
 * @return delvuelve 1 si el elemento se encuentra en caso contrario devuelve 0.
 */
int RegisterPointer::search(int pData) {
    RegisterPointerNode* temp1 = _head->GetNext();
 
    int cont = 0;
 
    if (_head->GetActual() == pData) {
        return 1;
    } 
    else {
        while (temp1) {
            if (temp1->GetActual() == pData) {
                temp1=_tail->GetNext();
                cont++;
            }
            temp1 = temp1->GetNext();
        }
    }
 
    if (cont == 0) {
        return 0;
    }
    else{
        return 1;
    }
}

/**
 * Elimina el head de la lista. (POP)
 * Referencia: http://ronnyml.wordpress.com/2009/07/04/listas-enlazadas-clase-lista-en-c/
 */
void RegisterPointer::deleteHead() {
    _head = _head->GetNext();
 
}

