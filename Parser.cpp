/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborysen <dborysen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 12:56:05 by dborysen          #+#    #+#             */
/*   Updated: 2019/02/27 17:41:47 by dborysen         ###   ########.fr       */
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

bool    Parser::ParseTokens(const std::vector<Lexer::Token>& tokens) const
{
    if (!IsExitExist(tokens))
    {
        std::cerr << "NO Exit" << std::endl;
        return false;
    }

    IsValuesInRightDiapason(tokens);

    return true;
}