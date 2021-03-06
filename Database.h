#ifndef DATABASE
#define DATABASE

#include "MultiMap.h"
#include <string>
#include <vector>

class	Database
{
public:
	enum	IndexType	{ it_none, it_indexed };
	enum	OrderingType	{ ot_ascending, ot_descending };

	struct	FieldDescriptor
	{
		std::string	name;
		IndexType	index;
	};

	struct	SearchCriterion
	{
		std::string	fieldName;
		std::string	minValue;
		std::string	maxValue;
	};

	struct	SortCriterion
	{
		std::string	fieldName;
		OrderingType	ordering;
	};

	static	const	int	ERROR_RESULT = -1;

	Database();
	~Database();
	bool	specifySchema(const	std::vector<FieldDescriptor>&	schema);
	bool	addRow(const	std::vector<std::string>&	rowOfData);
	bool	loadFromURL(std::string	url);
	bool	loadFromFile(std::string	filename);
	int		getNumRows()	const { return (int)m_rows.size(); }
	bool	getRow(int	rowNum, std::vector<std::string>&	row)	const;
	int		search(const	std::vector<SearchCriterion>&	searchCriteria,
		const	std::vector<SortCriterion>&	sortCriteria,
		std::vector<int>&	results);

private:
	//	To	prevent	Databases	from	being	copied	or	assigned,	declare	these	members	
	//	private	and	do	not	implement	them.	
	Database(const	Database&	other);
	Database&	operator=(const	Database&	rhs);
	std::vector<FieldDescriptor*> m_schema;
	std::vector<std::vector<std::string> > m_rows;
	std::vector<MultiMap*> m_fieldIndex;
};

#endif //DATABASE included