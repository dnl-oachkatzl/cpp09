/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daspring <daspring@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:48:28 by daspring          #+#    #+#             */
/*   Updated: 2025/04/29 00:21:59 by daspring         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "BitcoinExchange.hpp"

int	main(int argc, char** argv) {
	if (argc != 2) {
		std::cerr << "wrong parameters. expected './btc <path_to_input_file>'\n";
		return EXIT_FAILURE;
	}
	try {
		BitcoinExchange btc;
		btc.calcDailyTradingTurnover(argv[1]);
	} catch (const std::runtime_error& e) {
		std::cerr << "Failed to construct class BitcoinExchange: " << e.what() << "\n";
	}

	return EXIT_SUCCESS;
}
