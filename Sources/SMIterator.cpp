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

// Best case: There is no element in the list, k is less or equal to 0 or the iterator is invalid: Theta(1)
// Worst case: There are at least k elements: Theta(k)
// Average case: There are at most k elements: O(k)
// Total time complexity: O(k)
void SMIterator::jumpForward(int k)
{
	// If the iterator is invalid or k is not an appropriate value, throw an exception.
	if (!this->valid() || k <= 0)
		throw std::exception();

	// Call next k times.
	for (int i = 0; i < k; i++)
	{
		// When the iterator becomes invalid, break out of the loop.
		if (!this->valid())
			break;

		this->next();
	}
}


