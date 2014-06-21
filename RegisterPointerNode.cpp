/* 
 * File:   RegisterPointerNode.cpp
 * Author: jeremy
 * 
 * Created on 16 de mayo de 2014, 02:27 AM
 */
#include "RegisterPointerNode.h"
#include "schema.h"

RegisterPointerNode::RegisterPointerNode(int pActual, int pSiguiente) {
    this->_NumReg=pActual;
    this->_siguiente=pSiguiente;
    this->inMemory=false;
    this->_next=NULL;
    this->_Registro=NULL;
    this->_modify=false;
//    this->
}

/*Funcion que incializa desde un string de entrada de usuario el registro
 */
void RegisterPointerNode::init(string pDatos, schema * pSchema, int pOffset){
    cout<<"diskinit"<<endl;
    this->initVoidp(pDatos, pSchema);
    cout<<"initttttttttttt"<<endl;
    this->_modify=true;
    this->_offset=pOffset;
    this->inMemory=true;
}

/*Funcion que incializa desde un string de entrada de usuario el registro
 * @param void * pRegister :: el puntero void  del registro en memoria
 * @param int pOffset :: el offset del registro en el archivo
 * @return No returns
 */
void RegisterPointerNode::init(void *pRegister, int pOffset){
    this->_Registro=pRegister;
    this->_modify=false;
    this->_offset=pOffset;
    this->inMemory=true;
}

/*Funcion que modifica un registro en memoria
 * @param string * pDato :: el dato a modificar dentro del registro
 * @param string * pColum :: la columna donde se va a guardar el dato
 * @return No returns
 */
void RegisterPointerNode::modify(string* pDato, string* pColum, schema* pSchema){
    updateVoidP(pDato, pColum, pSchema);
    this->_modify=true;
}

RegisterPointerNode::RegisterPointerNode(const RegisterPointerNode& orig) {
}

RegisterPointerNode::~RegisterPointerNode() {
}

void RegisterPointerNode::SetNext(RegisterPointerNode* next) {
    this->_next = next;
    this->SetSiguiente(next->GetActual());
}

RegisterPointerNode* RegisterPointerNode::GetNext() const {
    return _next;
}

void RegisterPointerNode::SetSiguiente(int siguiente) {
    this->_siguiente = siguiente;
    this->_modify=true;
}

int RegisterPointerNode::GetSiguiente() const {
    return _siguiente;
}

void RegisterPointerNode::SetActual(int actual) {
    this->_NumReg = actual;
    this->_modify=true;
}

int RegisterPointerNode::GetActual() const {
    return _NumReg;
}

int RegisterPointerNode::GetOffset() const {
    return _offset;
}

void* RegisterPointerNode::GetRegistro() const {
    return _Registro;
}


/*
 * Inicializa el puntero void del registro llenandolo con los datos que le entran
 * en el pDatos y con el formato del pSchema
 * @param string * pDatos :: los datos a escribir en el puntero void
 * @param schema * pSchema :: el formato como se escriben en los datos
 * @return No return
 */
void RegisterPointerNode::initVoidp(string pDatos, schema* pSchema){
    string value="";  
    string nomb="";
    int tipo_dato = 1;
    int n = 3;
    cout<<"initvoid"<<endl;
    this->_Registro=(void*)malloc(pSchema->getTamanyoTotal());
    memset(_Registro, 0, pSchema->getTamanyoTotal());
    while(n < pDatos.size()-2) {
        cout<<"asdfghjkl"<<endl;
        int i = n;
        int j = 0;
        //string pru=pDatos->at(5); 
        while(pDatos[i] != '>') {
            
//            cout << j <<  "  j " <<endl;
//            cout << i <<  "  i " <<endl;
//            cout << pDatos.size()<< "  pdatos size " << endl;
//            cout << pDatos << endl;
//            cout << pDatos.at(i)<<endl;
            j++;
            i++;
        }
        string dato = pDatos.substr(n,j);
        cout<<"initvoid"<<endl;
        
        if(tipo_dato == 1) {
            nomb.clear();
            nomb.append(dato);
            tipo_dato++;
            n=i+3;
            cout << " if" << endl;
        }
        else {
            cout << " entra al else" << endl;
            value = dato;
            tipo_dato = 1;
            n = i+5;
            this->updateVoidP(&dato,&nomb,pSchema);
            cout << " sale del else " << endl;
        //    file->write(value, registLibre, file->getSchema()->getDesplazamiento(nomb), file->getSchema()->getConst(nomb), file->getSchema()->getColTam(nomb));
        }
    }
    cout<<" initvoidddddddddddddddddddd"<<endl;
}


void RegisterPointerNode::updateVoidP(string * pDato,string * pColum, schema* pSchema){
    pSchema->getConst(*pColum);
    switch(pSchema->getConst(*pColum)){
    case caseCharArray:
    {
        char* cToWriteChar = (char*)this->_Registro+pSchema->getDesplazamiento(*pColum);
        memset(cToWriteChar,0,pSchema->getTam(*pColum));
        strcpy(cToWriteChar, pDato->c_str());
        break;
    }
    case caseInteger:
    {
        if(isInteger(*pDato)){
            int* iToWrite = (int*)this->_Registro+pSchema->getDesplazamiento(*pColum);
            memset(iToWrite,0,pSchema->getTam(*pColum));
            *iToWrite=atoi(pDato->c_str());
        }else{
            throw -1;//Falta ponerle el verdadero error
        }
        break;
    }
    case caseFloat:
    {
        if(isFloat(*pDato)){
            float *fToWrite = (float*)this->_Registro+pSchema->getDesplazamiento(*pColum);
            memset(fToWrite,0,pSchema->getTam(*pColum));
            *fToWrite=std::stod(*pDato);
        }else{
            throw -1;//Falta ponerle el verdadero error
        }
        break;
    }
    case caseByte:
    {
        if(pDato->size()==1){
            char* cToWrite = (char*)this->_Registro+pSchema->getDesplazamiento(*pColum);
            memset(cToWrite,0,pSchema->getTam(*pColum));
            strcpy(cToWrite, pDato->c_str());
        }else{
            throw -1;//Falta ponerle el verdadero error
        }
        break;
    }
    case caseShort:
    {
        if(isShort(*pDato)){
            short* sToWrite = (short*)this->_Registro+pSchema->getDesplazamiento(*pColum);
            memset(sToWrite,0,pSchema->getTam(*pColum));
            * sToWrite = atof(pDato->c_str());
        }else{
            throw -1;//Falta ponerle el verdadero error
        }
        break;
    }
    case caseBigInt:
    {
        if(pSchema->getColTam(*pColum)%4==0){
            int cycle=pDato->size()/10;
            if(pDato->size()%10!=0){
                cycle++;
            }
            if((pSchema->getColTam(*pColum)/4)<=cycle){
                for(int i=0; i< cycle;i++){                        
//                        cout << "  tmp2 " << tmp2 << endl;
//                        pToWrite.copy(tmp2, 10, i*10);
                    string tmp=pDato->substr(i*10,10);
//                        cout <<"string  "<< tmp << "   ciclo "<<i<< endl;
                    if(isInteger(tmp.c_str())){
                        int* iToWrite = (int*)this->_Registro+pSchema->getDesplazamiento(*pColum)+(i*4);
                        memset(iToWrite, 0, sizeof(int));
                        * iToWrite = atoi(tmp.c_str());
                        
                    }
                    else{
                        throw -1;//Falta el codigo de error
                    }
                }
            }
            else{
                throw -1;//Falta el codigo de error
            }
        }
        else{
            throw -1; //Falta ponerle el verdadero error
        }
        break;
    }
    default:
    {
        throw -1;// poner error para cuando el id no es correcto
    }
    }
    this->_modify=true;
}

 /*
  * Funcion para verificar si el string es un int valido
  * 
  */
 inline bool RegisterPointerNode::isInteger(const std::string & s)
{
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;
   if((s.length()>11)) return false;
   if(!(-2147483649<stol(s.c_str()) && stol(s.c_str())<2147483648)) return false;
//   cout << stol(s.c_str()) << endl;
   char * p ;
   strtol(s.c_str(), &p, 10) ;
   
   return ((*p == 0));
}
 /*
  * Funcion para verificar si el string es un short valido
  * 
  */
 bool RegisterPointerNode::isShort(const std::string  s)
{
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;
   if((s.length()>11)) return false;
   if(!(-32769<stol(s.c_str()) && stol(s.c_str())<32768)) return false;
//   cout << stol(s.c_str()) << endl;
   char * p ;
   strtol(s.c_str(), &p, 10) ;
   
   return ((*p == 0));
}
 
  /*
  * Funcion para verificar si el string es un float valido
  * 
  */
 bool RegisterPointerNode::isFloat( string myString ) {
    std::istringstream iss(myString);
    float f;
    iss >> noskipws >> f; // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is set
    return iss.eof() && !iss.fail(); 
}

 bool RegisterPointerNode::IsInMemory() const {
    return this->inMemory;
}

 bool RegisterPointerNode::IsModify() const {
     return _modify;
 }
 
 void RegisterPointerNode::flush(){
     free(this->_Registro);
     this->_Registro=NULL;
     this->inMemory=false;
    this->_modify=false;
 }