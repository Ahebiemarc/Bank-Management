#include <iostream>
#include <vector>
#include "Hashtable.h"

using namespace std;

Hashtable::Hashtable(){
    start = nullptr;
}

void Hashtable::starthash()
{
    for(int i=0; i<12; i++){
        Node* temp1 = new Node(i);
        if (start == nullptr){
            start = temp1;
        }
        else{
            Node* current = start;
            while(current->next != nullptr){
                current = current->next;
            }
            current->next = temp1;

        }
        
    }
    loadhashtable();

}

void Hashtable::add(int a, int p)
{
    static int i = 0;
    ofstream __write;
    __write.open("hashtable.txt", ios::app);

    if(i !=0){
        __write << endl;
        __write << a << endl << p;
    }
    else{
        i++;
        __write << a << endl << p;
    }

    __write.close();

    starthash();
}

bool Hashtable::match(int a, int p)
{
    bool flag = false;
    int r = a % 10;
    Node* c = start;
    while(c->data != r){
        c = c->next;
    }
    Node_1* c1 = c->pre;
    while(c1 != nullptr){
        if (c1->account_number == a && c1->password == p)
        {
            flag = true;
            break;
        }
        c1 = c1->next;
        
    }
    return flag;
}

void Hashtable::loadhashtable()
{
    int acc=0, r, pass;

    ifstream __read;   
    __read.open("hashtable.txt");
    while(!__read.eof()){

        __read >> acc;
        __read >> pass;
        if(match(acc, pass)){
            continue;  // Si la combinaison existe déjà, passer à la suivante
        }

        if(acc != -858993460 && pass != -858993460){
            r = acc % 10; // Calculer le reste pour déterminer l'index
            Node* c = start;
            while(c->data != r){
                c = c->next; // Trouver le nœud correspondant à l'index
            }

            Node_1* temp = new Node_1(acc, pass); // Créer un nouveau nœud avec les données
            if(c->pre == nullptr){
                c->pre = temp; // Si c'est le premier élément, le définir comme premier
            }
            else{
                Node_1* root = c->pre;
                while(root->next != nullptr){
                    root = root->next; // Parcourir jusqu'à la fin de la liste
                }
                root->next = temp // Ajouter le nouveau nœud à la fin de la liste
            }
        }
        else{
            cout << "pas de mot de passe present" << endl; // Message si les valeurs sont invalides
        }

    }

    __read.close();
}

void Hashtable::display(){
    Node* current = start;
    while(current != nullptr){
        cout << "data: " << current->data << endl;
        current = current->next;
    }
}

void Hashtable::displayPasswords(){
    starthash(); // Initialise la table de hachage
    Node* c = start;

    // Parcours des nœuds de la table de hachage
    while(c != nullptr){

        // Parcours des nœuds liés à chaque Node (i.e., Node_1)
        Node* c1 = c->pre; // Ici, c->pre est la tête de la liste chaînée des Node_1
        while(c1 != nullptr){
            cout << "Account Number: " << c1->account_number << endl;
            cout << "Password: " << c1->password << endl;

            c1 = c1->next;  // Passe au Node_1 suivant
        }
        c = c->next; // Passe au Node suivant dans la table de hachage
    }
}