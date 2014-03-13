#include "Database.h"
#include <string>
using namespace std;

Database::Database()
{
}

Database::~Database()
{
	//clear m_rows
	m_rows.clear();
	//clear m_fieldIndexes
	for (size_t k = 0; k < m_fieldIndex.size(); k++)
	{
		delete m_fieldIndex[k];
	}
	m_fieldIndex.clear();
	//clear m_schema;
	for (size_t k = 0; k < m_schema.size(); k++)
	{
		delete m_schema[k];
	}
	m_schema.clear();
}

bool Database::specifySchema(const vector<FieldDescriptor>&	schema)
{
	//clear m_rows
	m_rows.clear();

	//clear m_fieldIndexes
	for (size_t k = 0; k < m_fieldIndex.size(); k++)
	{
		delete m_fieldIndex[k];
	}
	m_fieldIndex.clear();

	//clear m_schema;
	for (size_t k = 0; k < m_schema.size(); k++)
	{
		delete m_schema[k];
	}
	m_schema.clear();

	//checking if invalid schema
	if (schema.size() < 1)
		return false;

	//specify new schema
	for (size_t k = 0; k < schema.size(); k++)
	{
		FieldDescriptor* temp = new FieldDescriptor;
		temp->index = schema[k].index;
		temp->name = schema[k].name;
		m_schema.push_back(temp);
		MultiMap* map = new MultiMap;
		m_fieldIndex.push_back(map);
	}

	return true;
}

bool Database::addRow(const	vector<string>&	rowOfData)
{
	//checking for different number of values
	if (rowOfData.size() != m_schema.size())
		return false;
	
	//adding to m_row
	m_rows.push_back(rowOfData);

	//adding to m_fieldIndex	
	for (size_t k = 0; k < m_schema.size(); k++)
	{
		//if indexed, add to fieldIndexed
		if (m_schema[k]->index)
		{
			m_fieldIndex[k]->insert(rowOfData[k], m_rows.size() - 1);
		}
	}

	return true;
}

bool Database::loadFromURL(string url)
{
	return false;
}

bool Database::loadFromFile(string filename)
{
	return false;
}

bool Database::getRow(int rowNum, vector<string>& row)	const
{
	//checking invalid rowNum
	if (rowNum > getNumRows() || rowNum < 0)
		return false;

	//clearing any strings in row
	row.clear();

	//copying each string value into row
	for (size_t k = 0; k < m_rows[rowNum].size(); k++)
	{
		string temp = m_rows[rowNum][k];
		row.push_back(temp);
	}

	return true;
}

int	Database::search(const vector<SearchCriterion>&	searchCriteria,
	const vector<SortCriterion>& sortCriteria, vector<int>&	results)
{
	return 0;
}