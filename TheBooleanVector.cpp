/*
*
* by UnitedTimur (c)
*
*/

#include <iostream>

using namespace std;

typedef unsigned char byte;

class bv
{
public:
	bv(int const&);
	bv(const char*);
	bv(bv const&);
	~bv();

	bv operator&(bv const &);
	bv operator&=(bv const&);
	bv operator|(bv const&);
	bv operator|=(bv const&);
	bv operator^(bv const&);
	bv operator^=(bv const&);
	bv operator~();
	bv operator<<(int const&);
	bv operator>>(int const&);
	int operator[](int const&);
	void operator=(bv const&);
	void operator<<=(int const&);
	void operator>>=(int const&);

	int weight() const;
	int size() const;

	void set1(int const&);
	void set1(int const&, int const&);
	void set0(int const&);
	void set0(int const&, int const&);
	void print() const;
	void copy(byte*, int);
	void _error() const;

	friend ostream & operator<<(ostream &, bv const&);
	friend istream & operator>>(istream &, bv&);

private:
	byte* vector;
	int size_vector;
	int memory;
};

bv::bv(int const & size_vector = 8)
{
	try
	{
		if (size_vector > 0)
		{
			this->size_vector = size_vector;
			memory = (size_vector - 1) / 8 + 1;
			vector = new byte[memory]{};
		}
		else
		{
			throw "//The size of your boolean vector is zero or less than zero. I selected 1 byte of memory itself.";
		}
	}
	catch (const char* error)
	{
		vector = new byte[1]{};
		cout << error << endl;
	}
}

bv::bv(const char * string)
{
	try
	{
		for (auto i = 0; i < strlen(string); i++)
		{
			if (!isdigit(string[i]) || string[i] != '0' && string[i] != '1')
			{
				throw "//Not all symbols are zero or one.";
			}
		}
	}
	catch (const char* error)
	{
		cerr << error << endl;
		_error();
	}

	size_vector = strlen(string);
	memory = (size_vector - 1) / 8 + 1;
	vector = new byte[memory]{};

	byte mask = 1;

	auto index_string = memory - 1;

	for (auto i = size_vector - 1; i >= 0; i--, mask <<= 1)
	{
		if (!mask)
		{
			mask = 1;
			index_string--;
		}

		if (string[i] == '1')
		{
			vector[index_string] |= mask;
		}
	}
}

bv::bv(bv const & tmp)
{
	memory = tmp.memory;
	size_vector = tmp.size_vector;

	vector = new byte[memory];

	for (auto i = 0; i < memory; i++)
	{
		vector[i] = tmp.vector[i];
	}
}

bv::~bv()
{
	delete[] vector;
}

bv bv::operator&(bv const & tmp)
{
	try
	{
		if (&tmp == this)
		{
			throw "//Error. Logical and performs the multiplication operation of the same vector.";
		}

	}
	catch (const char* error)
	{
		cerr << error << endl;
		_error();
	}

	int t;
	int min;

	if (size_vector > tmp.size_vector)
	{
		t = tmp.size_vector;
		min = tmp.memory;
	}
	else
	{
		t = size_vector;
		min = memory;
	}

	bv temp(t);

	int i, index_string;

	temp.memory = min;
	temp.size_vector = t;

	for (i = memory, index_string = tmp.memory; min >= 0; i--, index_string--, min--)
	{
		temp.vector[min] = vector[i] & tmp.vector[index_string];
	}

	return temp;
}

bv bv::operator&=(bv const & tmp)
{
	try
	{
		if (&tmp == this)
		{
			throw "//Error. Logical and performs the multiplication operation of the same vector.";
		}

	}
	catch (const char* error)
	{
		cerr << error << endl;
		_error();
	}

	bv temp = (*this & tmp);

	*this = temp;

	return *this;
}

bv bv::operator|(bv const & tmp)
{
	try
	{
		if (&tmp == this)
		{
			throw "//Error. The logical sum is equal itself.";
		}

	}
	catch (const char* error)
	{
		cerr << error << endl;
		_error();
	}

	int t;
	int min;

	if (size_vector > tmp.size_vector)
	{
		t = tmp.size_vector;
		min = tmp.memory;
	}
	else
	{
		t = size_vector;
		min = memory;
	}

	bv temp(t);

	int i, index_string;

	temp.memory = min;
	temp.size_vector = t;

	for (i = memory, index_string = tmp.memory; min >= 0; i--, index_string--, min--)
	{
		temp.vector[min] = vector[i] | tmp.vector[index_string];
	}

	return temp;
}

bv bv::operator|=(bv const & tmp)
{
	try
	{
		if (&tmp == this)
		{
			throw "//Error. The logical sum is equal itself.";
		}

	}
	catch (const char* error)
	{
		cerr << error << endl;
		_error();
	}

	bv temp(*this | tmp);

	*this = temp;

	return *this;
}

bv bv::operator^(bv const & tmp)
{
	try
	{
		if (&tmp == this)
		{
			throw "//Error. Your object XOR your object is error.";
		}

	}
	catch (const char* error)
	{
		cerr << error << endl;
		_error();
	}

	int t;
	int min;

	if (size_vector > tmp.size_vector)
	{
		t = tmp.size_vector;
		min = tmp.memory;
	}
	else
	{
		t = size_vector;
		min = memory;
	}

	bv temp(t);

	int i, index_string;

	temp.memory = min;
	temp.size_vector = t;

	for (i = memory, index_string = tmp.memory; min >= 0; i--, index_string--, min--)
	{
		temp.vector[min] = vector[i] ^ tmp.vector[index_string];
	}

	return temp;
}

bv bv::operator^=(bv const & tmp)
{
	try
	{
		if (&tmp == this)
		{
			throw "//Error. Your object XOR your object is error.";
		}

	}
	catch (const char* error)
	{
		cerr << error << endl;
		_error();
	}

	bv temp(*this ^ tmp);

	*this = temp;

	return *this;
}

bv bv::operator~()
{
	try
	{
		if (memory == 0)
		{
			throw "//Error. The size of vector is 0.";
		}
	}
	catch (const char* error)
	{
		cerr << error << endl;
		_error();
	}

	for (auto index_string = 0; index_string < memory; index_string++)
	{
		vector[index_string] = ~vector[index_string];
	}

	return *this;
}

bv bv::operator<<(int const & number)
{
	bv temp(*this);

	temp <<= number;

	return temp;
}

bv bv::operator>>(int const & number)
{
	bv temp(*this);

	temp >>= number;

	return temp;
}

int bv::operator[](int const& key)
{
	try
	{
		if (key < 0 || key > size_vector)
		{
			throw "//Error. The key is more than size vector or is less than zero.";
		}
	}
	catch (const char* error)
	{
		cerr << error << endl;
		_error();
	}

	int i = memory - 1 - key / 8;
	int bit = key % 8;

	byte mask = 1 << bit;

	if (vector[i] & mask)
	{
		return 1;
	}

	return 0;
}

void bv::operator=(bv const & tmp)
{
	try
	{
		if (&tmp == this)
		{
			throw "//Error, but this object is equal to itself.";
		}
	}
	catch (const char* error)
	{
		cerr << error << endl;
		_error();
	}

	delete[] vector;

	memory = tmp.memory;
	size_vector = tmp.size_vector;
	vector = new byte[memory]{};

	for (auto index_string = 0; index_string < memory; index_string++)
	{
		vector[index_string] |= tmp.vector[index_string];
	}

}

void bv::operator<<=(int const & number)
{
	try
	{
		if (memory == 0)
		{
			throw "//The size of vector is 0";
		}
	}
	catch (const char* error)
	{
		cerr << error << endl;
		_error();
	}

	int i = size_vector - 1;

	for (auto k = i - number; k >= 0; k--, i--)
	{
		if (operator[](k))
		{
			set1(i);
		}
		else
		{
			set0(i);
		}
	}

	for (; i >= 0; i--)
	{
		set0(i);
	}
}

void bv::operator>>=(int const & number)
{
	int i;

	int temp = number;

	for (i = 0; temp < size_vector; i++, temp++)
	{
		if (operator[](temp))
		{
			set1(i);
		}
		else
		{
			set0(i);
		}
	}

	for (; i < size_vector; i++)
	{
		set0(i);
	}
}

int bv::weight() const
{
	byte mask;

	auto count = 0;

	for (auto index_string = 0; index_string < memory; index_string++)
	{
		for (mask = 1 << 7; mask; mask >>= 1)
		{
			if (!mask)
			{
				mask = 1 << 7;
			}

			if (vector[index_string] & mask)
			{
				count++;
			}
		}
	}

	return count;
}

int bv::size() const
{
	return size_vector;
}

void bv::set1(int const & key)
{
	try
	{
		if (key < 0 || key > size_vector)
		{
			throw "The key is less than zero or is more than size of vector.";
		}
	}
	catch (const char* error)
	{
		cerr << error << endl;
		_error();
	}

	int i = memory - 1 - key / 8;
	int bit = key % 8;

	byte mask = 1 << bit;

	vector[i] |= mask;
}

void bv::set1(int const & key, int const & number)
{
	for (auto i = key; i < key + number; i++)
	{
		set1(i);
	}
}

void bv::set0(int const & key)
{
	try
	{
		if (key < 0 || key > size_vector)
		{
			throw "The key is less than zero or is more than size of vector.";
		}
	}
	catch (const char* error)
	{
		cerr << error << endl;
		_error();
	}

	int i = memory - 1 - key / 8;
	int bit = key % 8;

	byte mask = 1 << bit;

	if (operator[](key))
	{
		mask = ~mask;
		vector[i] &= mask;
	}
}

void bv::set0(int const & key, int const & number)
{
	for (auto i = key; i < key + number; i++)
	{
		set0(i);
	}
}

void bv::print() const
{
	byte mask;

	for (auto index_string = 0; index_string < memory; index_string++)
	{
		for (mask = 1 << 7; mask; mask >>= 1)
		{
			if (!mask)
			{
				mask = 1 << 7;
			}

			if (vector[index_string] & mask)
			{
				cout << '1';
			}
			else
			{
				cout << '0';
			}
		}
	}

	cout << endl;
}

void bv::copy(byte * tmp, int nmas)
{
	for (auto i = 0; i < nmas; i++)
	{
		vector[i] = tmp[i];
	}
}

void bv::_error() const
{
	getchar();
	exit(0);
}

ostream & operator<<(ostream & os, bv const & tmp)
{
	byte mask;
	
	for (auto index_string = 0; index_string < tmp.memory; index_string++)
	{
		for (mask = 1 << 7; mask; mask >>= 1)
		{
			if (!mask)
			{
				mask = 1 << 7;
			}

			if (tmp.vector[index_string] & mask)
			{
				os << '1';
			}
			else
			{
				os << '0';
			}
		}
	}

	return os;
}

istream & operator>>(istream & is, bv & tmp)
{
	char * s;

	s = new char[INT_MAX];
	
	cin >> s;

	try
	{
		for (auto i = 0; i < strlen(s); i++)
		{
			if (!isdigit(s[i]) || s[i] != '0' && s[i] != '1')
			{
				throw "//Not all symbols are zero or one.";
			}
		}
	}
	catch (const char* error)
	{
		cerr << error << endl;
		tmp._error();
	}

	tmp.size_vector = strlen(s);
	tmp.memory = (tmp.size_vector - 1) / 8 + 1;
	tmp.vector = new byte[tmp.memory]{};

	byte mask = 1;

	auto index_string = tmp.memory - 1;

	for (auto i = tmp.size_vector - 1; i >= 0; i--, mask <<= 1)
	{
		if (!mask)
		{
			mask = 1;
			index_string--;
		}

		if (s[i] == '1')
		{
			tmp.vector[index_string] |= mask;
		}
	}

	delete[] s;

	return is;
}

void main()
{
	bv TAMERLAN("11100100");

	cout << TAMERLAN << endl;

	system("pause");
}
