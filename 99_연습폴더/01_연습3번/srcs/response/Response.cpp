/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:18:58 by cclaude           #+#    #+#             */
/*   Updated: 2021/04/25 14:34:27 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

// Member functions

void			Response::make(void)
{
	fillContent(); // _content 에 file 내용 담는다.
	// Set header accordingly
	_response = _header.getHeader(_content, _filename, _code) + _content; // Header 넣고, file 내용을 담아 보낸다.
}

// _filename.c_str() 이 index.html 의 스트링이고 이것을 _content 에 넣는다.
void			Response::fillContent(void)
{
	int		fd = open(_filename.c_str(), O_RDONLY);
	char	buffer[4096];
	int		ret = 4095;

	_content = ""; // std::string _content
	while (ret == 4095)
	{
		ft_memset(buffer, 0, 4096);
		ret = read(fd, buffer, 4095);
		_content += std::string(buffer); // 클래스 멤버 _content 에 읽은 값을 계속 담는다.
	}

	close(fd);
}

// Setter functions

void			Response::setFilename(std::string filename)
{
	_filename = filename;
}

// Getter functions

std::string		Response::getResponse(void)
{
	return (_response);
}

// Overloaders

Response & Response::operator=(const Response & src)
{
	(void)src;
	return (*this);
}

// Constructors and destructors

Response::Response(void)
{
	_code = 200;
}

Response::Response(const Response & src)
{
	(void)src;
}

Response::~Response(void)
{
}
