/* 
 * File:   header.h
 * Author: rodrigo
 *
 * Created on 16 de mayo de 2014, 12:59 AM
 */

#ifndef HEADER_H
#define	HEADER_H

class header {
public:
    header();
    header(int,int,int,int,int,int);
    header(const header& orig);
    virtual ~header();
    void modificacion();
    void setModificado(bool modificado);
    bool getModificado() const;
    void setSize(int size);
    int getSize() const;
    void setNumregtot(int numregtot);
    int getNumregtot() const;
    void setNumreglibres(int numreglibres);
    int getNumreglibres() const;
    void setRegistros_libres(int registros_libres);
    int getRegistros_libres() const;
    void setFin(int fin);
    int getFin() const;
    void setInicio(int inicio);
    int getInicio() const; //Devuelve el contenido de una carpeta
        
private:
    private:
        int inicio; 
        int fin; 
        int registros_libres;
        int numreglibres;
        int numregtot;
        int size;
        bool modificado= false;

};

#endif	/* HEADER_H */

