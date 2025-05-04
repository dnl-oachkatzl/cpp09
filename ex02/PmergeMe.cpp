/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daspring <daspring@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:36:26 by daspring          #+#    #+#             */
/*   Updated: 2025/05/04 19:21:52 by daspring         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <cmath>

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(std::vector<int> unsorted_array) :
	vec_array_(unsorted_array),
	deque_array_(unsorted_array.begin(), unsorted_array.end()) {
	generateJTN_();
}

PmergeMe::~PmergeMe() {}

void	PmergeMe::doSorting() {
	// printDeque_();
	std::cout << "isVecSorted: " << isVecSorted_() << "\n";
	std::cout << "isDequeSorted: " << isDequeSorted_() << "\n";
	sortVec_();
}

void	PmergeMe::sortVec_(int level) {
	std::cout << "recursion level: " << level << "\n";
	printVec_();
}

void	PmergeMe::generateJTN_() {
	int	JTN{0}, k{1};
	int	upper_bound = std::ceil(vec_array_.size() / 2.0);

	while (true) {
		JTN = (std::pow(2, k + 1) + std::pow(-1, k) ) / 3.0;
		JTN_.push_back(JTN);
		k++;
		if (JTN > upper_bound) break ;
	}
}

void	PmergeMe::printVec_() {
	for (auto e : vec_array_) {
		std::cout << e << " ";
	}
	std::cout << "\n";
}

void	PmergeMe::printDeque_() {
	for (auto e : deque_array_) {
		std::cout << e << " ";
	}
	std::cout << "\n";
}

bool	PmergeMe::isVecSorted_() {
	int	el0 = vec_array_.front();
	for (auto el1 : vec_array_) {
		if (el0 > el1) {
			return false;
		}
		el0 = el1;
	}
	return true;
}

bool	PmergeMe::isDequeSorted_() {
	int	el0 = deque_array_.front();
	for (auto el1 : deque_array_) {
		if (el0 > el1) {
			return false;
		}
		el0 = el1;
	}
	return true;
}
