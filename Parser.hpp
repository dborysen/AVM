/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborysen <dborysen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 15:16:48 by dborysen          #+#    #+#             */
/*   Updated: 2019/02/26 15:22:06 by dborysen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PARSER_HPP
# define PARSER_HPP

#include "Lexer.hpp"

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

    void    ParseTokens(const Lexer::Token& tokens) const;

private:

};


# endif