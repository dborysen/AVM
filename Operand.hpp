/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborysen <dborysen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 14:42:28 by dborysen          #+#    #+#             */
/*   Updated: 2019/02/28 15:53:53 by dborysen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IOperand.hpp"
#include <iostream>
#include <string>

class Operand : public IOperand
{
public:
    Operand(eOperandType type, const std::string& value);

    Operand() = delete;
    Operand(const Operand& other) = delete;
    Operand(const Operand&& other) = delete;

    Operand&    operator=(const Operand& other) = delete;
    Operand&&   operator=(const Operand&& other) = delete;

    int             GetPrecision() const override;
    double          GetPrecisionInDouble() const;
    eOperandType    GetType() const override;

    const IOperand* operator+( const IOperand& rhs ) const override;
    const IOperand* operator-( const IOperand& rhs ) const override;
    const IOperand* operator*( const IOperand& rhs ) const override;
    const IOperand* operator/( const IOperand& rhs ) const override;
    const IOperand* operator%( const IOperand& rhs ) const override;

    const std::string& ToString() const override;
 
    virtual ~Operand() = default;

private:
    std::string     _precision;
    eOperandType    _type;
};
