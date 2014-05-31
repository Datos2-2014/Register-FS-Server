/* 
 * File:   RegisterPointerNode.h
 * Author: jeremy
 *
 * Created on 16 de mayo de 2014, 02:27 AM
 */

#ifndef REGISTERPOINTERNODE_H
#define	REGISTERPOINTERNODE_H
#include <cstdio>
#include <string.h>
#include "ConfigurationFile.h"
#include "schema.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

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
    int GetOffset() const;
    void* GetRegistro() const;
    void init(string* , schema*);
    void modify(void* pDatos, string* pColum, schema * pSchema);
    void flush();
   
    
private:
    int _NumReg;
    int _siguiente;
    RegisterPointerNode* _next;
    void * _Registro;
    int _offset;
    
    bool _modify;
    bool inMemory;
    
    void initVoidp(string *, schema*);
    void updateVoidP(string*, string*, schema*);
    
    inline bool isInteger(const string &);
    bool isFloat( string );
    bool isShort(string);
    bool IsInMemory() const ;
};
#endif	/* REGISTERPOINTERNODE_H */

