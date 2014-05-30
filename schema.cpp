/* 
 * File:   schema.cpp
 * Author: jeremy
 * 
 * Created on 8 de mayo de 2014, 02:32 PM
 */

#include "schema.h"

schema::schema(string pFormato) {
    int tipo_dato=1;
     int n=3;
     while (n < pFormato.size()-2){
         int i=n;
         int j=n;
         while (pFormato[j]!='>'){
             j++;
         }
         string dato=pFormato.substr(i,j);  //string dato=formato.substr(i,i+j-1);
         if (tipo_dato==1){
             this->set_nombre(dato);
             tipo_dato++;
             n=j+3;
         }
         else{
             if (tipo_dato==2){
                 this->set_tipo(dato);
                 tipo_dato++;
                 n=j+3;
             }
             else{
                 if (tipo_dato==3){
                     this->set_tamanyo(dato);
                     tipo_dato=1;
                     n=j+5;
                 }
             }
         }
     }
     this->setTamanyoTotal();
}

schema::schema(const schema& orig) {
}

schema::~schema() {
}

void schema::set_nombre(string pNombre){
    nombre.push_back(pNombre);
}

void schema::set_tamanyo(string pSize){
    tamanyo.push_back(pSize);
}

void schema::set_tipo(string pTipo) {
    tipo.push_back(pTipo);
}

list<string> schema::get_nombre() {
    return nombre;
}

list<string> schema::get_tamanyo() {
    return tamanyo;
}

list<string> schema::get_tipo() {
    return tipo;
}

/**
 * Establece el total del tamaño del registro sumando los
 * tamaños de todas las columnas.
 */
void schema::setTamanyoTotal() {
    list<string>::iterator it_tamanyo = tamanyo.begin();
    while(it_tamanyo != tamanyo.end()) {
        string s = *it_tamanyo;
        int a = atoi(s.c_str());
        tamanyoTotal += a;
        it_tamanyo++;
     }
}

/**
 * Obtiene el desplazamiento para un registro de acuerdo a la
 * posicion de la columna.
 * @param pNombre Nombre de la columna.
 * @return Desplazamiento.
 */
int schema::getDesplazamiento(string pNombre) {
    list<string>::iterator it_nombre = nombre.begin();
    
    string data = *it_nombre;
    int pos = 0;
    
    while(data.compare(pNombre) != 0) {
        it_nombre++;
        data = *it_nombre;
        pos++;
    }
    
    list<string>::iterator it_tamanyo = tamanyo.begin();
    
    int count = 0;
    int desp = 0;
    
    while(count != pos) {
        string s = *it_tamanyo;
        int a = atoi(s.c_str());
        desp += a;
        
        it_tamanyo++;
        count++;
    }
    return desp;
}

/**
 * Obtiene la constante necesaria para hacer la escritura,
 * de acuerdo al tipo de dato de la columna. Si es un bigInt
 * obtiene su tamaño respectivo, de lo contrario retorna un 0.
 * @param pNombre Nombre de la columna a consultar.
 * @return 0-para cualquier tipo, tamaño-para BigInt.
 */
int schema::getColTam(string pNombre) {
    list<string>::iterator it_nombre = nombre.begin();
    
    string dataNombre = *it_nombre;
    int pos = 0;
    
    while(dataNombre.compare(pNombre) != 0) {
        it_nombre++;
        dataNombre = *it_nombre;
        pos++;
    }
    
    list<string>::iterator it_tipo = tipo.begin();
    
    string data;
    int count = 0;
    
    while(count <= pos) {
        data = *it_tipo;
        
        it_tipo++;
        count++;
    }
    
    if(data.compare("BigInt") == 0) {
        list<string>::iterator it_tamanyo = tamanyo.begin();

        int count = 0;
        int tam;
        
        while(count <= pos) {
            string s = *it_tamanyo;
            int a = atoi(s.c_str());
            tam = a;

            it_tamanyo++;
            count++;
        }
        return tam;
    }
    else {
        return 0;
    }
}
/**
 * Obtiene una constante que representa el tipo de dato en la columna buscada.
 * @param pNombre Columna para buscar y obtener su tipo de dato.
 * @return Valor constante que representa el tipo de dato.
 */
int schema::getConst(string pNombre) {
    list<string>::iterator it_nombre = nombre.begin();
    
    string dataNombre = *it_nombre;
    int pos = 0;
    
    while(dataNombre.compare(pNombre) != 0) {
        it_nombre++;
        dataNombre = *it_nombre;
        pos++;
    }
    
    list<string>::iterator it_tipo = tipo.begin();
    
    string data;
    int count = 0;
    
    while(count <= pos) {
        data = *it_tipo;
        
        it_tipo++;
        count++;
    }
    
    if (data.compare("Byte") == 0) {
        return 4;
    }
    else if (data.compare("Short") == 0) {
        return 5;
    }
    else if (data.compare("Int") == 0) {
        return 0;
    }
    else if (data.compare("float") == 0) {
        return 1;
    }
    else if (data.compare("BigInt") == 0) {
        return 2;
    }
    else {
        return 3;
    }
}

/**
 * Obtiene un nombre de columna de acuerdo a su posición en la lista.
 * @param pIndex Indice donde se necuentra el nombre.
 * @return Nombre en ese índice.
 */
string schema::getName(int pIndex) {
    list<string>::iterator it_nombre = nombre.begin();
    
    string dataNombre = *it_nombre;
    int pos = 0;
    
    while(pos<pIndex) {
        it_nombre++;
        dataNombre = *it_nombre;
        pos++;
    }
    return dataNombre;
}

/**
 * Obtiene el tamaño de una columna de acuerdo a su nombre.
 * @param pNombre Nombre de la columna.
 * @return tamaño de la columna.
 */
int schema::getTam(string pNombre) {
    list<string>::iterator it_nombre = nombre.begin();
    
    string dataNombre = *it_nombre;
    int pos = 0;
    
    while(dataNombre.compare(pNombre) != 0) {
        it_nombre++;
        dataNombre = *it_nombre;
        pos++;
    }
    
    list<string>::iterator it_tamanyo = tamanyo.begin();
    
    int tam;
    int count = 0;
    
    while(count <= pos) {
        string s = *it_tamanyo;
        int a = atoi(s.c_str());
        tam = a;
        it_tamanyo++;
        count++;
    }
    
    return tam;
}

int schema::getTamanyoTotal() const {
    return tamanyoTotal;
}

/**
 * Obtiene el tipo de dato de acuerdo al nombre de la columna
 * @param pNombre Nombre de la colimna
 * @return String que representa el tipo de dato en esta columna
 */
string schema::getTipo(string pNombre) {
    list<string>::iterator it_nombre = nombre.begin();
    
    string dataNombre = *it_nombre;
    int pos = 0;
    
    while(dataNombre.compare(pNombre) != 0) {
        it_nombre++;
        dataNombre = *it_nombre;
        pos++;
    }
    
    list<string>::iterator it_tipo = tipo.begin();
    
    string tipo;
    int count = 0;
    
    while(count <= pos) {
        string s = *it_tipo;
        tipo = s;
        it_tipo++;
        count++;
    }
    
    return tipo;
}
