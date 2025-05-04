/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daspring <daspring@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:36:53 by daspring          #+#    #+#             */
/*   Updated: 2025/05/04 14:50:47 by daspring         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>

class	PmergeMe {
public:
	PmergeMe();
	PmergeMe(const PmergeMe& other) = delete;
	~PmergeMe();

	PmergeMe& operator=(const PmergeMe& other) = delete;

private:
	void				sortVec_(std::vector<int> vec_array, int level = 0);
	void				sortDeque_(std::deque<int> deque_array, int level = 0);
	void				printVec_();
	void				printDeque_();
	bool				isVecSorted_();
	bool				isDequeSorted_();

	std::vector<int>	vec_array_;
	std::deque<int>		deque_array_;
};

#endif	// PMERGEME_HPP
