#pragma once
# include "BST_Tree.h"
# include "Hashtable.h"
void customer()
{
	BST_Tree t;
	Hashtable h;
	int condition = 0;
	while (condition != 3)
	{
		cout << "welcome CUSTOMER" << endl;
		cout << "choose the following please" << endl;
		cout << "press 1 to see account details" << endl;
		cout << "press 2 to see transaction history  " << endl;
		cout << "press 3 to exit" << endl;
		cin >> condition;
		if (condition == 1)
		{
			int account_num;
			cout << "please enter account number" << endl;
			cin >> account_num;
			BST_Node* temp = t.search(t.Root, account_num);
			cout << "Account Details Are :\t\t\t\t\t\t " << endl << endl;
			cout << "NAME :" << temp->name << endl;
			cout << "ADRESS :" << temp->address << endl;
			cout << "ACCOUNT NUMBER :" << temp->account_number << endl;
			cout << "PASSWORD :" << temp->password << endl;
			cout << "BALANCE :" << temp->balance << endl;
		}
		if (condition == 2)
		{
			//BST_Node* temp = t.search(t.Root, a)
		}
		if (condition == 3)
		{
			condition = 3;
		}

	}

}