/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:37:04 by bbrahim           #+#    #+#             */
/*   Updated: 2023/01/27 17:37:06 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
# define BOT_HPP

# include <iostream>
# include <string>

class bot
{
	public:
		// Constructors
		bot();
		bot(const bot &copy);
		
		// Destructor
		~bot();
		
		// Operators
		bot & operator=(const bot &assign);
		
	private:
		
};

#endif