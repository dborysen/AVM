/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborysen <dborysen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 12:56:05 by dborysen          #+#    #+#             */
/*   Updated: 2019/03/06 13:29:42 by dborysen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

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

static bool IsValueInRightDiapason(eOperandType type, double value)
{
    std::vector<std::pair<double, double>> typesLimits{
        { std::numeric_limits<int8_t>::min(), std::numeric_limits<int8_t>::max() },
        { std::numeric_limits<int16_t>::min(), std::numeric_limits<int16_t>::max() },
        { std::numeric_limits<int32_t>::min(), std::numeric_limits<int32_t>::max() },
        { -FLT_MAX, FLT_MAX },
        { -DBL_MAX, DBL_MAX }
    };

    auto min = typesLimits.at(type).first;
    auto max = typesLimits.at(type).second;

    return value >= min && value <= max;
}

bool    Parser::IsParseValidationOk(const std::vector<Lexer::Token>& tokens) const
{
    auto isOk = true;

    if (tokens.empty())
    {
        std::cerr << "\033[1;31mError:\033[0m no tokens" << std::endl;
        isOk = false;
    }

    if (!IsExitExist(tokens))
    {
        std::cerr << "\033[1;31mError:\033[0m no exit" << std::endl;
        isOk = false;
    }

    for (const auto& token : tokens)
    {
        if (!IsValueInRightDiapason(typeMap[token.type], token.value))
        {
            std::cerr << "\033[1;31mError:\033[0m value in wrong diapason:"
            << std::endl << "\t" + token.instruction + " " + token.type + "(";
            std::cout << std::fixed;
            std::cout << std::setprecision(2);
            std::cout << token.value;
            std::cout << ")" << std::endl;

            isOk = false;
        }
    }
    return isOk;
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
        throw std::logic_error("\033[1;31mError:\033[0m\
        Stack is empty, can't do Pop instruction");

    _mainStack.pop_back();
}

void    Parser::Dump()
{
    if (_mainStack.empty())
        throw std::logic_error("\033[1;31mError:\033[0m \
        Stack is empty, can't do Dump instruction");

    for (auto it = _mainStack.rbegin(); it != _mainStack.rend(); it++)
    {
        if ((*it)->GetType() < Float)
        {
            std::cout << (*it)->GetPrecision() << std::endl;
            continue;
        }

        std::cout << std::fixed;
        std::cout << std::setprecision(2);
        std::cout << std::stod((*it)->ToString()) << std::endl;
    }
}

void    Parser::Assert(eOperandType type, const std::string& value)
{
    if (_mainStack.empty())
        throw std::logic_error("\033[1;31mError:\033[0m \
        Stack is empty, can't do Assert instruction");

    const auto top = std::prev(_mainStack.cend());

    if ((*top)->ToString() != value || (*top)->GetType() != type)
        throw std::logic_error("\033[1;31mError:\033[0m \
        Value at the top of the stack not equal to the passed one");
}

void    Parser::ReplaceFirstTwoElem(const IOperand* newOne)
{
    if (!IsValueInRightDiapason(newOne->GetType(), std::stod(newOne->ToString())))
    {
        throw std::logic_error("\033[1;31mError:\033[0m value in wrong diapason");
    }
    _mainStack.pop_back();
    _mainStack.pop_back();
    _mainStack.push_back(std::unique_ptr<const IOperand>(newOne));
}

void    Parser::CheckIfMoreThenTwoElem(const std::string& funcName) const
{
    const std::string massage = "\033[1;31mError:\033[0m \
        Stack has less than 2 elementsm can't do " + funcName + " instruction";

    if (_mainStack.size() < minStackElemNum)
        throw std::logic_error(massage);
}

void    Parser::Add()
{
    CheckIfMoreThenTwoElem("Add");

    const auto top = std::prev(_mainStack.end());
    const auto second = std::prev(top);

    ReplaceFirstTwoElem(**second + **top);
}

void    Parser::Sub()
{
    CheckIfMoreThenTwoElem("Sub");

    auto top = std::prev(_mainStack.end());
    auto second = std::prev(top);

    ReplaceFirstTwoElem(**second - **top);
}

void    Parser::Mul()
{
    CheckIfMoreThenTwoElem("Mul");

    auto top = std::prev(_mainStack.end());
    auto second = std::prev(top);

    ReplaceFirstTwoElem(**second * **top);
}

void    Parser::Div()
{
    CheckIfMoreThenTwoElem("Div");

    auto top = std::prev(_mainStack.end());
    auto second = std::prev(top);

    ReplaceFirstTwoElem(**second / **top);
}

void    Parser::Mod()
{
    CheckIfMoreThenTwoElem("Mod");

    auto top = std::prev(_mainStack.end());
    auto second = std::prev(top);

    ReplaceFirstTwoElem(**second % **top);
}

void    Parser::Print()
{
    if (_mainStack.empty())
        throw std::logic_error("\033[1;31mError:\033[0m \
        Stack is empty, can't do Print instruction");
    
    auto top = std::prev(_mainStack.end());

    if ((*top)->GetType() != Int8)
        throw std::logic_error("\033[1;31mError:\033[0m \
        Top element is not Int8");
    
    std::cout << char((*top)->GetPrecision()) << std::endl;
}

void    Parser::Exit()
{
    std::exit(1);
}

const IOperand* Parser::CreateOperand(eOperandType type,
    const std::string& value) const
{
    std::vector<const IOperand* (Parser::*)(const std::string& value) const> funcVec{
        &Parser::CreateInt8,
        &Parser::CreateInt16,
        &Parser::CreateInt32,
        &Parser::CreateFloat,
        &Parser::CreateDouble
    };

    return (this->*funcVec.at(type))(value);
}

void    Parser::InitializeInstructionsMap()
{
    _instructionsMap = {
        {"pop", &Parser::Pop},
        {"dump", &Parser::Dump},
        {"add", &Parser::Add},
        {"sub", &Parser::Sub},
        {"mul", &Parser::Mul},
        {"div", &Parser::Div},
        {"mod", &Parser::Mod},
        {"print", &Parser::Print},
        {"exit", &Parser::Exit}};

    _paramInstructionsMap = {
        {"push", &Parser::Push},
        {"assert", &Parser::Assert}};
}

bool    Parser::ParseTokens(const std::vector<Lexer::Token>& tokens)
{
    if (!IsParseValidationOk(tokens))
        return false;

    InitializeInstructionsMap();

    for (const auto& token : tokens)
    {
        const auto instruction = token.instruction;

        if (instruction == "push" || instruction == "assert")
        {
            const auto type = typeMap.at(token.type);
            const auto value = std::to_string(token.value);

            (this->*_paramInstructionsMap.at(instruction))(type, value);
            continue;
        }
        (this->*_instructionsMap.at(instruction))();        
    }

    return true;
}