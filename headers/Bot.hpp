/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izail <izail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:20:12 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/23 16:09:24 by izail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
# define BOT_HPP

# include <iostream>
# include <string>

class Bot
{
	private:

	public:
		Bot();
		Bot(const Bot &copy);

		Bot & operator=(const Bot &assign);

		~Bot();
};


#endif