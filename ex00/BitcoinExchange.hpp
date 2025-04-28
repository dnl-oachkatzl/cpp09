/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daspring <daspring@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:48:46 by daspring          #+#    #+#             */
/*   Updated: 2025/04/28 14:26:56 by daspring         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <map>

class	BitcoinExchange {
public:
	BitcoinExchange();
	BitcoinExchange(std::string path_to_data);
	BitcoinExchange(const BitcoinExchange& other);
	~BitcoinExchange();

	BitcoinExchange&	operator=(const BitcoinExchange& other);

	void	calcDailyTradingTurnover(std::string path_to_input);

private:
	void	copyFrom_(const BitcoinExchange& other);
	void	parseData_(std::string path_to_data);
	bool	dateIsValid_(std::string date);

	std::map<std::string, float> exchange_data_;
};
