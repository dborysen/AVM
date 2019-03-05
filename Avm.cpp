/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Avm.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborysen <dborysen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:25:21 by dborysen          #+#    #+#             */
/*   Updated: 2019/03/04 17:56:18 by dborysen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Avm.hpp"

bool    Avm::ValidateData()
{
    if (_inputData.size() == 1 && *_inputData.begin() == "")
    {
        std::cerr << "Error: no data" << std::endl;
        return false;
    }
    
    std::regex validationReg("([\t ]*(push|assert)\\s+"
                            "((int8|int16|int32)"
                            "\\((-?[0-9]+)\\))"
                            "[\t ]*(;.*)?)"

                            "|([\t ]*(push|assert)\\s+"
                            "(float|double)"
                            "\\(-?[0-9]+.[0-9]*\\)"
                            "[\t ]*(;.*)?"

                            "|([\t ]*;.*)"
                            "|[\t ]*(pop|dump|add|sub|mul|div|mod|print|exit)"
                            "[\t ]*(;.*)?)"
                            "|(^\\s*$))");

    bool isOk = true;
    for(auto i = 0u; i < _inputData.size(); i++)
    {
        if (!std::regex_match(_inputData.at(i).c_str(), validationReg))
        {
            std::cerr << "[line " << i + 1
            << "]\033[1;31m Error\033[0m wrong input format:"
            << std::endl << "\t" + _inputData.at(i) << std::endl;

            isOk = false;
        }
    }
    return isOk;
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

std::vector<std::string> Avm::GetInputData() const
{
    return _inputData;
}
