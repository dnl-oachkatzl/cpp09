/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daspring <daspring@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:36:26 by daspring          #+#    #+#             */
/*   Updated: 2025/05/04 21:17:42 by daspring         ###   ########.fr       */
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

//	TODO: what if array is already sorted?
void	PmergeMe::doSorting() {
	// printDeque_();
	std::cout << "isVecSorted: " << isVecSorted_() << "\n";
	std::cout << "isDequeSorted: " << isDequeSorted_() << "\n";
	std::cout << "\n\n";
	sortVec_();
}

void	PmergeMe::sortVec_(int level) {
	int		width_of_elements = std::pow(2, level);
	int		max_i_of_a = vec_array_.size() / (2 * width_of_elements);
	int		max_i_of_b = std::ceil(vec_array_.size() / (2.0 * width_of_elements));
	int		first_idx_of_b = calc_first_idx_of_b_(level);
	int		first_idx_of_a = first_idx_of_b + width_of_elements;

	std::cout << "recursion level: " << level << "\n";
	std::cout << "width of elements: " << width_of_elements << "\n";
	std::cout << "max_i_of_a: " << max_i_of_a << "\n";
	std::cout << "max_i_of_b: " << max_i_of_b << "\n";
	std::cout << "first_idx_of_a: " << first_idx_of_a << "\n";
	std::cout << "first_idx_of_b: " << first_idx_of_b << "\n";
	std::cout << "\n\n";
	printVec_();

	// sort pairs
	for (int i_of_a = 1; i_of_a <= max_i_of_a; i_of_a++) {
		int idx_of_b = first_idx_of_b + (i_of_a-1) * width_of_elements * 2;
		int idx_of_a = idx_of_b + width_of_elements;
		if (vec_array_[idx_of_b] > vec_array_[idx_of_a]) {	// TODO: swap function which takes idx_of_b and width_of_elements as parameters
			int temp = vec_array_[idx_of_b];
			vec_array_[idx_of_b] = vec_array_[idx_of_a];
			vec_array_[idx_of_a] = temp;
		}
	}

	printVec_();
	if (max_i_of_a > 1) {
		sortVec_(++level);
	}

	// binary insertion
	// do I need an array which holds the idx for all bs? because the idx will change once insertion starts.
	// b_i | 1 | 2 | 3 | 4 |
	// -----------------------
	// idx |
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

int		PmergeMe::calc_first_idx_of_b_(const int level) {
	int		first_idx_of_b{0};

	for (int i = 0; i < level; i++) {
		int	step = std::pow(2, i);
		first_idx_of_b += step;
	}
	return first_idx_of_b;
}
