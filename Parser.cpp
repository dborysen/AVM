/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborysen <dborysen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 12:56:05 by dborysen          #+#    #+#             */
/*   Updated: 2019/03/01 17:31:17 by dborysen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

using OperandCreatorsVector = std::vector<std::function<
    const IOperand*(const std::string& value)> >;

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

void    Parser::Push(eOperandType type, const std::string& value)
{
    _mainStack.push_back(std::unique_ptr<const IOperand>
        (CreateOperand(type, value)));
}

void    Parser::Pop()
{
    if (_mainStack.empty())
        throw std::logic_error("Stack is empty, can't do Pop instruction");

    _mainStack.pop_back();
}

void    Parser::Dump()
{
    if (_mainStack.empty())
        throw std::logic_error("Stack is empty, can't do Dump instruction");


    for (auto it = _mainStack.rbegin(); it != _mainStack.rend(); it++)
    {
        std::cout << (*it)->ToString() << std::endl;
    }
}

void    Parser::Assert(eOperandType type, const std::string& value)
{
    if (_mainStack.empty())
        throw std::logic_error("Stack is empty, can't do Assert instruction");

    const auto top = std::prev(_mainStack.cend());

    if ((*top)->ToString() != value &&
        (*top)->GetPrecision() != type)
        throw std::logic_error("Value at the top of the stack not equal\
            to the passed");
}

void    Parser::ReplaceFirstTwoElem(const IOperand* newOne)
{
    _mainStack.pop_back();
    _mainStack.pop_back();
    _mainStack.push_back(std::unique_ptr<const IOperand>(newOne));
}

void    Parser::CheckIfMoreThenTwoElem(const std::string& funcName) const
{
    const std::string massage = "Stack has less than 2 elementsm can't do" +
        funcName + "instruction";

    if (_mainStack.size() < minStackElemNum)
        throw std::logic_error(massage);
}


void    Parser::Add()
{
    // _mainStack.push_back(std::unique_ptr<const IOperand>
    //     (CreateOperand(Int8, "2")));

    // _mainStack.push_back(std::unique_ptr<const IOperand>
    //     (CreateOperand(Int16, "3")));   

    //     _mainStack.push_back(std::unique_ptr<const IOperand>
    //     (CreateOperand(Float, "3.2")));   

    CheckIfMoreThenTwoElem("Add");

    const auto top = std::prev(_mainStack.end());
    const auto second = std::prev(top);

    ReplaceFirstTwoElem(**top + **second);
}

void    Parser::Sub()
{
    CheckIfMoreThenTwoElem("Sub");

    auto top = std::prev(_mainStack.end());
    auto second = std::prev(top);

    ReplaceFirstTwoElem(**top - **second);
}

void    Parser::Mul()
{
    CheckIfMoreThenTwoElem("Mul");

    auto top = std::prev(_mainStack.end());
    auto second = std::prev(top);

    ReplaceFirstTwoElem(**top * **second);
}

void    Parser::Div()
{
    CheckIfMoreThenTwoElem("Div");

    auto top = std::prev(_mainStack.end());
    auto second = std::prev(top);

    ReplaceFirstTwoElem(**top / **second);
}

void    Parser::Mod()
{
    CheckIfMoreThenTwoElem("Mod");

    auto top = std::prev(_mainStack.end());
    auto second = std::prev(top);

    ReplaceFirstTwoElem(**top % **second);
}

void    Parser::Print() const
{
    if (_mainStack.empty())
        throw std::logic_error("Stack is empty, can't do Print instruction");
    
    auto top = std::prev(_mainStack.end());

    if ((*top)->GetType() != Int8)
        throw std::logic_error("Top element is not Int8");
    
    std::cout << char((*top)->GetPrecision()) << std::endl;
}

void    Parser::Exit() const
{
    std::exit(1);
}

const IOperand* Parser::CreateOperand(eOperandType type,
    const std::string& value) const
{
    std::vector<const IOperand* (Parser::*)(const std::string& value) const> vec{
        &Parser::CreateInt8,
        &Parser::CreateInt16,
        &Parser::CreateInt32,
        &Parser::CreateFloat,
        &Parser::CreateDouble
    };

    return (Parser().*vec.at(type))(value);
}

void    Parser::ParseInstructions(const std::vector<Lexer::Token>& tokens)
{
    (void)(tokens);

    Add();
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