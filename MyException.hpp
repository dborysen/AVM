/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyException.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborysen <dborysen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 15:02:03 by dborysen          #+#    #+#             */
/*   Updated: 2019/04/01 15:30:12 by dborysen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_EXCEPTION_HPP
# define MY_EXCEPTION_HPP

#include <exception>
#include <iostream>

class MyException : public std::logic_error
{
public:
	MyException(const std::string& msg);
};

#endif