/* 
 * File:   ANB.h
 * Author: jeremy
 *
 * Created on 8 de mayo de 2014, 02:22 AM
 */

#ifndef ANB_H
#define	ANB_H

#include "SLLNode.h"
#include "Markup.h"

using namespace std;
class ANB {
public:
    ANB();
    ANB(const ANB& orig);
    virtual ~ANB();
    
    int newFolder(string, string); //Añade un nuevo contenedor.
    string newFile(string, string, string); //Añade un nuevo archivo al arbol.
    int createSchema(string, string); //Crea el esquema de registros para un archivo especifico.
    void deleteFile(string); //Elimina un archivo representado por el file descriptor entrado como parametro.
    void deleteFolder(string); //Elimina una carpeta. Esta operacion no se puede realizar si dicha carpeta tiene contenido.
    void queryFolder(string); //Consulta una carpeta para mostrar su contenido en pantalla.
    string getSchema(string); //Obtiene e imprime en consola los datos del esquema de regitro de un archivo.
    int addRegister(string, string); //Crea un nuevo registro en el archivo.
    string getRegister(string, int, int, string); //Obtiene el registro.
    int deleteRegister(string, int, int); //Borra un registro.
    void checkFile(string); //Consulta un archivo.
    void modifyReg(string, int, int, string);
    SLLNode* getRoot();
    void addUser(string,string,int);
    void addPermission(string,string,string);
    void flush();
    
private:
    SLLNode* root; //Raiz del arbol n-ario
    int id; //Identificador para el RegisterFS
    int userID;
    
    SLLNode* searchFolder(string); //Auxiliar, busca un nodo a partir de la direccion de la carpeta
    SLL* searchFile(string, SLL*); //Auxiliar, busca un arcivo, cuando lo encuentra devuelve la lista(carpeta) donde se encuentra.
    SLL* searchSLLFolder(string); //Busca una carpeta y retorna la lista donde esta se encuentra.
    void saveXML();
    void save_Aux(SLL*, CMarkup);
    void flush(SLL* pFolder);
};

#endif	/* ANB_H */

