#include "BST_Node.h"

BST_Node::BST_Node()
{
    left = nullptr;
    right = nullptr;
    name = "";
    address = "";
    account_number = 0;
    password = 0;
    balance = 0;

}

BST_Node::BST_Node(string name, string address, int account_number, int password, int balance)
{
    left = nullptr;
    right = nullptr;
    this->name = name;
    this->address = address;
    this->account_number = account_number;
    this->password = password;
    this->balance = balance;
}

/*BST_Node::~BST_Node()
{
    delete left;
    delete right;
}*/