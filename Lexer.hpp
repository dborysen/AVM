/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborysen <dborysen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:31:52 by dborysen          #+#    #+#             */
/*   Updated: 2019/03/05 12:12:20 by dborysen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef LEXER_HPP
# define LEXER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include "IOperand.hpp"

class Lexer
{
public:
    enum LexerAttributes
    {
        valueInstructionSize = 2,
        nonValueInstructionSize = 4,

        instuctionPlace = 1,
        typePlace = 2,
        valuePlace = 3,

        nonValueInstructionPlace = 4
    };

    struct Token
    {
        std::string instruction;
        std::string type;
        double      value = 0;
    };
    
    Lexer() = default;
    Lexer(const Lexer& other) = delete;
    Lexer(const Lexer&& other) = delete;

    Lexer&    operator=(const Lexer& other) = delete;
    Lexer&&   operator=(const Lexer&& other) = delete;

    virtual ~Lexer() = default;

    /************************************************/

    void                SaveTokens(const std::vector<std::string>& inputData);
    std::vector<Token>  GetTokens() const;

private:
    size_t  GetNonEmptySize(const std::cmatch& result) const;

    std::vector<Token> _tokens;
};

# endif