/* 
 * File:   schema.h
 * Author: jeremy
 *
 * Created on 8 de mayo de 2014, 02:32 PM
 */

#ifndef SCHEMA_H
#define	SCHEMA_H

#include <string>
#include <list>

using namespace std;

class schema {
public:
    schema();
    schema(const schema& orig);
    virtual ~schema();
    
private:
    char fileDescr[32];
    list<string> nombre;
    list<string> tipo;
    list<string> tamanyo;
};

#endif	/* SCHEMA_H */

