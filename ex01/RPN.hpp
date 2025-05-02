/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daspring <daspring@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 00:04:57 by daspring          #+#    #+#             */
/*   Updated: 2025/05/03 00:28:19 by daspring         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <stack>

class	RPN {
public:
	RPN();
	RPN(const RPN& other) = delete;
	~RPN();

	RPN&	operator=(const RPN& other) = delete;

	void	runOperations(const std::string input);
private:
	std::stack<int> numbers_stack_;
};

#endif	//RPN_HPP
