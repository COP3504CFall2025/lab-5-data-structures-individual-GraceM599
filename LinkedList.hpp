#pragma once
#include <iostream>
using namespace std;




template <typename T>
class LinkedList {
private:
	// Stores pointers to first and last nodes and count

	struct Node {
		T data;
		Node* prev;
		Node* next;
		Node() = default;
		Node(T d) {
			data = d;
			prev = nullptr;
			next = nullptr;
		}
	};
	Node* head;
	Node* tail;
	unsigned int count;
public:
	// Behaviors
	void printForward() const {
		std::cout << "Count: " << count << std::endl;
		Node* current = head;
		for (int i=0; i<count; ++i) {
			std::cout << current->data << std::endl;
			current = current->next;
		}
	}
	void printReverse() const {
		Node* current = tail;
		for (int i=0; i<count; ++i) {
			std::cout << current->data << std::endl;
			current = current->prev;
		}
	}
	// Accessors
	[[nodiscard]] unsigned int getCount() const {
		return count;
	}
	Node* getHead() {
		return head;
	}
	const Node* getHead() const {
		return head;
	}
	Node* getTail() {
		return tail;
	}

	const Node* getTail() const {
		return tail;
	}

	// Insertion
	void addHead(const T& data) {
		if (count == 0) {
			head = new Node(data);
			tail = head;
			count +=1;

		}
		else {
			Node* temp = new Node(data);
			temp->next = head;
			head->prev = temp;
			head = temp;
			count +=1;
		}


	}
	void addTail(const T& data) {
		if (count == 0) {
			tail = new Node(data);
			head = tail;
			count +=1;

		}
		else {
			Node* temp = new Node(data);
			temp->prev = tail;
			temp->next = nullptr;
			tail->next = temp;
			tail = temp;
			count +=1;
		}

	}

	// Removal
	bool removeHead() {
		if (count == 0 || head== nullptr) {
			return false;
		}
		if (head->next == nullptr) {
			delete head;
			head = nullptr;
			tail = nullptr;
			count -= 1;
			return true;
		}
		else {
			Node* temp = head->next;
			temp->prev = nullptr;
			delete head;
			head = temp;
			count -=1;
			return true;
		}

	}
	bool removeTail() {
		std::cout << "Remove Tail Count: " << count << std::endl;
		if (count ==0) {
			return false;
		}
		if (tail->prev ==nullptr) {
			delete tail;
			head = nullptr;
			tail = nullptr;
			count -= 1;
			return true;
		}
		else {

			Node* temp = tail->prev;
			temp->next = nullptr;
			delete tail;
			tail = temp;
			count -=1;
			return true;
		}

	}
	void clear() {
		Node* current = head;
		while (current != nullptr) {
			Node* temp = current->next;
			delete current;
			current = temp;

		}
		head = nullptr;
		tail = nullptr;
		count = 0;
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {

		if (&other == this) {
			return *this;
		}
		else {
			clear();
			count = other.getCount();
			head = other.getHead();
			tail = other.getTail();
			other.head = nullptr;
			other.tail = nullptr;
			other.count = 0;

		}
		return *this;
	}
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
		if (this == &rhs) {
			return *this;
		}
		clear();
		const Node* current = rhs.getHead();
		while (current  != nullptr) {
			addTail(current->data);
			current = current->next;
		}
		return *this;
	}

	// Construction/Destruction
	LinkedList(){
		head = nullptr;
		tail = nullptr;
		count = 0;

	}
	LinkedList(const LinkedList<T>& list) {
		head = nullptr;
		tail = nullptr;
		count = 0;
		Node* current = list.head;
		while (current != nullptr) {
			addTail(current->data);
			current = current->next;
		}


	}
	LinkedList(LinkedList<T>&& other) noexcept {

		count = other.getCount();
		head = other.getHead();
		tail = other.getTail();
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;




	}

	~LinkedList() {
		Node* current = head;
		while (current != nullptr) {
			Node* temp = current->next;
			delete current;
			current = temp;

		}
		head = nullptr;
		tail = nullptr;
		count = 0;


	}



};


