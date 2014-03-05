#include "MultiMap.h"
using namespace std;

bool MultiMap::Iterator::valid() const
{
	return m_valid;
}

bool MultiMap::Iterator::next()
{
	if (!valid())
		return false;

	if (!m_cur)
	{
		m_valid = false;
		return false;
	}

	return true;
}

void MultiMap::clear()
{
	FreeTree(m_root);
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
			ValueNode* duplicate = new ValueNode(value);
			ValueNode* temp = cur->m_duplicates;
			while (temp)
			{
				temp = temp->next;
			}
			temp = duplicate;

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