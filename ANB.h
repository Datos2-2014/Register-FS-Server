/* 
 * File:   ANB.h
 * Author: jeremy
 *
 * Created on 8 de mayo de 2014, 02:22 AM
 */

#ifndef ANB_H
#define	ANB_H

#include "SLLNode.h"

class ANB {
public:
    ANB();
    ANB(const ANB& orig);
    virtual ~ANB();
    
    int newFolder(string, char[]); //Añade un nuevo contenedor
//    char* newFile(char[16], char[64], char[]); //Añade un nuevo archivo al arbol
    
    
    
private:
    SLLNode* root; //Raiz del arbol n-ario
    
    SLLNode* searchFolder(char[]); //Auxiliar, busca un nodo a partir de la direccion de la carpeta
};

#endif	/* ANB_H */

