/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daspring <daspring@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:48:46 by daspring          #+#    #+#             */
/*   Updated: 2025/04/30 19:15:46 by daspring         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>

enum class Error {
	NoError,
	WrongFormat,
	NotDate,
	NotNumber,
	NegNumber,
	LargeNumber
};

class	BitcoinExchange {
public:
	BitcoinExchange();
	BitcoinExchange(std::string path_to_data);
	BitcoinExchange(const BitcoinExchange& other);
	~BitcoinExchange();

	BitcoinExchange&	operator=(const BitcoinExchange& other);

	void	calcDailyTradingTurnover(const std::string path_to_input);

private:
	void	copyFrom_(const BitcoinExchange& other);
	void	parseData_(std::string path_to_data);
	std::pair<std::string, float>	parseDataLine_(std::string line, int line_number);
	// std::pair<std::string, float>	parseInputLine_(std::string line);
	std::tuple<std::string, float, Error>	parseInputLine_(std::string line);
	float	calcOneDay_(std::pair<std::string, float>);
	bool	dateIsValid_(std::string date);
	bool	wholeStringIsNumber_(std::string value_str, std::size_t idx);

	std::map<std::string, float> exchange_data_;
};

#endif	//BITCOINEXCHANGE_HPP
