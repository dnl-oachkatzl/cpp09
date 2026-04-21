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

#include <algorithm>
#include <cmath>
#include <chrono>
#include <iostream>
#include <vector>

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(std::vector<int>& unsorted_array) :
	vec_(unsorted_array),
	deq_(unsorted_array.begin(), unsorted_array.end()) {
	generateJTN_(unsorted_array);
}

PmergeMe::~PmergeMe() {}

void	PmergeMe::doSorting() {
	std::cout << "Before:   ";
	vecPrint_(vec_);
	auto	start = std::chrono::high_resolution_clock::now();
	vecSort_();
	auto	end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::micro>	duration = end - start;
	std::cout << "After:    ";
	vecPrint_(vec_);
	std::cout << "using a vector-container this took "
				<< comps_ << " comparisons and "
				<< duration.count() << " us.\n";

	start = std::chrono::high_resolution_clock::now();
	comps_ = 0;
	deqSort_();
	end = std::chrono::high_resolution_clock::now();
	duration = end - start;
	std::cout << "using a deque-container this took "
				<< comps_ << " comparisons and "
				<< duration.count() << " us.\n";

	std::cout << "is Vec sorted: " << std::is_sorted(vec_.begin(), vec_.end()) << "\n";
	std::cout << "is Deq sorted: " << std::is_sorted(deq_.begin(), deq_.end()) << "\n";
}

void	PmergeMe::vecSort_(int level) {
	int		width_of_elements = 1 << level;
	int		max_i_of_a = vec_.size() / width_of_elements / 2;

	vecSortPairs_(level);

	if (max_i_of_a > 1) {
		vecSort_(level + 1);
	}

	std::vector<int> a, b, rest;
	vecSplitArray_(a, b, rest, level);

	vecPutBIntoA_(a, b, level);
	a.insert(a.end(), rest.begin(), rest.end());
	vec_ = std::move(a);
}
 
void	PmergeMe::vecPrint_(std::vector<int>& vec) {
	for (auto e : vec) {
		std::cout << e << " ";
	}
	std::cout << "\n";
}

void	PmergeMe::vecSortPairs_(int level) {
	int		width_of_elements = 1 << level;
	int		max_i_of_a = vec_.size() / width_of_elements / 2;
	int		first_idx_of_b = width_of_elements - 1;

	for (int i_of_a = 1; i_of_a <= max_i_of_a; i_of_a++) {
		int idx_of_b = first_idx_of_b + (i_of_a - 1) * width_of_elements * 2;
		int idx_of_a = idx_of_b + width_of_elements;
		comps_++;
		if (vec_[idx_of_b] > vec_[idx_of_a]) {
			vecSwapElements_(idx_of_b, width_of_elements);
		}
	}
}

void	PmergeMe::vecSwapElements_(int idx_of_b, int width) {
	int	idx_of_a = idx_of_b + width;
	for (int i = 0; i < width; i++) {
		std::swap(vec_[idx_of_a - i], vec_[idx_of_b - i]);
	}
}

//	lower starts at 1 !
int		PmergeMe::vecFindInsertPos_(std::vector<int>& a, int lower, int upper, int value, int level) {
	int width = 1 << level;
	int test = (lower + upper) / 2;
	comps_++;
	if (value < a[test * width - 1]) {
		if (test == lower) {
			return test - 1;
		} else {
			return vecFindInsertPos_(a, lower, test - 1, value, level);
		}
	} else {
		if (test == upper) {
			return test;
		} else {
			return vecFindInsertPos_(a, test + 1, upper, value, level);
		}
	}
}

void	PmergeMe::vecSplitArray_(std::vector<int>& a, std::vector<int>& b, std::vector<int>& rest, int level) {
	std::size_t width = 1 << level;
	while (vec_.size() >= 2 * width) {
		for (std::size_t i = 0; i < width; i++) {
			b.push_back(vec_.front());
			vec_.erase(vec_.begin());
		}
		for (std::size_t i = 0; i < width; i++) {
			a.push_back(vec_.front());
			vec_.erase(vec_.begin());
		}
	}
	while (vec_.size() >= 1 * width) {
		for (std::size_t i = 0; i < width; i++) {
			b.push_back(vec_.front());
			vec_.erase(vec_.begin());
		}
	}
	rest = std::move(vec_);
}

void	PmergeMe::vecPutBIntoA_(std::vector<int>& a, std::vector<int>& b, int level) {
	int			width = 1 << level;
	std::size_t	a_original_size = a.size();

	// a_idxs - do not link a_i to a directly
	// they keep track of the relative positions of a_i's to oneanother
	std::vector<int>	a_idxs;
	for (std::size_t i = 0; i <= a.size() / (1 << level); i++) {
		a_idxs.push_back(i);
	}

 	std::vector<int>	JTN_indices;
	createJTNIndices(JTN_indices, b.size(), level);
	int	insertion_position;
	for (int JTN : JTN_indices) {
		auto max_el = std::max_element(JTN_indices.begin(), JTN_indices.end());

		//	NO COMPARISON FOR a1 and b1 !!!!
		if (JTN == 1) {
			insertion_position = 0;
		} else if (JTN == *max_el && !(a_original_size == b.size())) {
			insertion_position = vecFindInsertPos_(a, 1, a_idxs[JTN - 1], b[JTN * width - 1], level);
		} else {
			insertion_position = vecFindInsertPos_(a, 1, a_idxs[JTN] - 1, b[JTN * width - 1], level);
		}
		vecInsertElements_(a, b, insertion_position, JTN, level);
		udpateA_idxs_(a_idxs, insertion_position);
	}
}

void	PmergeMe::vecInsertElements_(std::vector<int>& dest, std::vector<int>& src, int into, int from, int level) {
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


void	PmergeMe::deqSort_(int level) {
	int		width_of_elements = 1 << level;
	int		max_i_of_a = deq_.size() / width_of_elements / 2;

	deqSortPairs_(level);

	if (max_i_of_a > 1) {
		deqSort_(level + 1);
	}

	std::deque<int> a, b, rest;
	deqSplitArray_(a, b, rest, level);

	deqPutBIntoA_(a, b, level);
	a.insert(a.end(), rest.begin(), rest.end());
	deq_ = std::move(a);
}

void	PmergeMe::deqPrint_(std::deque<int>& deq) {
	for (auto e : deq) {
		std::cout << e << " ";
	}
	std::cout << "\n";
}


void	PmergeMe::deqSortPairs_(int level) {
	int		width_of_elements = 1 << level;
	int		max_i_of_a = deq_.size() / width_of_elements / 2;
	int		first_idx_of_b = width_of_elements - 1;

	for (int i_of_a = 1; i_of_a <= max_i_of_a; i_of_a++) {
		int idx_of_b = first_idx_of_b + (i_of_a - 1) * width_of_elements * 2;
		int idx_of_a = idx_of_b + width_of_elements;
		comps_++;
		if (deq_[idx_of_b] > deq_[idx_of_a]) {
			deqSwapElements_(idx_of_b, width_of_elements);
		}
	}
}


void	PmergeMe::deqSwapElements_(int idx_of_b, int width) {
	int	idx_of_a = idx_of_b + width;
	for (int i = 0; i < width; i++) {
		std::swap(deq_[idx_of_a - i], deq_[idx_of_b - i]);
	}
}

//	lower starts at 1 !
int		PmergeMe::deqFindInsertPos_(std::deque<int>& a, int lower, int upper, int value, int level) {
	int width = 1 << level;
	int test = (lower + upper) / 2;
	comps_++;
	if (value < a[test * width - 1]) {
		if (test == lower) {
			return test - 1;
		} else {
			return deqFindInsertPos_(a, lower, test - 1, value, level);
		}
	} else {
		if (test == upper) {
			return test;
		} else {
			return deqFindInsertPos_(a, test + 1, upper, value, level);
		}
	}
}

void	PmergeMe::deqSplitArray_(std::deque<int>& a, std::deque<int>& b, std::deque<int>& rest, int level) {
	std::size_t width = 1 << level;
	while (deq_.size() >= 2 * width) {
		for (std::size_t i = 0; i < width; i++) {
			b.push_back(deq_.front());
			deq_.erase(deq_.begin());
		}
		for (std::size_t i = 0; i < width; i++) {
			a.push_back(deq_.front());
			deq_.erase(deq_.begin());
		}
	}
	while (deq_.size() >= 1 * width) {
		for (std::size_t i = 0; i < width; i++) {
			b.push_back(deq_.front());
			deq_.erase(deq_.begin());
		}
	}
	rest = std::move(deq_);
}

void	PmergeMe::deqPutBIntoA_(std::deque<int>& a, std::deque<int>& b, int level) {
	int			width = 1 << level;
	std::size_t	a_original_size = a.size();

	// a_idxs - do not link a_i to a directly
	// they keep track of the relative positions of a_i's to oneanother
	std::vector<int>	a_idxs;
	for (std::size_t i = 0; i <= a.size() / (1 << level); i++) {
		a_idxs.push_back(i);
	}

 	std::vector<int>	JTN_indices;
	createJTNIndices(JTN_indices, b.size(), level);
	int	insertion_position;
	for (int JTN : JTN_indices) {
		auto max_el = std::max_element(JTN_indices.begin(), JTN_indices.end());

		//	NO COMPARISON FOR a1 and b1 !!!!
		if (JTN == 1) {
			insertion_position = 0;
		} else if (JTN == *max_el && !(a_original_size == b.size())) {
			insertion_position = deqFindInsertPos_(a, 1, a_idxs[JTN - 1], b[JTN * width - 1], level);
		} else {
			insertion_position = deqFindInsertPos_(a, 1, a_idxs[JTN] - 1, b[JTN * width - 1], level);
		}
		deqInsertElements_(a, b, insertion_position, JTN, level);
		udpateA_idxs_(a_idxs, insertion_position);
	}
}

void	PmergeMe::deqInsertElements_(std::deque<int>& dest, std::deque<int>& src, int into, int from, int level) {
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

void	PmergeMe::generateJTN_(std::vector<int>& unsorted_array) {
	int	JTN{0}, k{1};
	int	upper_bound = std::ceil(unsorted_array.size() / 2.0);

	while (true) {
		// page 185, equation (13) of D.Knuth's AOCP - volume 3
		JTN = (std::pow(2, k + 1) + std::pow(-1, k) ) / 3.0;
		JTN_.push_back(JTN);
		k++;
		if (JTN > upper_bound) break ;
	}
}

void	PmergeMe::createJTNIndices(std::vector<int>& JTN_indices, size_t length, int level) {
	int	width = 1 << level;

	std::vector<int>	b_idxs;
	for (std::size_t i = 0; i <= length / width; i++) {
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

