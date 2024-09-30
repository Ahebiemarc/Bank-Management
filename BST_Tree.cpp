#include "BST_Tree.h"
#include "Hashtable.h"

BST_Tree::BST_Tree(){

}

void BST_Tree::addAccount(string name, string address, int account_num, int password,int balance)
{
    h.add(account_num, password);
    ofstream __write;
    __write.open("server", ios::app);
    __write << name << endl << address << endl << account_num << endl << password << endl << balance << endl;
    __write.close();

    BST_Node* temp = new BST_Node(name, address, account_num, password, balance);

    BST_Node* current = Root;
    if (Root == nullptr)
    {
        Root = temp;
    }
    else
    {
        while (true)
        {
            if (account_num < current->account_number)
            {
                if (current->left == nullptr)
                {
                    current->left = temp;
                    break;
                }
                current = current->left;
                
            }

            if (account_num > current->account_number)
            {
                if (current->right == nullptr)
                {
                    current->right = temp;
					break;
                }
                current = current->right;              
            }                    
        }     
    }   
}

BST_Node* BST_Tree::deleteAccount(BST_Node* root, int account_num){
	// Si l'arbre est vide ou que le numéro de compte est introuvable
    if(root == nullptr){
        cout << "it seems that Tree is empty OR You have entered wrong data";
    }

	// Recherche du nœud à supprimer
    else if (account_num < root->account_number) root->left = deleteAccount(root->left, account_num);
    else if ( account_num > root->account_number) root->right = deleteAccount(root->right, account_num);
    else
    {
		// Nœud trouvé avec deux enfants
        if (root->left && root->right)
        {
            findMax(root->left); // Trouver le maximum dans le sous-arbre gauche
            root->account_number = v.back();  // Remplacer par le maximum
            root->left = deleteAccount(root->left, root->account_number); // Supprimer le maximum

        }
		// Nœud avec un ou aucun enfant
        else
        {
            cout << "aya" << endl;
			BST_Node* temp = root; // Stocker le nœud à supprimer

			// Remplacer par l'enfant
			if (root->left == nullptr)
				root = root->right;
			else if (root->right == nullptr)
				root = root->left;
			delete temp; // Libérer la mémoire
        }      
    }
    return (root); // Retourner le nœud modifié
}


void BST_Tree::withdraw(int account_num, int amount) {
    loadServer(); // Charger les données du serveur
    BST_Node *temp = search(Root, account_num); // Rechercher le compte

    // Mettre à jour le solde du compte
    temp->balance = temp->balance - amount;
    vector <int> data; // Stocker les données de transaction

    ifstream __read;
    __read.open("transaction.txt", ios::app); // Ouvrir le fichier de transactions
    int line = 0;
    while (!__read.eof()) {
        __read >> line; // Lire chaque ligne
        if (line == account_num) {
            data.push_back(line); // Ajouter le numéro de compte
            line = (amount * -1); // Débiter le montant
            data.push_back(line); // Ajouter le montant débité
            continue;
        }
        data.push_back(line); // Ajouter les autres lignes
    }
    __read.close();

    // Écrire les données mises à jour dans un fichier temporaire
    ofstream __write;
    __write.open("temp.txt", ios::app);
    for (size_t i = 0; i < data.size(); i++) {
        __write << data[i] << endl; // Écrire chaque donnée
    }
    __write.close();

    remove("transaction.txt"); // Supprimer l'ancien fichier de transactions
    rename("temp.txt", "transaction.txt"); // Renommer le fichier temporaire

    updateServer(Root); // Mettre à jour les données sur le serveur
}




void BST_Tree::deposit(int account_num, int amount) {
    loadServer(); // Charger les données du serveur
    BST_Node *temp = search(Root, account_num); // Rechercher le compte

    // Mettre à jour le solde du compte
    temp->balance = temp->balance + amount;

    vector <int> data; // Stocker les données de transaction
    ifstream __read;
    __read.open("transaction.txt", ios::app); // Ouvrir le fichier de transactions
    int line = 0;
    while (!__read.eof()) {
        __read >> line; // Lire chaque ligne
        if (line == account_num) {
            data.push_back(line); // Ajouter le numéro de compte
            line = amount; // Enregistrer le montant déposé
            data.push_back(line); // Ajouter le montant déposé
            continue;
        }
        data.push_back(line); // Ajouter les autres lignes
    }
    __read.close();

    // Écrire les données mises à jour dans un fichier temporaire
    ofstream __write;
    __write.open("temp.txt", ios::app);
    for (size_t i = 0; i < data.size(); i++) {
        __write << data[i] << endl; // Écrire chaque donnée
    }
    __write.close();

    remove("transaction.txt"); // Supprimer l'ancien fichier de transactions
    rename("temp.txt", "transaction.txt"); // Renommer le fichier temporaire

    updateServer(Root); // Mettre à jour les données sur le serveur
}

void BST_Tree::editaccountByAdmin()
{

}
void BST_Tree::transfer(int sender_account_num, int reciever_account_num, int sender_amount) {
    // Recherche et mise à jour du solde du compte expéditeur
    BST_Node *sender = search(Root, sender_account_num);
    sender->balance = sender->balance - sender_amount; // Débiter le montant du compte expéditeur

    // Recherche et mise à jour du solde du compte récepteur
    BST_Node *reciever = search(Root, reciever_account_num);
    reciever->balance = reciever->balance + sender_amount; // Crédite le montant au compte récepteur

    updateServer(Root); // Mettre à jour les données sur le serveur

    vector<int> data; // Stocker les données de transaction
    ifstream __read;
    __read.open("transaction.txt", ios::app); // Ouvrir le fichier de transactions
    int line = 0;

    // Enregistrer la transaction de l'expéditeur
    while (!__read.eof()) {
        __read >> line; // Lire chaque ligne
        if (line == sender_account_num) {
            data.push_back(line); // Ajouter le numéro de compte expéditeur
            line = (sender_amount * -1); // Enregistrer le montant comme négatif
            data.push_back(line); // Ajouter le montant retiré
            continue;
        }
        data.push_back(line); // Ajouter les autres lignes
    }
    __read.close();

    // Écrire les données mises à jour dans un fichier temporaire
    ofstream __write;
    __write.open("temp.txt", ios::app);
    for (size_t i = 0; i < data.size(); i++) {
        __write << data[i] << endl; // Écrire chaque donnée
    }
    __write.close();
    remove("transaction.txt"); // Supprimer l'ancien fichier de transactions
    rename("temp.txt", "transaction.txt"); // Renommer le fichier temporaire

    // Réinitialiser les données pour le compte récepteur
    data.clear(); // Effacer les données précédentes
    __read.open("transaction.txt", ios::app); // Ouvrir à nouveau le fichier de transactions
    line = 0;

    // Enregistrer la transaction du récepteur
    while (!__read.eof()) {
        __read >> line; // Lire chaque ligne
        if (line == reciever_account_num) {
            data.push_back(line); // Ajouter le numéro de compte récepteur
            line = sender_amount; // Enregistrer le montant déposé
            data.push_back(line); // Ajouter le montant crédité
            continue;
        }
        data.push_back(line); // Ajouter les autres lignes
    }
    __read.close();

    // Écrire les données mises à jour dans un fichier temporaire
    ofstream write;
    write.open("temp.txt", ios::app);
    for (size_t i = 0; i < data.size(); i++) {
        write << data[i] << endl; // Écrire chaque donnée
    }
    write.close();
    remove("transaction.txt"); // Supprimer l'ancien fichier de transactions
    rename("temp.txt", "transaction.txt"); // Renommer le fichier temporaire
}


void BST_Tree::transactionHistory()
{
    ifstream __read;
	__read.open("transaction.txt");

	if(!__read) {
		cout << "Le fichier des transactions est introuvable." << endl;
        return;
	}

	int account_num;
    int amount;
    
    cout << "Historique des transactions : " << endl;
    while (__read >> account_num >> amount) {
        if (amount < 0) {
            cout << "Compte " << account_num << " a retiré " << -amount << " unités." << endl;
        } else {
            cout << "Compte " << account_num << " a déposé " << amount << " unités." << endl;
        }
    }

    __read.close();
}
void BST_Tree:: findMax(BST_Node* root)
{
	if (root)
	{
		findMax(root->left);
		v.push_back(root->account_number);
		findMax(root->right);
	}
}
void BST_Tree::loadServer()
{
	ifstream __read;
	__read.open("server.txt", ios::app);

	string name = "";
	string address = "";
	int account_num = 0;
	int password = 0;
	int balance = 0;
	//cin.ignore();
	while (!__read.eof())
	{
		
		
		
		getline(__read, name);
		getline(__read, address);
		__read >> account_num;
		__read >> password;
		__read >> balance;
		__read.ignore();
		__read.ignore();

		if (name!="" && address != "" && account_num != 0 && password != 0 )
		{
			//cout << "enter hua" << endl;
			BST_Node * temp = new BST_Node(name, address, account_num, password, balance);
			BST_Node * current = Root;
			if (Root == nullptr)
			{

				Root = temp;
			}
			else
			{
				while (true)
				{

					if (account_num < current->account_number)
					{
						if (current->left == nullptr)
						{
							current->left = temp;
							break;
						}
						current = current->left;
					}

					if (account_num > current->account_number)
					{
						if (current->right == nullptr)
						{
							current->right = temp;
							break;
						}
						current = current->right;
					}
					if (account_num == current->account_number)
					{
						break;
					}
				}
			}
		}
	}
	__read.close();
}
void BST_Tree:: updateServer(BST_Node *root)
{
	static int i = 0;
	if (i == 0)
	{
		i++;
		remove("server.txt");
	}
	ofstream __write;
	__write.open("server.txt");
	if (root)
	{
		updateServer(root->left);
		__write << root->name<<endl;
		__write << root->address<<endl;
		__write << root->account_number<<endl;
		__write << root->password<<endl;
		__write << root->balance<<endl;
		updateServer(root->right);
	}
	__write.close();
	
	
}
BST_Node* BST_Tree:: search (BST_Node* root, int account_num)
{
	if (root == nullptr) return (root);
	else if (account_num < root->account_number) return (search(root->left, account_num));
	else if (account_num > root->account_number) return (search(root->right, account_num));
	return (root);

}
void BST_Tree:: printInfo(BST_Node* root)
{

	if (root)
	{
		printInfo(root->left);
		cout << root->name << endl;
		cout << root->address<<endl;
		cout << root->account_number<<endl;
		cout << root->password<<endl;
		cout << root->balance<<endl;
		printInfo(root->right);
	}
}


