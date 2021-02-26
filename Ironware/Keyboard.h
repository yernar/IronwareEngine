/*!
 * \file Keyboard.h
 * \date 2020/11/12 18:30
 *
 * \author Yernar Aldabergenov
 * Contact: yernar.aa@gmail.com
 *
 * \brief A class that is responsible for controlling keyboard input
 *
 * TODO:
 *
 * \note Contains Event class inside and Window is friend class
 * * as we will need to access this class' member private functions from Window
*/
#pragma once

#include <queue>
#include <bitset>
#include <optional>

class Keyboard
{
	friend class Window;
public:
	class Event
	{
	public:
		enum class Type
		{
			PRESS,
			RELEASE,
		};

	private:
		Type type;
		uint8_t code = 0u;

	public:
		Event( Type type, uint8_t code ) noexcept :
			type( type ),
			code( code )
		{}

		inline bool IsPress() const noexcept { return type == Type::PRESS; }
		inline bool IsRelease() const noexcept { return type == Type::RELEASE; }
		inline uint8_t GetCode() const noexcept { return code; }
	};

public:
	Keyboard() = default;
	Keyboard( const Keyboard& ) = delete;
	Keyboard& operator=( const Keyboard& ) = delete;

	// clears key and char events
	inline void Clear() noexcept { ClearKey(), ClearChar(); }

	/******************************* KEY EVENTS START ******************************/
	std::optional<Event> ReadKey() noexcept;
	inline bool KeyIsPressed( uint8_t keycode ) const noexcept { return keystates[keycode]; }
	inline bool KeyIsEmpty() const noexcept { return keybuffer.empty(); }
	inline void ClearKey() noexcept { std::queue<Event>().swap( keybuffer ); }
	/******************************* KEY EVENTS END ******************************/

	/******************************* CHAR EVENT START ******************************/
	std::optional<wchar_t> ReadChar() noexcept;
	inline bool CharIsEmpty() const noexcept { return charbuffer.empty(); }
	inline void ClearChar() noexcept { std::queue<wchar_t>().swap( charbuffer ); }
	/******************************* CHAR EVENT END ******************************/

	/******************************* AUTOREPEAT START ******************************/
	inline void EnableAutorepeat() noexcept { autorepeatEnabled = true; }
	inline void DisableAutorepeat() noexcept { autorepeatEnabled = false; }
	inline bool AutorepeatIsEnabled() const noexcept { return autorepeatEnabled; }
	/******************************* AUTOREPEAT END ******************************/

private:
	void OnKeyPressed( uint8_t keycode ) noexcept;
	void OnKeyReleased( uint8_t keycode ) noexcept;
	void OnChar( wchar_t character ) noexcept;
	void ClearState() noexcept;
	template<typename T>
	static void TrimBuffer( std::queue<T>& buffer ) noexcept;

private:
	// number of keys
	static constexpr uint32_t NKEYS = 256u;
	// max buffer size
	static constexpr uint32_t MAXBUFFERSIZE = 16u;
	bool autorepeatEnabled = false;
	std::bitset<NKEYS> keystates;
	std::queue<Event> keybuffer;
	std::queue<wchar_t> charbuffer;
};