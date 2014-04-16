/*
 * HashMap.h
 *
 *  Created on: Mar 23, 2014
 *      Author: 	Chandra Thara Chandrika
 *      Student ID: 82878
 */

#ifndef HASHMAP_H_
#define HASHMAP_H_

#include <iostream>
#include <string>

using namespace std;

class DoublyLinkedListNode {//Node class for DoublyLinkedList
	public:
		DoublyLinkedListNode *prev, *next;
		DoublyLinkedListNode() { //constructor with no arg
			prev = next = NULL;
		}
};

class DoublyLinkedList {//class for DoublyLinkedList
	private:
		long int count;
	public:
		DoublyLinkedListNode *head, *tail;
		DoublyLinkedList() {
			count = 0;
			head = tail = NULL;
		}
		int getSize() { //function to get the no.of slots in the hash map
			return count;
		}

		DoublyLinkedListNode * createNode(){//function to allocate memory for new node
			DoublyLinkedListNode * pNode = new DoublyLinkedListNode();
			return pNode;
		}

		DoublyLinkedListNode * insert(DoublyLinkedListNode * pNode) { //insert new node

			if (count == 0) {     //if list is empty
				head = pNode;        //make head point to pNode
				pNode->prev = NULL;
			}
			else {
				tail->next = pNode;  //make tail point to pNode
				pNode->prev = tail;
			}
			tail = pNode;        //tail is now pNode
			pNode->next = NULL;  //pNode next now points to NULL
			count++;
			return pNode;
		}

		void del(DoublyLinkedListNode *pNode) {
			if (pNode == NULL)
				return;

			if (pNode->prev == NULL)  //if removing the head
				head = pNode->next;
			else
				pNode->prev->next = pNode->next;  //if removing a middle node

			if (pNode->next == NULL)  //if removing the tail
				tail = pNode->prev;
			else
				pNode->next->prev = pNode->prev;
			delete pNode;  //*free the memory
			pNode = NULL;
			count--;
		}

};

template <class Data> class DoublyLinkedListDataNode : public DoublyLinkedListNode  {//DataNode class for DoublyLinkedList
	public:
		Data nodedata;
};


template <class Slot, class Data> class DoublyLinkedListSlotNode : public DoublyLinkedListNode, public DoublyLinkedList {
	public:
		Slot slot;

		void del(Data x) {
			DoublyLinkedList::del(findSlot(x));
		}

		DoublyLinkedListDataNode<Data> * findSlot(Data x) {
			DoublyLinkedListDataNode<Data> * pNode;
			for (pNode = (DoublyLinkedListDataNode<Data> *)head; pNode != NULL; pNode = (DoublyLinkedListDataNode<Data> *)pNode->next) {
				if (pNode->nodedata == x) {
					return pNode;
				}
			}
			return NULL;
		}
		DoublyLinkedListDataNode<Data> * getHeadData() {
			return (DoublyLinkedListDataNode<Data> *) head;
		}
};


template <class Slot, class Data> class HashMap : public DoublyLinkedList { //class for HashMap
	public:
		DoublyLinkedListSlotNode<Slot, Data> * createNode() {
			DoublyLinkedListSlotNode<Slot, Data> * pNode = new DoublyLinkedListSlotNode<Slot, Data>(); //allocate memory for new node
			return pNode;
		}
		DoublyLinkedListNode * insert(Slot s) {
			DoublyLinkedListSlotNode<Slot, Data> * doublyLinkedListSlotNode = (DoublyLinkedListSlotNode<Slot, Data> *)DoublyLinkedList::insert(findSlot(s, true));
			doublyLinkedListSlotNode->slot = s;
			return doublyLinkedListSlotNode;
		}

		void insert(Slot s, Data x) {
			DoublyLinkedListSlotNode<Slot, Data> * doublyLinkedListSlotNode = findSlot(s, false);
			DoublyLinkedListDataNode<Data> * data = (DoublyLinkedListDataNode<Data> *)doublyLinkedListSlotNode->insert(new DoublyLinkedListDataNode<Data>());
			data->nodedata = x;
		}

		void del(Slot s) {
			DoublyLinkedList::del(findSlot(s, false));
		}

		void del(Slot s, Data x) {
			DoublyLinkedListSlotNode<Slot, Data> * pNode = findSlot(s, false);
			pNode->del(x);
		}

		DoublyLinkedListSlotNode<Slot, Data> * findSlot(Slot s) {
			return findSlot(s, false);
		}
		DoublyLinkedListSlotNode<Slot, Data> * getHeadSlot() {
			return (DoublyLinkedListSlotNode<Slot, Data> *) head;
		}
		DoublyLinkedListNode * get (Slot *s) {
			DoublyLinkedListSlotNode<Slot, Data> * doublyLinkedListSlotNode = findSlot(*s, false);
			return doublyLinkedListSlotNode->head;
		}
		DoublyLinkedListSlotNode<Slot, Data> * currSlotNode;
		DoublyLinkedListDataNode<Data> * currDataNode;
	private:
		DoublyLinkedListSlotNode<Slot, Data> * findSlot(Slot s, bool createNew) {

			DoublyLinkedListSlotNode<Slot, Data> * pNode;
			for (pNode = (DoublyLinkedListSlotNode<Slot, Data> *)head; pNode != NULL; pNode = (DoublyLinkedListSlotNode<Slot, Data> *)pNode->next) {
				if (pNode->slot == s) {
					return pNode;
				}
			}
			if (createNew)
				return createNode();
			else
				return NULL;
		}
};



#endif /* HASHMAP_H_ */
