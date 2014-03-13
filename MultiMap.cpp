#include "MultiMap.h"
using namespace std;

//Iterator Implementation

bool MultiMap::Iterator::next()
{
	//checking if valid
	if (!valid())
		return false;

	//check if any duplicates
	if (m_ValueNode->m_next)
	{
		m_ValueNode = m_ValueNode->m_next;
	}
	//check if any right node
	else if (m_cur->m_right != nullptr)
	{
		m_cur = m_cur->m_right;
		//check if any left node
		if (m_cur->m_left != nullptr)
		{
			//go to left most node
			while (m_cur->m_left != nullptr)
			{
				m_cur = m_cur->m_left;
			}
		}

		//set value
		m_ValueNode = m_cur->m_duplicates;
	}
	//go to ancestor node
	else
	{
		//looking for first parent whose left child is cur
		while (m_cur->m_parent != nullptr && m_cur->m_parent->m_left != m_cur)
		{
			m_cur = m_cur->m_parent;
		}

		//when m_cur->m_parent == nullptr, iterator has
		//gone through the whole tree and is on root node
		if (m_cur->m_parent == nullptr)
		{
			m_cur = nullptr;
			m_ValueNode = nullptr;
			return false;
		}

		//m_cur is now on node before next node
		m_cur = m_cur->m_parent;

		//set value
		m_ValueNode = m_cur->m_duplicates;
	}

	return true;
}

bool MultiMap::Iterator::prev()
{
	//checking if valid
	if (!valid())
		return false;

	//check if any duplicates
	if (m_ValueNode->m_prev)
	{
		m_ValueNode = m_ValueNode->m_prev;
	}
	//check if any left node
	else if (m_cur->m_left != nullptr)
	{
		m_cur = m_cur->m_left;
		//check if any right node
		if (m_cur->m_right != nullptr)
		{
			//go to right most node
			while (m_cur->m_right != nullptr)
			{
				m_cur = m_cur->m_right;
			}
		}

		//set value
		m_ValueNode = m_cur->m_duplicates;
		while (m_ValueNode->m_next)
		{
			m_ValueNode = m_ValueNode->m_next;
		}
	}
	//go to ancestor node
	else
	{
		//looking for first parent whose right child is cur
		while (m_cur->m_parent != nullptr && m_cur->m_parent->m_right != m_cur)
		{
			m_cur = m_cur->m_parent;
		}

		//when m_cur->m_parent == nullptr, iterator has
		//gone through the whole tree and is on root node
		if (m_cur->m_parent == nullptr)
		{
			m_cur = nullptr;
			m_ValueNode = nullptr;
			return false;
		}

		//m_cur is now on node before next node
		m_cur = m_cur->m_parent;

		//set value
		m_ValueNode = m_cur->m_duplicates;
		while (m_ValueNode->m_next)
		{
			m_ValueNode = m_ValueNode->m_next;
		}
	}

	return true;
}

//MultiMap Implementation

void MultiMap::insert(string key, unsigned int value)
{
	//if empty, insert root node
	if (!m_root)
	{
		m_root = new Node(key, value);
		return;
	}

	Node* cur = m_root;
	for (;;)
	{
		//if key already exists
		if (key == cur->m_key)
		{
			//add ValueNode*
			ValueNode* temp = cur->m_duplicates;
			while (temp->m_next)
			{
				temp = temp->m_next;
			}
			temp->m_next = new ValueNode(value);
			temp->m_next->m_prev = temp;
			return;
		}
		else if (key < cur->m_key)
		{
			//traverse left child
			if (cur->m_left != nullptr)
			{
				cur = cur->m_left;
			}
			//if not there, create left child
			else
			{
				cur->m_left = new Node(key, value);
				cur->m_left->m_parent = cur;
				return;
			}
		}
		else if (key > cur->m_key)
		{
			//traverse right child
			if (cur->m_right != nullptr)
			{
				cur = cur->m_right;
			}
			//if not there, create right child
			else
			{
				cur->m_right = new Node(key, value);
				cur->m_right->m_parent = cur;
				return;
			}
		}
	}
}

MultiMap::Iterator MultiMap::findEqual(string key) const
{
	Iterator temp(m_root);
	Iterator prev;
	while (temp.valid())
	{
		//check prev node
		temp.prev();
		if (temp.valid())
		{
			prev = temp;
			temp.next();
		}
		else
		{
			temp = prev;
			prev.prev();
		}
		if (temp.getKey() == key)
		{
			//making sure points to first ValueNode*
			if (prev.valid() && temp.getKey() == prev.getKey())
			{
				temp.prev();
			}
			else
				return temp;
		}
		else if (key > temp.getKey())
		{
			temp.next();
		}
		else if (key < temp.getKey())
		{
			temp.prev();
		}
	}
	Iterator invalid;
	return invalid;
}

MultiMap::Iterator	MultiMap::findEqualOrSuccessor(string key) const
{
	Iterator temp(m_root);
	Iterator prev;
	Iterator next;
	while (temp.valid())
	{
		//checking next Node
		temp.next();
		if (temp.valid())
		{
			next = temp;
			temp.prev();
		}
		else
		{
			Iterator invalid;
			return invalid;
		}
		if (next.valid() && temp.getKey() == key)
		{
			//checking prev Node
			temp.prev();
			if (temp.valid())
			{
				prev = temp;
				temp.next();
			}
			else
			{
				temp = prev;
				prev.prev();
			}
			//making sure points to first ValueNode*
			if (prev.valid() && temp.getKey() == prev.getKey())
			{
				temp.prev();
			}
			else
				return temp;
		}
		else if (key > temp.getKey())
		{
			temp.next();
			//make sure returns successor
			if (temp.getKey() > key)
			{
				return temp;
			}
		}
		else if (key < temp.getKey())
		{
			Iterator after = temp;
			temp.prev();
			//make sure return predecesor
			if (temp.getKey() < key)
			{
				return after;
			}
		}
	}

	//if not found, return invalid Iterator
	Iterator invalid;
	return invalid;
}

MultiMap::Iterator MultiMap::findEqualOrPredecessor(string key)	const
{
	Iterator temp(m_root);
	Iterator prev;
	Iterator next;
	while (temp.valid())
	{
		//checking next Node
		temp.next();
		if (temp.valid())
		{
			next = temp;
			temp.prev();
		}
		else
		{
			temp = next;
			return temp;
		}
		if (temp.getKey() == key)
		{
			//make sure last ValueNode*
			if (next.valid() && temp.getKey() == next.getKey())
			{
				temp.next();
			}
			else
				return temp;
		}
		else if (key > temp.getKey())
		{
			Iterator before = temp;
			temp.next();
			//make sure return predecessor
			if (temp.getKey() > key)
			{
				return before;
			}
		}
		else if (key < temp.getKey())
		{
			//check prev ValueNode*
			temp.prev();
			if (temp.valid())
			{
				prev = temp;
				temp.next();
			}
			else
			{
				Iterator invalid;
				return invalid;
			}
			if (temp.getKey() < key)
			{
				return prev;
			}
		}
	}

	//if not found, return invalid Iterator
	Iterator invalid;
	return invalid;
}