/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborysen <dborysen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 11:31:31 by dborysen          #+#    #+#             */
/*   Updated: 2019/02/27 15:32:39 by dborysen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Avm.hpp"

int main(int argc, char** argv)
{
    if (argc > maxArgNum)
    {
        std::cerr << "Error Input Params" << std::endl;
        exit(1);
    }

    Avm avm;

    const auto isInputFromFile = argc == maxArgNum;

    isInputFromFile ? avm.LoadData(argv[argId]) : avm.LoadData();

    if (!avm.ValidateData())
    {
        std::cerr << "Data validation fail" << std::endl;
        exit(1);
    }

    avm.lexer.SaveTokens(avm.GetInputData());
    avm.parser.ParseTokens(avm.lexer.GetTokens());
    

    for (const auto& token : avm.lexer.GetTokens())
    {
        std::cout << token.instruction + " " 
        << token.type << " " << token.value << std::endl; 
    }

    return 0;
}
