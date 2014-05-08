/* 
 * File:   SLLNode.h
 * Author: jeremy
 *
 * Created on 19 de marzo de 2014, 08:05 PM
 */

#ifndef SLLNODE_H
#define	SLLNODE_H

class SLLNode {
    public:
        SLLNode(int);
        SLLNode(const SLLNode& orig);
        virtual ~SLLNode();
        
        int getData();
        SLLNode* getNext();
        void setNext(SLLNode*);
        
    private:
        int data;
        SLLNode* next;
};

#endif	/* SLLNODE_H */

