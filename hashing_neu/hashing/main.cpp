//  ***********************************************************************************************************
//  Name:       main.cpp
//  Author:     Florian Liehr
//  Datum:      07.05.2019
//  Uhrzeit:    21:14
//  Beschreib.: Implementiert wichtige Funktionen für Hashing
//  ***********************************************************************************************************
#include <iostream>
#include <iomanip>
#include <cmath>

#define MAX_HASH 53
#define TABLE_SIZE 53
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


/*
 * typedef struct key
 *  Erstellt die Struktur key
 *	welche aus der Data und dem State besteht
 *
 * */
typedef struct key {
	int data;
	int state; // -1 = frei, 0 = entfernt, 1 = belegt
}key;

typedef struct search {
	int erfolg = 0;
	int erfolglos = 0;
}search;

key* hashtable[TABLE_SIZE];
key* hashtable_quad[TABLE_SIZE];
search anzahl;


int main() {
	for (int i = 0; i < TABLE_SIZE; i++) {
		hashtable[i] = new key{ 0, FREI };
	}

	/*for (int j = 0; j < TABLE_SIZE; j++) {
		hashtable_quad[j] = new key{ 0, FREI };
	}*/

	try {
		while (true) {
			
			if (system("CLS")) system("clear");

			cout << "************************************" << endl;
			print_hashtable();
			//print_hashtable_quad();
			cout << "0 -> Element in Hashtabelle einfuegen" << endl;
			cout << "1 -> Element in Hashtabelle suchen" << endl;
			cout << "2 -> Element in Hashtabelle QUAD einfuegen" << endl;
			cout << "5 -> Testrutiene ausführen!" << endl;
			cout << "3 -> Programm schliessen" << endl;
			cout << "************************************" << endl;
			cout << "Anzahl der Schluesselvergleiche (insgesamt): " << comparisons << endl;
			cout << "Anzahl der erfolgreichen Suchen: " << anzahl.erfolg << endl;
			cout << "Anzahl der erfolglosen Suchen: " << anzahl.erfolglos << endl;
			//cout << "Lin: Anzahl der Cluster: " << clusterAmount() << endl;
			//cout << "Lin: Groestes Cluster: " << biggestClusterSize() << endl;

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

			case 5:
				cout << "-Testrutieren wird ausgeführt!" << endl;
				for (int i = 0; i < MAX_HASH; i++) {
					insert_key(i);
					search_key(i);
					search_key(MAX_HASH + i);
				}
				//delete_key(4);
				//delete_key(10);
				break;
			}

		}
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}


}

/*
 * int insert_key(int data)
 *  Fuegt ein Element nach linearem Sondieren in die Liste ein!
 *	
 * Parameterliste:
 *  int data: Der Key der eingefügt werden soll.
 *
 * Rückgabeparameter:
 *  @i = Der gehashte Key
 *
 * */
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

/*
 * int insert_key_quad(int data)
 *  Fuegt ein Element nach quadratischem Sondieren in die Liste ein!
 *
 * Parameterliste:
 *  int data: Der Key der eingefügt werden soll.
 *
 * Rückgabeparameter:
 *  @i = Der gehashte Key
 *
 * */
/*int insert_key_quad(int data) {
	int i = 0, j = 0;

	do{
		i = (quad_hash(data, j));
		if (hashtable_quad[i]->state == BELEGT) {
			comparisons++;
		}
		if (j > TABLE_SIZE) {
			throw "Hashtabelle ist voll! [insert_key_quad]";
		}
		j++;
	} while (hashtable_quad[i]->state == BELEGT);

	hashtable_quad[i]->data = data;
	hashtable_quad[i]->state = BELEGT;

	return i;
}*/

int insert_key_quad(int data) {
	int i = 1;

	do {
		int hash = quad_hash(data, i++);

		if (hashtable_quad[hash]->state == FREI || hashtable_quad[hash]->state == ENTFERNT) {
			hashtable_quad[hash]->data = data;
			hashtable_quad[hash]->state = BELEGT;
			return hash;
		}
		comparisons++;
	} while (i < TABLE_SIZE);

	throw "Hashtabelle ist voll! [insert_key_quad]";
}
/*
 * int search_key(int data)
 *  Sucht einen Key in der Liste und vergleich in jedem Behälter die Schlüssel!
 *
 * Parameterliste:
 *  int data: Der Key der eingefügt werden soll.
 *
 * Rückgabeparameter:
 *  @i = Der gehashte Key
 *	@FREI = Ein leerer Slot wurde entdeckt!
 *
 * */

int search_key(int data) {
	int i = 0, hash = lin_hash(data, i++);

	while (hashtable[hash]->state == BELEGT && i < TABLE_SIZE) {
		comparisons++;

		if (hashtable[hash]->data == data) {
			anzahl.erfolg += 1;
			return hash;
		}

		hash = lin_hash(data, i++);
	}
	
	anzahl.erfolglos += 1;
	return FREI;
}

void delete_key(int data) {
	int hash = 0, i = 0;

	do {
		hash = (lin_hash(data, i));
		if (hashtable[hash]->state == BELEGT) {
			comparisons++;
		}
		i++;
	} while (hashtable[hash]->state == BELEGT && hashtable[hash]->data != data);

	if (hashtable[hash]->state == BELEGT && hashtable[hash]->data == data) {
		hashtable[hash]->state = ENTFERNT;
		hashtable[hash]->data = 0;
	}
}

/*
 * int biggestClusterSize()
 *  Wie groß das größte Cluster ist!
 *
 * Rückgabeparameter:
 *  @ count > max = return count
 *  @ max = return max;
 *
 * */
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

/*
 * int clusterAmount()
 *  Zählt die Cluster in der Hashtabelle!
 *
 * Rückgabeparameter:
 *  @count = Anzahl der Cluster!
 *
 * */
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


/*
 * double alpha(int capacity, int number_of_elements)
 *  Gibt an zu wie viel % die Liste gefüllt ist
 * 
 * Parameterliste:
 *	int capacity: Größe der Tabelle
 *  int number_of_elements: Anzahl der Elemente in der Liste
 *
 * Rückgabeparamter:
 *  @number_of_elements * 1.0 / capacity = Füllstand der Hashtabelle
 *
 * */
double alpha(int capacity, int number_of_elements) {
	return number_of_elements * 1.0 / capacity;
}

double lin_success(double alpha) {
	return 0.5* (1 + (1 / (1 - alpha)));
}

double lin_fail(double alpha) {
	return 0.5* (1 + (1 / (1 - alpha) * (1 - alpha)));
}



/*
 * int lin_hash(int data, int i)
 *  Hash nach linearer Sondierung
 *
 * Parameterliste:
 *  int data: Der Key der eingefügt werden soll.
 *  int i: Position in der Angefangen wird Keys einzufügen!
 *
 * Rückgabeparameter:
 *  @(getHash(data) + i) % MAX_HASH = Linear gehashter Key
 *
 * */
int lin_hash(int data, int i) {
	return (getHash(data) + i) % MAX_HASH;
}

/*
 * int quad_hash(int data, int i)
 *  Hash nach quadratischer Sondierung
 *
 * Parameterliste:
 *  int data: Der Key der eingefügt werden soll.
 *  int i: Position in der Angefangen wird Keys einzufügen!
 *
 * Rückgabeparameter:
 *  @getHash(getHash(data) + (pow(i / 2, 2) * pow(-1, i)));H = Quadratisch sondierter Key
 *
 * */
int quad_hash(int data, int i) {
	return getHash(getHash(data) + (pow(i / 2, 2) * pow(-1, i)));
}

/*
 * int getHash(int data)
 *  Gehashter Key nach Divisionsmethode!
 *
 * Parameterliste:
 *  int data: Der Key der gehasht wird.
 *
 * Rückgabeparameter:
 *  @data % MAX_HASH = Gehashter Key
 *
 * */
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
