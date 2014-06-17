/* 
 * File:   Disk_File.h
 * Author: malcolm
 *
 * Created on 7 de mayo de 2013, 12:19 PM
 */

#ifndef DISK_FILE_H
#define	DISK_FILE_H


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "header.h"
#include "RegisterPointer.h"


class Disk_File {
public:
    Disk_File(string, string);
    Disk_File(string);
    virtual ~Disk_File();
    
    int addReg(string);
    
    void modifyR(string  pColum_datos,int pRegister);
    void modifyO(string  pColum_datos,int pRegister);
    void* readR(int pRegister);
    void* readO(int pOffset);
    void deleteRegisterR(int pRegister);
    void deleteRegisterO(int pOffset);
    
   
    string getPeerDescriptor() const;
    
    void setSchema(string);
    schema* getSchema();

    string getClientDescriptor();
    int getHeaderSize() const;
    int getRegisterSize() const;
    string getFileDescriptor() const;
    RegisterPointer getDeletedRecords() const;
    RegisterPointer getUsedRecords() const;
    header* getHeader() ;
    
    
    string getName() const ;
    int getOffset(int pRegister);
    int getRegisterNumberOffset(int pOffset);
    void flush();
private:
    const short zero=0;
    string _clientDescriptor;
    string _fileDescriptor;
    string _Name;
    string _Path;
    header* _header;
    RegisterPointer _usedRecords;
    RegisterPointer _deletedRecords;
    char* _peerDescriptor;
    int _registerSize;
    schema* schemeRegister;
    void move(int, int, fstream*);
    int _headerSize;//Bytes
    bool isValid(string);
    bool exists(char*);
    char* getValidPeer();
    void setRegisterSize(int);
    void loadRegisters();
    static const int _registerHeaderSize=7;
    void updateRegisterHeader(int,int, short, bool);
    void init(int);
    void loadHeader();
    void flushHeader();
    int getRegisterSize();
    int getRegisterFree();
    void write(RegisterPointerNode * pRegister);
    //void format();
};

#endif	/* DISK_FILE_H */

