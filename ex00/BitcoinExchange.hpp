/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daspring <daspring@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:48:46 by daspring          #+#    #+#             */
/*   Updated: 2025/04/29 00:56:57 by daspring         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <map>
#include <utility>

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
	std::pair<std::string, float>	parseInputLine_(std::string line);
	bool	dateIsValid_(std::string date);
	float	calcOneDay_(std::pair<std::string, float>);

	std::map<std::string, float> exchange_data_;
};
