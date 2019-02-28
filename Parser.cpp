/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborysen <dborysen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 12:56:05 by dborysen          #+#    #+#             */
/*   Updated: 2019/02/28 17:26:28 by dborysen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

using OperandCreatorsVector = std::vector<std::function<const IOperand*(const std::string& value)> >;

static std::map<std::string, eOperandType> typeMap{
    {"int8", Int8 },
    {"int16", Int16},
    {"int32", Int32},
    {"float", Float},
    {"double", Double}};

static bool IsExitExist(const std::vector<Lexer::Token>& tokens)
{
    const auto it = std::find_if(tokens.begin(), tokens.end(),
        [](const Lexer::Token& item)
        {
            return item.instruction == "exit";
        });

    return it != tokens.end();
}

static bool IsValuesInRightDiapason(const std::vector<Lexer::Token>& tokens)
{
    std::vector<std::pair<double, double>> typesLimits{
        { std::numeric_limits<int8_t>::min(), std::numeric_limits<int8_t>::max() },
        { std::numeric_limits<int16_t>::min(), std::numeric_limits<int16_t>::max() },
        { std::numeric_limits<int32_t>::min(), std::numeric_limits<int32_t>::max() },
        { std::numeric_limits<float>::min(), std::numeric_limits<float>::max() },
        { std::numeric_limits<double>::min(), std::numeric_limits<double>::max() }
    };

    for (const auto& token : tokens)
    {
        if (token.type.empty())
            continue;
        
        const auto min = typesLimits.at(typeMap[token.type]).first;
        const auto max = typesLimits.at(typeMap[token.type]).second;

        if (token.value < min || token.value > max)
            return false;
    }
    return true;
}

bool    Parser::IsParseValidationOk(const std::vector<Lexer::Token>& tokens) const
{
    if (!IsExitExist(tokens))
    {
        std::cerr << "\033[1;31mError:\033[0m no exit" << std::endl;
        return false;
    }

    if (!IsValuesInRightDiapason(tokens))
    {
        std::cerr << "\033[1;31mError:\033[0m value in wrong diapason" << std::endl;
        return false;
    }
    return true;
}

const IOperand* Parser::CreateInt8(const std::string& value) const
{
    return new Operand(Int8, value);
}

const IOperand* Parser::CreateInt16(const std::string& value) const
{
    return new Operand(Int16, value);
}

const IOperand* Parser::CreateInt32(const std::string& value) const
{
    return new Operand(Int32, value);
}

const IOperand* Parser::CreateFloat(const std::string& value) const
{
    return new Operand(Float, value);
}

const IOperand* Parser::CreateDouble(const std::string& value) const
{
    return new Operand(Double, value);
}

void Parser::CreateOperand(eOperandType type,
    const std::string& value) const
{
    (void)type;
    (void)value;

    OperandCreatorsVector operandCreators ;

    const IOperand* (Parser::*x)(const std::string& value) const;

    x = &Parser::CreateInt8;

    // std::function<const IOperand*(const std::string& value)> f = 
    //     [=](const std::string& value) { this->CreateInt8(value); }; 
}

void    Parser::ParseInstructions(const std::vector<Lexer::Token>& tokens)
{
    (void)(tokens);
    // for (const auto& token : tokens)
    // {
        
    // }
}

bool    Parser::ParseTokens(const std::vector<Lexer::Token>& tokens)
{
    if (!IsParseValidationOk(tokens))
        return false;

    ParseInstructions(tokens);

    return true;
}