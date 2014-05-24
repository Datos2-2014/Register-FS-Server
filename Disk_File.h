/* 
 * File:   Disk_File.h
 * Author: malcolm
 *
 * Created on 7 de mayo de 2013, 12:19 PM
 */

#ifndef DISK_FILE_H
#define	DISK_FILE_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "header.h"
#include "RegisterPointer.h"
#include "ConfigurationFile.h"
#include "schema.h"

#define Peer_SIZE 16
#define LETTER 26
#define NUMBER 10
#define caseInteger 0
#define caseFloat 1
#define caseBigInt 2
#define caseCharArray 3
#define caseByte 4
#define caseShort 5
using namespace std;



class Disk_File {
public:
    Disk_File(string, string);
    Disk_File();
    Disk_File(const Disk_File& orig);
    int getRegisterSize();
    virtual ~Disk_File();
    void write(string, int ,int , int, int);
    string read(int, int, int, int);
    
    void cleanRegister(int);
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
    
    int getRegisterFree();
    
    string getName() const ;
    int getOffset(int pRegister);
    int getRegisterNumberOffset(int pOffset);
    //void format();
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
    inline bool isInteger(const string &);
    bool isFloat( string );
    bool isShort(string);
    static const int _registerHeaderSize=7;
    void updateRegisterHeader(int,int, short, bool);
    void init(int);
    void loadHeader();
    void flushHeader();
};

#endif	/* DISK_FILE_H */

