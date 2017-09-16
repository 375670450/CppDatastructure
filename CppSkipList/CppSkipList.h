#ifndef _CPPSKIPLIST_H
#define _CPPSKIPLIST_H

#include <iostream>
#include <memory>
#include <algorithm>
#include <list>
#include <vector>
#include <random>

/*
	Type: The type of stored data
	Comparator: the compare method to judge if a < b, must be a class with the operator ().
*/
template <typename Type, class Comparator = std::less<Type>>
class SkipList {
private:
	/*
		Constants
	*/
public:

	const static size_t MaxLevel = 12;

	struct NodeStruct;

	typedef std::shared_ptr<NodeStruct> NodePtr;

	typedef struct NodeStruct {

		Type val;

		NodePtr nexts[MaxLevel];

	} Node;

	SkipList ( ) {
		_header = _createNodePtr();
	}

	bool Insert (const Type & val) {
		auto newNode = _createNodePtr (val);
		auto cur = _header;									
		NodePtr updateNexts[ MaxLevel], tmp;		// updateNests[i] = p indicated the pointer p at level i should be update

		// find a proper position to insert the new 
		for ( int i = _level-1; i >= 0; i-- ) {		// search from the top level
			while ( ( tmp = cur->nexts[i] ) != nullptr
				   && _less (tmp->val, val) ) {		// traversal to find a position to insert val.
				cur = tmp;					
			}
			updateNexts[i] = cur;						// the new node will be inserted after cur, thus the cur	will be update			
		}

		if ( tmp != nullptr && tmp->val == val ) {	// if the skiplist has the same value inserted, return
			return false;										// if there exists val, insertion failed, return false
		}

		auto rand_level = _randLevel ( );
		//std::cout << "rand level = " << rand_level << ", value = " << val << "\n";

		if ( rand_level > this->_level ) {			// if the new node is to be inserted at a new empty level
			for ( int i = this->_level; i < rand_level; i++ ) {	// the header->nexts of the new levels should be update
				updateNexts[i] = _header;
			}
			this->_level = rand_level;					// update level of this skiplist
		}

		for ( int i = 0; i < rand_level; i++ ) {		// update the pointers of some nodes
			newNode->nexts[i] = updateNexts[i]->nexts[i];
			updateNexts[i]->nexts[i] = newNode;
		}
		_size++;

		return true;											// if inserted successfully, return true
	}


	bool Delete (const Type & val) {

		NodePtr updateNexts[ MaxLevel], tmp;		// updateNests[i] = p indicated the pointer p at level i should be update
		auto cur = _header;

		for ( int i = _level-1; i >= 0; i-- ) {		// search from the top level
			while ( ( tmp = cur->nexts[i] ) != nullptr
				   && _less (tmp->val, val) ) {		// traversal to find the val to delete.
				cur = tmp;					
			}
			updateNexts[i] = cur;						// the node after cur will be delete, thus the cur	will be update			
		}
		if ( tmp != nullptr && tmp->val == val ) {		// if has found

			for ( int i = 0; i < this->_level; i++ ) {
				if ( updateNexts[i]->nexts[i] == tmp ) {		// delete node and update pointers
					updateNexts[i]->nexts[i] = tmp->nexts[i];
				}
			}

			for ( int i = this->_level - 1; i >= 0; i-- ) {	// clear the empty level
				if ( _header->nexts[i] == nullptr )			// if this level has no nodes
					this->_level--;									
			}

			_size--;
			return true;

		} else {																	// cannot find the node to be delete
			return false;
		}
	}

	bool Search (const Type & val) const {		// if contains val return true, otherwise return false
		auto cur = this->_header;
		NodePtr tmp;

		for ( int i = _level-1; i >= 0; i-- ) {		// search from the top level
			while ( ( tmp = cur->nexts[i] ) != nullptr
				   && _less (tmp->val, val) ) {		// traversal to find the val.
				cur = tmp;					
			}
		}

		if ( tmp != nullptr && tmp->val == val )		// if the val has found
			return true;
		else
			return false;												// if cannot find the val, return false

	}

	size_t Size ( ) const {											// return the node amount of the skiplist
		return _size;
	}

	size_t Level ( ) const {													// return the current height of skiplist
		return _level;
	}

	void Print ( ) const {				// print the structure of skiplist level by level
		
		std::cout << "level = " << this->_level << "\n";
		for ( size_t level = 0; level < this->_level; level++ ) {
			std::cout << level << ": ";
			for ( auto cur = _header->nexts[level]; cur != nullptr; cur = cur->nexts[level] ) {
				std::cout << cur->val << ( cur->nexts[level] == nullptr ? "\n" : "-> " );
			}
		}
		return;
	}

private:

	NodePtr _header;								// empty node

	size_t _level = 0;

	size_t _size = 0;

	Comparator _less;								// the function(actually an object) to be invoked to compare elements

	NodePtr _createNodePtr (Type val = {}) {		// create a new node within value val, {} get default values of any type
		NodePtr newPtr = std::make_shared<Node> ();
		newPtr->val = val;
		for ( int i = 0; i <  MaxLevel; i++ )
			newPtr->nexts[i] = nullptr;
		
		return newPtr;
	}

	size_t _randLevel ( ) {										// generate a random number to be the level of a new node

		static std::default_random_engine engine{ std::random_device{ } ( ) };
		static std::uniform_int_distribution<size_t> u;
		
		size_t level = 1;
		while ( u (engine) % 2 ) {
			level++;
		}
//		std::cout << level << std::endl; 
		return level < MaxLevel ? level : MaxLevel;
	}

};


#endif //_CPPSKIPLIST_H
