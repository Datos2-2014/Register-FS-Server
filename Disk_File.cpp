/* 
 * File:   Disk_File.cpp
 * Author: malcolm
 * 
 * Created on 7 de mayo de 2013, 12:19 PM
 */


#include "Disk_File.h"

/*
 * CONSTRUCTOR Para instanciar un nuevo archivo
 * Parameters:
 * pFileName::char* the desired name of the file
 * pClientDescriptor::a string with the client descriptor
 */
Disk_File::Disk_File(string pClientDescriptor, string pFileName) {
    if(pClientDescriptor.size()<=16){
        if(pFileName.size()<=64){
            this->_peerDescriptor = (getValidPeer());
            this->_Path = string(pathRFS) + _peerDescriptor + ".bin";
            this->_Name = pFileName;
            this->_header=new header(0,0,0,0,0,0);
            this->getHeader()->setFilename(pFileName);
            this->_clientDescriptor = pClientDescriptor;
            this->getHeader()->setClientDescriptor(pFileName);
            this->_fileDescriptor = _clientDescriptor + _peerDescriptor;
        }
        else{
            throw -1;
        }
    }
    else{
        throw -1;
    }
}
/*
 * CONSTRUCTOR Para instanciar un archivo ya existente
 * Parameters:
 * pFileName::char* the desired name of the file
 * pSize::float the desired size of the file in gb
 */
Disk_File::Disk_File(string pPeerDescriptor) {
    strcpy(this->_peerDescriptor, pPeerDescriptor.c_str());
    this->_Path = string(pathRFS) + _peerDescriptor + ".bin";
    this->loadHeader();
    this->_Name = this->getHeader()->getFilename();
    this->_clientDescriptor = this->getHeader()->getClientDescriptor();
    this->_fileDescriptor = _clientDescriptor + _peerDescriptor;
}

RegisterPointer Disk_File::getDeletedRecords() const {
    return _deletedRecords;
}

RegisterPointer Disk_File::getUsedRecords() const {
    return _usedRecords;
}

header* Disk_File::getHeader() {
    return _header;
}

/* 
 * Initialize the disk file
 * @param  pSize: int with the size of the register
 * 
 * @return void
 */
void Disk_File::init(int pSize) {
    fstream fs(_Path, std::ios::out | std::ios::binary);
    fs.close();
    this->_registerSize = pSize + _registerHeaderSize;
    this->_header = new header(0, 0, 0, 0, 0, 0);
    this->_deletedRecords = RegisterPointer();
    this->_usedRecords = RegisterPointer();
}

/*
 * Retorna el proximo registro escribible
 * @param none
 * @return int with the register number
 * 
 */
int Disk_File::getRegisterFree() {
    if (_deletedRecords.GetHead() != NULL) {
        RegisterPointerNode * tmp1 = _deletedRecords.deleteHead();
        updateRegisterHeader(_usedRecords.GetTail()->GetActual(), tmp1->GetActual(), 0, 0);
        _usedRecords.addRegister(tmp1->GetActual(), -1);
        _header->setFin(tmp1->GetActual());
        _header->setNumregtot(_header->getNumregtot() + 1);
        return tmp1->GetActual();
    } else {
        RegisterPointerNode * tmp;
        if (_header->getNumregtot() - 1 == _header->getFin() || _header->getNumregtot() == 0) {
            //            cout<< " header->getfin: " << _header->getFin()<< endl;
            if (_usedRecords.GetHead() != NULL) {
                tmp = new RegisterPointerNode(_header->getFin() + 1, -1);
                updateRegisterHeader(_usedRecords.GetTail()->GetActual(), tmp->GetActual(), 0, 0);
                _header->setFin(tmp->GetActual());
                _usedRecords.addRegister(tmp->GetActual(), -1);
                _header->setNumregtot(_header->getNumregtot() + 1);
            } else {

                tmp = new RegisterPointerNode(_header->getFin(), -1);
                _header->setFin(tmp->GetActual());
                _usedRecords.addRegister(tmp->GetActual(), -1);
                _header->setNumregtot(_header->getNumregtot() + 1);
            }
        }
        //          cout <<" registro a escribir "<< tmp->GetActual() <<endl ;
        return tmp->GetActual();
    }
}

/**
 * Establece el esquema de registro para este archivo.
 * @param formato Representa el formato como van a ordenarsen las columnas y especifica
 * los tipos, nombres y tamaños de datos.
 */
void Disk_File::setSchema(string pFormato) {
    this->schemeRegister = new schema(pFormato);
    this->init(schemeRegister->getTamanyoTotal());
    this->getHeader()->setSchema(pFormato);
    this->flushHeader();
}

/**
 * retorna el esquema de registro para este archivo.
 * @param None
 * @return el esquema de registro para este archivo.
 */
schema* Disk_File::getSchema() {
    //     list<string> nombre = schemeRegister->get_nombre();
    //     list<string>::iterator it_nombre = nombre.begin();
    //     while(it_nombre != nombre.end()) {
    //         cout << *it_nombre++ << "\t";
    //     }
    //     cout << endl;
    //     
    //     list<string> tipo = schemeRegister->get_tipo();
    //     list<string>::iterator it_tipo = tipo.begin();
    //     while(it_tipo != tipo.end()) {
    //         cout << *it_tipo++ <<  "\t";
    //     }
    //     cout << endl;
    //     
    //     list<string> tamanyo = schemeRegister->get_tamanyo();
    //     list<string>::iterator it_tamanyo = tamanyo.begin();
    //     while(it_tamanyo != tamanyo.end()) {
    //         cout << *it_tamanyo++ <<  "\t";
    //     }
    //     cout << endl;

    return schemeRegister;
}

Disk_File::~Disk_File() {
}

/*
 * @param el numero de registro que quiere ser borrado::int
 * @return No returns
 * 
 */
void Disk_File::deleteRegisterR(int pRegister) {
    RegisterPointerNode * tmp = this->_usedRecords.search(pRegister);
    this->_deletedRecords.addRegister(tmp->GetActual(), -1);
    this->_usedRecords.remove(tmp->GetActual());
    tmp->~RegisterPointerNode();
}

/*
 * Parameters:
 * pTowrite::std::string the string to write in the file
 * pRegister::int the block in the file where the string will be write
 * pDisp::int the displacement in bytes in the block
 * pId::int the type; use de cases variables defined before
 * pSize::int use this for the big ints is the size of the big int (in bytes)  
 * that you want to write 
 * 
 * No returns
 * 
 * Writes a string in the file 
 */
int Disk_File::addReg(string pToWrite) {
    //    switch(pId){
    //        case caseCharArray:
    //        {
    //            char* cToWriteChar = strdup(pToWrite.c_str());
    //            fstream fs(_Path, ios::in | ios::out | ios::binary);
    //            move(pRegistro, pDisp+ _registerHeaderSize, &fs);
    //            fs.write(cToWriteChar, pToWrite.size());
    //            fs.close();
    //            break;
    //        }
    //        case caseInteger:
    //        {
    //            if(this->isInteger(pToWrite)){
    //                int iToWrite = atoi(pToWrite.c_str());
    //                fstream fs(_Path, ios::in | ios::out | ios::binary);
    //                move(pRegistro, pDisp+ _registerHeaderSize, &fs);
    //                fs.write((char*)&iToWrite, sizeof(iToWrite));
    //                fs.close();
    //            }else{
    //                throw -1;//Falta ponerle el verdadero error
    //            }
    //            break;
    //        }
    //        case caseFloat:
    //        {
    //            if(isFloat(pToWrite)){
    //                float fToWrite = std::stod(pToWrite);
    //                fstream fs(_Path, ios::in | ios::out | ios::binary);
    //                move(pRegistro, pDisp+ _registerHeaderSize, &fs);
    //                fs.write((char*)&fToWrite, sizeof(fToWrite));
    //                fs.close();
    //            }else{
    //                throw -1;//Falta ponerle el verdadero error
    //            }
    //            break;
    //        }
    //        case caseByte:
    //        {
    //            if(pToWrite.size()==1){
    //                char* cToWrite = strdup(pToWrite.c_str());
    //                fstream fs(_Path, ios::in | ios::out | ios::binary);
    //                move(pRegistro, pDisp+ _registerHeaderSize, &fs);
    //                fs.write((char*)cToWrite, sizeof(cToWrite));
    //                fs.close();
    //            }else{
    //                throw -1;//Falta ponerle el verdadero error
    //            }
    //            break;
    //        }
    //        case caseShort:
    //        {
    //            if(isShort(pToWrite)){
    //                short iToWrite = atoi(pToWrite.c_str());
    //                fstream fs(_Path, ios::in | ios::out | ios::binary);
    //                move(pRegistro, pDisp+ _registerHeaderSize, &fs);
    //                fs.write((char*)&iToWrite, sizeof(iToWrite));
    //                fs.close();
    //            }else{
    //                throw -1;//Falta ponerle el verdadero error
    //            }
    //            break;
    //        }
    //        case caseBigInt:
    //        {
    //            if(pSize%4==0){
    //                int cycle=pToWrite.size()/10;
    //                if(pToWrite.size()%10!=0){
    //                    cycle++;
    //                }
    //                if((pSize/4)<=cycle){
    //                    for(int i=0; i< cycle;i++){                        
    ////                        cout << "  tmp2 " << tmp2 << endl;
    ////                        pToWrite.copy(tmp2, 10, i*10);
    //                        string tmp=pToWrite.substr(i*10,10);
    ////                        cout <<"string  "<< tmp << "   ciclo "<<i<< endl;
    //                        if(isInteger(tmp.c_str())){
    //                            int iToWrite = atoi(tmp.c_str());
    //                            fstream fs(_Path, ios::in | ios::out | ios::binary);
    //                            move(pRegistro, pDisp+(i*4)+ _registerHeaderSize, &fs);
    //                            fs.write((char*)&iToWrite, sizeof(iToWrite));
    //                            fs.close();
    //                        }
    //                        else{
    //                            throw -1;//Falta el codigo de error
    //                        }
    //                    }
    //                }
    //                else{
    //                    throw -1;//Falta el codigo de error
    //                }
    //            }
    //            else{
    //                throw -1; //Falta ponerle el verdadero error
    //            }
    //            break;
    //        }
    //        default:
    //        {
    //            throw -1;// poner error para cuando el id no es correcto
    //        }
    //            
    //    }
    //    cout << "valor a escribir "<<pToWrite << endl;
    int registro = this->getRegisterFree();
    RegisterPointerNode* tmp = this->_usedRecords.search(registro);
    tmp->init(&pToWrite, this->getSchema(), getOffset(registro));
    char* cToWriteChar = strdup(pToWrite.c_str());
    fstream fs(_Path, ios::in | ios::out | ios::binary);
    move(tmp->GetActual(), _registerHeaderSize, &fs);
    fs.write(cToWriteChar, pToWrite.size());
    fs.close();
    return registro;
}

/* Funcion que modifica un registro, con los datos que entran en el void * 
 * y se escriben correspondientemente con los nombres de las columnas que entran
 * al string* separados por una coma
 * 
 * Parameters:
 * pRegister::int::El numero de registro a modificar
 * pDatos::void*:: Los datos que se desean modificar seguidos en el void*
 * pColum::string* los nombres de las columnas separadas por una coma deben de
 *  estar acomodadas del mismo modo que los datos del void*
 * 
 * No returns
 * 
 * Writes a string in the file 
 */
void Disk_File::modifyR(string pColum_datos, int pRegister) {
    try {
        RegisterPointerNode* tmp = this->_usedRecords.search(pRegister);
        
        if(!tmp->IsInMemory()){
            tmp->init(this->readR(tmp->GetActual()), this->getOffset(tmp->GetActual()));
        }
        int tipo_dato = 1;
        int n = 3;
    
        string nomb;
        while(n < pColum_datos.size()) {
            int i = n;
            int j = 0;
        
        while(pColum_datos[i] != ',') {
            j++;
            i++;
        }
        string dato = pColum_datos.substr(n,j);
        
        if(tipo_dato == 1) {
            nomb = dato;
            tipo_dato++;
            n=i+1;
        }
        else {
            tipo_dato = 1;
            n = i+1;
            tmp->modify(&dato, &nomb, this->getSchema());
        }
    }
        
    }    catch (int e) {
        switch (e) {
            default:
                throw -1;
        }
    }
}

/* Funcion que modifica un registro, con los datos que entran en el void * 
 * y se escriben correspondientemente con los nombres de las columnas que entran
 * al string* separados por una coma
 * 
 * Parameters:
 * pDatos::string*:: Nombre de la columna que se desea modificar, seguido del 
 * dato separado por una coma
 * pOffset::int::El numero de desplazamiento dentro del archivo
 *  estar acomodadas del mismo modo que los datos del void*
 * 
 * No returns
 * 
 * Writes a string in the file 
 */
void Disk_File::modifyO(string pColum_datos, int pOffset) {
    //    int registro = this->getRegisterFree();
    //    RegisterPointerNode* tmp = this->_usedRecords.search(registro);
    //    tmp->init(pToWrite, this->getSchema());
    //    char* cToWriteChar = strdup(pToWrite.c_str());
    //    fstream fs(_Path, ios::in | ios::out | ios::binary);
    //    move(tmp->GetActual(), _registerHeaderSize, &fs);
    //    fs.write(cToWriteChar, pToWrite.size());
    //    fs.close();
    //    break;
    this->modifyR(pColum_datos, getRegisterNumberOffset(pOffset));
}


/*
 * @param int pRegister the number of register
 * @return int with the offset in the file of the register
 * 
 * Return the position of the register in the file
 */

int Disk_File::getOffset(int pRegister) {
    return _headerSize + (pRegister * (_registerSize + 1));
}

/*
 * @param int pRegister the number of register
 * @return int with the offset in the file of the register
 * 
 * Return the position of the register in the file
 */

int Disk_File::getRegisterNumberOffset(int pOffset) {
    return pOffset / (_headerSize + ((_registerSize + 1)));
}

/*
 * Parameters:
 * pRegister::int the block in the file where the string will be write
 * pDisp::int the displacement in bytes in the block
 * pSize::int the size in bytes of the string to read
 * pId::int the type; use de cases variables defined before
 * Returns:
 * The read of the position in string
 * 
 * Reads a string from the file 
 */
void* Disk_File::readR(int pRegister) {
    //    string result="";
    //    switch(pID){
    //        case caseCharArray:
    //        {
    //            
    //            char Read[pSize];
    //            fstream fs(_Path,  ios::in | ios::out |ios::binary);
    //            move(pRegister, pDisp+ _registerHeaderSize, &fs);
    //            fs.read((char*)&Read, pSize);
    //            fs.close();
    //            result = Read;
    //            break;
    //        }
    //        case caseInteger:
    //        {
    //            int iRead= 0;
    //            fstream fs(_Path,  ios::in | ios::out |ios::binary);
    //            move(pRegister, pDisp+ _registerHeaderSize, &fs);
    //            fs.read((char*)&iRead, pSize);
    //            fs.close();
    //            result = to_string(iRead);
    //            break;
    //        }
    //        case caseFloat:
    //        {
    //            float fRead= 0;
    //            fstream fs(_Path,  ios::in | ios::out |ios::binary);
    //            move(pRegister, pDisp+ _registerHeaderSize, &fs);
    //            fs.read((char*)&fRead, sizeof(fRead));
    //            fs.close();
    //            result = to_string(fRead);
    //            break;
    //        }
    //        case caseByte:
    //        {
    //            if(pSize==1){
    //                char bRead;
    //                fstream fs(_Path,  ios::in | ios::out |ios::binary);
    //                move(pRegister, pDisp+ _registerHeaderSize, &fs);
    //                fs.read((char*)&bRead, pSize);
    //                fs.close();
    //                result = bRead;
    //            }else{
    //                throw -1;// Poner el codigo de error
    //            }
    //            break;
    //        }
    //        case caseShort:
    //        {
    //            short iRead= 0;
    //            fstream fs(_Path,  ios::in | ios::out |ios::binary);
    //            move(pRegister, pDisp+ _registerHeaderSize, &fs);
    //            fs.read((char*)&iRead, pSize);
    //            fs.close();
    //            result = to_string(iRead);
    //            break;
    //        }
    //        case caseBigInt:
    //        {
    //            if(pSize%4==0){
    //                int cycle=pSize/sizeof(int);
    //                for(int i=0; i<cycle; i++){
    //                    int iRead= 0;
    //                    fstream fs(_Path,  ios::in | ios::out |ios::binary);
    //                    move(pRegister, pDisp+(i*4)+_registerHeaderSize, &fs);
    //                    fs.read((char*)&iRead, pSize);
    //                    fs.close();
    //                    result.append(to_string(iRead).c_str());
    //                }
    //            }
    //            else{
    //                throw -1; //Falta poDisk_File.cpp:415:10: error: invalid use of incomplete type ‘std::fstream {aka class std::basic_fstream<char>}’nerle el verdadero error
    //            }
    //            break;
    //        }
    //        default:
    //        {
    //            throw -1;// poner error para cuando el id no es correcto
    //        }
    //    }
    //        
    //    return result;
    void * iRead=malloc(this->getSchema()->getTamanyoTotal());
    memset(iRead, 0, this->getSchema()->getTamanyoTotal());
    fstream fs(_Path,  ios::in | ios::out |ios::binary);
    move(pRegister, _registerHeaderSize, &fs);
    fs.read((char*)iRead, this->getSchema()->getTamanyoTotal());
    fs.close();
    return iRead;
}

/*
 * Parameters:
 * pRegister::int the block in the file where the string will be write
 * Returns:
 * The read of the position in string
 * 
 * Reads a string from the file 
 */
void* Disk_File::readO(int pOffset) {
    //    string result="";
    //    switch(pID){
    //        case caseCharArray:
    //        {
    //            
    //            char Read[pSize];
    //            fstream fs(_Path,  ios::in | ios::out |ios::binary);
    //            move(pRegister, pDisp+ _registerHeaderSize, &fs);
    //            fs.read((char*)&Read, pSize);
    //            fs.close();
    //            result = Read;
    //            break;
    //        }
    //        case caseInteger:
    //        {
    //            int iRead= 0;
    //            fstream fs(_Path,  ios::in | ios::out |ios::binary);
    //            move(pRegister, pDisp+ _registerHeaderSize, &fs);
    //            fs.read((char*)&iRead, pSize);
    //            fs.close();
    //            result = to_string(iRead);
    //            break;
    //        }
    //        case caseFloat:
    //        {
    //            float fRead= 0;
    //            fstream fs(_Path,  ios::in | ios::out |ios::binary);
    //            move(pRegister, pDisp+ _registerHeaderSize, &fs);
    //            fs.read((char*)&fRead, sizeof(fRead));
    //            fs.close();
    //            result = to_string(fRead);
    //            break;
    //        }
    //        case caseByte:
    //        {
    //            if(pSize==1){
    //                char bRead;
    //                fstream fs(_Path,  ios::in | ios::out |ios::binary);
    //                move(pRegister, pDisp+ _registerHeaderSize, &fs);
    //                fs.read((char*)&bRead, pSize);
    //                fs.close();
    //                result = bRead;
    //            }else{
    //                throw -1;// Poner el codigo de error
    //            }
    //            break;
    //        }
    //        case caseShort:
    //        {
    //            short iRead= 0;
    //            fstream fs(_Path,  ios::in | ios::out |ios::binary);
    //            move(pRegister, pDisp+ _registerHeaderSize, &fs);
    //            fs.read((char*)&iRead, pSize);
    //            fs.close();
    //            result = to_string(iRead);
    //            break;
    //        }
    //        case caseBigInt:
    //        {
    //            if(pSize%4==0){
    //                int cycle=pSize/sizeof(int);
    //                for(int i=0; i<cycle; i++){
    //                    int iRead= 0;
    //                    fstream fs(_Path,  ios::in | ios::out |ios::binary);
    //                    move(pRegister, pDisp+(i*4)+_registerHeaderSize, &fs);
    //                    fs.read((char*)&iRead, pSize);
    //                    fs.close();
    //                    result.append(to_string(iRead).c_str());
    //                }
    //            }
    //            else{
    //                throw -1; //Falta poDisk_File.cpp:415:10: error: invalid use of incomplete type ‘std::fstream {aka class std::basic_fstream<char>}’nerle el verdadero error
    //            }
    //            break;
    //        }
    //        default:
    //        {
    //            throw -1;// poner error para cuando el id no es correcto
    //        }
    //    }
    //        
    //    return result;
    readR(this->getRegisterNumberOffset(pOffset));
}

/*
 * Parameters:
 * pRegister::int the block in the file where the string will be write
 * pNext::int pointer to the next register
 * pTime::int the time value when the was deleted
 * pDeleted:: flag to know if the register was deleted
 * Returns:
 * void return
 * 
 * update the values of the header of the register 
 * 
 */
void Disk_File::updateRegisterHeader(int pRegister, int pNext, short pTime, bool pDeleted) {
    fstream fs(_Path, ios::in | ios::out | ios::binary);
    move(pRegister, 0, &fs);
    fs.write((char*) &pNext, sizeof (pNext));
    move(pRegister, sizeof (pNext), &fs);
    fs.write((char*) &pTime, sizeof (pTime));
    move(pRegister, sizeof (pNext) + sizeof (pTime), &fs);
    fs.write((char*) &pDeleted, sizeof (pDeleted));
    fs.close();
}

/*
 * Parameters:
 * toBlock::int the block where you want to move the pointer
 * pBytes::int the displacement in bytes in the block
 * pFile::fstream* the file 
 * 
 * No returns
 * 
 * Move the pointer of a file to write or read
 * 
 */
void Disk_File::move(int pRegister, int pBytes, fstream* pFile) {
    pFile->seekp(0, std::ios::end);
    pFile->seekg(0, std::ios::end);
    std::streampos fsize = pFile->tellp();
    //    cout << " tama;o archivo  " << fsize << endl;
    //    cout << "posicion del puntero g"<< pFile->tellg() << endl;
    //    cout << " posicion que quiere   " << _headerSize+(pRegister*(_registerSize+1))+pBytes << endl;
    //    cout << " tama;o del registro " << _registerSize << endl;
    //    cout << " tama;o del header  " << _headerSize << endl;
    //    cout << " registroo " << pRegister << endl;
    //    cout << " desplazamiento  " << pBytes << endl;
    if (_headerSize + (pRegister * (_registerSize + 1)) + pBytes > fsize) {
        for (int i = fsize; i < (_headerSize + (pRegister * (_registerSize + 1) + _registerSize + 1) + pBytes); i++) {
            pFile->write((char*) &zero, 1);
        }
    }
    pFile->seekp(_headerSize + (pRegister * (_registerSize + 1)) + pBytes, ios_base::beg);
    pFile->seekg(_headerSize + (pRegister * (_registerSize + 1)) + pBytes, ios_base::beg);
    //    cout<< "wto Byte: "<< pFile->tellp() << endl;
}


/*
 * Parameters:
 * pFileName::char* the name of the file to check
 * 
 * Returns:
 * bool: true if exist or false if do not;
 * 
 * Check if a file exist;
 */
bool Disk_File::exists(char* pFileName) {
    fstream fs(_Path + pFileName, ios::in | ios::out | ios::binary);
    fs.seekp(0, fstream::end);
    if (fs.tellg() != -1) {
        return true;
    } else {
        return false;
    }
}

/*
 * Paramaters:
 * pFileName::char* the name of the file to check
 * 
 * Returns 
 * boolean true if the name is valid, false if is not
 * 
 * Check if the name of the file is valid (name.bin like)
 */
bool Disk_File::isValid(string pFileName) {
    char* pFileNameChar1 = strdup(pFileName.c_str());
    int size = pFileName.size();
    const char* bin = ".bin";
    bool isvalid = true;
    int j = 0;
    //    cout << "Name to check  " << pFileNameChar1 <<endl;
    if (size > 4) {
        for (int i = size - 4; i < size; i++) {
            if (pFileNameChar1[i] != bin[j]) {
                isvalid = false;
            }
            j++;
        }
    } else {
        isvalid = false;
    }
    free(pFileNameChar1);
    return isvalid;
}

/*
 * Parameters
 * 
 * No returns
 * 
 * Write the header of the file
 */
void Disk_File::flushHeader() {
    this->_headerSize = 22+16+64+this->getHeader()->getSchema().size();
    
    fstream fs;
    char* pSchema = strdup(this->getHeader()->getSchema().c_str());
    fs.open(_Path, ios::in | ios::out | ios::binary);
    fs.seekp(0, std::ios::beg);
    int tmp =this->getHeader()->getInicio();
    fs.write((char*)&tmp, sizeof(int));
    fs.seekp(4, std::ios::beg);
    tmp=this->getHeader()->getFin();
    fs.write((char*)&tmp, sizeof(int));
    fs.seekp(4+4, std::ios::beg);
    tmp=this->getHeader()->getRegistros_libres();
    fs.write((char*)&tmp, sizeof(int));
    fs.seekp(4+4+4, std::ios::beg);
    tmp=this->getHeader()->getNumreglibres();
    fs.write((char*)&tmp, sizeof(int));
    fs.seekp(4+4+4+4, std::ios::beg);
    tmp=this->getHeader()->getNumregtot();
    fs.write((char*)&tmp, sizeof(int));
    fs.seekp(4+4+4+4+4, std::ios::beg);
    tmp=this->getHeader()->getSize();
    fs.write((char*)&tmp, sizeof(int));
    fs.seekp(22, std::ios::beg);
    string tmp2=string(this->getHeader()->getFilename());
    fs.write((char*)&tmp2, 64);
    fs.seekp(22+64, std::ios::beg);
    tmp2=string(this->getHeader()->getClientDescriptor());
    fs.read((char*)&tmp2, 16);
    fs.seekp(102, std::ios::beg);
    tmp2=string(this->getHeader()->getSchema());
    fs.read((char*)&tmp2, this->getHeader()->getSchema().size());
    fs.close();
}

/*
 * Parameters
 * 
 * Returns
 * 
 * Read the header of the file
 */
void Disk_File::loadHeader() {
        fstream fs;
        cout << "reading header" << endl;
        fs.open(_Path,  ios::in |ios::out| ios::binary);
        fs.seekg(0, std::ios::beg);
        int read=0;
        fs.read((char*)&read, sizeof(int));
        this->getHeader()->setInicio(read);
        fs.seekg(4, std::ios::beg);
        fs.read((char*)&read, sizeof(int));
        this->getHeader()->setFin(read);
        fs.seekg(4+4, std::ios::beg);
        fs.read((char*)&read, sizeof(int));
        this->getHeader()->setRegistros_libres(read);
        fs.seekg(4+4+4, std::ios::beg);
        fs.read((char*)&read, sizeof(int));
        this->getHeader()->setNumreglibres(read);
        fs.seekg(4+4+4+4, std::ios::beg);
        fs.read((char*)&read, sizeof(int));
        this->getHeader()->setNumregtot(read);
        fs.seekg(4+4+4+4+4, std::ios::beg);
        fs.read((char*)&read, sizeof(int));
        this->getHeader()->setSize(read);
        fs.seekg(22, std::ios::beg);
        char filename[64];
        fs.read((char*)&filename, 64);
        this->getHeader()->setFilename(string(filename));
        fs.seekg(22+64, std::ios::beg);
        char clientdescriptor[16];
        fs.read((char*)&clientdescriptor, 16);
        this->getHeader()->setClientDescriptor(string(clientdescriptor));
        fs.seekg(102, std::ios::beg);
        char schema[this->getHeader()->getSize()-22];
        fs.read((char*)&schema, this->getHeader()->getSize()-22);
        this->setSchema(string(schema));
        fs.close();
}

static char random_letter(int is_cap) {
    int letter = (int) (LETTER * (rand() / (RAND_MAX + 1.0)));
    return ((char) ((is_cap == 1) ? (letter + 65) : (letter + 97)));
}

static char random_number() {
    int number = (int) (NUMBER * (rand() / (RAND_MAX + 1.0)));
    return ((char) (number + 48));
}

static void random_string(int length, char *str) {
    int i;
    int char_type;

    for (i = 0; i < length; i++) {
        char_type = (int) (3 * (rand() / (RAND_MAX + 1.0)));

        switch (char_type) {
            case 0:
                str[i] = random_letter(0);
                break;
            case 1:
                str[i] = random_letter(1);
                break;
            case 2:
                str[i] = random_number();
                break;
            default:
                str[i] = random_number();
                break;
        }
    }
}

/*
 * No params
 * 
 * Returns:
 * A valid name for the file (String)
 * 
 * Returns a valid name of a file
 */
char* Disk_File::getValidPeer() {
    int i = 1;
    char random_str[Peer_SIZE + 1];

    srand((unsigned) time(NULL));

    random_str[Peer_SIZE] = '\0';

    random_string(Peer_SIZE, random_str);

    string nameToCheck = string(random_str) + ".bin";
    char* nametoCheckChar = strdup(nameToCheck.c_str());
    if (exists((char*) nametoCheckChar)) {
        nameToCheck = getValidPeer();
    }
    nameToCheck = string(random_str);
    return strdup(nameToCheck.c_str());
}

string Disk_File::getName() const {
    return _Name;
}

/*
 * No parameters
 * 
 * Return:
 * The int that representes the size of the blocks in the file
 * 
 * Returns the blocksize
 */
int Disk_File::getRegisterSize() {
    return this->_registerSize;
}

/*
 * Parameters:
 * pBlockSize::float the desired size of the block(cluster)
 * 
 * No returns
 * 
 * Set the size of the block(Cluster)
 */
void Disk_File::setRegisterSize(int pBlockSize) {
    this->_registerSize = pBlockSize;
}

/*
 * No params
 * 
 * Returns:
 *      the Client descriptor
 * 
 * Returns the Client descriptor
 */
string Disk_File::getClientDescriptor() {
    return _clientDescriptor;
}

int Disk_File::getHeaderSize() const {
    return _headerSize;
}

int Disk_File::getRegisterSize() const {
    return _registerSize;
}

string Disk_File::getFileDescriptor() const {
    return _fileDescriptor;
}

/*
 * No parameters
 * 
 * Returns:
 * The name of this file string
 * 
 * Returns the name of the file
 */
string Disk_File::getPeerDescriptor() const {
    string name(_peerDescriptor);
    return name;
}


/* writes all the registers that was modified on disk
 * @param None 
 * @return none
 */
void Disk_File::flush(){
    this->flushHeader();
    RegisterPointerNode * tmp=  this->_usedRecords.GetHead();
    while(tmp!=NULL){
        if(tmp->IsModify()){
            write(tmp);
            tmp->flush();
        }
        tmp=tmp->GetNext();
    }
}


/*
 * writes a register on disk
 * @param ReegisterPointerNode * pRegister:: the register to write
 * @return No returns
 */
void Disk_File::write(RegisterPointerNode * pRegister){
    void * iwrite=pRegister->GetRegistro();
    fstream fs(_Path,  ios::in | ios::out |ios::binary);
    move(pRegister->GetActual(), _registerHeaderSize, &fs);
    fs.write((char*)iwrite, this->getSchema()->getTamanyoTotal());
    fs.close();
}