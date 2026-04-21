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
	if (argc != 2) {
		std::cout	<< "Wrong arguments. Expected usage: './BTC <\"arguments to be evaluated\">'\n"
					<< "e.g.: './BTC \"7 6 *\"'\n";
		return EXIT_FAILURE;
	}
	RPN	RPN;
	RPN.runOperations(argv[1]);

	// std::cout << "\n'3 4 +' equates to '3 + 4' which is 7\n";
	// RPN.runOperations("3 4 +");
	// std::cout << "\n'5 1 2 + 4 * + 3 -' equates to '5 + (1 + 2) * 4 - 3' which is 14\n";
	// RPN.runOperations("5 1 2 + 4 * + 3 -");
	// std::cout << "\n'9 1 -' equates to '9 - 1' which is 8\n";
	// RPN.runOperations("9 1 -");
	// std::cout << "\n'2 3 *' equates to '2 * 3' which is 6\n";
	// RPN.runOperations("2 3 *");
	// std::cout << "\n'8 4 /' equates to '8 / 4' which is 2\n";
	// RPN.runOperations("8 4 /");
	// std::cout << "\n'7 2 3 * -' equates to '7 - 2 * 3' which is 1\n";
	// RPN.runOperations("7 2 3 * -");
	// std::cout << "\n'+' equates to '+' which is INVALID\n";
	// RPN.runOperations("+");
	// std::cout << "\n'3 +' equates to '3 +' which is INVALID\n";
	// RPN.runOperations("3 +");
	// std::cout << "\n'3 3 3 +' equates to '3 + 3 3' which is INVALID\n";
	// RPN.runOperations("3 3 3 +");
	// std::cout << "\n'3 a +' equates to '3 + a' which is INVALID\n";
	// RPN.runOperations("3 a +");
	// std::cout << "\n'10 2 +' equates to '10 + 2' which is INVALID\n";
	// RPN.runOperations("10 2 +");
	// std::cout << "\n'4 0 /' equates to '4 / 0' which is UNDEFINED\n";
	// RPN.runOperations("4 0 /");

	return EXIT_SUCCESS;
}
