/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborysen <dborysen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 11:31:31 by dborysen          #+#    #+#             */
/*   Updated: 2019/02/25 17:30:16 by dborysen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Avm.hpp"

int main(int argc, char** argv)
{
    if (argc > 2)
    {
        std::cerr << "Error Input Params" << std::endl;
        exit(1);
    }

    Avm avm;

    const auto isInputFromFile = argc == 2;

    isInputFromFile ? avm.LoadData(argv[argc - 1]) : avm.LoadData();

    if (avm.ValidateData())
    {
        
    }
    // avm.ShowData();    

    return 0;
}
