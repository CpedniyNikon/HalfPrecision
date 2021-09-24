#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>	
#include <vector>
using std::string;
using std::cout;
using std::endl;

typedef string binary_digit_half_precision;
typedef string hexadecimal_digit_half_precision;

binary_digit_half_precision get_binary_digit_half_precision(string value)
{
	string binary_answer("");
	if (value[0] == '-')
	{
		value.erase(value.begin());
		binary_answer += '1';
	}
	else binary_answer += '0';

	int the_integer_part_of_number = 0;
	double the_fractional_part_of_number = 0;
	int power_fraction = 1;
	int power_integer = 0;
	bool point_founded = false;
	for (int i = 0; i < value.size(); ++i)
	{
		if (value[i] != '.' && !point_founded)
		{
			the_integer_part_of_number *= 10;
			the_integer_part_of_number += value[i] - '0';
		}
		else
		{
			point_founded = true;
		}
		if (point_founded && value[i] != '.')
		{
			the_fractional_part_of_number *= 10;
			the_fractional_part_of_number += value[i] - '0';
			power_fraction *= 10;
		}
	}
	string binary_the_integer_part_of_number(""), binary_the_fractional_part_of_number("");
	while (the_integer_part_of_number)
	{
		binary_the_integer_part_of_number += the_integer_part_of_number % 2 + '0';
		the_integer_part_of_number /= 2;
		if (value[0] != '0')
			power_integer++;
	}
	the_fractional_part_of_number = the_fractional_part_of_number / power_fraction; // преобразовываю дробную часть
	bool binary_1_founded = true;
	while (the_fractional_part_of_number != 0.0)
	{
		if (value[0] == '0')
		{
			if (binary_1_founded)
			{
				power_integer--;
			}
			if (((int)(the_fractional_part_of_number * 2) + '0') == '1')
				binary_1_founded = false;
		}
		binary_the_fractional_part_of_number += (int)(the_fractional_part_of_number * 2) + '0';
		the_fractional_part_of_number *= 2;
		the_fractional_part_of_number -= (int)the_fractional_part_of_number;
	}
	if (binary_the_integer_part_of_number.size())
		binary_the_integer_part_of_number.pop_back();
	if (value[0] == '0')
	{
		power_integer += 1;
	}
	std::reverse(binary_the_integer_part_of_number.begin(), binary_the_integer_part_of_number.end());
	//std::cout << binary_the_integer_part_of_number << " " << binary_the_fractional_part_of_number << std::endl; // выводим целую и дробную часть числа
	//cout << c - 1 << endl;
	for (int i = 0; i > power_integer - 1; i--)
	{
		binary_the_fractional_part_of_number.erase(binary_the_fractional_part_of_number.begin());
	}
	//cout << binary_the_fractional_part_of_number << endl; //выводим дробную часть в случае нулевой целой части 
	int poryadok = 15 + power_integer - 1;
	string binary_poryadok("");
	while (poryadok)
	{
		binary_poryadok += poryadok % 2 + '0';
		poryadok /= 2;
	}
	while (binary_poryadok.size() != 5)
		binary_poryadok.push_back('0');
	std::reverse(binary_poryadok.begin(), binary_poryadok.end());
	//cout << binary_poryadok << endl; //выводим порядок
	binary_answer += binary_poryadok;
	binary_answer += binary_the_integer_part_of_number;
	binary_answer += binary_the_fractional_part_of_number;
	if (binary_answer.size() < 16)
	{
		while (binary_answer.size() != 16)
		{
			binary_answer.push_back('0');
		}
	}
	else
	{
		while (binary_answer.size() != 16)
		{
			binary_answer.pop_back();
		}
	}
	return binary_answer;
}
hexadecimal_digit_half_precision get_hexadecimal_digit_half_precision(string value)
{
	string binary_answer = get_binary_digit_half_precision(value);
	string Hex_answer("");
	int numbering = 0;
	string tetrad("");
	std::unordered_map<string, char> binary_to_hex = { {"0000",'0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'}, {"0100", '4'}, {"0101",'5'},{"0110",'6'},{"0111",'7'},{"1000",'8'},{"1001", '9'}, {"1010",'A'},{"1011",'B'},{"1100",'C'},{"1101",'D'},{"1110",'E'},{"1111",'F'} };
	for (int i = 0; i < binary_answer.size(); i++)
	{
		tetrad += binary_answer[i];
		numbering++;
		if (numbering == 4)
		{
			Hex_answer += binary_to_hex[tetrad];
			binary_answer.insert(binary_answer.begin() + ++i, '.');
			numbering = 0;
			tetrad = "";
		}
	}
	return Hex_answer;
}


int main() {
	for (;;)
	{
		std::cout << "Enter one digit" << std::endl;
		string value("");
		std::cin >> value;
		std::vector<string> strings;
		strings.push_back(value);
		bool is_ok = true;
		for (const auto& str : strings)
		{
			if (!((str[str.size() - 1] != '.') &&
				(str[0] != '.') &&
				(std::count(str.begin(), str.end(), '.') <= 1) &&
				(std::all_of(str.begin(), str.end(), [](char c)->bool {return	((c >= '0' && c <= '9') || (c == '.') || (c == '-')); }))))
				is_ok = false;
		}
		if (is_ok)
		{
			cout << "binary digit : " << get_binary_digit_half_precision(value) << endl;
			cout << "hexadecimal digit : " << get_hexadecimal_digit_half_precision(value) << endl;
			break;
		}
		else
		{
			std::cout << "Try Again, You should not enter words or more than one point" << std::endl;
			continue;
		}

	}
	return 0;
}
