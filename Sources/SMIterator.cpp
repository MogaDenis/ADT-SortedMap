#include "../Headers/SMIterator.h"
#include "../Headers/SortedMap.h"
#include <exception>

using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m){
	this->currentNode = m.head;
	this->head = m.head;
}

// Time complexity: Theta(1)
void SMIterator::first(){
	this->currentNode = this->head;
}

// Time complexity: Theta(1)
void SMIterator::next(){
	if (!this->valid())
		throw std::exception();

	this->currentNode = this->currentNode->next;
}

// Time complexity: Theta(1)
bool SMIterator::valid() const{
	return this->currentNode != nullptr;
}

// Time complexity: Theta(1)
TElem SMIterator::getCurrent() const{
	if (!this->valid())
		throw std::exception();

	return this->currentNode->data;
}


