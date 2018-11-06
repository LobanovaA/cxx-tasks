/* Custom manipulators.
* @file
* @date 2018-08-05
* @author Anonymous
*/

#ifndef __IOMANIP_HPP__
#define __IOMANIP_HPP__

#include <iostream>

//{ endm manipulator
std::ostream& endm(std::ostream& stream)
{
	return stream << "[eol]\n";
}
//}

//{ squares manipulator
class squarer
{
public:
	squarer(std::ostream & stream) :
		stream(stream)
	{}

	template <typename Insert>
	std::ostream & operator<<(Insert const input)
	{
		return stream << '[' << input << ']';
	}

private:
	std::ostream & stream;
};

class squares_container { } squares;

squarer operator<<(std::ostream & stream, squares_container)
{
	return squarer(stream);
}
//}

//{ add manipulator
template <typename Insert>
class adder_2
{
public:
	adder_2(std::ostream & stream, Insert const& a) :
		stream(stream),
		a(a)
	{
	}

	std::ostream & operator<<(Insert const& b)
	{
		Insert res = a + b;
		return stream << res;
	}

private:
	std::ostream & stream;
	Insert a;
};

class adder_1
{
public:
	adder_1(std::ostream & stream) :
		stream(stream)
	{
	}

	template <typename Insert>
	struct adder_2<Insert> operator<<(Insert const& input)
	{
		return adder_2<Insert>(stream, input);
	}

private:
	std::ostream & stream;
};

class add_container { } add;

adder_1 operator<<(std::ostream & stream, add_container)
{
	return adder_1(stream);
}
//}

#endif // __IOMANIP_HPP__