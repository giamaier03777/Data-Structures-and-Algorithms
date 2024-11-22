#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

//Best-Case: ϴ(1), Avarage-Case:ϴ(1), Worst-Case:ϴ(1) -nu are conditii repetitive
SortedMap::SortedMap(Relation r) {
    this->relation = r;
    maxSize = 1;
    map = new TElem[maxSize];   //alocarea spatiului pt map
    currentSize = 0;
}

//Best-Case: ϴ(n), Avarage-Case:ϴ(n), Worst-Case:ϴ(n) -acel for se parcurge mereu tot, nu este conditie de oprire
void SortedMap::resizeUp() {
    int newSize = maxSize * 2;
    TElem *newMap = new TElem[newSize]; //map nou cu dimensiunea marita
    for (int i = 0; i < currentSize; ++i) {
        newMap[i] = map[i]; //copiem elem din mapul vechi in cel nou
    }
    delete[] map;   //eliberam memoria mapului vechi
    map = newMap;   //actualizare pointer pt noul map
    maxSize = newSize;      //actualizare a dim maxime
}

//Best-Case: ϴ(n), Avarage-Case:ϴ(n), Worst-Case:ϴ(n) -acel for se parcurge mereu tot, nu este conditie de oprire
void SortedMap::resizeDown() {
    int newSize = maxSize / 2;  //redimensionam la jumatate
    TElem *newMap = new TElem[newSize];     //map nou cu dim mai mica
    for (int i = 0; i < currentSize; ++i) {
        newMap[i] = map[i];     //copiere elem in cel nou
    }
    delete[] map;
    map = newMap;
    maxSize = newSize;
}

//Best-Case: ϴ(1), Avarage-Case:ϴ(n), Worst-Case:ϴ(n) -acel for se parcurge mereu tot, avand si while ar fi 2n, care e n
TValue SortedMap::add(TKey k, TValue v) {
    if (currentSize == maxSize) {   //daca mapul e plin, il marim
        resizeUp();
    }

    int poz = 0;
    while (poz < currentSize && !relation(k,
                                          map[poz].first)) { // parcurgem mapul si gasim poz potrivita pt adaugare
        poz++;
    }
    if (poz < currentSize && map[poz].first == k) { //verif daca cheia exista
        TValue old_value = map[poz].second;
        map[poz].second = v;
        return old_value;
    }

    for (int j = currentSize; j > poz; j--) {
        map[j] = map[j - 1];    //mutam elementele pt a face loc noului elem
    }
    map[poz].first = k; //adaugam cheia
    map[poz].second = v;    //adaugam valoarea
    currentSize++;  //actualizare marime
    return NULL_TVALUE;
}

//Best-Case: ϴ(n), Avarage-Case:ϴ(n), Worst-Case:ϴ(n) -acel for se parcurge mereu tot, doar for e repetitiv, nu si if
TValue SortedMap::search(TKey k) const {
    for (int i = 0; i < this->currentSize; i++) {
        if (map[i].first == k)  //verif daca exista cheia in map
            return map[i].second;      //returnam valoarea cheii
    }
    return NULL_TVALUE;     //daca cheia nu a fost gasita
}

//Best-Case: ϴ(n), Avarage-Case:ϴ(n), Worst-Case:ϴ(n) -acel for se parcurge mereu tot, nu este conditie de oprire in for, deci face toti pasii
TValue SortedMap::remove(TKey k) {
    if (search(k) == NULL_TVALUE) { //verif daca exista cheia in map
        return NULL_TVALUE; //daca nu se gaseste cheia
    }

    int poz = 0;
    while (poz < currentSize && k != map[poz].first) {  //gasim valoarea elem de sters
        poz++;
    }
    TValue deleted_value = map[poz].second; //retinem valoarea elem de sters
    for (int j = poz; j < currentSize - 1; j++) {
        map[j] = map[j + 1];    //mutam elem pt a umple golul lasat
    }
    currentSize--;

    if (currentSize <= maxSize / 2) {   //verif daca mapul trb redim
        resizeDown();
    }
    return deleted_value;   //returnam valoarea elem de sters
}

//Best-Case: ϴ(1), Avarage-Case:ϴ(1), Worst-Case:ϴ(1) -pace o sg atribuire
int SortedMap::size() const {   //marime curenta
    return this->currentSize;
}

//Best-Case: ϴ(1), Avarage-Case:ϴ(1), Worst-Case:ϴ(1) -pace o sg atribuire
bool SortedMap::isEmpty() const {   //true daca marimea e 0
    return this->currentSize == 0;
}

//Best-Case: ϴ(1), Avarage-Case:ϴ(1), Worst-Case:ϴ(1) -pace o sg atribuire
SMIterator SortedMap::iterator() const {
    return SMIterator(*this);   //returneaza iteratorul init cu mapul curent
}

//Best-Case: ϴ(1), Avarage-Case:ϴ(1), Worst-Case:ϴ(1)
SortedMap::~SortedMap() {
    delete[] map;   //elib memoria alocata pt map
}
