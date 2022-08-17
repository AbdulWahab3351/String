#include"String.h"
String::String()
{
	data = nullptr;
	size = 0;
}
String::String(const char c) : String()
{
	if (c == '\0')
		return;
	size = 2;
	data = new char[size] { c, '\0' };
}
String::String(const char* str) : String()
{
	if (str == nullptr || *str == '\0')
		return;

	size = findLength(str) + 1;
	data = new char[size];
	strCopy(data, str);
}
String::String(const String& ref) :String()
{
	if (!ref.data)
		return;
	data = new char[ref.size];
	for (int i = 0; i < ref.size; i++)
		data[i] = ref.data[i];
	size = ref.size;
}
String::~String()
{
	if (data)
		delete[]data;
	data = nullptr;
	size = 0;
}
void String::shrink()
{
	size = findLength(data) + 1;
	char* temp = new char[size];
	strCopy(temp, data);
	delete[]data;
	data = temp;
}
char& String::operator [](const int index)
{
	if (index >= 0 && index < size)
		return data[index];
	exit(0);
}

const char& String::operator [](const int index) const
{
	if (index >= 0 && index < size)
		return data[index];
	exit(0);
}
int String::getLength() const
{
	return findLength(data);
}
int String::findLength(const char* str) const
{
	if (!str)
		return 0;
	int i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return i;
}
int String::getSize()const
{
	return size;
}
int String::find(const String& subStr, const int start) const
{
	int startCopy = start;
	int length = getLength();
	do
	{
		if (findString(subStr.data, startCopy))
		{
			return startCopy;
		}
		else
			startCopy++;
	} while (start < length);
	return -1;
}
bool String::findString(const char* str, const int index) const
{
	int i = 0;
	int indexCopy = index;
	while (str[i] != '\0')
	{
		if (str[i] != data[indexCopy])
			return false;
		indexCopy++;
		i++;
	}
	return true;
}
void String::insert(const int index, const String& subStr)
{
	int lengthSubStr = findLength(subStr.data);
	int lengthOriginal = getLength();
	if (index<0 || index>lengthOriginal)
		return;
	if (size > lengthSubStr + lengthOriginal)
		myMemMove(&data[index + lengthSubStr], &data[index], lengthOriginal - index);
	else
	{
		reSize(lengthOriginal + lengthSubStr + 1);
		myMemMove(&data[index + lengthSubStr], &data[index], lengthOriginal - index);
	}
	myMemCpy(&data[index], subStr.data, lengthSubStr);
	data[lengthOriginal + lengthSubStr] = '\0';
}
void String::remove(const int index, const int count)
{
	if (!*this)
		return;
	if (index < 0 || index > getLength())
		return;
	if (index + count > getLength())
	{
		data[index] = '\0';
		return;
	}
	strCopy(&data[index], &data[index + count]);
}
int String::replace(const String& old, const String& newSubStr)
{
	int occurrences = 0;
	int start = 0;
	int index = find(old, start);
	if (index == -1)
		return occurrences;
	do
	{
		occurrences++;
		remove(index, old.getLength());
		insert(index, newSubStr);
		start = index + newSubStr.getLength();
		index = find(old, start);
	} while (index != -1);
	return occurrences;
}
void String::trimLeft()
{
	if (!*this)
		return;
	int firstNonWhiteSpaceIndex = 0;
	while ((data[firstNonWhiteSpaceIndex] != '\0') && (data[firstNonWhiteSpaceIndex] == '\t') || (data[firstNonWhiteSpaceIndex] == ' ') || (data[firstNonWhiteSpaceIndex] == '\n'))
		firstNonWhiteSpaceIndex++;
	strCopy(data, &data[firstNonWhiteSpaceIndex]);
}
void String::trimRight()
{
	if (!*this)
		return;
	int lastIndex = findLength(data) - 1;
	while ((lastIndex >= 0) && (data[lastIndex] == '\t') || (data[lastIndex] == ' ') || (data[lastIndex] == '\n'))
	{
		data[lastIndex] = '\0';
		lastIndex--;
	}
}
void String::trim()
{
	trimLeft();
	trimRight();
}
void String::makeUpper()
{
	int i = 0;
	while (data[i] != '\0' && i < size)
	{

		if (data[i] >= 'a' && data[i] <= 'z')
			data[i] -= 'a' - 'A';
		i++;
	}
}
void String::makeLower()
{
	int i = 0;
	while (data[i] != '\0' && i < size)
	{
		if (data[i] >= 'A' && data[i] <= 'Z')
			data[i] += 'a' - 'A';
		i++;
	}
}
void String::reverse()
{
	int length = getLength();
	for (int i = 0; i < length / 2; i++)
		swapChar(data[i], data[length - i - 1]);
}
void String::swapChar(char& ch1, char& ch2)
{
	char temp = ch1;
	ch1 = ch2;
	ch2 = temp;
}
void String::reSize(int newSize)
{
	if (newSize <= 0)
	{
		this->~String();
		return;
	}
	char* temp = new char[newSize];
	int i = 0;
	while ((i < size - 1) && (i < newSize - 1))
	{
		temp[i] = data[i];
		i++;
	}
	temp[i] = '\0';
	this->~String();
	data = temp;
	size = newSize;
}
int String::operator==(const String& s2) const
{
	if (!*this && !s2)
		return 0;
	else if (!*this && !(!s2))
		return -1;
	else if (!(!*this) && !s2)
		return 1;

	int index = 0;
	while ((data[index] != '\0') && s2.data[index] != '\0')
	{
		if (data[index] - s2.data[index] > 0)
			return 1;
		else if (data[index] - s2.data[index] < 0)
			return -1;
		index++;
	}

	if ((data[index] == '\0') && (s2.data[index] == '\0'))
		return 0;
	else if ((data[index] == '\0') && (s2.data[index] != '\0'))
		return -1;
	else
		return 1;
}
String String::left(const int count)
{
	if (!*this)
		return *this;
	if (count <= 0)
	{
		String temp;
		return temp;
	}
	int length = getLength();
	if (count >= length)
	{
		String temp(*this);
		data[0] = '\0';
		return temp;
	}
	String temp;
	temp.size = count + 1;
	temp.data = new char[temp.size];
	int i = 0;
	for (i = 0; i < temp.size - 1; i++)
		temp.data[i] = data[i];
	temp.data[i] = '\0';
	myMemMove(&data[0], &data[i], length - count + 1);
	return temp;
}
String String::right(const int count)
{
	if (!*this)
		return *this;
	if (count <= 0)
	{
		String temp;
		return temp;
	}
	int length = getLength();
	if (count >= length)
	{
		String temp(*this);
		data[0] = '\0';
		return temp;
	}
	String temp;
	temp.size = count + 1;
	temp.data = new char[temp.size];
	myMemCpy(temp.data, &data[length - count], temp.size);
	data[count] = '\0';
	return temp;
}
String:: operator long long int() const
{
	long long int temp = 0;
	int i = 0;
	bool isNegative = false;
	if (data[i] == '-')
	{
		i++;
		isNegative = true;
	}
	while (data[i] != '\0' && (data[i] >= '0' && data[i] <= '9'))
	{
		temp = temp * 10 + data[i] - '0';
		i++;
	}
	return isNegative ? (temp * -1) : (temp);
}
String :: operator double()const
{
	double fractionalPart = 0;
	double integralPart = 0;
	int index = 0;
	bool isNegative = false;
	if (data[index] == '-')
	{
		index++;
		isNegative = true;
	}
	while (data[index] >= '0' && data[index] <= '9')
	{
		integralPart = integralPart * 10 + data[index] - '0';
		index++;
	}
	if (data[index] == '.')
	{
		index++;
		int dividedBy = 1;
		while (data[index] != '\0' && (data[index] >= '0' && data[index] <= '9'))
		{
			fractionalPart = fractionalPart * 10 + data[index] - '0';
			index++;
			dividedBy *= 10;
		}
		fractionalPart /= dividedBy;
		double temp = integralPart + fractionalPart;
		return isNegative ? (temp * -1) : (temp);
	}
	return isNegative ? ((double)integralPart * -1) : ((double)integralPart);
}
String String::operator +(const String& s2) const
{
	if (!s2)
		return *this;
	if (!*this)
		return s2;
	String merged(*this);
	merged.insert(getLength(), s2);
	return merged;
}
void String :: operator+=(const String& s2)
{
	insert(getLength(), s2);
}
String& String ::operator=(const long long int num)
{
	int copyNum = num;
	bool isNegative = false;
	if (num < 0)
	{
		isNegative = true;
		copyNum *= -1;
	}
	int numDigits = logTen(copyNum) + 1;
	if (!data || numDigits + 2 > getSize())
		reSize(numDigits + 2);
	int controlIteration = (isNegative ? 1 : 0);
	int start = (isNegative ? numDigits + 1 : numDigits);
	data[start] = '\0';
	start--;
	char temp;
	while (start >= controlIteration)
	{
		temp = (copyNum % 10) + '0';
		copyNum = copyNum / 10;
		data[start] = temp;
		start--;
	}
	if (isNegative)
		data[0] = '-';
	return *this;
}
void String::myMemMove(void* dest, const void* src, int bytes)
{
	char* d = (char*)dest;
	char* s = (char*)src;

	if (s < d)
	{
		d += bytes - 1;
		s += bytes - 1;

		for (int i = 0; i < bytes; i++)
		{
			*d = *s;
			d--;
			s--;
		}
	}
	else
	{
		for (int i = 0; i < bytes; i++)
		{
			*d = *s;
			d++;
			s++;
		}
	}
}

void String::myMemCpy(void* dest, const void* src, int bytes)
{
	char* d = (char*)dest;
	char* s = (char*)src;
	for (int i = 0; i < bytes; i++)
	{
		*d = *s;
		d++;
		s++;
	}
}
void String::strCopy(char* dest, const char* source)
{
	if (dest == nullptr)
		return;
	if (source == nullptr)
	{
		dest[0] = '\0';
		return;
	}
	int i = 0;
	while (source[i] != '\0')
	{
		dest[i] = source[i];
		i++;
	}
	dest[i] = '\0';
}
int String::logTen(int num)
{
	int count = 0;
	int base = 10;
	int result = base;
	while (result <= num)
	{
		count++;
		result *= base;
	}
	return count;
}
String& String::operator =(const String& ref)
{
	if (this == &ref)
		return *this;
	this->~String();
	if (ref.data == nullptr)
		return *this;
	data = new char[ref.size];
	for (int i = 0; i < ref.size; i++)
		data[i] = ref.data[i];
	size = ref.size;
	return *this;
}
bool String:: operator ! ()const
{
	return (data == nullptr || data[0] == '\0');
}
String& String:: operator=(const double num)
{
	*this = (long long int)num;
	if ((num - (int)num) == 0)
		return *this;
	int decimal = (num - (int)num) * 10000000;
	if (decimal < 0)
		decimal *= -1;
	while (decimal % 10 == 0)
		decimal /= 10;
	*this += '.';
	String temp;
	temp = (long long int)decimal;
	*this += temp;
	return *this;
}
String:: operator bool()const
{
	return !(!*this);
}
istream& operator >> (istream& temp, String& ref)
{
	if (!ref.data)
	{
		ref.size = 10;
		ref.data = new char[ref.size];
	}
	int i = 0;
	char ch = temp.get();
	//while (ch != '\n' && ch != EOF)
	while (temp && ch != '\n')
	{
		if (i == ref.size - 1)
			ref.reSize(ref.size * 2);
		ref.data[i] = ch;
		temp.get(ch);
		i++;
	}
	ref.data[i] = '\0';
	return temp;
}
String::String(String&& ref)
{
	data = ref.data;
	size = ref.size;
	ref.data = nullptr;
}
String& String:: operator=(String&& ref)
{
	this->~String();
	data = ref.data;
	size = ref.size;
	ref.data = nullptr;
	return *this;
}
ostream& operator << (ostream& temp, const String& str)
{
	if(str.getSize() > 0)
		temp << &str[0];
	return temp;
}
String String:: operator()(const String& delim)
{
	if (!*this)
		return *this;
	if (!delim)
		return left(getLength());
	int i = 0, j;
	bool isMatched = false;
	while (data[i] != '\0')
	{
		j = 0;
		while (delim[j] != '\0')
		{
			if (delim[j] == data[i])
			{
				remove(i);
				return left(i);
			}
				j++;
		}
		i++;
	}
	return left(getLength());
}
