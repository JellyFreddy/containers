#ifndef TREES_H
# define TREES_H

# include "iterators_utils.hpp"
# include <iomanip>
# include <iostream>

namespace ft {

	template<class T, class Z, class Allocator>
	class TreeNode {
	private:
		typedef T   		value_type;
		typedef const Z   	key_type;
		ft::pair<const key_type, value_type> *_data;
		int         		_height;
		Allocator 			_allocator;
		bool 				_isDummy;
		TreeNode<T, Z, Allocator>    *_left_child;
		TreeNode<T, Z, Allocator>   *_right_child;
		TreeNode<T, Z, Allocator>    *_parent;
	public:
		TreeNode(key_type key, value_type value, Allocator allocator = Allocator()) : _height(0),
		_parent(nullptr), _left_child(nullptr), _right_child(nullptr), _allocator(allocator) {
			_data = _allocator.allocate(1);
			_allocator.construct(_data, ft::pair<key_type, value_type>(key, value));
		};
		TreeNode(TreeNode & other) {
			_allocator = other._allocator;
			_isDummy = other._isDummy;
			if (!_isDummy) {
				_data = _allocator.allocate(1);
				_allocator.construct(_data, ft::pair<key_type, value_type>(other.getKey(), other.getValue()));
			}
			_height = other.getHeight();
			_parent = other.getParent();
			_left_child = other.getLeftChild();
			_right_child = other.getRightChild();
		}
		TreeNode() : _height(0), _parent(nullptr), _left_child(nullptr), _right_child(nullptr), _isDummy(true) {};
		~TreeNode() {
			if (_isDummy == false) {
				_allocator.destroy(&(*_data));
				_allocator.deallocate(_data, 1);
			}
		}
		int         getBalance() {
			if(_left_child == nullptr) {
				if (_right_child == nullptr)
					return (0);
				return ((-1) * (_right_child->getHeight()) - 1);
			}
			else if (_right_child == nullptr)
				return (_left_child->getHeight() + 1);
			else
				return (_left_child->getHeight() - _right_child->getHeight());
		};
		void change_value(value_type val) {
			key_type key = _data->first;
			_allocator.destroy(_data);
			_allocator.construct(_data, ft::pair<key_type, value_type>(key, val));
		}
		key_type  getKey() {
			return (_data->first);
		};
		value_type & getValue() {
			return (_data->second);
		};
		ft::pair<const key_type, value_type> * getData() {
			return (_data);
		};
		int         getHeight() {
			return (_height);
		};
		TreeNode    *getLeftChild() {
			return (_left_child);
		};
		TreeNode    *getRightChild() {
			return (_right_child);
		};
		TreeNode    *getParent() {
			return (_parent);
		};
		void        removeParent() {
			_parent = nullptr;
		};
		TreeNode    *setLeftChild(TreeNode *newLeft) {
			if (newLeft != nullptr)
				newLeft->_parent = this;
			_left_child = newLeft;
			updateHeight();
			return (_left_child);
		};
		TreeNode    *setRightChild(TreeNode *newRight) {
			if (newRight != nullptr)
				newRight->_parent = this;
			_right_child = newRight;
			updateHeight();
			return (_right_child);
		};
		int         updateHeight() {
			if (_left_child == nullptr) {
				if (_right_child == nullptr)
					_height = 0;
				else
					_height = _right_child->getHeight() + 1;
			}
			else if (_right_child == nullptr)
				_height = _left_child->getHeight() + 1;
			else if (_left_child->getHeight() > _right_child->getHeight())
				_height = _left_child->getHeight() + 1;
			else
				_height = _right_child->getHeight() + 1;
			return (_height);
		};
	};

	template<class T,class Z, class Compare, class Allocator>
	class AVLTree {
	private:
		typedef T               key_type;
		typedef Z               value_type;
		TreeNode<value_type, key_type, Allocator>    	*_root;
		Compare								_comparator;

		void                    balanceAtNode(TreeNode<value_type, key_type, Allocator> *n) {
			if (n->getBalance() > 1) {
				if (n->getLeftChild()->getBalance() < 0)
					rotateLeft(n->getLeftChild());
				rotateRight(n);
			}
			else if (n->getBalance() < -1) {
				if (n->getRightChild()->getBalance() > 0)
					rotateRight(n->getRightChild());
				rotateLeft(n);
			}
		};
		void                    rotateLeft(TreeNode<value_type, key_type, Allocator> *n) {
			int side = -1;
			const int LEFT = 0;
			const int RIGHT = 1;
			TreeNode<value_type, key_type, Allocator> *p = n->getParent();
			if (p != nullptr && p->getLeftChild() == n)
				side = LEFT;
			else
				side = RIGHT;
			TreeNode<value_type, key_type, Allocator> *temp = n->getRightChild();
			n->setRightChild(temp->getLeftChild());
			temp->setLeftChild(n);

			if (p == nullptr)
				setRoot(temp);
			else if (side == LEFT)
				p->setLeftChild(temp);
			else
				p->setRightChild(temp);
		};
		void                    rotateRight(TreeNode<value_type, key_type, Allocator> *n) {
			int side = -1;
			const int LEFT = 0;
			const int RIGHT = 1;
			TreeNode<value_type, key_type, Allocator> *p = n->getParent();
			if (p != nullptr && p->getLeftChild() == n)
				side = LEFT;
			else
				side = RIGHT;
			TreeNode<value_type, key_type, Allocator> *temp = n->getLeftChild();
			n->setLeftChild(temp->getRightChild());
			temp->setRightChild(n);

			if (p == nullptr)
				setRoot(temp);
			else if (side == LEFT)
				p->setLeftChild(temp);
			else
				p->setRightChild(temp);
		};
		void                    setRoot(TreeNode<value_type, key_type, Allocator> *n) {
			_root = n;
  			if (_root != nullptr)
				_root->removeParent();
		};
	public:
		TreeNode<value_type, key_type, Allocator>    *findNode(key_type key) {
			TreeNode<value_type, key_type, Allocator> *temp = _root;
			while (temp != nullptr) {
				if (!_comparator(key, temp->getKey()) && !_comparator(temp->getKey(), key))
					break;
				else if (key < temp->getKey())
					temp = temp->getLeftChild();
				else
					temp = temp->getRightChild();
			}
			return (temp);
		};
		AVLTree() : _root(nullptr) {};
		AVLTree(key_type key, value_type val, Compare comparator) : _root(key, val),
		_comparator(comparator) {};
		~AVLTree() {};
		int getHeight() { return (_root->getHeight()); };
		bool insert(key_type key, value_type val) {
			if (_root == nullptr) {
				_root = new TreeNode<value_type, key_type, Allocator>(key, val);
			}
			else {
				TreeNode<value_type, key_type, Allocator> *added_node = nullptr;
				TreeNode<value_type, key_type, Allocator> *temp = _root;
				while(temp != nullptr && added_node == nullptr) {
					if (_comparator(key, temp->getKey())) {
						if (temp->getLeftChild() == nullptr) {
							added_node = temp->setLeftChild(new TreeNode<value_type, key_type, Allocator>(key, val));
						}
						else
							temp = temp->getLeftChild();
					}
					else if (_comparator(temp->getKey(), key)) {
						if (temp->getRightChild() == nullptr) {
							added_node = temp->setRightChild(new TreeNode<value_type, key_type, Allocator>(key, val));
						}
						else
							temp = temp->getRightChild();
					}
					else {
						temp->change_value(val);
						return true;
					}
				}
				temp = added_node;
				while(temp != nullptr) {
					temp->updateHeight();
					balanceAtNode(temp);
					temp = temp->getParent();
				}
			}
			return (true);
		};
		bool remove(key_type key) {
			TreeNode<value_type, key_type, Allocator> *nodeToBeRemoved = findNode(key);
			int side = -1;
			const int LEFT = 0;
			const int RIGHT = 1;
			
			if (nodeToBeRemoved == nullptr)
				return (false);

			TreeNode<value_type, key_type, Allocator> *p = nodeToBeRemoved->getParent();
			if (p != nullptr && p->getLeftChild() == nodeToBeRemoved) {
				side = LEFT;
			}
			else {
				side = RIGHT;
			}

			
			if (nodeToBeRemoved->getLeftChild() == nullptr) {
				if (nodeToBeRemoved->getRightChild() == nullptr) {
					if (p == nullptr) {
						setRoot(nullptr);
						delete nodeToBeRemoved;
					}
					else {
						if (side == LEFT)
							p->setLeftChild(nullptr);
						else
							p->setRightChild(nullptr);
						delete nodeToBeRemoved;
						p->updateHeight();
						balanceAtNode(p);
					}
				}
				else {
					if (p == nullptr) {
						setRoot(nodeToBeRemoved->getRightChild());
						delete nodeToBeRemoved;
					}
					else {
						if (side == LEFT)
							p->setLeftChild(nodeToBeRemoved->getRightChild());
						else
							p->setRightChild(nodeToBeRemoved->getRightChild());
						delete nodeToBeRemoved;
						p->updateHeight();
						balanceAtNode(p);
					}
				}
			}
			else if (nodeToBeRemoved->getRightChild() == nullptr) {
				if (p == nullptr) {
					setRoot(nodeToBeRemoved->getLeftChild());
					delete nodeToBeRemoved;
				}
				else {
					if (side == LEFT)
						p->setLeftChild(nodeToBeRemoved->getLeftChild());
					else
						p->setRightChild(nodeToBeRemoved->getLeftChild());
					delete nodeToBeRemoved;
					p->updateHeight();
					balanceAtNode(p);
				}
			}
			else {
				TreeNode<value_type, key_type, Allocator> *replacement;
				TreeNode<value_type, key_type, Allocator> *replacement_parent;
				TreeNode<value_type, key_type, Allocator> *temp_node;
				int bal = nodeToBeRemoved->getBalance();
				if (bal > 0) {
					if (nodeToBeRemoved->getLeftChild()->getRightChild() == nullptr) {
						replacement = nodeToBeRemoved->getLeftChild();
						replacement->setRightChild(nodeToBeRemoved->getRightChild());
						temp_node = replacement;
					}
					else {
						replacement = nodeToBeRemoved->getLeftChild()->getRightChild();
						while(replacement->getRightChild() != nullptr)
							replacement = replacement->getRightChild();
						replacement_parent = replacement->getParent();
						replacement_parent->setRightChild(replacement->getLeftChild());
						temp_node = replacement_parent;
						replacement->setLeftChild(nodeToBeRemoved->getLeftChild());
						replacement->setRightChild(nodeToBeRemoved->getRightChild());
					}
				}
				else if (nodeToBeRemoved->getRightChild()->getLeftChild() == nullptr) {
					replacement = nodeToBeRemoved->getRightChild();
					replacement->setLeftChild(nodeToBeRemoved->getLeftChild());
					temp_node = replacement;
				}
				else {
					replacement = nodeToBeRemoved->getRightChild()->getLeftChild();
					while (replacement->getLeftChild() != nullptr)
						replacement = replacement->getLeftChild();
					replacement_parent = replacement->getParent();
					replacement_parent->setLeftChild(replacement->getRightChild());
					temp_node = replacement_parent;
					replacement->setLeftChild(nodeToBeRemoved->getLeftChild());
					replacement->setRightChild(nodeToBeRemoved->getRightChild());
				}

				if (p == nullptr)
					setRoot(replacement);
				else if (side == LEFT)
					p->setLeftChild(replacement);
				else
					p->setRightChild(replacement);
				delete nodeToBeRemoved;
				balanceAtNode(temp_node);
			}
			return true;
		};
		TreeNode<value_type, key_type, Allocator> *getLastElem() {
			TreeNode<value_type, key_type, Allocator> *temp = _root;

			while(temp != nullptr && temp->getRightChild() != nullptr) {
				temp = temp->getRightChild();
			}
			return temp;
		}
		TreeNode<value_type, key_type, Allocator> *getFirstElem() const {
			TreeNode<value_type, key_type, Allocator> *temp = _root;


			while(temp != nullptr && temp->getLeftChild() != nullptr) {
				temp = temp->getLeftChild();
			}
			return temp;
		}
		int spacing(int level) {
			int result = 2;
			for (int i = 0; i < level; i++)
				result += result;
			return result;
		}
		void printSubtree(TreeNode<value_type, key_type, Allocator> *subtree, int depth,
								   int level, bool first) {

			if (depth > 0) {
				if (subtree == nullptr) {
					printSubtree(subtree, depth-1, level, first);
					printSubtree(subtree, depth-1, level, false);
				} else {
					printSubtree(subtree->getLeftChild(), depth-1,
								 level, first);
					printSubtree(subtree->getRightChild(), depth-1,
								 level, false);
				} // if

			} else if (subtree == nullptr)
				std::cout << std::setw((first)?
				spacing(level)/2:spacing(level)) << "-";

			else
				std::cout << std::setw((first)?
				spacing(level)/2:spacing(level)) <<
				subtree->getKey();
		}
		void print() {

			// If the tree is empty, say so.
			if (_root == nullptr)
				std::cout << "Tree is empty!" <<
				std::endl;

			// Otherwise, if the tree has a height more than 4
			// (5 rows), it is too wide.
			else if (_root->getHeight() > 4)
				std::cout << "Not currently supported!" <<
				std::endl;

			// Otherwise, set up to display the tree. Get
			// the maximum depth and for each possible
			// level, output that level's elements and
			// finish off the line.
			else {
				int max = _root->getHeight();
				for (int depth = 0; depth <= max; depth++) {
					printSubtree(_root, depth, max-depth+1, true);
					std::cout << std::endl;
				} // for
			} // if
		}
	};
}

#endif
