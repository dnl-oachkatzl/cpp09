/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daspring <daspring@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:06:03 by daspring          #+#    #+#             */
/*   Updated: 2025/05/04 19:51:15 by daspring         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

#include "PmergeMe.hpp"

void	putInputIntoArray(std::vector<int>& input_array, char **input, const int len);
bool	wholeStringIsNumber_(std::string value_str, std::size_t idx);

int	main(int argc, char** argv) {
	if (argc == 1) {
		std::cerr << "No input given.\n";
		return EXIT_FAILURE;
	}
		std::vector<int>	input_array;
	try {
		putInputIntoArray(input_array, ++argv, --argc);
	} catch (const std::invalid_argument& e) {
		std::cerr << "argument not an integer: " << e.what() << "\n";
		return EXIT_FAILURE;
	}

	PmergeMe	ford_johnson(input_array);
	ford_johnson.doSorting();

	return EXIT_SUCCESS;
}

void	putInputIntoArray(std::vector<int>& input_array, char **input, const int len) {
	std::size_t	idx = 0;

	for (int i = 0; i < len; i++) {
		input_array.push_back(std::stod(input[i], &idx));
		if (!wholeStringIsNumber_(input[i], idx)) {
			throw std::invalid_argument(input[i]);
		}
	}
}

bool	wholeStringIsNumber_(std::string value_str, std::size_t idx) {
	return	value_str.length() == idx || \
			value_str.substr(idx).find_first_not_of(" \n\t\r") == std::string::npos;
}
