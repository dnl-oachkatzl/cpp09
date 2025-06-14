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
	void				sortVec_(int level = 0);
	void				sortDeque_(int level = 0);
	void				printVec_(std::vector<int>& vec);
	void				printDeque_(std::deque<int>& deq);
	bool				isVecSorted_(std::vector<int>& vec);
	bool				isDequeSorted_();
	void				generateJTN_(std::vector<int>& unsorted_array);
	void				createJTNIndices(std::vector<int>& JTN_indices, std::vector<int>& b, int level);
	void				sortVecPairs_(int level);
	void				swapVecElements_(int idx_of_b, int width);
	void				splitVecArray_(std::vector<int>& a, std::vector<int>& b, std::vector<int>& rest, int level);
	void				putBIntoA_(std::vector<int>& a, std::vector<int>& b, int level);
	int					findInsertPos_(std::vector<int>& a, int fi, int li, int value, int level);
	void				insertVecElements_(std::vector<int>& dest, std::vector<int>& src, int into, int from, int level);
	void				udpateA_idxs_(std::vector<int>& a_idxs, int insertion_position);

	std::vector<int>	vec_array_;
	std::deque<int>		deque_array_;
	std::deque<int>		JTN_;
	int					comps_{0};
};

#endif	// PMERGEME_HPP
