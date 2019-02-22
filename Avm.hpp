/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Avm.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborysen <dborysen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 12:16:49 by dborysen          #+#    #+#             */
/*   Updated: 2019/02/22 15:18:15 by dborysen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Avm
{
    public:
        Avm() = default;
        Avm(const Avm& other) = delete;
        Avm(const Avm&& other) = delete;

        Avm&    operator=(const Avm& other) = delete;
        Avm&&   operator=(const Avm&& other) = delete;

        virtual ~Avm() = default;

        void    LoadData();
        void    LoadData(const std::string& fileName);

        bool    ValidateData();

        void    ShowData() const;

    private:
        std::vector<std::string> _inputData;
};