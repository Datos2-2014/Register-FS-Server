/* 
 * File:   SLL.h
 * Author: jeremy
 *
 * Created on 19 de marzo de 2014, 08:03 PM
 */
#ifndef SLL_H
#define	SLL_H
#include "SLLNode.h"

using namespace std;
class SLLNode;
class SLL {
    public:
        SLL();
        SLL(const SLL& orig);
        virtual ~SLL();
        
        SLLNode* getFirst();
        void setFirst(SLLNode*);
        int getSize();
        
//        void print();
//        void insertHead(int);
        void insert(Disk_File*, string);
//        void insertInOrder(int);
        void removeFile(string);
//        bool search(int);
//        SLL* merge(SLL&);
//        SLL* intersection(SLL&);
//        void invert();
//        void insertRandom(int);
    
    private:
        SLLNode *first;
        int size;
};

#endif	/* SLL_H */

