/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Avm.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborysen <dborysen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 12:16:49 by dborysen          #+#    #+#             */
/*   Updated: 2019/02/28 13:02:23 by dborysen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef AVM_HPP
# define AVM_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include "Lexer.hpp"
#include "Parser.hpp"
#include "IOperand.hpp"

enum avmAttributes
{
    maxArgNum = 2,
    argId = 1
};

class Avm
{
public:
    Avm() = default;
    Avm(const Avm&& other) = delete;
    Avm(const Avm& other) = delete;

    Avm&    operator=(const Avm& other) = delete;
    Avm&&   operator=(const Avm&& other) = delete;

    virtual ~Avm() = default;

    /********************************************/

    std::vector<std::string> GetInputData() const;

    void    LoadData();
    void    LoadData(const std::string& fileName);

    bool    ValidateData();

    void    ShowData() const;

    Lexer   lexer;
    Parser  parser;

private:
    std::vector<std::string>    _inputData;
};

# endif