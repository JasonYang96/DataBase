#ifndef MULTI_MAP
#define MULTI_MAP

#include <string>

class	MultiMap
{
private:
	struct ValueNode
	{
		ValueNode(unsigned int value)
		{
			m_value = value;
			m_next = nullptr;
			m_prev = nullptr;
		}
		~ValueNode() {};

		unsigned int m_value;
		ValueNode* m_next;
		ValueNode* m_prev;
	};

	struct Node
	{
		Node(std::string Key, unsigned int Value)
		{
			m_key = Key;
			m_left = nullptr;
			m_right = nullptr;
			m_parent = nullptr;
			m_duplicates = new ValueNode(Value);
		}
		~Node()
		{
			if (m_duplicates)
			{
				ValueNode* cur = m_duplicates;
				while (cur)
				{
					ValueNode* temp = cur;
					cur = m_duplicates->m_next;
					delete temp;
				}
			}
		}

		std::string  m_key;
		Node* m_left;
		Node* m_right;
		Node* m_parent;
		ValueNode* m_duplicates;
	};

public:	
	class	Iterator
	{
	public:
		Iterator()
		{
			m_cur = nullptr;
			m_ValueNode = nullptr;
		}
		Iterator(Node* node)
		{
			m_cur = node;
			m_ValueNode = node->m_duplicates;
		}

		//accessors
		std::string	 getKey()		 const { return m_cur->m_key; }
		unsigned int getValue()		 const;
		bool		 valid()		 const;

		//mutators
		bool next();
		bool prev();

	private:
		Node*      m_cur;
		ValueNode* m_ValueNode;
	};

	MultiMap()
	{
		m_root = nullptr;
		isBegin = true;
		isEnd = true;
	}
	~MultiMap()
	{
		clear();
		delete m_root;
	}

	//mutators
	void	clear() { FreeTree(m_root); }
	void	insert(std::string	key, unsigned	int	value);

	//accessors
	Iterator	findEqual(std::string	key)	const;
	Iterator	findEqualOrSuccessor(std::string	key)	const;
	Iterator	findEqualOrPredecessor(std::string	key)	const;

private:
	//	To	prevent	Multimaps	from	being	copied	or	assigned,	declare	these	members	
	//	private	and	do	not	implement	them.	
	MultiMap(const	MultiMap&	other);
	MultiMap&	operator=(const	MultiMap&	rhs);
	Node* m_root;
	bool isBegin;
	bool isEnd;

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