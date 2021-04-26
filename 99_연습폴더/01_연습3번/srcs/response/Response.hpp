/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:18:58 by cclaude           #+#    #+#             */
/*   Updated: 2021/04/25 14:31:23 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "webserv.hpp"
# include "ResponseHeader.hpp"

class Response {
public:
	Response(void);
	Response(const Response & src);
	~Response(void);

	Response & operator=(const Response & src);

	// Setter functions
	void			setFilename(std::string filename);

	// Getter functions
	std::string		getResponse(void);

	// Member functions
	void			make(void);
	void			fillContent(void);

private:
	std::string		_response; // 말 그대로 response 관련 string
	ResponseHeader	_header;
	std::string		_content; // 이건 file 에서 index.html 에서 읽은 것들 담는 곳
	std::string		_filename;
	int				_code;
};

#endif
