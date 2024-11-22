#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

//Best-Case: ϴ(1), Avarage-Case:ϴ(1), Worst-Case:ϴ(1) -face o atribuire
SMIterator::SMIterator(const SortedMap &m) : map(m) {
    this->index = 0;
}

//Best-Case: ϴ(1), Avarage-Case:ϴ(1), Worst-Case:ϴ(1) -face o atribuire (initializeaza index cu 0)
void SMIterator::first() {  //muta iteratorul pe prima poz a mapului
    this->index = 0;
}

//Best-Case: ϴ(1), Avarage-Case:ϴ(1), Worst-Case:ϴ(1)- nu are conditii repetitive
void SMIterator::next() {   //iterator->urm. poz
    if (!valid()) {
        throw exception();
    }
    this->index++;
}

//Best-Case: ϴ(1), Avarage-Case:ϴ(1), Worst-Case:ϴ(1) -nu are conditii repetitive
bool SMIterator::valid() const {    //ret true daca indexul < dimensiune map
    return this->index < map.size();
}

//Best-Case: ϴ(1), Avarage-Case:ϴ(1), Worst-Case:ϴ(1) -nu are conditii repetitive
TElem SMIterator::getCurrent() const {
    if (!valid())
        throw exception();
    return map.map[this->index];    //elem curent
}

//Best-Case: ϴ(1), Avarage-Case:ϴ(1), Worst-Case:ϴ(1) -nu are conditii repetitive
void SMIterator::iterator_schritte(int cat) {
    if (cat >= 0) {
        if (!valid() || index + cat > map.currentSize) {
            throw exception();
        }
        this->index += cat;
    } else {
        if (map.currentSize <= 0 || map.currentSize - cat >= 0) {
            throw exception();
        }
        index -= cat;
    }
}
//void SMIterator::iterator_schritte() {
//    if (cat >= 0) {
//        if (!valid() || index + this->cat> map.currentSize) {
//            throw exception();
//        }
//        this->index += this->cat;
//    } else {
//        if (map.currentSize <= 0 || map.currentSize - this->cat>= 0) {
//            throw exception();
//        }
//        index -= map.cat;
//    }
//}

int SMIterator::getIndex() {
    return index;
}
