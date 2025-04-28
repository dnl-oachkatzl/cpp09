/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daspring <daspring@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:48:39 by daspring          #+#    #+#             */
/*   Updated: 2025/04/28 14:29:05 by daspring         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
