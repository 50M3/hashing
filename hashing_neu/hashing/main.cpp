
#include <iostream>
#include <iomanip>

#define MAX_HASH 10
#define TABLE_SIZE 10
#define FREI -1
#define ENTFERNT -2
#define BELEGT 1

int comparisons = 0;

int insert_key(int data);
int search_key(int data);
void delete_key(int data);
void print_hashtable();
void resetComparisons();

int lin_hash(int data, int i);
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

// *********************************************
// MAIN
// *********************************************
int main() {
	for (int i = 0; i < TABLE_SIZE; i++) {
		hashtable[i] = new key{ 0, FREI };
	}

	while (true) {
		cout << "************************************" << endl;
		print_hashtable();
		cout << "0 -> Element in Hashtabelle einfuegen" << endl;
		cout << "1 -> Element in Hashtabelle suchen" << endl;
		cout << "2 -> Programm schliessen" << endl;
		cout << "************************************" << endl;
		cout << "Anzahl der Schluesselvergleiche: " << comparisons << endl;

		int eingabe = 0;
		int select = 0;

		cin >> select;

		switch (select) {

		case 0:
			cout << "-Element in Hashtabelle einfuegen" << endl;
			cin >> eingabe;
			insert_key(eingabe);
			break;

		case 1:
			cout << "-Element in Hashtabelle suchen" << endl;
			cin >> eingabe;
			search_key(eingabe);
			break;
 
		case 2:
			cout << "-Programm schliessen" << endl;
			exit(EXIT_SUCCESS);
		}
		
	}


}


// *********************************************
// FUNKTIONEN
// *********************************************
int insert_key(int data) {
	int i = 0, j = 0;  // k = KEY COMPARISONS

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

int search_key(int data) {
	int i = 0, hash = lin_hash(data, i++);

	while (hashtable[hash]->state != FREI && i < TABLE_SIZE) {
		comparisons++;
		if (hashtable[hash]->data == data) {
			return hash;
		}

		hash = lin_hash(data, i++);
	}
	return FREI;
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

void resetComparisons(){
	comparisons = 0;
}