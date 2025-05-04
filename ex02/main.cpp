/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daspring <daspring@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:06:03 by daspring          #+#    #+#             */
/*   Updated: 2025/05/03 20:24:03 by daspring         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>
#include <iostream>


float	index_series(int k) {
	std::cout << std::pow(2, k + 1) << " + " << std::pow(-1, k) << " / 3.0\n";
	return (std::pow(2, k + 1) + std::pow(-1, k) ) / 3.0;
}

int	main(int argc, char** argv) {
	(void)argc;
	(void)argv;

	for (int i = 0; i < 15; i++) {
		float index = index_series(i);
		std::cout << "k = " << i << " -> t = " << index << "\n";
	}

	return EXIT_SUCCESS;
}
