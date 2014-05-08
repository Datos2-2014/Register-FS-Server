/* 
 * File:   Disk_File.cpp
 * Author: malcolm
 * 
 * Created on 7 de mayo de 2013, 12:19 PM
 */

#include "Disk_File.h"
/*
 * CONSTRUCTOR
 * Parameters:
 * pFileName::char* the desired name of the file
 * pSize::float the desired size of the file in gb
 */
Disk_File::Disk_File(string pFileName, float pSize) {
    this->size=pSize;
    char* name = strdup(pFileName.c_str());
    if(exists(name)|!isValid(pFileName)){
        setFileName(getValidName());
    }else{
        setFileName(name);
    }
    this->format();
    this->blockSize=defaultBlockSize;
    cout << "BlockSize: " << blockSize << endl;
}
/*
 * 
 */
Disk_File::Disk_File(){
    this->size=defaultDiskSize;
    setFileName(getValidName());
    this->format();
    this->blockSize=defaultBlockSize;
    cout << "BlockSize: " << blockSize << endl;
    
}

Disk_File::Disk_File(const Disk_File& orig) {
}

Disk_File::~Disk_File() {
}
/*
 * No params
 * Returns Void
 * Fills the document with 0
 */
void Disk_File::format(){
    fstream fs((char*)fileName, std::ios::out | std::ios::binary);
    cout << "Formating     " << fileName << "  .... "<< endl;
    move(0, 0, &fs);
    for(int i=0; i<=(size*(1024*1024*1024));i++){
        fs.write((char*)&zero, 1);
    }
    fs.close();
}
/*
 * Parameters:
 * pTowrite::std::string the string to write in the file
 * pBlock::int the block in the file where the string will be write
 * pByte::int the displacement in bytes in the block
 * 
 * No returns
 * 
 * Writes a string in the file 
 */
void Disk_File::write(string pToWrite, int pBlock, int pDisp){
    char* pToWriteChar = strdup(pToWrite.c_str());
    fstream fs(fileName, ios::in | ios::out | ios::binary);
    move(pBlock, pDisp, &fs);
    fs.write(pToWriteChar, sizeOF(pToWrite));
    fs.close();
}
/*
 * Parameters:
 * pBlock::int the block in the file where the string will be write
 * pByte::int the displacement in bytes in the block
 * pSize::int the size in bytes of the string to read
 * Returns:
 * The read of the position in string
 * 
 * Reads a string from the file 
 */
string Disk_File::read(int pBlock, int pDisp, int pSize){
    char* Read;
    fstream fs(fileName, ios::in | ios::out | ios::binary);
    move(pBlock, pDisp, &fs);
    fs.read(Read, pSize);
    fs.close();
    string result = Read;
    return result;
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
void Disk_File::move(int toBlock, int pBytes,fstream* pFile){
    pFile->seekp(headerSize+(toBlock*(blockSize+1))+pBytes, ios_base::beg);
    pFile->seekg(headerSize+(toBlock*(blockSize+1))+pBytes, ios_base::beg);
    cout<< "rto Byte: "<<toBlock*(blockSize+1)+pBytes << endl;
}

/*
 * No parameters
 * 
 * Return:
 * The int that representes the size of the blocks in the file
 * 
 * Returns the blocksize
 */
int Disk_File::getBlockSize(){
    return this->blockSize;
}
/*
 * Parameters:
 * pBlockSize::float the desired size of the block(cluster)
 * 
 * No returns
 * 
 * Set the size of the block(Cluster)
 */
void Disk_File::setBlockSize(float pBlockSize){
    this->blockSize=pBlockSize;
}
/*
 * Parameters:
 *pBlock::int the block to format
 * 
 * No returns
 * 
 * Will fill with 0 all the bytes in the block
 */
void Disk_File::cleanBlock(int pBlock){
    fstream fs(fileName, ios::in | ios::out | ios::binary);
    for(int i=0; i<=blockSize; i++){
        move(pBlock, i, &fs);
        fs.write((char*)&zero, 1);
    }
    fs.close();
}
/*
 * Parameters:
 * filename::char* the name of the file
 * 
 * No returns
 * 
 * Set the name of the file
 */
void Disk_File::setFileName(char* fileName) {
    this->fileName = fileName;
}
/*
 * No parameters
 * 
 * Returns:
 * The name of this file string
 * 
 * Returns the name of the file
 */
string Disk_File::getFileName() const {
    string name(fileName);
    return name;
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
bool Disk_File::exists(char* pFileName){
    fstream fs(pFileName, ios::in | ios::out | ios::binary);
    fs.seekp(0, fstream::end);
    if(fs.tellg()!=-1){
        return true;
    }
    else{
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
bool Disk_File::isValid(string pFileName){
    char* pFileNameChar1 = strdup(pFileName.c_str());
    int size=sizeOF(pFileName);
    const char* bin=".bin";
    bool isvalid=true;
    int j=0;
    cout << "Name to check  " << pFileNameChar1 <<endl;
    if(size>4){
        for(int i = size-4; i<size;i++){
            if(pFileNameChar1[i]!=bin[j]){
                isvalid=false;
            }
            j++;
        }
    }
    else{
        isvalid=false;
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
void Disk_File::writeHeader(string pHeader){
    fstream fs;
    char* pFileNameChar2 = strdup(pHeader.c_str());
    cout << "Writing header" << endl;
    fs.open(fileName, ios::in | ios::out | ios::binary);
    fs.seekp(0);
    fs.write(pFileNameChar2, sizeOF(pHeader));
    fs.close();
}

/*
 * Parameters
 * 
 * Returns
 * 
 * Read the header of the file
 */
string Disk_File::readHeader(){
    fstream fs;
    cout << "reading header" << endl;
    fs.open(fileName, ios::in | ios::out | ios::binary);
    fs.seekg(0);
    fs.seekp(0);
    char* read;
    fs.read(read, headerSize);
    fs.close();
    return read;
}
/*
 * Parameters:
 * pString::string  the string to check
 * 
 * Returns:
 * The size of the string in int
 * 
 * Returns the size of the string that you enter
 */
int Disk_File::sizeOF(string pString){
    int size=0;
    while(pString[size]!=NULL){
        size++;
    }
    return size;
}

/*
 * No params
 * 
 * Returns:
 * A valid name for the file (String)
 * 
 * Returns a valid name of a file
 */
char* Disk_File::getValidName(){
    int i=1;
    string nameToCheck=defaultName+to_string(i)+".bin";
    char* nametoCheckChar = strdup(nameToCheck.c_str());
    while(exists((char*)nametoCheckChar)){
        i++;
        nameToCheck=defaultName+to_string(i)+".bin";
        nametoCheckChar = strdup(nameToCheck.c_str());
    }
    return nametoCheckChar;
}
