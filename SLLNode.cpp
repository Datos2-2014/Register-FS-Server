/* 
 * File:   SLLNode.cpp
 * Author: jeremy
 * 
 * Created on 19 de marzo de 2014, 08:05 PM
 */

#include "SLLNode.h"

SLLNode::SLLNode(int pData) {
    data = pData;
    next = 0;
}

SLLNode::SLLNode(const SLLNode& orig) {
}

SLLNode::~SLLNode() {
}

int SLLNode::getData() {
    return this->data;
}

SLLNode* SLLNode::getNext() {
    return next;
}

void SLLNode::setNext(SLLNode* pNext) {
    this->next = pNext;
}