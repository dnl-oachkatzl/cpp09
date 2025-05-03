/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daspring <daspring@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 00:04:57 by daspring          #+#    #+#             */
/*   Updated: 2025/05/03 18:09:19 by daspring         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <stack>

enum class Error {
	NoError,
	Error,
};

class	RPN {
public:
	RPN();
	RPN(const RPN& other) = delete;
	~RPN();

	RPN&	operator=(const RPN& other) = delete;

	void	runOperations(const std::string input);
private:
	std::pair<float, Error> handleWord_(std::string word);

	std::stack<float> numbers_stack_;
};

#endif	//RPN_HPP
