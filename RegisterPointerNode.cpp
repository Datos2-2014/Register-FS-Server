/* 
 * File:   RegisterPointerNode.cpp
 * Author: jeremy
 * 
 * Created on 16 de mayo de 2014, 02:27 AM
 */

#include "RegisterPointerNode.h"

RegisterPointerNode::RegisterPointerNode(int pActual, int pSiguiente) {
    this->actual=pActual;
    this->siguiente=pSiguiente;
}

RegisterPointerNode::RegisterPointerNode(const RegisterPointerNode& orig) {
}

RegisterPointerNode::~RegisterPointerNode() {
}

void RegisterPointerNode::SetNext(RegisterPointerNode* next) {
    this->next = next;
}

RegisterPointerNode* RegisterPointerNode::GetNext() const {
    return next;
}

void RegisterPointerNode::SetSiguiente(int siguiente) {
    this->siguiente = siguiente;
}

int RegisterPointerNode::GetSiguiente() const {
    return siguiente;
}

void RegisterPointerNode::SetActual(int actual) {
    this->actual = actual;
}

int RegisterPointerNode::GetActual() const {
    return actual;
}

