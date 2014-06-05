/* 
 * File:   header.h
 * Author: rodrigo
 *
 * Created on 16 de mayo de 2014, 12:59 AM
 */

#ifndef HEADER_H
#define	HEADER_H
#include <string>
using namespace std;
class header {
public:
    header();
    header(int,int,int,int,int,int);
    header(const header& orig);
    virtual ~header();
    void modificacion();
    void setModificado(bool modificado);
    bool getModificado() const;
    void setSize(short size);
    unsigned short getSize() const;
    void setNumregtot(int numregtot);
    unsigned int getNumregtot() const;
    void setNumreglibres(int numreglibres);
    unsigned int getNumreglibres() const;
    void setRegistros_libres(int registros_libres);
    unsigned int getRegistros_libres() const;
    void setFin(int fin);
    unsigned int getFin() const;
    void setInicio(int inicio);
    unsigned int getInicio() const;
    void setSchema(string schema);
    string getSchema() const;
    void setFilename(string filename);
    string getFilename() const;
    void setClientDescriptor(string clientDescriptor);
    string getClientDescriptor() const; 
        
private:
    private:
        unsigned int inicio; 
        unsigned int fin; 
        unsigned int registros_libres;
        unsigned int numreglibres;
        unsigned int numregtot;
        unsigned short size;
        bool modificado= false;
        string schema;
        string clientDescriptor;
        string filename;
};

#endif	/* HEADER_H */

