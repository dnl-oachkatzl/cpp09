/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daspring <daspring@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:48:39 by daspring          #+#    #+#             */
/*   Updated: 2025/05/04 18:31:12 by daspring         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <string>
#include <stdexcept>
#include <regex>
#include <utility>

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() : BitcoinExchange("./data.csv") {};

BitcoinExchange::BitcoinExchange(std::string path_to_data) {
	parseData_(path_to_data);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
	copyFrom_(other);
}

BitcoinExchange::~BitcoinExchange() {};

BitcoinExchange&	BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this != &other) {
		copyFrom_(other);
	}
	return *this;
}

void	BitcoinExchange::copyFrom_(const BitcoinExchange& other) {
	exchange_data_ = other.exchange_data_;
}

void	BitcoinExchange::parseData_(std::string path_to_data) {
	std::cout << "parsing data file:\n";
	std::ifstream file(path_to_data);
	if (!file) {
		throw std::runtime_error("Failed to open data file. '" + path_to_data + "'");
	}
	std::string	line;
	int			line_number{1};

	std::getline(file, line);
	if (line != "date,exchange_rate") {
		std::cerr << "Data has wrong format. Expected 'date,exchange_rate' as a header.\n";
	}
	while (std::getline(file, line)) {
		line_number++;
		if (line.empty()) {
			continue;
		}
		std::pair<std::string, float> map_entry = parseDataLine_(line, line_number);
		if (map_entry.first != "error") {
			if (exchange_data_.insert({map_entry.first, map_entry.second}).second == false) {
				std::cout << "line " << line_number << " : duplicate date - not included.\n";
			}
		}
	}
	std::cout << "done parsing data file\n\n";
}

std::pair<std::string, float>	BitcoinExchange::parseDataLine_(std::string line, int line_number) {
	std::string	date, value_str;
	std::stringstream	ss(line);
	float		value;
	std::size_t	idx{0};

	getline(ss, date, ',');
	getline(ss, value_str);
	if (!dateIsValid_(date)) {
		std::cout << "line " << line_number << \
			": Not a valid date - not included.\n";
		return std::pair("error", value);
	}
	try {
		value = stof(value_str, &idx);
		if (!wholeStringIsNumber_(value_str, idx)) {
			std::cerr << "line " << line_number << \
			": Invalid Value: '" << value_str << "' is not a number.\n";
		}
		else {
			return std::pair(date, value);
		}
	} catch (const std::invalid_argument& e) {
		std::cerr << "line " << line_number << \
			": Invalid Agument: unable to convert string to float. Not included." << e.what() << "\n";
	} catch (const std::out_of_range& e) {
		std::cerr << "line " << line_number << \
			": Out of range: number is too large or too small. Not included." << e.what() << "\n";
	}
	return std::pair("error", value);
}

void	BitcoinExchange::calcDailyTradingTurnover(const std::string path_to_input) {
	std::ifstream	file(path_to_input);
	std::string	line;
	int			line_number{1};

	if (!file) {
		std::cerr << "Failed to open input file.\n";
		return ;
	}
	std::getline(file, line);
	if (line != "date | value") {
		std::cerr << "Input has wrong format. Expected 'date | value' as a header.\n";
	}
	while (std::getline(file, line)) {
		line_number++;
		if (line.empty()) {
			std::cout << "\n";
			continue;
		}
		std::tuple<std::string, float, Error> parsed_line = parseInputLine_(line);
		if (std::get<2>(parsed_line) == Error::NoError) {
		std::cout << constructOutputString_(std::get<0>(parsed_line),
									  		std::get<1>(parsed_line),
											std::get<2>(parsed_line));
		} else {
		std::cerr << constructOutputString_(std::get<0>(parsed_line),
									  		std::get<1>(parsed_line),
											std::get<2>(parsed_line));
		}
	}
}

std::string	BitcoinExchange::constructOutputString_(std::string date, float value, Error error) {
	std::string			output_string;
	std::stringstream	output_ss;

	auto it = exchange_data_.lower_bound(date);
	// const auto it = exchange_data_.upper_bound(date);
	switch (error) {
		case Error::NoError:
			if (it == exchange_data_.begin() && date < it->first ) {
				output_ss << date << " lies before the first record.\n";
			} else {
				if (it->first != date) it--;
				output_ss << date << " => " << value <<  " = " << it->second * value << "\n";
			}
			break ;
		case Error::WrongFormat:
			output_ss << "Error: Wrong format. Expected 'year-month-day | value'\n";
			break ;
		case Error::NotDate:
			output_ss << "Error: Not a valid date. " + date + "\n";
			break ;
		case Error::NotNumber:
			output_ss << "Error: Not a valid number - must be [0 - 1000].\n";
	}
	return output_ss.str();
}

std::tuple<std::string, float, Error>	BitcoinExchange::parseInputLine_(std::string line) {
	std::string	date, value_str;
	std::stringstream	ss(line);
	float		value;
	std::size_t	idx{0};

	ss >> date;
	getline(ss, value_str);	
	if (value_str.substr(0,3) != " | ") {
		return std::tuple(date, 0, Error::WrongFormat);
	}
	value_str = value_str.substr(3, value_str.length());
	if (!dateIsValid_(date)) {
		return std::tuple(date, 0, Error::NotDate);
	}
	try {
		value = stof(value_str, &idx);
		if (!wholeStringIsNumber_(value_str, idx) ||
			value < 0 || value > 1000) {
			return std::tuple(date, 0, Error::NotNumber);
		}
	} catch (const std::invalid_argument& e) {
		return std::tuple(date, 0, Error::NotNumber);
	} catch (const std::out_of_range& e) {
		return std::tuple(date, 0, Error::NotNumber);
	}
	return std::tuple(date, value, Error::NoError);
}

//	requires date to be in ISO-8601 format to enable lexicographical comparison of dates.
bool	BitcoinExchange::dateIsValid_(std::string date) {
	std::stringstream	ss(date);
	int					year, month, day;
	char				c1, c2;
	std::string			remainder;
	bool				is_leap_year;
	int					days_in_year[12]		= {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int					days_in_leap_year[12] 	= {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	std::regex	pattern(R"(-?\d{4}-\d{2}-\d{2})");
	if (!std::regex_match(date, pattern)) {
		return false;
	}
	ss >> year >> c1 >> month >> c2 >> day >> remainder;
	if (c1 != '-' || c2 != '-' || remainder.length() != 0) {
		return false;
	}
	if (day < 1 || month < 1 || month > 12) {
		return false;
	}
	is_leap_year = ((year%4 == 0 && !(year%100 == 0)) || year%400 == 0);
	if (day > days_in_leap_year[month-1] || (!is_leap_year && day > days_in_year[month-1])) {
		return false;
	}
	return true;
}

bool	BitcoinExchange::wholeStringIsNumber_(std::string value_str, std::size_t idx) {
	return	value_str.length() == idx || \
			value_str.substr(idx).find_first_not_of(" \n\t\r") == std::string::npos;
}
