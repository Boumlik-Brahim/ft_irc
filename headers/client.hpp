/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:37:17 by bbrahim           #+#    #+#             */
/*   Updated: 2023/01/27 17:37:18 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <string>

class client
{
	public:
		// Constructors
		client();
		client(const client &copy);
		
		// Destructor
		~client();
		
		// Operators
		client & operator=(const client &assign);
		
	private:
		
};

#endif