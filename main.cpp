/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborysen <dborysen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 11:31:31 by dborysen          #+#    #+#             */
/*   Updated: 2019/02/28 12:48:58 by dborysen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Avm.hpp"

int main(int argc, char** argv)
{
    try
    {
        if (argc > maxArgNum)
            throw std::logic_error("\033[1;31mError:\033[0m wrong params num");

        Avm avm;

        const auto isInputFromFile = argc == maxArgNum;

        isInputFromFile ? avm.LoadData(argv[argId]) : avm.LoadData();

        if (!avm.ValidateData())
            throw std::logic_error("\tData validation fail");

        avm.lexer.SaveTokens(avm.GetInputData());

        if (!avm.parser.ParseTokens(avm.lexer.GetTokens()))
            throw std::logic_error("\tParsing fail");

            for (const auto& token : avm.lexer.GetTokens())
            {
                std::cout << token.instruction + " " 
                << token.type << " " << token.value << std::endl; 
            }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
