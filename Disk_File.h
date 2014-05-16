/* 
 * File:   Disk_File.h
 * Author: malcolm
 *
 * Created on 7 de mayo de 2013, 12:19 PM
 */

#ifndef DISK_FILE_H
#define	DISK_FILE_H
#include <cstring>
#include <fstream>
#include <iostream>
#include "schema.h"
#include <sstream>

using namespace std;

static const short caseInteger=0;
static const short caseFloat=1;
static const short caseBigInt=2;
static const short caseCharArray=3;
static const short caseByte=4;
static const short caseShort=5;


class Disk_File {
public:
    Disk_File(string, string);
    Disk_File();
    Disk_File(const Disk_File& orig);
    int getRegisterSize();
    virtual ~Disk_File();
    //void format();
    void write(string, int ,int , int);
    string read(int, int, int, int);
    string readHeader();
    void writeHeader(string);
    void cleanRegister(int);
    string getPeerDescriptor() const;
    void init(int);
    string getClientDescriptor();

    void setSchema(string);
    schema* getSchema();

    int getHeaderSize() const;
    int getRegisterSize() const;
    string getFileDescriptor() const;

    string getName() const;

    int getRegisterFree();
    
private:
    const short zero=0;
    string _clientDescriptor;
    string _fileDescriptor;
    string _Name;
    char* _peerDescriptor;
    int _registerSize; 
    const string defaultName="Disk";
    schema* schemeRegister;
    
    void move(int, int, fstream*);
    int _headerSize;//Bytes
    bool isValid(string);
    bool exists(char*);
    char* getValidName();
    void setRegisterSize(int);
    inline bool isInteger(const string &);
    bool isFloat( string );
};

#endif	/* DISK_FILE_H */

