/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daspring <daspring@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:36:53 by daspring          #+#    #+#             */
/*   Updated: 2025/05/07 23:04:46 by daspring         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <memory>

struct Node;

class	PmergeMe {
public:
	PmergeMe() = delete;
	PmergeMe(std::vector<int>& unsorted_array);
	PmergeMe(const PmergeMe& other) = delete;
	~PmergeMe();

	PmergeMe& operator=(const PmergeMe& other) = delete;

	void				doSorting();

private:
	void				vecSort_(int level = 0);
	void				vecPrint_(std::vector<int>& vec);
	void				vecSortPairs_(int level);
	void				vecSwapElements_(int idx_of_b, int width);
	void				vecSplitArray_(std::vector<int>& a, std::vector<int>& b, std::vector<int>& rest, int level);
	void				vecPutBIntoA_(std::vector<int>& a, std::vector<int>& b, int level);
	int					vecFindInsertPos_(std::vector<int>& a, int fi, int li, int value, int level);
	void				vecInsertElements_(std::vector<int>& dest, std::vector<int>& src, int into, int from, int level);

	void				deqSort_(int level = 0);
	void				deqPrint_(std::deque<int>& deq);
	void				deqSortPairs_(int level);
	void				deqSwapElements_(int idx_of_b, int width);
	void				deqSplitArray_(std::deque<int>& a, std::deque<int>& b, std::deque<int>& rest, int level);
	void				deqPutBIntoA_(std::deque<int>& a, std::deque<int>& b, int level);
	int					deqFindInsertPos_(std::deque<int>& a, int fi, int li, int value, int level);
	void				deqInsertElements_(std::deque<int>& dest, std::deque<int>& src, int into, int from, int level);

	void				udpateA_idxs_(std::vector<int>& a_idxs, int insertion_position);
	void				generateJTN_(std::vector<int>& unsorted_array);
	void				createJTNIndices(std::vector<int>& JTN_indices, size_t length, int level);

	std::vector<int>	vec_;
	std::deque<int>		deq_;
	std::deque<int>		JTN_;
	int					comps_{0};
};

#endif	// PMERGEME_HPP
