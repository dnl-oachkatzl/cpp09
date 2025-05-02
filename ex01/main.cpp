/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daspring <daspring@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 00:00:44 by daspring          #+#    #+#             */
/*   Updated: 2025/05/03 00:14:27 by daspring         ###   ########.fr       */
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
	return EXIT_SUCCESS;
}
