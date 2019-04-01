/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborysen <dborysen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 11:31:31 by dborysen          #+#    #+#             */
/*   Updated: 2019/04/01 15:30:35 by dborysen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Avm.hpp"

int main(int argc, char** argv)
{
    try
    {
        if (argc > maxArgNum)
            throw MyException("\033[1;31mError:\033[0m wrong params num");

        Avm avm;

        const auto isInputFromFile = argc == maxArgNum;

        isInputFromFile ? avm.LoadData(argv[argId]) : avm.LoadData();

        if (!avm.ValidateData())
            throw MyException("\tData validation fail");

        avm.lexer.SaveTokens(avm.GetInputData());

        if (!avm.parser.ParseTokens(avm.lexer.GetTokens()))
            throw MyException("\tParsing fail");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
