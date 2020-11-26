/*!
 * \class Keyboard
 *
 * \ingroup DEV
 *
 * \brief A class that is responsible for controlling keyboard input
 *
 * TODO:
 *
 * \note 
 *
 * \author Yernar Aldabergenov
 *
 * \version 1.0
 *
 * \date November 2020
 *
 * Contact: yernar.aa@gmail.com
 *
 */
#include "Keyboard.h"

bool Keyboard::KeyIsPressed( uint8_t keycode ) const noexcept
{
	return keystates[keycode];
}

std::optional<Keyboard::Event> Keyboard::ReadKey() noexcept
{
	if( keybuffer.size() > 0u )
	{
		Keyboard::Event e = keybuffer.front();
		keybuffer.pop();
		return e;
	}
	return {};
}

bool Keyboard::KeyIsEmpty() const noexcept
{
	return keybuffer.empty();
}

std::optional<wchar_t> Keyboard::ReadChar() noexcept
{
	if( charbuffer.size() > 0u )
	{
		wchar_t charcode = charbuffer.front();
		charbuffer.pop();
		return charcode;
	}

	return {};
}

bool Keyboard::CharIsEmpty() const noexcept
{
	return charbuffer.empty();
}

void Keyboard::ClearKey() noexcept
{
	keybuffer = std::queue<Event>();
}

void Keyboard::ClearChar() noexcept
{
	charbuffer = std::queue<wchar_t>();
}

void Keyboard::Clear() noexcept
{
	ClearKey();
	ClearChar();
}

void Keyboard::OnKeyPressed( uint8_t keycode ) noexcept
{
	keystates[keycode] = true;
	keybuffer.push( Keyboard::Event( Keyboard::Event::Type::PRESS, keycode ) );
	TrimBuffer( keybuffer );
}

void Keyboard::OnKeyReleased( uint8_t keycode ) noexcept
{
	keystates[keycode] = false;
	keybuffer.push( Keyboard::Event( Keyboard::Event::Type::RELEASE, keycode ) );
	TrimBuffer( keybuffer );
}

void Keyboard::OnChar( wchar_t character ) noexcept
{
	charbuffer.push( character );
	TrimBuffer( charbuffer );
}

void Keyboard::ClearState() noexcept
{
	keystates.reset();
}

template<typename T>
void Keyboard::TrimBuffer( std::queue<T>& buffer ) noexcept
{
	while( buffer.size() > MAXBUFFERSIZE )
	{
		buffer.pop();
	}
}
