/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daspring <daspring@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:48:39 by daspring          #+#    #+#             */
/*   Updated: 2025/04/29 00:57:16 by daspring         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <charconv>
#include <stdexcept>
#include <utility>

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() : BitcoinExchange("./data.csv") {};

BitcoinExchange::BitcoinExchange(std::string path_to_data) {
	parseData_(path_to_data);
	// for (const auto& a : exchange_data_) {
	// 	std::cout << a.first << " - " << a.second << "\n";
	// }
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
		std::pair<std::string, float> map_entry = parseDataLine_(line, line_number);
		if (map_entry.first != "error") {
			if (exchange_data_.insert({map_entry.first, map_entry.second}).second == false) {
				std::cout << "line " << line_number << " : duplicate date - not included.\n";
			}
		}
	}
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
		std::pair<std::string, float> parsed_line = parseInputLine_(line);
		float	one_day = calcOneDay_(parsed_line);
		std::cout << parsed_line.first << "=> " << parsed_line.second << " = " << one_day << "\n";
			// std::cout << date << "=> " << value;
	}
}

std::pair<std::string, float>	BitcoinExchange::parseDataLine_(std::string line, int line_number) {
	std::string	date, value_str;
	std::stringstream	ss(line);
	float		value;
	getline(ss, date, ',');
	getline(ss, value_str);
	// std::cout << date << " - " << value_str << "\n";
	try {
		value = stof(value_str);
		// std::cout << "value_str: " << value_str << ", to_string(value): " << std::to_chars(value) << "\n";
		// if (dateIsValid_(date) && (value_str == std::to_string(value))) {
		if (dateIsValid_(date)) {
			return std::pair(date, value);
			// std::cout << date << " - " << value << "\n";
		}
		else {
			// std::cout << "line " << line_number << " : (potentially) bad input - not included.\n";
			std::cout << "line " << line_number << " : not a date - not included.\n";
		}
	} catch (const std::invalid_argument& e) {
		std::cout << "line " << line_number << \
			": Invalid Agument: unable to convert string to float." << e.what() << "\n";
	} catch (const std::out_of_range& e) {
		std::cout << "line " << line_number << \
			": Out of range: number is too large or too small." << e.what() << "\n";
	}
	return std::pair("error", value);
}

std::pair<std::string, float>	BitcoinExchange::parseInputLine_(std::string line) {
	std::string	date, value_str;
	std::stringstream	ss(line);
	float		value;
	getline(ss, date, '|');
	getline(ss, value_str);
	// std::cout << date << " - " << value_str << "\n";


	try {
		value = stof(value_str);
		// std::cout << "value_str: " << value_str << ", to_string(value): " << std::to_chars(value) << "\n";
		// if (dateIsValid_(date) && (value_str == std::to_string(value))) {
		if (dateIsValid_(date)) {
			return std::pair(date, value);
			// std::cout << date << " - " << value << "\n";
		}
		else {
			std::cout <<  "Error: not a date => " << date << "\n";
		}
	} catch (const std::invalid_argument& e) {
		std::cout << "Invalid Agument: unable to convert string to float." << e.what() << "\n";
	} catch (const std::out_of_range& e) {
		std::cout << "Out of range: number is too large or too small." << e.what() << "\n";
	}
	return std::pair("error", value);
}

bool	BitcoinExchange::dateIsValid_(std::string date) {
	std::stringstream	ss(date);
	int					year, month, day;
	char				c1, c2;
	bool				is_leap_year;
	int					days_in_year[12]		= {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int					days_in_leap_year[12] 	= {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	ss >> year >> c1 >> month >> c2 >> day;
	is_leap_year = ((year%4 == 0 && !(year%100 == 0)) || year%400 == 0);
	if (day < 1 || month < 1 || month > 12) {
		return false;
	}
	if (day > days_in_leap_year[month-1] || (!is_leap_year && day > days_in_year[month-1])) {
		return false;
	}
	return true;
}
