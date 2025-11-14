#pragma once
#include <iostream>
using namespace std;

template <typename T>
class LinkedList {

	struct Node{
		T info;
		Node* prev;
		Node* next;
		Node(T info, Node* prev, Node* next)
		:info(info), prev(prev), next(next){}
	};

	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;

public:
	// Behaviors
	void printForward() const{
		Node* temp = head;
		while(temp != nullptr){
			std::cout<<temp->info << std::endl;
			temp = temp->next;
		}

	}
	void printReverse() const{

		Node* temp = tail;
		while(temp != nullptr){
			std::cout<<temp->info << std::endl;
			temp = temp->prev;
		}

	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const{
		return count;
	}
	Node* getHead(){
		return head;
	}
	const Node* getHead() const{
		return head;
	}
	Node* getTail(){
		return tail;
	}
	const Node* getTail() const{
		return tail;
	}

	// Insertion
	void addHead(const T& data){
		if(count == 0) {
			Node* temp = new Node(data,nullptr,nullptr);
			head = temp;
			tail = temp;
			count++;
			return;
		}
		head->prev = new Node(data,nullptr,head);
		head = head->prev;
		count++;
	}

	void addTail(const T& data){
		if(count == 0) {
			Node* temp = new Node(data,nullptr,nullptr);
			head = temp;
			tail = temp;
			count++;
			return;
		}
		tail->next = new Node(data,tail,nullptr);
		tail = tail->next;
		count++;
	}

	// Removal
	bool removeHead(){
		if(count == 0){
			return false;
		}
		else if(count == 1){

			delete head;
			head = nullptr;
			tail = nullptr;
			count--;
			return true;

		}
		Node* temp = head;
		head = head->next;
		delete temp;
		head->prev = nullptr;
		count--;
		return true;

	}
	bool removeTail(){
		if(count == 0){
			return false;
		}
		else if(count == 1){

			delete head;
			head = nullptr;
			tail = nullptr;
			count--;
			return true;

		}
		Node* temp = tail;
		tail = tail->prev;
		delete temp;
		tail->next = nullptr;
		count--;
		return true;

	
	}
	void clear(){

		while(count !=0){
			removeHead();
		}

	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept{
		if(this == &other){
       return *this;
   }
       clear();
       head = other.head;
	   tail = other.tail;
	   count = other.count;

       other.head = nullptr;
       other.tail = nullptr;
       other.count = 0;
       
       return *this;
	}
	LinkedList<T>& operator=(const LinkedList<T>& rhs){
		if(this == &rhs){
       return *this;
   }
    	clear();
		Node* temp = rhs.head;
    	while(temp != nullptr){
			addTail(temp->info);
			temp = temp->next;
		}

      
       return *this;
	

	}

	// Construction/Destruction
	LinkedList(){
	head = nullptr;
	tail = nullptr;
	count = 0;
	}

	LinkedList(const LinkedList<T>& list){
		head = nullptr;
		tail = nullptr;
		count = 0;

		Node* temp = list.head;

		while(temp != nullptr){
		addTail(temp->info);
		temp = temp->next;
		}
			
		//intialize head and tail before you addTail/addHead
	}
	LinkedList(LinkedList<T>&& other) noexcept{
		head = other.head;
		tail = other.tail;
		count = other.count;

		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	}

	~LinkedList(){
		clear();
		head = nullptr;
		tail = nullptr;
		count = 0;
	}


};


