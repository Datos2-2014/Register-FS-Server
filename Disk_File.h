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
    Disk_File(string, float);
    Disk_File();
    Disk_File(const Disk_File& orig);
    int getBlockSize();
    virtual ~Disk_File();
    void format();
    void write(string, int ,int );
    string read(int, int, int);
    string readHeader();
    void writeHeader(string);
    void cleanBlock(int);
    string getFileName() const;
    void setBlockSize(float);
    
    
private:
    float size;
    const float defaultDiskSize=0.5;
    const short zero=0;
    char* fileName;
    float blockSize;
    const int GB=1073741824;//Bytes
    const string defaultName="Disk";
    void move(int, int, fstream*);
    const float defaultBlockSize=0.5;//Megabytes
    const int headerSize=32;//Bytes
    void setFileName(char*);
    bool isValid(string);
    bool exists(char*);
    int sizeOF(string);
    char* getValidName();
};

#endif	/* DISK_FILE_H */

