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
    int createSchema(char[32], string); //Crea el esquema de registros para un archivo especifico
    void deleteFile(char[32]); //Elimina un archivo representado por el file descriptor entrado como parametro
    
private:
    SLLNode* root; //Raiz del arbol n-ario
    
    SLLNode* searchFolder(char[]); //Auxiliar, busca un nodo a partir de la direccion de la carpeta
    SLL* searchFile(char[32], SLL*); //Auxiliar, busca un arcivo, cuando lo encuentra devuelve la lista(carpeta) donde se encuentra.
};

#endif	/* ANB_H */

