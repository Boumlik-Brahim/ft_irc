#include "../../headers/Bot.hpp"

Bot::Bot()
{}

Bot::Bot(const Bot &copy)
{
	(void) copy;
	std::cout << "\e[0;33mCopy Constructor called of Bot\e[0m" << std::endl;
}

Bot & Bot::operator=(const Bot &assign)
{
	(void) assign;
	return *this;
}

Bot::~Bot()
{}

