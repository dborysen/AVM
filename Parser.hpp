/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborysen <dborysen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 15:16:48 by dborysen          #+#    #+#             */
/*   Updated: 2019/02/27 17:12:13 by dborysen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PARSER_HPP
# define PARSER_HPP

#include <map>
#include <limits>
#include "Lexer.hpp"
#include "IOperand.hpp"

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

    bool            ParseTokens(const std::vector<Lexer::Token>& tokens) const;
    const IOperand* CreateOperand(eOperandType type,
                                const std::string& value ) const;

private:
    const IOperand* CreateInt8(const std::string& value ) const;
    const IOperand* CreateInt16(const std::string& value ) const;
    const IOperand* CreateInt32(const std::string& value ) const;
    const IOperand* CreateFloat(const std::string& value ) const;
    const IOperand* CreateDouble(const std::string& value ) const;

};


# endif