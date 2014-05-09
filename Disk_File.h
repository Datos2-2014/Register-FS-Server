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
using namespace std;

class Disk_File {
public:
    Disk_File(string, string);
    Disk_File();
    Disk_File(const Disk_File& orig);
    int getBlockSize();
    virtual ~Disk_File();
    //void format();
    void write(string, int ,int , int);
    string read(int, int, int, int);
    string readHeader();
    void writeHeader(string);
    void cleanRegister(int);
    string getFileName() const;
    void init(int);

    string getClientDescriptor();
    
private:
    const short zero=0;
    string _clientDescriptor;
    char* fileName;
    int _registerSize;
   // const int GB=1073741824;//Bytes
    const string defaultName="Disk";
    void move(int, int, fstream*);
    int _headerSize;//Bytes
    void setFileName(char*);
    bool isValid(string);
    bool exists(char*);
    char* getValidName();
    void setRegisterSize(int);
};

#endif	/* DISK_FILE_H */

