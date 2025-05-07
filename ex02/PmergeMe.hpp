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

class	PmergeMe {
public:
	PmergeMe() = delete;
	PmergeMe(std::vector<int> unsorted_array);
	PmergeMe(const PmergeMe& other) = delete;
	~PmergeMe();

	PmergeMe& operator=(const PmergeMe& other) = delete;

	void				doSorting();

private:
	void				sortVec_(int level = 0);
	void				sortDeque_(std::deque<int>& deque_array, int level = 0);
	void				printVec_();
	void				printDeque_();
	bool				isVecSorted_();
	bool				isDequeSorted_();
	void				generateJTN_();
	void				swapVecElements_(int idx_of_b, int width);
	int					calcFirstIdxOfB_(const int level);
	int					findEndPos_(int fi, int li, int value, int step);

	std::vector<int>	vec_array_;
	std::deque<int>		deque_array_;
	std::deque<int>		JTN_;
};

#endif	// PMERGEME_HPP
