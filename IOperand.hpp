/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborysen <dborysen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 15:47:07 by dborysen          #+#    #+#             */
/*   Updated: 2019/02/27 12:55:22 by dborysen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef IOPERAND_HPP
# define IOPERAND_HPP

#include <iostream>
#include <string>

enum eOperandType
{
    Int8,
    Int16,
    Int32,
    Float,
    Double
};

class IOperand
{
public:
    virtual int             GetPrecision( void ) const = 0; // Precision of the type of the instance
    virtual eOperandType    GetType( void ) const = 0; // Type of the instance

    virtual const IOperand* operator+( const IOperand& rhs ) const = 0; // Sum
    virtual const IOperand* operator-( const IOperand& rhs ) const = 0; // Difference
    virtual const IOperand* operator*( const IOperand& rhs ) const = 0; // Product
    virtual const IOperand* operator/( const IOperand& rhs ) const = 0; // Quotient
    virtual const IOperand* operator%( const IOperand& rhs ) const = 0; // Modulo

    virtual const std::string& ToString() const = 0; // String representation of the instance
 
    virtual ~IOperand( void ) {}
};

# endif