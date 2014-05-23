/* 
 * File:   RegisterPointer.h
 * Author: jeremy
 *
 * Created on 16 de mayo de 2014, 02:21 AM
 */

#ifndef REGISTERPOINTER_H
#define	REGISTERPOINTER_H

#include "RegisterPointerNode.h"
#include <cstdio>

class RegisterPointer {
public:
    RegisterPointer();
    RegisterPointer(const RegisterPointer& orig);
    virtual ~RegisterPointer();
    void SetTail(RegisterPointerNode* _tail);
    RegisterPointerNode* GetTail() const;
    void SetHead(RegisterPointerNode* _head);
    RegisterPointerNode* GetHead() const;
    void addRegister(int, int);
    void remove(int);
    int search(int);
    RegisterPointerNode* deleteHead();
private:
    RegisterPointerNode* _head;
    RegisterPointerNode* _tail;
};

#endif	/* REGISTERPOINTER_H */

