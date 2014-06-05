/* 
 * File:   header.cpp
 * Author: rodrigo
 * 
 * Created on 16 de mayo de 2014, 12:59 AM
 */

#include "header.h"

header::header(int ini, int finn, int regLibres, int regsLibres, int regtotales, int tamanyo){
    inicio=ini;
    fin=finn;
    registros_libres=regLibres;
    numreglibres=regsLibres;
    numregtot=regtotales;
    size=tamanyo;
    
    
}

header::header() {
}

header::header(const header& orig) {
}

header::~header() {
    
}

void header::modificacion(){
    if (modificado==0){
        modificado=true;
    }
    else{
        modificado=false;
    }
    
}

void header::setModificado(bool modificado) {
    this->modificado = modificado;
}

bool header::getModificado() const {
    return modificado;
}

void header::setSize(short size) {
    this->size = size;
}

unsigned short header::getSize() const {
    return size;
}

void header::setNumregtot(int numregtot) {
    this->numregtot = numregtot;
}

unsigned int header::getNumregtot() const {
    return numregtot;
}

void header::setNumreglibres(int numreglibres) {
    this->numreglibres = numreglibres;
}

unsigned int header::getNumreglibres() const {
    return numreglibres;
}

void header::setRegistros_libres(int registros_libres) {
    this->registros_libres = registros_libres;
}

unsigned int header::getRegistros_libres() const {
    return registros_libres;
}

void header::setFin(int fin) {
    this->fin = fin;
}

unsigned int header::getFin() const {
    return fin;
}

void header::setInicio(int inicio) {
    this->inicio = inicio;
}

unsigned int header::getInicio() const {
    return inicio;
}

void header::setSchema(string schema) {
    this->schema = schema;
}

string header::getSchema() const {
    return schema;
}

void header::setFilename(string filename) {
    this->filename = filename;
}

string header::getFilename() const {
    return filename;
}

void header::setClientDescriptor(string clientDescriptor) {
    this->clientDescriptor = clientDescriptor;
}

string header::getClientDescriptor() const {
    return clientDescriptor;
}

