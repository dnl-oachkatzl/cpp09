// /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daspring <daspring@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 00:06:07 by daspring          #+#    #+#             */
/*   Updated: 2025/05/03 18:26:22 by daspring         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cctype>
#include <stack>
#include <string>
#include <sstream>
#include <iostream>
#include <utility>

#include "RPN.hpp"

RPN::RPN() {}
RPN::~RPN() {}

void	RPN::runOperations(const std::string input) {
	bool	no_error_occured{true};
	numbers_stack_ = std::stack<float>();
	std::stringstream	ss(input);

	while (true) {
		std::string	word;
		ss >> word;
		if (word.length() == 0) break;
		std::pair<float, Error>	handled_word = handleWord_(word);
		if (handled_word.second == Error::Error) {
			no_error_occured = false;
			break ;
		} else {
			numbers_stack_.push(handled_word.first);
		}
	}
	if (no_error_occured) {
		if (numbers_stack_.size() == 1) {
			std::cout << numbers_stack_.top() << "\n";
		} else if (numbers_stack_.size() > 1) {
			std::cerr << "Invalid expression - not enough operators.\n";
		}
	}
}

std::pair<float, Error>	RPN::handleWord_(std::string word) {
	float	left, right;
	if (word.length() == 1) {
		if (std::isdigit(word[0])) {
			return std::pair(std::stoi(word), Error::NoError);
		}
		if (word[0] == '+' || word[0] == '-' ||
			word[0] == '*' || word[0] == '/') {
			if (numbers_stack_.size() < 2) {
				std::cerr << "Invalid expression - not enough operands before operator call.\n";
				return std::pair(0, Error::Error);
			}
			right = numbers_stack_.top();
			numbers_stack_.pop();
			left = numbers_stack_.top();
			numbers_stack_.pop();
			switch (word[0]) {
				case '+':
					return std::pair(left + right, Error::NoError);
				case '-':
					return std::pair(left - right, Error::NoError);
				case '*':
					return std::pair(left * right, Error::NoError);
				case '/':
					if (right == 0) {
						std::cerr << "Error: Division by zero not defined.\n";
						return std::pair(0, Error::Error);
					}
					return std::pair(left / right, Error::NoError);
			}
		}
	}
	std::cerr << "Invalid token: '" << word << "'\n";
	std::cerr << "Only integers in range [0-9] and operators '+, -, *, /', all separated by whitespace are allowed.\n";
	return std::pair(0, Error::Error);
}
