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
	printVec_(vec_array_);
	std::cout << "isVecSorted: " << isVecSorted_(vec_array_) << "\n";
	std::cout << "isDequeSorted: " << isDequeSorted_() << "\n";
	std::cout << "\n\n";
	auto	start = std::chrono::high_resolution_clock::now();
	sortVec_();
	auto	end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::micro>	duration = end - start;
	printVec_(vec_array_);
	std::cout << "isVecSorted: " << std::is_sorted(vec_array_.begin(), vec_array_.end()) << "\n";
	std::cout << "this took "
				<< comps_ << " comparisons and "
				<< duration.count() << " us.\n";

	std::cout << "isDequeSorted: " << isDequeSorted_() << "\n";
}

void	PmergeMe::sortVec_(int level) {
	int		width_of_elements = 1 << level;
	int		max_i_of_a = vec_array_.size() / width_of_elements / 2;

	sortVecPairs_(level);

	if (max_i_of_a > 1) {
		sortVec_(level + 1);
	}

	std::vector<int> a, b, rest;
	splitVecArray_(a, b, rest, level);

	putBIntoA_(a, b, level);
	a.insert(a.end(), rest.begin(), rest.end());
	vec_array_ = std::move(a);
}
 
void	PmergeMe::sortVecPairs_(int level) {
	int		width_of_elements = 1 << level;
	int		max_i_of_a = vec_array_.size() / width_of_elements / 2;
	int		first_idx_of_b = width_of_elements - 1;

	for (int i_of_a = 1; i_of_a <= max_i_of_a; i_of_a++) {
		int idx_of_b = first_idx_of_b + (i_of_a - 1) * width_of_elements * 2;
		int idx_of_a = idx_of_b + width_of_elements;
		comps_++;
		if (vec_array_[idx_of_b] > vec_array_[idx_of_a]) {
			swapVecElements_(idx_of_b, width_of_elements);
		}
	}
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

bool	PmergeMe::isVecSorted_(std::vector<int>& vec) {
	int	el0 = vec.front();
	for (auto el1 : vec) {
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

void	PmergeMe::swapVecElements_(int idx_of_b, int width) {
	int	idx_of_a = idx_of_b + width;
	for (int i = 0; i < width; i++) {
		std::swap(vec_array_[idx_of_a - i], vec_array_[idx_of_b - i]);
		// std::swap(vec_array_[idx_of_b - i], vec_array_[idx_of_b + width - i]);
	}
	// std::swap_ranges(vec_array_.begin() + idx_of_b - width + 1,
	// 				vec_array_.begin() + idx_of_b + 1,
	// 				vec_array_.begin() + idx_of_b + 1);
}

//	lower starts at 1 !
int		PmergeMe::findInsertPos_(std::vector<int>& a, int lower, int upper, int value, int level) {
	int width = 1 << level;
	int test = (lower + upper) / 2;
	comps_++;
	if (value < a[test * width - 1]) {
		if (test == lower) {
			return test - 1;
		} else {
			return findInsertPos_(a, lower, test - 1, value, level);
		}
	} else {
		if (test == upper) {
			return test;
		} else {
			return findInsertPos_(a, test + 1, upper, value, level);
		}
	}
}
// int		PmergeMe::findInsertPos_(std::vector<int>& a, int lower, int upper, int value, int level) {
// 	int width = 1 << level;
// 	int test = (lower + upper) / 2;
// 	comps_++;
// 	if (value < a[test * width - 1]) {
// 		if (test == lower) {
// 			return test - 1;
// 		} else {
// 			return findInsertPos_(a, lower, test - 1, value, level);
// 		}
// 	} else if (a[test * width - 1] < value) {
// 	comps_++;
// 		if (test == upper) {
// 			return test;
// 		} else {
// 			return findInsertPos_(a, test + 1, upper, value, level);
// 		}
// 	} else {
// 	comps_++;
// 			return test;
// 		}
// }

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
	int			width = 1 << level;
	std::size_t	a_original_size = a.size();

	// a_idxs - do not link a_i to a directly
	// they keep track of the relative positions of a_i's to oneanother
	std::vector<int>	a_idxs;
	for (std::size_t i = 0; i <= a.size() / (1 << level); i++) {
		a_idxs.push_back(i);
	}

 	std::vector<int>	JTN_indices;
	createJTNIndices(JTN_indices, b, level);
	int	insertion_position;
	for (auto JTN : JTN_indices) {
		auto max_el = std::max_element(JTN_indices.begin(), JTN_indices.end());

		//	NO COMPARISON FOR a1 and b1 !!!!
		if (JTN == 1) {
			insertion_position = 0;
		} else if (JTN == *max_el && !(a_original_size == b.size())) {
			insertion_position = findInsertPos_(a, 1, a_idxs[JTN - 1], b[JTN * width - 1], level);
		} else {
			insertion_position = findInsertPos_(a, 1, a_idxs[JTN] - 1, b[JTN * width - 1], level);
		}
		insertVecElements_(a, b, insertion_position, JTN, level);
		udpateA_idxs_(a_idxs, insertion_position);
	}
}

void	PmergeMe::createJTNIndices(std::vector<int>& JTN_indices, std::vector<int>& b, int level) {
	int	width = 1 << level;

	std::vector<int>	b_idxs;
	for (std::size_t i = 0; i <= b.size() / width; i++) {
		b_idxs.push_back(i);
	}
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
}

void	PmergeMe::insertVecElements_(std::vector<int>& dest, std::vector<int>& src, int into, int from, int level) {
	int	width = 1 << level;

	std::deque<int>	temp;
	int idx_into = into * width;
	int idx_from = (from - 1) * width;

	for (int i = 0; i < width; i++) {
		temp.push_front(src[idx_from + i]);
	}
	for (int i = 0; i < width; i++) {
		dest.insert(dest.begin() + idx_into, temp[i]);
	}
}

void	PmergeMe::udpateA_idxs_(std::vector<int>& a_idxs, int insertion_position) {
	for (auto& el : a_idxs) {
		if (el >= insertion_position) el++;
	}
}
