// i = 4
// j = 2


#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <stack>
#include <queue>

using namespace std;


int* CreateArray(int sizeofarr) {
	cout << "Unesite elemente niza: ";
	int* arr = new int[sizeofarr];
	for (int i = 0; i < sizeofarr; i++) {
		cin >> arr[i];
	}
	return arr;
}

int* ArrayFromFile(string FileName, int& sizeofarr) {
	int* arr;
	ifstream InputFile;
	InputFile.open(FileName);
	if (!InputFile.is_open()) {
		cout << "Nepostojeci fajl!\n";
		arr = nullptr;
		return arr;
	}
	InputFile >> sizeofarr;
	arr = new int[sizeofarr];
	for (int i = 0; i < sizeofarr; i++) {
		InputFile >> arr[i];
	}
	InputFile.close();
	return arr;
}

int* CreateArrayRandom(int high, int low, int sizeofarr) {
	int* arr = new int[sizeofarr];
	for (int i = 0; i < sizeofarr; i++) {
		arr[i] = (rand() % (high - low + 1)) + low;
	}
	int temp;
	for (int i = 0; i < sizeofarr - 1; i++) {
		for (int j = i + 1; j < sizeofarr; j++) {
			if (arr[j] > arr[i]) {
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
	return arr;
}

void PrintArr(int* arr, int arrsize) {
	for (int i = 0; i < arrsize; i++) {
		cout << arr[i] << " ";
	}
	cout << "\n";
}





//high i low su granice niza - stavljeno je zbog toga jer se koristi u SearchMul
//funkcije za zadatak 1
int Search(int* arr, int m, int key, int sizeofarr, float high, float low, float& steps) {
	int prev, curr, i;


	if ((key > arr[(int)low]) || (key < arr[(int)high])) {
		steps += 2;
		return -1;
	}
	steps += 2;

	prev = low;
	while ((high - low + 1) > m) {


		for (i = 1; i <= m; i++) {

			if (i == m) {
				curr = high;
			}
			else {
				curr = (((high - low) / m) * i) + low;
			}



			if (key == arr[prev]) {
				steps++;
				return prev;
			}
			steps++;

			if (key == arr[curr]) {
				steps++;
				return curr;
			}
			steps++;


			if ((key < arr[prev]) && (key > arr[curr])) {
				high = curr;
				low = prev;
				steps += 4;
				break;
			}
			steps += 2;
			prev = curr;
		}


	}

	//ovaj ovde deo ide sekvencijalno i trazi kada sizeofarr >= m !!!!
	for (i = low; i <= high; i++) {
		steps++;
		if (arr[i] == key) {
			return i;
		}
	}
	return -1;
}

int* SearchMul(int* arr, int m, int* keys, int sizeofkeys, int sizeofarr, float& steps) {
	int* indexs = new int[sizeofkeys];
	float high = sizeofarr - 1, low = 0;
	int temp;


	for (int i = 0; i < sizeofkeys; i++) {
		temp = Search(arr, m, keys[i], sizeofarr, high, low, steps);
		indexs[i] = temp;
		if (temp != -1) {
			low = (float)temp;
		}
	}
	return indexs;
}

void Steps(float l_limit, float h_limit, int sizeofarr, int choice) {
	int* arr = CreateArrayRandom(h_limit, l_limit, sizeofarr);
	//da isprintuje niz;
	for (int i = 0; i < sizeofarr; i++) {
		cout << arr[i] << " ";
	}
	cout << "\n";
	//kljucevi na koje se vrsi pretraga

	int sizeofkeys;
	cout << "Unesite koliko kljuceva zelite da trazite:";
	cin >> sizeofkeys;
	int lower, higher;
	cout << "Unesite donju granicu: ";
	cin >> lower;
	cout << "Unesite gornju granicu: ";
	cin >> higher;
	int* keys = CreateArrayRandom(higher, lower, sizeofkeys);
	//imam niz kljuceva sada


	//ovde krece obrada
	if (choice == 1) {
		float steps;
		for (int i = 2; i <= 6; i++) {
			steps = 0;
			for (int j = 0; j < sizeofkeys; j++) {
				Search(arr, i, keys[j], sizeofarr, sizeofarr - 1, 0, steps);	
			}
			cout << "Za m = " << i << " prosecan broj koraka je : " << (steps / sizeofkeys) << "\n";
		}
		return;
	}
	else if (choice == 2) {
		for (int i = 2; i <= 6; i++) {
			float steps = 0;
			SearchMul(arr, i, keys, sizeofkeys, sizeofarr, steps);
			cout << "Za m = " << i << " prosecan broj koraka je : " << (steps / sizeofkeys) << "\n";
		}
		return;
	}
}


//-------------------------------------------------ZADATAK 2------------------------------------------------------------------//


typedef struct node {
	int id;
	struct node* left;
	struct node* right;
	struct node* parent;
	int l_limit;
	int h_limit;
	int height;
}Node;

Node* InitNode(int id, Node* parent) {
	Node* NewNode = new Node[1];
	NewNode->id = id;
	if (parent != nullptr) {
		NewNode->height = parent->height + 1;
	}
	NewNode->left = nullptr;
	NewNode->right = nullptr;
	NewNode->parent = parent;
	return NewNode;
}

Node* CreateBST(int* arr, int arrsize) {
	int low = 0, high = arrsize - 1, mid;
	stack<Node*> Stack;
	mid = (high + low) / 2;
	Node* root = InitNode(arr[mid], nullptr);
	root->height = 1;
	root->l_limit = mid + 1;
	root->h_limit = high;
	Stack.push(root);
	high = mid - 1;


	Node* next = root;
	while (low <= high) {

		mid = (low + high) / 2;
		next->left = InitNode(arr[mid], next);
		next = next->left;
		next->l_limit = mid + 1;
		next->h_limit = high;
		Stack.push(next);
		high = mid - 1;	
	}
	next->left = nullptr;	




	while (!Stack.empty()) {
		next = Stack.top();
		Stack.pop();
		low = next->l_limit;
		high = next->h_limit;

		if (low <= high) {
			
			mid = (low + high) / 2;
			next->right = InitNode(arr[mid], next);
			next = next->right;
			next->l_limit = mid + 1;
			next->h_limit = high;
			Stack.push(next);
			high = mid - 1;
			

			while (low <= high) {
				mid = (low + high) / 2;
				next->left = InitNode(arr[mid], next);
				next = next->left;
				next->l_limit = mid + 1;
				next->h_limit = high;
				Stack.push(next);
				high = mid - 1;
			}
			next->left = nullptr;
		}	
		else {
			next->right = nullptr;
		}
	}
	return root;
}

Node* FindKey(Node* root, int find_id, float& steps) {
	Node* travel = root;
	Node* found = nullptr;

	while (travel != nullptr) {
		if (travel->id == find_id) {
			steps++;
			found = travel;
			return found;
		}
		else {
			if (find_id > travel->id) {
				travel = travel->left;
			}
			else {
				travel = travel->right;
			}
			steps += 2;
		}
	}
	return found;
}

void AddNode(Node* root, int new_id) {
	Node* NewNode = InitNode(new_id, nullptr);
	Node* current_node = root;
	Node* parent = nullptr;

	while (current_node != nullptr) {
		parent = current_node;
		if (NewNode->id == current_node->id) {

			//ubaci ga kao sledbenika
			if (current_node->right == nullptr) {
				current_node->right = NewNode;
				NewNode->parent = current_node;
				NewNode->height = parent->height + 1;
				return;
			}
			else {
				//spustanje za jedan desno i onda skroz u levo
				current_node = current_node->right;
				while (current_node != nullptr) {
					parent = current_node;
					current_node = current_node->left;
				}
				parent->left = NewNode;
				NewNode->parent = parent;
				NewNode->height = parent->height + 1;
				return;
			}

		}
		else {
			if (NewNode->id > current_node->id) {
				current_node = current_node->left;
			}
			else {
				current_node = current_node->right;
			}
		}
	}


	if (parent == nullptr) {
		root = NewNode;
	}
	else {
		if (NewNode->id > parent->id) {
			parent->left = NewNode;
			NewNode->parent = parent;
			NewNode->height = parent->height + 1;
		}
		else {
			parent->right = NewNode;
			NewNode->parent = parent;
			NewNode->height = parent->height + 1;
		}
	}

}

void PrintTree(Node* root) {
	int tree_height = 0;
	int node_count = 0;
	queue<Node*> Queue;
	Node* currentNode;

	Queue.push(root);

	while (!Queue.empty()) {
		tree_height++;
		node_count = Queue.size();

		while (node_count--) {
			currentNode = Queue.front();
			if (currentNode->left != nullptr) {
				Queue.push(currentNode->left);
			}
			if (currentNode->right != nullptr) {
				Queue.push(currentNode->right);
			}
			Queue.pop();
		}
	}
	Queue.empty();
	//sad ide ispis


	Node* travel = root;
	int i, line_len = 62;
	int first_skip = line_len, in_between_skips;
	Queue.push(travel);
	for (i = 0; i <= tree_height; i++) {
		int j = 1 << i, k, l;
		in_between_skips = first_skip;
		first_skip = (first_skip - 2) / 2;
		for (k = 0; k < first_skip; k++) {
			cout << " ";
		}
		for (k = 0; k < j; k++) {
			travel = Queue.front();
			Queue.pop();
			if (travel != nullptr) {
				Queue.push(travel->left);
				Queue.push(travel->right);
			}
			else {
				Queue.push(nullptr);
				Queue.push(nullptr);
			}
			if (travel != nullptr) {
				cout << travel->id;
			}
			else {
				cout << "  ";
			}
			for (l = 0; l < in_between_skips; l++) {
				cout << " ";
			}
		}
		cout << "\n\n";
	}


}

float StepsBST(Node* root, int* keys, int sizeofkeys) {
	float steps = 0;

	for (int i = 0; i < sizeofkeys; i++) {

		FindKey(root, keys[i], steps);

	}

	return (steps / sizeofkeys);

}

void DeleteBST(Node* root) {
	queue<Node*> Queue;
	Node* current;
	Queue.push(root);

	while (!Queue.empty()) {

		current = Queue.front();
		Queue.pop();

		if (current->left != nullptr) {
			Queue.push(current->left);
		}
		if (current->right != nullptr) {
			Queue.push(current->right);
		}

		delete current;

	}


}

void PrintTreeLevelOrder(Node* root) {
	queue<Node*> Queue;
	Node* current;
	Queue.push(root);

	while (!Queue.empty()) {

		current = Queue.front();
		Queue.pop();

		cout << current->id << " ";

		if (current->left != nullptr) {
			Queue.push(current->left);
		}
		if (current->right != nullptr) {
			Queue.push(current->right);
		}

		if ((!Queue.empty()) && (current->height != Queue.front()->height)) {
			cout << "\n";
		}
	}

}



int main(){
	srand(time(NULL));
	cout << fixed << setprecision(2);

	float steps;
	int choice, lchoice, temp;
	int l_limit, h_limit;	
	int m, key;
	int* arr = nullptr;
	int* keys = nullptr;
	int* indexs = nullptr;
	int arrsize, keysize;
	string FileName;	
	int problem;


	do {
		cout << "----------IZABERITE ZADATAK----------\n";
		cout << "1. Zadatak\n";
		cout << "2. Zadatak\n";
		cin >> problem;
	} while ((problem < 1) || (problem > 2));



	if (problem == 1) {
		while (1) {

			do {
				cout << "----------MENI----------\n";
				cout << "Izaberite opciju:\n";
				cout << "1. Unos uredjenog niza\n";
				cout << "2. Generisanje uredjenog niza sa pseudoslucajnim brojevima\n";
				cout << "3. M-arna pretraga trazenog kljuca\n";
				cout << "4. M-arna pretraga trazenih kljuceva\n";
				cout << "5. Evaluacija performansi m-arnog pretrazivanja\n";
				cout << "6. Evaluacija performansi optimizovanog m-arnog pretrazivanja\n";
				cout << "7. Brisanje postojeceg niza\n";
				cout << "8. Ispis trenutnog niza\n";
				cout << "9. Kraj\n";
				cin >> choice;
			} while ((choice < 1) || (choice > 9));


			if (choice == 1) {
				if (arr != nullptr) {
					cout << "Niz je vec napravljen!\n";
					continue;
				}
				do {
					cout << "1. Unos niza preko konzole\n";
					cout << "2. Unos niza preko datoteke\n";
					cin >> lchoice;
				} while ((lchoice < 1) || (lchoice > 2));
				if (lchoice == 1) {
					do {
						cout << "Unesite duzinu niza: ";
						cin >> arrsize;
					} while (arrsize < 1);
					arr = CreateArray(arrsize);
				}
				else {
					cout << "Unesite ime datoteke: ";
					cin >> FileName;

					arrsize = 0; //za sada nepoznato , ucitace se u fajlu
					arr = ArrayFromFile(FileName, arrsize);
				}
			}
			else if (choice == 2) {
				if (arr != nullptr) {
					cout << "Niz je vec naprevaljen!\n";
					continue;
				}
				do {
					cout << "Unesite donju granicu: ";
					cin >> l_limit;
					cout << "Unesite gornju granicu: ";
					cin >> h_limit;
				} while (l_limit > h_limit);
				do {
					cout << "Unesite duzinu niza: ";
					cin >> arrsize;
				} while (arrsize < 1);
				arr = CreateArrayRandom(h_limit, l_limit, arrsize);
			}


			else if (choice == 3) {
				if (arr == nullptr) {
					cout << "Niz nije napravljen!\n";
					continue;
				}
				steps = 0;
				do {
					cout << "Unesite m: ";
					cin >> m;
				} while (m < 0);
				cout << "Unesite kljuc koji zelite da nadjete: ";
				cin >> key;
				temp = Search(arr, m, key, arrsize, arrsize - 1, 0, steps);
				if (temp == -1) {
					cout << "Kljuc sa vrednoscu " << key << " ne postoji u nizu!\n";
				}
				else {
					cout << "Indeks trazenog kljuca u nizu je: " << temp << "\n";
				}
			}
			else if (choice == 4) {
				if (arr == nullptr) {
					cout << "Niz nije napravljen!\n";
					continue;
				}
				steps = 0;
				do {
					cout << "Unesite m: ";
					cin >> m;
				} while (m < 0);
				do {
					cout << "Unesite koliko kljuceva zelite da nadjete: ";
					cin >> keysize;
				} while (keysize < 0);
				cout << "Unesite kljuceve koje zelite da nadjete: ";
				keys = new int[keysize];
				for (int i = 0; i < keysize; i++) {
					cin >> keys[i];
				}
				indexs = SearchMul(arr, m, keys, keysize, arrsize, steps);
				for (int i = 0; i < keysize; i++) {
					if (indexs[i] == -1) {
						cout << "Kljuc " << keys[i] << " ne postoji u nizu!\n";
					}
					else {
						cout << "Indeks kljuca sa vrednoscu " << keys[i] << " je " << indexs[i] << "!\n";
					}
				}
			}
			else if ((choice == 5) || (choice == 6)) {
				do {
					cout << "Unesite donju granicu: ";
					cin >> l_limit;
					cout << "Unesite gornju granicu: ";
					cin >> h_limit;
				} while (l_limit > h_limit);
				do {
					cout << "Unesite duzinu niza: ";
					cin >> arrsize;
				} while (arrsize < 1);
				if (choice == 5) {
					Steps(l_limit, h_limit, arrsize, 1);
				}
				else {
					Steps(l_limit, h_limit, arrsize, 2);
				}
			}
			else if (choice == 7) {
				delete[] arr;
				arr = nullptr;
			}

			else if (choice == 8) {
				if (arr == nullptr) {
					cout << "Niz ne postoji!\n";
					continue;
				}
				PrintArr(arr, arrsize);
			}


			else if (choice == 9) {
				return 0;
			}
		}
	}

	//ovde pocinje kod za drugi zadatak---------------------------------------------------------------------------------------------------------

	else {
		
		//krece obrada zadatka
		Node* root = nullptr;
		arr = nullptr;

		while (1) {

			do {
				cout << "----------MENI----------\n";
				cout << "1. Formiranje stabla na osnovu uredjenog niza kljuceva\n";
				cout << "2. Umetanje novog kljuca u stablo\n";
				cout << "3. Pretraga zadatog kljuca\n";
				cout << "4. Evoluacija performansni\n";
				cout << "5. Brisanje stabla iz memorije\n";
				cout << "6. Formatiran ispis stabla\n";
				cout << "7. Level order ispis stabla\n";
				cout << "8. Kraj\n";
				cin >> choice;
			} while (choice < 1 || choice > 8);


			if (choice == 1) {
				if (root != nullptr) {
					cout << "Stablo vec postoji!\n";
					continue;
				}
				if (arr == nullptr) {
					do {
						cout << "----------IZABERITE NACIN ZA FORMIRANJE NIZA KLJUCEVA----------\n";
						cout << "1. Unos uredjenog niza\n";
						cout << "2. Generisanje uredjenog niza sa pseudoslucajnim brojevima\n";
						cin >> choice;
					} while ((choice < 1) || (choice > 2));

					if (choice == 1) {
						do {
							cout << "Unesite duzinu niza: ";
							cin >> arrsize;
						} while (arrsize < 1);
						arr = CreateArray(arrsize);
					}
					else {
						do {
							cout << "Unesite donju granicu: ";
							cin >> l_limit;
							cout << "Unesite gornju granicu: ";
							cin >> h_limit;
						} while (l_limit > h_limit);
						do {
							cout << "Unesite duzinu niza: ";
							cin >> arrsize;
						} while (arrsize < 1);

						arr = CreateArrayRandom(h_limit, l_limit, arrsize);
						PrintArr(arr, arrsize);
					}
					root = CreateBST(arr, arrsize);
				}
				

			}
			else if (choice == 2) {
				if (root == nullptr) {
					cout << "Stablo ne postoji!\n";
					continue;
				}
				cout << "Unesite kljuc koji zelite da dodate: ";
				int new_id;
				cin >> new_id;
				AddNode(root, new_id);
			}
			else if (choice == 3) {
				if (root == nullptr) {
					cout << "Stablo ne postoji!\n";
					continue;
				}
				cout << "Unesite kljuc koji zelite da nadjete: ";
				int key;
				float steps = 0;
				cin >> key;
				Node* found = FindKey(root, key, steps);
				if (found != nullptr) {
					cout << "Kljuc pronadjen!\n";
				}
				else {
					cout << "Kljuc ne postoji!\n";
				}
			}
			else if (choice == 4) {
				if (root == nullptr) {
					cout << "Stablo ne postoji!\n";
					continue;
				}
				float steps = 0;
				do {
					cout << "Unesite koliko kljuceva zelite da pretrazite: ";
					cin >> keysize;
				} while (keysize < 1);
				do {
					cout << "Unesite donju granicu: ";
					cin >> l_limit;
					cout << "Unesite gornju granicu: ";
					cin >> h_limit;
				} while (l_limit > h_limit);
				keys = CreateArrayRandom(h_limit, l_limit, keysize);
				cout << "Kljucevi koji se traze su: ";
				for (int i = 0; i < keysize; i++) {
					cout << keys[i] << " ";
				}
				cout << "\n";
				cout << "Prosecan broj koraka je: " << StepsBST(root, keys, keysize) << endl;
			}
			else if (choice == 5) {
				if (root == nullptr) {
					cout << "Stablo ne postoji!\n";
					continue;
				}
				DeleteBST(root);
				delete[] arr;
				arr = nullptr;
				root = nullptr;
			}
			else if (choice == 6) {
				if (root == nullptr) {
					cout << "Stablo ne postji!\n";
					continue;
				}
				PrintTree(root);
				cout << "\n";
			}
			else if (choice == 7){
			if (root == nullptr) {
				cout << "Stablo ne postoji!\n";
				continue;
				}
				PrintTreeLevelOrder(root);
				cout << "\n";
			}
			else if (choice == 8) {
				cout << "KRAJ\n";
				return 0;
			}
		}

	





	}

	return 0;
}	