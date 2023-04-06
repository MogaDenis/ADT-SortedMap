#include "../Headers/SMIterator.h"
#include "../Headers/SortedMap.h"
#include <exception>

using namespace std;

SortedMap::SortedMap(Relation r) 
{
	this->head = nullptr;
	this->currentSize = 0;
	this->relationBetweenKeys = r;
}

// Copy constructor.
// Time complexity: Theta(n)
SortedMap::SortedMap(const SortedMap& sortedMap)
{
	this->currentSize = sortedMap.currentSize;
	this->relationBetweenKeys = sortedMap.relationBetweenKeys;

	Node* previousNode = nullptr;
	Node* currentNode = sortedMap.head;

	if (currentNode != nullptr)
		previousNode = new Node();

	while (currentNode != nullptr)
	{
		Node* newNode = new Node();
		newNode->data = currentNode->data;
		newNode->next = nullptr;
		previousNode->next = newNode;

		currentNode = currentNode->next;
	}
}

// Best case: The list is empty, or the key k is on the first position: Theta(1)
// Worst case: The key k belongs to the end of the list: Theta(n)
// Average case: O(n)
// Total time complexity => O(n)
TValue SortedMap::add(TKey k, TValue v) 
{
	Node* newNode = new Node();
	newNode->data.first = k;
	newNode->data.second = v;

	Node* currentNode = this->head;
	Node* previousNode = nullptr;

	// If the linked list is empty, add the new node at the beginning.
	if (this->head == nullptr)
	{
		this->head = newNode;
		newNode->next = nullptr;
		this->currentSize++;

		return NULL_TVALUE;
	}

	// Search the position where the new node will be inserted.
	while (currentNode != nullptr)
	{
		if (this->relationBetweenKeys(newNode->data.first, currentNode->data.first))
			break;

		previousNode = currentNode;
		currentNode = currentNode->next;
	}

	// Add the new node at the end of the linked list.
	if (currentNode == nullptr)
	{
		previousNode->next = newNode;
		newNode->next = nullptr;
		this->currentSize++;

		return NULL_TVALUE;
	}

	// If the key already exists, replace the value and return the replaced value.
	if (currentNode->data.first == newNode->data.first)
	{
		TValue oldValue = currentNode->data.second;
		currentNode->data.second = newNode->data.second;

		// Delete the new node since it is not inserted in the list.
		delete newNode;

		return oldValue;
	}

	// If the new node belongs to the beginning of the linked list, make it the new head.
	if (previousNode == nullptr)
	{
		newNode->next = this->head;
		this->head = newNode;
		this->currentSize++;

		return NULL_TVALUE;
	}

	// Otherwise, insert it.
	previousNode->next = newNode;
	newNode->next = currentNode;

	this->currentSize++;

	return NULL_TVALUE;
}

// Best case: The searched key is on the first position, or the list is empty: Theta(1)
// Worst case: The key is not found, parse the whole list: Theta(n)
// Average case: O(n)
// Total time complexity => O(n)
TValue SortedMap::search(TKey k) const 
{
	Node* currentNode = this->head;

	while (currentNode != nullptr)
	{
		if (currentNode->data.first == k)
			return currentNode->data.second;

		currentNode = currentNode->next;
	}

	return NULL_TVALUE;
}

// Best case: The searched key is on the first position, or the list is empty: Theta(1)
// Worst case: The key is not found, parse the whole list: Theta(n)
// Average case: O(n)
// Total time complexity => O(n)
TValue SortedMap::remove(TKey k) 
{
	// If the linked list is empty then there is nothing to remove.
	if (this->head == nullptr)
		return NULL_TVALUE;

	// If the node that needs to be deleted is the first one, update the head.
	if (this->head->data.first == k)
	{
		Node* headNode = this->head;
		TValue value = headNode->data.second;
		this->head = this->head->next;

		this->currentSize--;

		delete headNode;
		return value;
	}

	Node* currentNode = this->head;
	Node* previousNode = nullptr;

	// Search the node that needs to be eliminated.
	while (currentNode != nullptr && currentNode->data.first != k)
	{
		previousNode = currentNode;
		currentNode = currentNode->next;
	}

	// If we are at the end, then the key was not found.
	if (currentNode == nullptr)
		return NULL_TVALUE;

	// "Unlink" the node from the list.
	TValue value = currentNode->data.second;
	previousNode->next = currentNode->next;
	delete currentNode;

	this->currentSize--;

	return value;
}

// Time complexity: Theta(1)
int SortedMap::size() const 
{
	return this->currentSize;
}

// Time complexity: Theta(1)
bool SortedMap::isEmpty() const 
{
	return this->currentSize == 0;
}

// Iterator.
// Time complexity: Theta(1)
SMIterator SortedMap::iterator() const 
{
	return SMIterator(*this);
}

// Destructor.
// Time complexity: Theta(n)
SortedMap::~SortedMap() 
{
	Node* currentNode = this->head;

	while (currentNode != nullptr)
	{
		Node* nextNode = currentNode->next;
		delete currentNode;
		currentNode = nextNode;
	}
}
