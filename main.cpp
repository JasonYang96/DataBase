#include "MultiMap.h"
#include "Database.h"
#include <iostream>
#include <cassert>
#include <fstream>
using namespace std;

int main()
{
	/*Database db;
	db.loadFromURL("http://cs.ucla.edu/classes/winter14/cs32/Projects/4/Data/census.csv");
*/
	MultiMap m;
	m.insert("D", 8);
	m.insert("B", 4);
	m.insert("F", 12);
	m.insert("A", 1);
	m.insert("C", 5);
	m.insert("E", 9);
	m.insert("G", 13);
	m.insert("A", 2);
	m.insert("C", 6);
	m.insert("E", 10);
	m.insert("G", 14);
	m.insert("A", 3);
	m.insert("C", 7);
	m.insert("E", 11);
	m.insert("G", 15);

	MultiMap::Iterator c(m.findEqual("D"));
	assert(c.valid());
	MultiMap::Iterator d;
	for (; c.valid(); c.prev())
		d = c;
	for (; d.valid(); d.next())
		cout << d.getKey() << " " << d.getValue() << endl;

	cout << endl;

	MultiMap::Iterator a(m.findEqual("D"));
	assert(a.valid());
	MultiMap::Iterator b;
	for (; a.valid(); a.next())
		b = a;
	for (; b.valid(); b.prev())
		cout << b.getKey() << " " << b.getValue() << endl;

	MultiMap::Iterator t;
	t = m.findEqual("A");
	if (t.valid())
	{
		cout << endl;
		cout << t.getKey() << " " << t.getValue() << endl;
		t.next();
		cout << t.getKey() << " " << t.getValue() << endl;
		t.next();
		cout << t.getKey() << " " << t.getValue() << endl;
	}
	t = m.findEqualOrSuccessor("Fz");
	if (t.valid())
	{
		cout << endl;
		cout << t.getKey() << " " << t.getValue() << endl;
		t.next();
		cout << t.getKey() << " " << t.getValue() << endl;
		t.next();
		cout << t.getKey() << " " << t.getValue() << endl;
	}
	t = m.findEqualOrPredecessor("E");
	t.next();
	MultiMap::Iterator after = t;
	t.next();
	MultiMap::Iterator afterafter = t;
	t.prev();
	t.prev();
	if (t.valid() && after.valid() && afterafter.valid())
	{
		cout << endl;
		cout << t.getKey() << " " << t.getValue() << endl;
		t.next();
		cout << t.getKey() << " " << t.getValue() << endl;
		t.next();
		cout << t.getKey() << " " << t.getValue() << endl;
	}

	Database database;

	Database::FieldDescriptor fd1, fd2, fd3;

	fd1.name = "username";
	fd1.index = Database::it_indexed;	//	username	is	an	indexed	field	

	fd2.name = "phonenum";
	fd2.index = Database::it_indexed;	//	phone	#	is	an	indexed	field	

	fd3.name = "age";
	fd3.index = Database::it_none;	//	age	is	NOT	an	indexed	field	

	std::vector<Database::FieldDescriptor>	schema;
	schema.push_back(fd1);
	schema.push_back(fd2);
	schema.push_back(fd3);

	database.specifySchema(schema);

	vector<string> row;
	string username = "Jasoniful";
	string phonenum = "6265375521";
	string age = "17";
	row.push_back(username);
	row.push_back(phonenum);
	row.push_back(age);

	database.addRow(row);

	vector<string> row2;
	username = "Aaron";
	phonenum = "5403317654";
	age = "20";
	row2.push_back(username);
	row2.push_back(phonenum);
	row2.push_back(age);

	database.addRow(row2);

	vector<string> row3;
	username = "Aaron";
	phonenum = "6265375521";
	age = "25";
	row3.push_back(username);
	row3.push_back(phonenum);
	row3.push_back(age);

	database.addRow(row3);

	vector<int> results;
	vector<Database::SortCriterion> sortCrit;
	vector<Database::SearchCriterion> searchCrit;
	
	Database::SearchCriterion s1;
	s1.fieldName = "username";
	s1.minValue = "A";
	s1.maxValue = "C";

	Database::SearchCriterion s2;
	s2.fieldName = "phonenum";
	s2.minValue = "6000000000";
	s2.maxValue = "";

	searchCrit.push_back(s1);
	searchCrit.push_back(s2);


	database.search(searchCrit, sortCrit, results);

	cout << endl << "Passed all tests" << endl;
}