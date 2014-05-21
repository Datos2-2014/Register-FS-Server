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
    RegisterPointerNode(int, int);
    RegisterPointerNode(const RegisterPointerNode& orig);
    virtual ~RegisterPointerNode();
    void SetNext(RegisterPointerNode* next);
    RegisterPointerNode* GetNext() const;
    void SetSiguiente(int siguiente);
    int GetSiguiente() const;
    void SetActual(int actual);
    int GetActual() const;
    
private:
    int actual;
    int siguiente;
    RegisterPointerNode* next;
};

#endif	/* REGISTERPOINTERNODE_H */

