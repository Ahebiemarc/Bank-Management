#pragma once
#include <stdio.h>
#include "BST_Node.h"
#include "Hashtable.h"


class BST_Tree 
{
    vector <int> v;

    public:
        Hashtable h;
        BST_Node *Root;

        BST_Tree();
        void addAccount(string,string,int,int,int);
        BST_Node* deleteAccount(BST_Node*, int);
        void withdraw(int,int);
        void deposit(int,int);
        void editaccountByAdmin();
        void transfer(int, int,int);
        void transactionHistory();
        void findMax(BST_Node*);
        void loadServer();
        void updateServer(BST_Node*);
        BST_Node* search(BST_Node*, int);
        void printInfo(BST_Node*);

};