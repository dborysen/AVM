/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Avm.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborysen <dborysen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:25:21 by dborysen          #+#    #+#             */
/*   Updated: 2019/02/22 15:22:16 by dborysen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Avm.hpp"

bool    Avm::ValidateData()
{
    if (_inputData.empty())
    {
        std::cerr << "Error: no data" << std::endl;
        return false;
    }

}

void    Avm::LoadData()
{
    const std::string endOfInput = ";;";

    for (std::string line; std::getline(std::cin, line) && line != endOfInput;)
    {
        _inputData.push_back(line);
    }
}

void    Avm::LoadData(const std::string& fileName)
{
    std::ifstream inFile;

    inFile.open(fileName);
    if (inFile.fail())
    {
        std::cerr << "Error Opening File" << std::endl;
        exit(1);
    }

    for (std::string line; !inFile.eof(); line = "")
    {
        std::getline(inFile, line);
        _inputData.push_back(line);
    }
    inFile.close();
}

void    Avm::ShowData() const
{
    for (const auto& line : _inputData)
    {
        std::cout << line << std::endl;
    }
}
