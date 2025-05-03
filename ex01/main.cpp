/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daspring <daspring@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 00:00:44 by daspring          #+#    #+#             */
/*   Updated: 2025/05/03 19:34:42 by daspring         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "RPN.hpp"

int	main(int argc, char** argv) {
	(void)argv;
	if (argc != 2) {
		std::cout	<< "Wrong arguments. Expected usage: './BTC <\"arguments to be evaluated\">'\n"
					<< "e.g.: './BTC \"7 6 *\"'\n";
	}
	RPN	RPN;
	RPN.runOperations(argv[1]);

	// RPN.runOperations("3 4 +");
	// RPN.runOperations("5 1 2 + 4 * + 3 -");
	// RPN.runOperations("9 1 -");
	// RPN.runOperations("2 3 *");
	// RPN.runOperations("8 4 /");
	// RPN.runOperations("7 2 3 * -");
	// RPN.runOperations("+");
	// RPN.runOperations("3 +");
	// RPN.runOperations("3 3 3 +");
	// RPN.runOperations("3 a +");
	// RPN.runOperations("10 2 +");
	// RPN.runOperations("4 0 /");

	return EXIT_SUCCESS;
}
