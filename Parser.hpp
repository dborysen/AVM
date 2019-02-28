/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborysen <dborysen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 15:16:48 by dborysen          #+#    #+#             */
/*   Updated: 2019/02/28 17:26:29 by dborysen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PARSER_HPP
# define PARSER_HPP

#include <map>
#include <limits>
#include <functional>
#include "Lexer.hpp"
#include "IOperand.hpp"
#include "Operand.hpp"

using OperandsVector = std::vector<std::unique_ptr<IOperand> >;

class Parser
{
public:
    Parser() = default;
    Parser(const Parser& other) = delete;
    Parser(const Parser&& other) = delete;

    Parser&    operator=(const Parser& other) = delete;
    Parser&&   operator=(const Parser&& other) = delete;

    virtual ~Parser() = default;

    /************************************************/

    bool            ParseTokens(const std::vector<Lexer::Token>& tokens);
    void CreateOperand(eOperandType type,
        const std::string& value) const;

    OperandsVector mainStack;

private:
    const IOperand* CreateInt8(const std::string& value) const;
    const IOperand* CreateInt16(const std::string& value) const;
    const IOperand* CreateInt32(const std::string& value) const;
    const IOperand* CreateFloat(const std::string& value) const;
    const IOperand* CreateDouble(const std::string& value) const;

    bool    IsParseValidationOk(const std::vector<Lexer::Token>& tokens) const;
    void    ParseInstructions(const std::vector<Lexer::Token>& tokens);
};


# endif