#ifndef MULTI_MAP
#define MULTI_MAP

#include <string>

class Node;

class	MultiMap
{
public:	
	class	Iterator
	{
	public:
		Iterator()
		{
			m_cur = m_parent = nullptr;
			m_valid = false;
		}
		Iterator(Node* root)
		{
			m_parent = nullptr;
			m_cur = root;
			if (root)
				m_valid = true;
			else
				m_valid = false;
		}

		//accessors
		std::string	getKey()	const;
		unsigned int	getValue()	const;
		bool	valid()	const;

		//mutators
		bool	next();
		bool	prev();

	private:
		Node* m_cur;
		Node* m_parent;
		bool  m_valid;
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
	void	clear();
	void	insert(std::string	key, unsigned	int	value);
	Iterator	findEqual(std::string	key)	const;
	Iterator	findEqualOrSuccessor(std::string	key)	const;
	Iterator	findEqualOrPredecessor(std::string	key)	const;

private:
	//	To	prevent	Multimaps	from	being	copied	or	assigned,	declare	these	members	
	//	private	and	do	not	implement	them.	
	MultiMap(const	MultiMap&	other);
	MultiMap&	operator=(const	MultiMap&	rhs);

	struct ValueNode
	{
		ValueNode(unsigned int value)
		{
			m_value = value;
			next = nullptr;
		}

		unsigned int m_value;
		ValueNode* next;
	};

	struct Node
	{
		Node(std::string Key, unsigned int Value)
		{
			m_key = Key;
			m_value = Value;
			m_left = nullptr;
			m_right = nullptr;
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
					cur = m_duplicates->next;
					delete temp;
				}
			}
		}

		std::string  m_key;
		unsigned int m_value;
		Node* m_left;
		Node* m_right;
		ValueNode* m_duplicates;
	};
	Node* m_root;

	void FreeTree(Node* root)
	{
		if(!root)
			return;

		FreeTree(root->m_left);
		FreeTree(root->m_right);

		delete root;
	}
};

#endif