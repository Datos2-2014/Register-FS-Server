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
    void set_nombre(string);
    void set_tipo(string);
    void set_tamanyo(string);
    schema();
    schema(const schema& orig);
    virtual ~schema();
    list<string> get_nombre();
    list<string> get_tipo();
    list<string> get_tamanyo();
    void setTamanyoTotal();
    int getDesplazamiento(string);
    int getColTam(string);
    int getConst(string);
    
private:
    list<string> nombre;
    list<string> tipo;
    list<string> tamanyo;
    int tamanyoTotal=0;
};

#endif	/* SCHEMA_H */

