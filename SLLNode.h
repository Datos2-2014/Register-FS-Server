/* 
 * File:   SLLNode.h
 * Author: jeremy
 *
 * Created on 19 de marzo de 2014, 08:05 PM
 */
#ifndef SLLNODE_H
#define	SLLNODE_H
#include "Disk_File.h"
#include "SLL.h"

using namespace std;

class SLL;
class SLLNode {
    public:
        SLLNode(Disk_File*, string);
        SLLNode(const SLLNode& orig);
        virtual ~SLLNode();
        
        Disk_File* getFile();
        SLLNode* getNext();
        void setNext(SLLNode*);
        int getFlag();
        
    private:
        SLLNode* next;
        
        int flag; //1:Archivo; 0:Carpeta
        
        Disk_File* file;
        
        SLL* folder;
        string name;
};

#endif	/* SLLNODE_H */

