/* 
 * File:   RegisterPointer.h
 * Author: jeremy
 *
 * Created on 16 de mayo de 2014, 02:21 AM
 */

#ifndef REGISTERPOINTER_H
#define	REGISTERPOINTER_H

#include "RegisterPointerNode.h"

class RegisterPointer {
public:
    RegisterPointer();
    RegisterPointer(const RegisterPointer& orig);
    virtual ~RegisterPointer();
    
private:
    RegisterPointerNode* first;
    RegisterPointerNode* tail;
};

#endif	/* REGISTERPOINTER_H */

