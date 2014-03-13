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
		~ValueNode()
		{
			if (m_next)
				delete m_next;
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
			m_left = nullptr;
			m_right = nullptr;
			m_parent = nullptr;
			m_duplicates = new ValueNode(Value);
		}
		~Node()
		{
			delete m_duplicates;
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
		std::string	 getKey()   const { return m_cur->m_key; }
		unsigned int getValue() const { return m_ValueNode->m_value; }
		bool		 valid()    const
		{
			if (!m_cur) //invalid
				return false;
			else //valid
				return true;
		}

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
	}
	~MultiMap()
	{
		clear();
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

	void FreeTree(Node* root)
	{
		if(root == nullptr)
			return;

		//deleting m_left and m_right
		FreeTree(root->m_left);
		FreeTree(root->m_right);

		delete root;
	}
};

#endif //MULTI_MAP included