#include <iostream>
#include <fstream>
using namespace std;

struct AVLNode {
	int dato;
	AVLNode * hijoIzq;
	AVLNode * hijoDer;
	int altura;
	int indice;
};


class arbol {

private:


public:

	int max(int a, int b) {
		return (a > b) ? a : b;
	}

	int altura(AVLNode* t)
	{//es_vacio(t)
		if (t == NULL)
			return 0;
		return t->altura;
	}

	AVLNode* hacer(int x) {
		AVLNode* t = (struct AVLNode*) malloc(sizeof(struct AVLNode));
		t->hijoIzq = 0;
		t->hijoDer = 0;
		t->dato = x;
		t->altura = 1;
		return t;
	}

	int getFE(AVLNode* t)
	{
		if (t == NULL)
			return 0;
		return altura(t->hijoIzq) - altura(t->hijoDer);
	}

	bool es_vacio(AVLNode* t) {
		return (t == NULL) ? true : false;
	}

	void actualizar_altura(AVLNode* t)
	{
		if (!es_vacio(t))// !es_vacio(t)
			t->altura = max(altura((t)->hijoIzq), altura((t)->hijoDer)) + 1;
	}

	AVLNode* rotar_s(AVLNode* t, bool izq) {
		AVLNode* t1 = (AVLNode*)malloc(sizeof(AVLNode));
		if (izq){ //rotacion a la derecha 
			t1 = t->hijoIzq;
			(t)->hijoIzq = t1->hijoDer;
			t1->hijoDer = t;
		}
		else { //rotacion a la izquierda 
			t1 = t->hijoDer;
			(t)->hijoDer = t1->hijoIzq;
			t1->hijoIzq = t;
		}
		actualizar_altura(t);
		actualizar_altura(t1);
		t = t1; //se asigna nueva raiz.
		return t;
	}

	AVLNode* rotar_d(AVLNode* t, bool izq) {
		if (izq) //rotacion a la derecha IZQ-DER
		{
			t->hijoIzq = rotar_s((t)->hijoIzq, false);
			return rotar_s(t, true);
		}
		else { //DER-IZQ
			t->hijoDer = rotar_s(t->hijoDer, true);
			return rotar_s(t, false);
		}
	}

	AVLNode* balancear(AVLNode* t) {
		if (!es_vacio(t)) {
			if (altura(t->hijoIzq) - altura(t->hijoDer) == 2) { /* desequilibrio hacia la izquierda! */
				if (altura((t)->hijoIzq->hijoIzq) >= altura((t)->hijoIzq->hijoDer)) 
					return rotar_s(t, true);
				else 
					return rotar_d(t, true);
			}
			else if (altura(t->hijoDer) - altura(t->hijoIzq) == 2) { /* desequilibrio hacia la derecha! */
				if (altura((t)->hijoDer->hijoDer) >= altura((t)->hijoDer->hijoIzq)) 
					return rotar_s(t, false);
				else 
					return rotar_d(t, false);
			}
			else {
				return t;//cuando no hay balanceo
				cout << "no hubo balanceoo" << endl;
			}
		}
	}

	AVLNode* insert(AVLNode* t, int x) {
		if ( t == NULL) 
			return hacer(x);
		else {
			if (x < t->dato)
				t->hijoIzq = insert(t->hijoIzq, x);
			else 
				t->hijoDer = insert(t->hijoDer, x);
			actualizar_altura(t);
			t = balancear(t);
			return t;
		}
	}

	AVLNode* deleteNode(AVLNode* raiz, int x) {
		if (raiz == NULL) //si no existe, se devuelve.
			return raiz;
		if (x < raiz->dato)
			raiz->hijoIzq = deleteNode(raiz->hijoIzq, x);
		else if (x > raiz->dato)
			raiz->hijoDer = deleteNode(raiz->hijoDer, x);
		else { //coincidencia
			if ((raiz->hijoIzq == NULL) || (raiz->hijoDer == NULL)) { // nodo  hoja o con 1 hijo.
				AVLNode* temp = raiz->hijoIzq ? raiz->hijoIzq : raiz->hijoDer;

				// nodo sin hijos
				if (temp == NULL) {
					//temp = raiz;
					//raiz = NULL;
					free(raiz);
					raiz = NULL;
				}
				else // Nodo tiene 1 hijo
					*raiz = *temp;
				free(temp);
			}
			else { //NODO CON DOS HIJOS
				cout << "1. Predecesor 2. Sucesor \n Ingrese opcion: " << endl;
				int n;
				cin >> n;
				while (n < 1 || n > 2) {
					cout << "opcion invalida. Ingrese otra vez: " << endl;
					cin >> n;
				}
				if (n == 1) {
					AVLNode* temp = maxValueNode(raiz->hijoIzq);
					raiz->dato = temp->dato;
					raiz->hijoIzq = deleteNode(raiz->hijoIzq, temp->dato);
				}
				else if (n == 2) {
					AVLNode* temp = minValueNode(raiz->hijoDer);
					raiz->dato = temp->dato;
					raiz->hijoDer = deleteNode(raiz->hijoDer, temp->dato);
				}
			}
		}

		// si el arbol solo tiene un nodo
		if (raiz == NULL)
			return raiz;

		actualizar_altura(raiz);
		raiz = balancear(raiz);
		return raiz;
	}

	AVLNode* insertF(AVLNode* raiz, int x) {
		ofstream fileC("avl.dat", ios::out | ios::binary);
		if (!fileC) {
			cout << "Error de apertura en el archivo. " << endl;
			return NULL;
		}
		else {
			fileC.seekp(0, ios::end);
			AVLNode* tree = insert(raiz, x);
			fileC.write(reinterpret_cast<const char*>(&tree), sizeof(tree));
			fileC.close();
			return tree;
		}
		cout << "No se pudo insertar al archivo. " << endl;
		return NULL;
	}

	AVLNode* deleteNodeF(AVLNode* raiz, int x) {
		ofstream fileC("avl.dat", ios::out | ios::binary);
		if (!fileC) {
			cout << "Error de apertura en el archivo. " << endl;
			return NULL;
		}
		else {
			fileC.seekp(0, ios::end);
			AVLNode* tree = deleteNode(raiz, x);
			fileC.write(reinterpret_cast<const char*>(&tree), sizeof(tree));
			fileC.close();
			return tree;
		}
		cout << "No se pudo borrar el nodo en el archivo. " << endl;
		return NULL;
	}
	
	AVLNode* minValueNode(AVLNode* t) { //entrega el sucesor
		AVLNode* actual = t;
		while (actual->hijoIzq != NULL)
			actual = actual->hijoIzq;

		return actual;
	}

	AVLNode* maxValueNode(AVLNode* t) {//entrega predecesor
		AVLNode* actual = t;
		while (actual->hijoDer != NULL)
			actual = actual->hijoDer;

		return actual;
	}

	AVLNode* readInsertion() {
		ifstream fileC("avl.dat", ios::in | ios::binary);
		if (!fileC) {
			cout << "Error de aprtura en el archivo!" << endl;
		}

		fileC.seekg(0, ios::beg);
		AVLNode* tree;
		fileC.read(reinterpret_cast<char*>(&tree), sizeof(tree));

		/*while (!fileC.eof()) {
			fileC.read(reinterpret_cast<char*>(&tree), sizeof(tree));
		}*/
		printRecorridos(tree);
		return tree;
	}

	void printRecorridos(AVLNode* raiz) {
		cout << "	Tres Recorridos: " << endl;
		cout << "Pre Orden: ";
		preOrder(raiz);
		cout << "\nEn Orden: ";
		inOrder(raiz);
		cout << "\nPost Orden: ";
		postOrder(raiz);
		cout << endl;
	}

	void preOrder(AVLNode* t) {
		if (!es_vacio(t)) {
			cout << t->dato << " ";
			preOrder(t->hijoIzq);
			preOrder(t->hijoDer);
		}
	}

	void inOrder(AVLNode* t) {
		if (!es_vacio(t)) {
			inOrder(t->hijoIzq);
			cout << t->dato << " ";
			inOrder(t->hijoDer);
		}
	}

	void postOrder(AVLNode* t) {
		if (!es_vacio(t)) {
			postOrder(t->hijoIzq);
			postOrder(t->hijoDer);
			cout << t->dato << " ";
		}
	}

	
};



