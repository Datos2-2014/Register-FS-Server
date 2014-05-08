/* 
 * File:   SLLNode.cpp
 * Author: jeremy
 * 
 * Created on 19 de marzo de 2014, 08:05 PM
 */
#include "SLLNode.h"


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
        name = "";
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
