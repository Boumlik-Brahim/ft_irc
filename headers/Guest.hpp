/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Guest.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:59:00 by iomayr            #+#    #+#             */
/*   Updated: 2023/02/05 11:45:28 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUEST_HPP
# define GUEST_HPP

#include <iostream>

class Guest {
    private:
        int         _guestFd;
        std::string _nick;
        std::string _user;
        std::string _realName;
        bool        _passValid;
        bool        _nickValid;
    public:
        Guest();
        Guest(int newSocketFd);
        Guest(const Guest &copy);
        Guest &operator=(const Guest &assign);
        ~Guest();

        bool getPassValid( void ) const ;
        void setPassValid(bool isValid) ;
        bool getNickValid( void ) const ;
        void setNickValid(bool isValid) ;
        int         getGuestFd( void ) const ;
        std::string getGuestNick( void ) const ;
        std::string getGuestUser( void ) const ;
        std::string getGuestRealName( void ) const ;
        void setGuestNick(std::string nick) ;
        void setGuestUser(std::string nick) ;
        void setGuestRealName(std::string nick) ;
};

#endif