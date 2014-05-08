/* 
 * File:   SLLNode.cpp
 * Author: jeremy
 * 
 * Created on 19 de marzo de 2014, 08:05 PM
 */
#include "SLLNode.h"

/**
 * Constructor, crea un nodo a partir de su dato, sea carpeta o archivo
 * @param pFile Archivo para establecercomo contenido, en el caso de que sea nulo se crea una carpeta a partir del siguiente parametro
 * @param pFolderName Nombre para la carpeta a crear en caso de que lo que se quiera sea una carpeta
 */
SLLNode::SLLNode(Disk_File *pFile, string pFolderName) {
    if(pFile == NULL) {
        flag = 0;
        file = NULL;
        folder = new SLL();
        name = pFolderName;
        next = NULL;
    }
    else {
        file = pFile;
        name = pFolderName;
        flag = 1;
        next = NULL;
    }
}

SLLNode::SLLNode(const SLLNode& orig) {
}

SLLNode::~SLLNode() {
}

Disk_File* SLLNode::getFile() {
    return file;
}

SLLNode* SLLNode::getNext() {
    return next;
}

void SLLNode::setNext(SLLNode* pNext) {
    this->next = pNext;
}

int SLLNode::getFlag() {
    return flag;
}

SLL* SLLNode::getFolder() {
    return folder;
}

string SLLNode::getName() {
    return name;
}

