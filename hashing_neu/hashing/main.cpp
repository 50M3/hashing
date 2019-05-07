
#include <iostream>
#include <iomanip>
#include <cmath>

#define MAX_HASH 10
#define TABLE_SIZE 10
#define FREI -1
#define ENTFERNT -2
#define BELEGT 1

int comparisons = 0;

int insert_key(int data);
int insert_key_quad(int data);
int search_key(int data);
int biggestClusterSize();
int clusterAmount();
void delete_key(int data);
void print_hashtable();
void print_hashtable_quad();
void resetComparisons();

int lin_hash(int data, int i);
int quad_hash(int data, int i);
int getHash(int data);

using namespace std;

// *********************************************
// KEY STRUKTUR
// *********************************************
typedef struct key {
	int data;
	int state; // -1 = frei, 0 = entfernt, 1 = belegt
}key;

key* hashtable[TABLE_SIZE];
key* hashtable_quad[TABLE_SIZE];

// *********************************************
// MAIN
// *********************************************
int main() {
	for (int i = 0; i < TABLE_SIZE; i++) {
		hashtable[i] = new key{ 0, FREI };
	}

	for (int j = 0; j < TABLE_SIZE; j++) {
		hashtable_quad[j] = new key{ 0, FREI };
	}

	try {
		while (true) {
			
			if (system("CLS")) system("clear");

			cout << "************************************" << endl;
			print_hashtable();
			print_hashtable_quad();
			cout << "0 -> Element in Hashtabelle einfuegen" << endl;
			cout << "1 -> Element in Hashtabelle suchen" << endl;
			cout << "2 -> Element in Hashtabelle QUAD einfuegen" << endl;
			cout << "3 -> Programm schliessen" << endl;
			cout << "************************************" << endl;
			cout << "Anzahl der Schluesselvergleiche (insgesamt): " << comparisons << endl;
			cout << "Lin: Anzahl der Cluster: " << clusterAmount() << endl;
			cout << "Lin: Groestes Cluster: " << biggestClusterSize() << endl;

			int eingabe = 0;
			int select = 0;

			cin >> select;

			switch (select) {

			case 0:
				cout << "-Element in Hashtabelle einfuegen" << endl;
				cin >> eingabe;
				resetComparisons();
				insert_key(eingabe);
				break;

			case 1:
				cout << "-Element in Hashtabelle suchen" << endl;
				cin >> eingabe;
				resetComparisons;
				search_key(eingabe);
				break;

			case 2:
				cout << "-Element in Hashtabelle QUAD einfuegen" << endl;
				cin >> eingabe;
				resetComparisons;
				insert_key_quad(eingabe);
				break;
			case 3:
				cout << "-Programm schliessen" << endl;
				exit(EXIT_SUCCESS);
			}

		}
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}


}


// *********************************************
// FUNKTIONEN
// *********************************************
int insert_key(int data) {
	int i = 0, j = 0;

	do {
		i = (lin_hash(data, j));
		if (hashtable[i]->state == BELEGT) {
			comparisons++;
		}

		if (j >= TABLE_SIZE) {
			throw "Hashtabelle ist voll! [insert_key]";
		}
		j++;
	} while (hashtable[i]->state == BELEGT);

	hashtable[i]->data = data;
	hashtable[i]->state = BELEGT;

	return i;
}

int insert_key_quad(int data) {
	int i = 0, j = 0;

	do{
		i = (quad_hash(data, j));
		if (hashtable_quad[i]->state == BELEGT) {
			comparisons++;
		}
		if (j >= TABLE_SIZE) {
			throw "Hashtabelle ist voll! [insert_key_quad]";
		}
		j++;
	} while (hashtable_quad[i]->state == BELEGT);

	hashtable_quad[i]->data = data;
	hashtable_quad[i]->state = BELEGT;

	return i;
}

int search_key(int data) {
	/*int i = 0, hash = lin_hash(data, i++);

	while (hashtable[hash]->state != FREI && i < TABLE_SIZE) {
		comparisons++;
		if (hashtable[hash]->data == data) {
			return hash;
		}

		hash = lin_hash(data, i++);
	}
	return FREI;*/

	int i = 0, j = 0;

	do {
		i = (lin_hash(data, j));
		if (hashtable[i]->state == BELEGT) {
			comparisons++;
		}
		if (hashtable[i]->data == data) {
			return i;
		}
		j++;
	} while (hashtable[i]->state != FREI && j < TABLE_SIZE);

	return FREI;
}

int biggestClusterSize(){
	int count = 0, max = 0;

	for (int i = 0; i < TABLE_SIZE; i++) {
		if (hashtable[i]->state != FREI && hashtable[i]->state != ENTFERNT) {
			count++;
		}
		else {
			if (count > max) {
				max = count;
			}

			count = 0;
		}
	}
	return (count > max) ? count : max;
}

int clusterAmount() {
	int count = 0;
	bool found = false;

	for (int i = 0; i < TABLE_SIZE; i++) {
		if (hashtable[i]->state != FREI && hashtable[i]->state != ENTFERNT) {
			if (!found) {
				found = true;
				count++;
			}
			else {
				found = false;
			}
		}
	}
	return count;
}


// *********************************************
// ALGORITHMEN
// *********************************************

double alpha(int capacity, int number_of_elements) {
	return number_of_elements * 1.0 / capacity;
}

double lin_success(double alpha) {
	return 0.5* (1 + (1 / (1 - alpha)));
}

double lin_fail(double alpha) {
	return 0.5* (1 + (1 / (1 - alpha) * (1 - alpha)));
}


// *********************************************
// HASHING
// *********************************************

int lin_hash(int data, int i) {
	return (getHash(data) + i) % MAX_HASH;
}

int quad_hash(int data, int i) {
	return getHash(getHash(data) + (pow(i / 2, 2) * pow(-1, i)));
}

int getHash(int data) {
	return data % MAX_HASH;
}


void print_hashtable() {
	cout << "------------------------------------" << endl;
	for (int i = 0; i < TABLE_SIZE; i++) {
		cout << setw(3) << i << " Memory " << hashtable[i] << " -> "
			 << setw(5) << hashtable[i]->data << " -> "
			 << hashtable[i]->state << endl;
	}
	cout << "------------------------------------" << endl;
}

void print_hashtable_quad() {
	cout << "------------------------------------" << endl;
	for (int i = 0; i < TABLE_SIZE; i++) {
		cout << setw(3) << i << " Memory " << hashtable_quad[i] << " -> "
			<< setw(5) << hashtable_quad[i]->data << " -> "
			<< hashtable_quad[i]->state << endl;
	}
	cout << "------------------------------------" << endl;
}

void resetComparisons(){
	comparisons = 0;
}
