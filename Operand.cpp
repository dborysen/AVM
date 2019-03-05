/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborysen <dborysen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 15:54:51 by dborysen          #+#    #+#             */
/*   Updated: 2019/03/05 15:48:27 by dborysen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Operand.hpp"

Operand::Operand(eOperandType type, const std::string& value) : 
_precision(value),
_type(type) {}

int Operand::GetPrecision() const
{
    return std::atoi(_precision.c_str());
}

eOperandType    Operand::GetType() const
{
    return _type;
}

const std::string& Operand::ToString() const
{
    return _precision;
}

const IOperand* Operand::operator+(const IOperand& rhs) const
{
    const auto value = std::stod(ToString()) + std::stod(rhs.ToString());
    const auto type = _type >= rhs.GetType() ? _type : rhs.GetType();

    return new Operand(type, std::to_string(value));
}

const IOperand* Operand::operator-(const IOperand& rhs) const
{
    const auto value = std::stod(ToString()) - std::stod(rhs.ToString());
    const auto type = _type >= rhs.GetType() ? _type : rhs.GetType();

    return new Operand(type, std::to_string(value));
}

const IOperand* Operand::operator*(const IOperand& rhs) const
{
    const auto value = std::stod(ToString()) * std::stod(rhs.ToString());
    const auto type = _type >= rhs.GetType() ? _type : rhs.GetType();

    return new Operand(type, std::to_string(value));
}

const IOperand* Operand::operator/(const IOperand& rhs) const
{
    if (std::stod(rhs.ToString()) == 0)
        throw std::logic_error("\033[1;31mError:\033[0m Division by 0");

    const auto value = std::stod(ToString()) / std::stod(rhs.ToString());
    const auto type = _type >= rhs.GetType() ? _type : rhs.GetType();

    return new Operand(type, std::to_string(value));
}

const IOperand* Operand::operator%(const IOperand& rhs) const
{
    if (rhs.GetPrecision() == 0)
        throw std::logic_error("\033[1;31mError:\033[0m Modulo by 0");

    const auto value = GetPrecision() % rhs.GetPrecision();
    const auto type = _type >= rhs.GetType() ? _type : rhs.GetType();

    return new Operand(type, std::to_string(value));
}
