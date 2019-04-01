/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyException.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborysen <dborysen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 15:19:06 by dborysen          #+#    #+#             */
/*   Updated: 2019/04/01 15:26:40 by dborysen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MyException.hpp"

MyException::MyException(const std::string& msg) : std::logic_error(msg) {}
