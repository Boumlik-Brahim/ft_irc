
#ifndef GUEST_HPP
#define GUEST_HPP

#include <iostream>

class Guest
{
	private:
		int			_guestFd;
		std::string	_nick;
		std::string	_user;
		std::string	_realName;
		bool		_passValid;
		bool		_nickValid;
		bool		_userValid;

	public:
		Guest();
		Guest(int newSocketFd);
		Guest(const Guest &copy);
		Guest &operator=(const Guest &assign);

		int			getGuestFd(void) const;
		void		setGuestFd(int guestFd);
		bool		getPassValid(void) const;
		void		setPassValid(bool isValid);
		bool		getNickValid(void) const;
		void		setNickValid(bool isValid);
		std::string	getGuestNick(void) const;
		void		setGuestNick(std::string nick);
		std::string	getGuestUser(void) const;
		void		setGuestUser(std::string nick);
		std::string	getGuestRealName(void) const;
		void		setGuestRealName(std::string nick);
		bool 		getUserValid(void) const;
		void 		setUserValid(bool isValid);

		~Guest();
};

#endif