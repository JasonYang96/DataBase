#ifndef MULTI_MAP
#define MULTI_MAP

#include <string>

class	MultiMap
{
private:
	class Node;
	class ValueNode;
public:	
	class	Iterator
	{
	public:
		Iterator()
		{
			m_cur = nullptr;
			m_valid = false;
		}
		Iterator(Node* root)
		{
			m_cur = root;
			if (root)
				m_valid = true;
			else
				m_valid = false;
		}

		//accessors
		std::string	 getKey()	const { return m_cur->m_key; }
		unsigned int getValue()	const { return m_cur->m_value; }
		bool		 valid()    const { return m_valid; }

		//mutators
		bool next();
		bool prev();

	private:
		Node*      m_cur;
		ValueNode* m_duplicate;
		bool	   m_valid;
	};

	MultiMap()
	{
		m_root = nullptr;
	}
	~MultiMap()
	{
		clear();
		delete m_root;
	}
	void	clear() { FreeTree(m_root); }
	void	insert(std::string	key, unsigned	int	value);
	Iterator	findEqual(std::string	key)	const;
	Iterator	findEqualOrSuccessor(std::string	key)	const;
	Iterator	findEqualOrPredecessor(std::string	key)	const;

private:
	//	To	prevent	Multimaps	from	being	copied	or	assigned,	declare	these	members	
	//	private	and	do	not	implement	them.	
	MultiMap(const	MultiMap&	other);
	MultiMap&	operator=(const	MultiMap&	rhs);

	Node* m_root;

	struct ValueNode
	{
		ValueNode(unsigned int value)
		{
			m_value = value;
			m_next = nullptr;
			m_prev = nullptr;
		}

		unsigned int m_value;
		ValueNode* m_next;
		ValueNode* m_prev;
	};

	struct Node
	{
		Node(std::string Key, unsigned int Value)
		{
			m_key = Key;
			m_value = Value;
			m_left = nullptr;
			m_right = nullptr;
			m_parent = nullptr;
			m_duplicates = nullptr;
		}
		~Node()
		{
			if (m_duplicates)
			{
				ValueNode* cur = m_duplicates;
				while (!m_duplicates)
				{
					ValueNode* temp = cur;
					cur = m_duplicates->m_next;
					delete temp;
				}
			}
		}

		std::string  m_key;
		unsigned int m_value;
		Node* m_left;
		Node* m_right;
		Node* m_parent;
		ValueNode* m_duplicates;
	};

	void FreeTree(Node* root)
	{
		if(!root)
			return;

		//deleting m_left and m_right
		FreeTree(root->m_left);
		FreeTree(root->m_right);

		//deleting m_duplicates
		while (root->m_duplicates != nullptr)
		{
			ValueNode* temp = root->m_duplicates->m_next;
			delete root->m_duplicates;
			root->m_duplicates = temp;
		}
	}
};

#endif