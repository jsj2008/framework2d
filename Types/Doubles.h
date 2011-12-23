#ifndef _DOUBLES_
#define _DOUBLES_
#include <cassert>
template <typename HashKey, typename Variable>
class Doubles //: public Hasher<HashKey, Variable>
{
public:
	Doubles(unsigned int HashSize = 10);
	~Doubles();
	bool add(HashKey &hK, Variable const &v);// true means successful add, false means it exists
	void clear();
	void push(HashKey &hK, Variable const &v);// Doesnt check for existance
	bool checkFor(HashKey const &hK);// true = exists, false = doesnt exist
	bool remove(HashKey const &hK);// true = was removed, false = didn't exist in the first place
	Variable& get (HashKey j);
	unsigned int find(HashKey &hK);// Returns next value in the array if T doesn't exist
protected:
	struct element
	{
		HashKey hashKey;
		Variable variable;
	};
	std::vector<element>* items;
	unsigned int hashSize;
};

template <typename HashKey, typename Variable>
bool Doubles<HashKey, Variable>::add(HashKey &hK, Variable const &v)
{

	element e;
	e.hashKey = hK;
	e.variable = v;
	unsigned int index = (hK)%hashSize;
	items[index].size();
    if (items[index].size()==find(hK))
    {
        push(hK, v);
        return true;
    }
	return false;
}

template <typename HashKey, typename Variable>
Variable& Doubles<HashKey, Variable>::get(HashKey j)
{
	int index = j%hashSize;
	unsigned int location = (find(j));
	if (location == items[index].size())
	{
		return nullptr;
	}
	else
	{
		return items[index][location].variable;
	}
}

template <typename HashKey, typename Variable>
Doubles<HashKey, Variable>::Doubles(unsigned int HashSize)
{
	items = nullptr;
	hashSize = HashSize;
	items = new std::vector<element>[hashSize];
}
template <typename HashKey, typename Variable>
Doubles<HashKey, Variable>::~Doubles()
{
    delete[] items;
}
template <typename HashKey, typename Variable>
void Doubles<HashKey, Variable>::clear()
{
    delete[] items;
	items = new std::vector<element>[hashSize];
}
template <typename HashKey, typename Variable>
void Doubles<HashKey, Variable>::push(HashKey &hK, Variable const &v)
{
	element e;
	e.hashKey = hK;
	e.variable = v;
	items[hK%hashSize].push_back(e);
}

/*template <typename HashKey, typename Variable>
bool Hasher<HashKey, Variable>::checkFor(HashKey const &hK)
{
	return find(hK) != items[index.size()];
}*/

template <typename HashKey, typename Variable>
bool Doubles<HashKey, Variable>::remove(HashKey const &hK)
{
	int index = hK%hashSize;
	int size = items[index].size();
	items[hK%hashSize].erase(find(hK));
	return items[index].size() < size;
}

template <typename HashKey, typename Variable>
unsigned int Doubles<HashKey, Variable>::find(HashKey &hK)
{
	unsigned int index = hK%hashSize;
	if (index < hashSize)
	{
		for (unsigned int j = 0; j < items[index].size(); j++)
		{
			if (items[index][j].hashKey == hK)
			{
				return j;
			}
		}
	}
	return (unsigned int)items[index].size();
}
#endif
