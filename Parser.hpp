/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborysen <dborysen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 15:16:48 by dborysen          #+#    #+#             */
/*   Updated: 2019/03/05 15:41:18 by dborysen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PARSER_HPP
# define PARSER_HPP

#include <map>
#include <limits>
#include <functional>
#include <float.h>
#include "Lexer.hpp"
#include "IOperand.hpp"
#include "Operand.hpp"

class Parser
{
public:
    using InstuctionsMap = std::map<std::string, void (Parser::*)()>;
    using OperandsVector = std::vector<std::unique_ptr<const IOperand> >;
    using ParamInstuctionsMap = std::map<std::string, void (Parser::*)
        (eOperandType type, const std::string& value)>;
    using OperandCreatorsVector = std::vector<std::function<
        const IOperand*(const std::string& value)> >;

    enum instructions
    {
        push,
        pop,
        dump,
        assert,
        add,
        sub,
        mul,
        div,
        mod,
        print,
        exit
    };

    enum elemAttributes
    { 
        firstElem,
        secondElem,

        minStackElemNum
    };

    Parser() = default;
    Parser(const Parser& other) = delete;
    Parser(const Parser&& other) = delete;

    Parser&    operator=(const Parser& other) = delete;
    Parser&&   operator=(const Parser&& other) = delete;

    virtual ~Parser() = default;

    /************************************************/

    bool            ParseTokens(const std::vector<Lexer::Token>& tokens);
    const IOperand* CreateOperand(eOperandType type,
        const std::string& value) const;

private:
    const IOperand* CreateInt8(const std::string& value) const;
    const IOperand* CreateInt16(const std::string& value) const;
    const IOperand* CreateInt32(const std::string& value) const;
    const IOperand* CreateFloat(const std::string& value) const;
    const IOperand* CreateDouble(const std::string& value) const;

    /* Instructions */
    void    Push(eOperandType type, const std::string& value);
    void    Pop();
    void    Dump();
    void    Assert(eOperandType type, const std::string& value);
    void    Add();
    void    Sub();
    void    Mul();
    void    Div();
    void    Mod();
    void    Print();
    void    Exit();

    bool    IsParseValidationOk(const std::vector<Lexer::Token>& tokens) const;
    void    ReplaceFirstTwoElem(const IOperand* newOne);
    void    CheckIfMoreThenTwoElem(const std::string& funcName) const;
    void    InitializeInstructionsMap();

    OperandsVector      _mainStack;
    InstuctionsMap      _instructionsMap;
    ParamInstuctionsMap _paramInstructionsMap;
};

# endif