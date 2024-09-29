#pragma once
# include "BST_Tree.h"
# include "Hashtable.h"
void admin()
{
	BST_Tree t;
	Hashtable h;
	int condition = 0;
	while (condition != 6)
	{
		cout << "welcome ADMIN" << endl;
		cout << "choose the following please" << endl;
		cout << "press 1 to add account " << endl;
		cout << "press 2 to delete account " << endl;
		cout << "press 3 to check all account " << endl;
		cout << "press 4 to see password of account " << endl;
		cout << "press 5 to edit account " << endl;
		cout << "press 6 to exit" << endl;
		cin >> condition;
		if (condition == 1)
		{
			string n = "", a = "";
			int acc, p, b;
			cout << "enter name" << endl;
			cin >> n;
			cout << "enter adress" << endl;
			cin >> a;
			cout << "enter account number" << endl;
			cin >> acc;
			cout << "enter password" << endl;
			cin >> p;
			cout << "enter balance" << endl;
			cin >> b;
			t.addAccount(n, a, acc, p, b);
		}
		if (condition == 2)
		{
			int acc = 0;
			cout << "enter account number" << endl;
			cin >> acc;
			t.loadServer();
			t.Root=t.deleteAccount(t.Root, acc);
			cout << "bar a gia delete se" << endl;
			h.deletePassword(acc);
			cout << "delete pass" << endl;
			t.updateServer(t.Root);
			cout << "update h gia" << endl;
		}
		if (condition == 3)
		{
			t.loadServer();
			t.printInfo(t.Root);
		}
		if (condition == 4)
		{
			h.displayPasswords();
		}
		if (condition == 5)
		{

		}
		if (condition == 6)
		{
			condition = 6;
		}
	}
}