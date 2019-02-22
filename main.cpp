/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborysen <dborysen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 11:31:31 by dborysen          #+#    #+#             */
/*   Updated: 2019/02/22 14:51:45 by dborysen         ###   ########.fr       */
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

    avm.ParseData();

    avm.ShowData();    


    return 0;
}
