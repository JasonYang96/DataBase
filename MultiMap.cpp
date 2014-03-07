#include "MultiMap.h"
using namespace std;

//Iterator Implementation

bool MultiMap::Iterator::next()
{
	if (!valid())
		return false;

	//check if any more duplicates
	if (m_duplicate != nullptr || m_duplicate->m_next != nullptr)
	{
		m_duplicate = m_duplicate->m_next;
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
	}
	//go to ancestor node
	else
	{
		while (m_cur->m_parent->m_left != m_cur)
		{
			m_cur = m_cur->m_parent;

			//when m_cur == nullptr, iterator has
			//gone through the whole tree
			if (!m_cur)
			{
				m_valid = false;
				return false;
			}
		}

		//m_cur is now on node before next node
		m_cur = m_cur->m_parent;
	}

	return true;
}

bool MultiMap::Iterator::prev()
{
	if (!valid())
		return false;

	//check if any more duplicates
	if (m_duplicate != nullptr || m_duplicate->m_prev != nullptr)
	{
		m_duplicate = m_duplicate->m_prev;
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
	}
	//go to ancestor node
	else
	{
		while (m_cur->m_parent->m_right != m_cur)
		{
			m_cur = m_cur->m_parent;

			//when m_cur == nullptr, iterator has
			//gone through the whole tree
			if (!m_cur)
			{
				m_valid = false;
				return false;
			}
		}

		//m_cur is now on node before next node
		m_cur = m_cur->m_parent;
	}

	return true;
}

void MultiMap::insert(string key, unsigned int value)
{
	if (!m_root)
	{
		m_root = new Node(key, value);
		return;
	}

	Node* cur = m_root;
	for (;;)
	{
		if (key == cur->m_key)
		{
			ValueNode* temp = cur->m_duplicates;
			while (temp)
			{
				temp = temp->m_next;
			}
			temp = new ValueNode(value);

		}
		else if (key < cur->m_key)
		{
			if (cur->m_left != nullptr)
			{
				cur = cur->m_left;
			}
			else
			{
				cur->m_left = new Node(key, value);
				return;
			}
		}
		else if (key > cur->m_key)
		{
			if (cur->m_right != nullptr)
			{
				cur = cur->m_right;
			}
			else
			{
				cur->m_right = new Node(key, value);
				return;
			}
		}
	}
}