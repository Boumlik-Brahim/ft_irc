/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:37:11 by bbrahim           #+#    #+#             */
/*   Updated: 2023/01/27 17:37:13 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>

class channel
{
	public:
		// Constructors
		channel();
		channel(const channel &copy);
		
		// Destructor
		~channel();
		
		// Operators
		channel & operator=(const channel &assign);
		
	private:
		
};

#endif