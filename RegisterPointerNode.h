/* 
 * File:   RegisterPointerNode.h
 * Author: jeremy
 *
 * Created on 16 de mayo de 2014, 02:27 AM
 */

#ifndef REGISTERPOINTERNODE_H
#define	REGISTERPOINTERNODE_H

class RegisterPointerNode {
public:
    RegisterPointerNode();
    RegisterPointerNode(const RegisterPointerNode& orig);
    virtual ~RegisterPointerNode();
    
private:
    int actual;
    int siguiente;
    RegisterPointerNode* next;
};

#endif	/* REGISTERPOINTERNODE_H */

