#include <iostream>
#include "arbol.h"
using namespace std;

int main() {

	int resp = -1;
	AVLNode* raiz = NULL;
	arbol a;
	int n = -1, llave = -1;


	do {
		cout << "\n1. Arbol AVL en RAM" << endl
			 << "2. Arbol AVL en Fichero" << endl 
			 << "3. Salir " << endl;
		cin >> resp;

		if (resp == 1) {
			raiz = NULL;
			/*raiz = a.insert(raiz, 9);
			raiz = a.insert(raiz, 5);
			raiz = a.insert(raiz, 10);
			raiz = a.insert(raiz, 0);
			raiz = a.insert(raiz, 6);
			raiz = a.insert(raiz, 11);
			raiz = a.insert(raiz, -1);
			raiz = a.insert(raiz, 1);
			raiz = a.insert(raiz, 2);*/

			cout << "Ingrese cantidad de nodos: " << endl;
			cin >> n;
			for (int i = 0; i < n; i++){
				cout << "Ingrese llave: " << endl;
				cin >> llave;
				raiz = a.insert(raiz, llave);
			}
			a.printRecorridos(raiz);

			cout << "Ingrese cantidad de nodos a eliminar: " << endl;
			cin >> n;
			for (int i = 0; i < n; i++) {
				cout << "Ingrese llave a eliminar: " << endl;
				cin >> llave;
				raiz = a.deleteNode(raiz, llave);
			}
			a.printRecorridos(raiz);
		}

		if (resp == 2) {
			raiz = NULL;
			/*raiz = a.insertF(raiz, 9);
			raiz = a.insertF(raiz, 5);
			raiz = a.insertF(raiz, 10);
			raiz = a.insertF(raiz, 0);
			raiz = a.insertF(raiz, 6);
			raiz = a.insertF(raiz, 11);
			raiz = a.insertF(raiz, -1);
			raiz = a.insertF(raiz, 1);
			raiz = a.insertF(raiz, 2);*/

			cout << "Ingrese cantidad de nodos: " << endl;
			cin >> n;
			for (int i = 0; i < n; i++) {
				cout << "Ingrese llave: " << endl;
				cin >> llave;
				raiz = a.insertF(raiz, llave);
			}
			raiz = a.readInsertion();

			/*cout << "Ingrese cantidad de nodos a eliminar: " << endl;
			cin >> n;
			for (int i = 0; i < n; i++) {
				cout << "Ingrese llave a eliminar: " << endl;
				cin >> llave;
				raiz = a.deleteNode(raiz, llave);
			}
			a.readInsertion();*/
		}

	} while (resp != 3);

	return 0;
};