/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daspring <daspring@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:36:26 by daspring          #+#    #+#             */
/*   Updated: 2025/05/07 23:15:28 by daspring         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <cmath>

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(std::vector<int>& unsorted_array) :
	vec_array_(unsorted_array),
	deque_array_(unsorted_array.begin(), unsorted_array.end()) {
	generateJTN_(unsorted_array);
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
	int		width_of_elements = 1 << level;
	int		max_i_of_a = vec_array_.size() / width_of_elements / 2;
	// int		max_i_of_b = ceil(vec_array_.size() / width_of_elements / 2.0);
	int		first_idx_of_b = width_of_elements - 1;
	// int		first_idx_of_a = first_idx_of_b + width_of_elements;

	std::cout << "RECURSION LEVEL: " << level << "\n";
	// std::cout << "width of elements: " << width_of_elements << "\n";
	// std::cout << "max_i_of_a: " << max_i_of_a << "\n";
	// std::cout << "max_i_of_b: " << max_i_of_b << "\n";
	// std::cout << "first_idx_of_a: " << first_idx_of_a << "\n";
	// std::cout << "first_idx_of_b: " << first_idx_of_b << "\n";
	printVec_(vec_array_);

	// sort pairs
	for (int i_of_a = 1; i_of_a <= max_i_of_a; i_of_a++) {
		int idx_of_b = first_idx_of_b + (i_of_a - 1) * width_of_elements * 2;
		int idx_of_a = idx_of_b + width_of_elements;
		if (vec_array_[idx_of_b] > vec_array_[idx_of_a]) {
			swapVecElements_(idx_of_b, width_of_elements);
		}
	}
	printVec_(vec_array_);

	if (max_i_of_a > 1) {
		sortVec_(level + 1);
	}

	std::cout << "\n";
	std::cout << "now on the way back\nrec_level: " << level << "\n";

//		split array into a and b and rest
	std::vector<int> a, b, rest;
	std::cout << "vec a:\n";
	printVec_(a);
	std::cout << "vec b:\n";
	printVec_(b);
	std::cout << "vec rest:\n";
	printVec_(rest);
	splitVecArray_(a, b, rest, level);
	std::cout << "vec a:\n";
	printVec_(a);
	std::cout << "vec b:\n";
	printVec_(b);
	std::cout << "vec rest:\n";
	printVec_(rest);
	std::cout << "\n";

//			insert b into a using the series
	putBIntoA_(a, b, level);

//			add rest to a
	a.insert(a.end(), rest.begin(), rest.end());
//			move a into vec_array_
	vec_array_ = std::move(a);

	printVec_(vec_array_);

	// std::cout << "insert number at pos: " << findInsertPos_(0, 6, 0) << "\n";
	// std::cout << "insert number at pos: " << findInsertPos_(0, 6, 1) << "\n";

	// binary insertion
	// do I need an array which holds the idx for all bs? because the idx will change once insertion starts.
	// b_i | 1 | 2 | 3 | 4 |
	// -----------------------
	// idx |


}

void	PmergeMe::generateJTN_(std::vector<int>& unsorted_array) {
	int	JTN{0}, k{1};
	int	upper_bound = std::ceil(unsorted_array.size() / 2.0);

	while (true) {
		JTN = (std::pow(2, k + 1) + std::pow(-1, k) ) / 3.0;
		JTN_.push_back(JTN);
		k++;
		if (JTN > upper_bound) break ;
	}
}

void	PmergeMe::printVec_(std::vector<int>& vec) {
	for (auto e : vec) {
		std::cout << e << " ";
	}
	std::cout << "\n";
}

void	PmergeMe::printDeque_(std::deque<int>& deq) {
	for (auto e : deq) {
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

// int		PmergeMe::calcFirstIdxOfB_(const int level) {
// 	int		first_idx_of_b{0};

// 	for (int i = 0; i < level; i++) {
// 		int	step = 1 << i;
// 		first_idx_of_b += step;
// 	}
// 	return first_idx_of_b;
// }

void	PmergeMe::swapVecElements_(int idx_of_b, int width) {
	int	idx_of_a = idx_of_b + width;
	for (int i = 0; i < width; i++) {
		std::swap(vec_array_[idx_of_a - i], vec_array_[idx_of_b - i]);
	}
}

//	lower starts at 1 !
int		PmergeMe::findInsertPos_(std::vector<int>& a, int lower, int upper, int value, int level) {
	int width = 1 << level;
	(void)width;
	int test = (lower + upper) / 2;
std::cout << "test: " << test << "\n";
	if (value < a[test * width - 1]) {
		if (test == lower) {
			return test - 1;
		} else {
			return findInsertPos_(a, lower, test - 1, value, level);
		}
	} else if (a[test * width - 1] < value) {
		if (test == upper) {
			return test;
		} else {
			return findInsertPos_(a, test + 1, upper, value, level);
		}
	} else {
			return test;
		}
}

void	PmergeMe::splitVecArray_(std::vector<int>& a, std::vector<int>& b, std::vector<int>& rest, int level) {
	int width = 1 << level;
	while (vec_array_.size() >= 2 * static_cast<std::size_t>(width)) {
		for (int i = 0; i < width; i++) {
			b.push_back(vec_array_.front());
			vec_array_.erase(vec_array_.begin());
		}
		for (int i = 0; i < width; i++) {
			a.push_back(vec_array_.front());
			vec_array_.erase(vec_array_.begin());
		}
	}
	while (vec_array_.size() >= 1 * static_cast<std::size_t>(width)) {
		for (int i = 0; i < width; i++) {
			b.push_back(vec_array_.front());
			vec_array_.erase(vec_array_.begin());
		}
	}
	rest = std::move(vec_array_);
}


void	PmergeMe::putBIntoA_(std::vector<int>& a, std::vector<int>& b, int level) {
	int	width = 1 << level;

	// a_idxs and b_idxs - do not link b_i to b directly
	// they keep track of the relative positions of b_i's to oneanother
	std::vector<int>	a_idxs;
	// std::vector<int>	b_idxs;
	// for (std::size_t i = 0; i <= a.size(); i++) {
	// 	a_idxs.push_back(i * width - 1);
	// }
	// for (std::size_t i = 0; i <= b.size(); i++) {
	// 	b_idxs.push_back(i * width - 1);
	// }
	for (std::size_t i = 0; i <= a.size(); i++) {
		a_idxs.push_back(i);
	}
	// for (std::size_t i = 0; i <= b.size(); i++) {
	// 	b_idxs.push_back(i);
	// }

 	std::vector<int>	JTN_indices;
	createJTNIndices(JTN_indices, b, level);
	// std::cout << "JTN points to those values of b: ";
	for (auto e : JTN_indices) {
//	NO COMPARISON FOR a1 and b1 !!!!
		if (e == 1) {
			;
			// just put b before a
			// update a_idxs
		} else {
			// std::cout << b[b_idxs[e * width - 1]] << " ";
			std::cout << "a_idxs[e - 1]" << a_idxs[e - 1] << "\n";
			//	b_i has already been compared to a_i, we want to compare it to a_i-1)
			std::cout << "for JTN: " << e << " with corresponding b: " << b[e * width - 1] << "\n";
			int insertion_position = findInsertPos_(a, 1, a_idxs[e - 1], b[e * width - 1], level);
			std::cout << "the right index for insertion into a is: " << insertion_position << "\n\n";
		}
	}
	std::cout << "\n";
	a.insert(a.begin(), b.begin(), b.end());
}

void	PmergeMe::createJTNIndices(std::vector<int>& JTN_indices, std::vector<int>& b, int level) {
	int	width = 1 << level;

	std::vector<int>	b_idxs;
	for (std::size_t i = 0; i <= b.size() / width; i++) {
		b_idxs.push_back(i);
	}
	
	std::cout << "idx of b according to JTN: ";
	for (std::size_t i = 0; i < JTN_.size(); i++) {
		bool	reached_end = false;
		int	JTN = JTN_[i];
		for (std::size_t k = JTN; k > 0; k--) {
			if (k > b_idxs.size() - 1) {
				reached_end = true;
			} else if (b_idxs[k] == 0) {
				break ;
			} else {
			JTN_indices.push_back(k);
				b_idxs[k] = 0;
			}
		}
		if (reached_end == true) break ;
	}
	printVec_(JTN_indices);
}

// void	PmergeMe::moveVecElements_(int into, int from, int len) {
// 	int idx_into = len - 1 + into * len;		// might also start at zero
// 	int idx_from = len - 1 + from * len;

// 	for (int i = 0; i < len; i++) {
// 		;
// 	}
// }
