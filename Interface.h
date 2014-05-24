/* 
 * File:   Interface.h
 * Author: rodrigo
 *
 * Created on 23 de mayo de 2014, 07:57 PM
 */

#ifndef INTERFACE_H
#define	INTERFACE_H
#include <string>
#include "ANB.h"

using namespace std;

class Interface {
public:
    Interface();
    Interface(const Interface& orig);
    virtual ~Interface();
    string run(string,ANB*);
private:

};

#endif	/* INTERFACE_H */

