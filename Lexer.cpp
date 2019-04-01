/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborysen <dborysen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:51:56 by dborysen          #+#    #+#             */
/*   Updated: 2019/04/01 13:27:40 by dborysen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"

std::vector<Lexer::Token>  Lexer::GetTokens() const
{
    return _tokens;
}

size_t  Lexer::GetNonEmptySize(const std::cmatch& result) const
{
    auto nonEmpty = 0u;

    for (const auto& res: result)
    {
        if (res.length() != 0)
            nonEmpty++;
    }
    return nonEmpty;
}

std::string GetNonCommentLine(const std::string& line)
{
    const auto pos = line.find(';');

    return pos == std::string::npos ? line : line.substr(0, pos);
}

void    Lexer::SaveTokens(const std::vector<std::string>& inputData)
{
    std::cmatch result;
    std::regex regular("(push|assert)\\s+"
                        "(int8|int16|int32|double|float)"
                        "\\((-?[0-9]+\\.?[0-9]*)\\)"
                        "|(pop|dump|add|sub|mul|div|mod|print|exit)");

    for (const auto& line : inputData)
    {
        Lexer::Token token;

        const auto nonCommentLine = line.substr(0, line.find(';'));

        if (std::regex_search(nonCommentLine.c_str(), result, regular))
        {
            const auto nonEmptyResultSize = GetNonEmptySize(result);

            if (nonEmptyResultSize == valueInstructionSize)
                token.instruction = result[nonValueInstructionPlace];
            else if (nonEmptyResultSize == nonValueInstructionSize)
            {
                token.instruction = result[instuctionPlace];
                token.type = result[typePlace];
                token.value = std::stod(result[valuePlace]);
            }
            _tokens.push_back(token);
        }
    }
}
