#pragma once

#include "Core/Core.h"

/*
	Key codes for TextureForge.
	Taken from glfw3.h key codes.
*/

namespace TexWriter
{
	typedef enum class KeyCode : uint16_t
	{
		/* Printable keys */
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

/* Printable keys */
#define TW_KEY_SPACE           ::TexWriter::Key::Space
#define TW_KEY_APOSTROPHE      ::TexWriter::Key::Apostrophe    /* ' */
#define TW_KEY_COMMA           ::TexWriter::Key::Comma         /* , */
#define TW_KEY_MINUS           ::TexWriter::Key::Minus         /* - */
#define TW_KEY_PERIOD          ::TexWriter::Key::Period        /* . */
#define TW_KEY_SLASH           ::TexWriter::Key::Slash         /* / */
#define TW_KEY_0               ::TexWriter::Key::D0
#define TW_KEY_1               ::TexWriter::Key::D1
#define TW_KEY_2               ::TexWriter::Key::D2
#define TW_KEY_3               ::TexWriter::Key::D3
#define TW_KEY_4               ::TexWriter::Key::D4
#define TW_KEY_5               ::TexWriter::Key::D5
#define TW_KEY_6               ::TexWriter::Key::D6
#define TW_KEY_7               ::TexWriter::Key::D7
#define TW_KEY_8               ::TexWriter::Key::D8
#define TW_KEY_9               ::TexWriter::Key::D9
#define TW_KEY_SEMICOLON       ::TexWriter::Key::Semicolon     /* ; */
#define TW_KEY_EQUAL           ::TexWriter::Key::Equal         /* = */
#define TW_KEY_A               ::TexWriter::Key::A
#define TW_KEY_B               ::TexWriter::Key::B
#define TW_KEY_C               ::TexWriter::Key::C
#define TW_KEY_D               ::TexWriter::Key::D
#define TW_KEY_E               ::TexWriter::Key::E
#define TW_KEY_F               ::TexWriter::Key::F
#define TW_KEY_G               ::TexWriter::Key::G
#define TW_KEY_H               ::TexWriter::Key::H
#define TW_KEY_I               ::TexWriter::Key::I
#define TW_KEY_J               ::TexWriter::Key::J
#define TW_KEY_K               ::TexWriter::Key::K
#define TW_KEY_L               ::TexWriter::Key::L
#define TW_KEY_M               ::TexWriter::Key::M
#define TW_KEY_N               ::TexWriter::Key::N
#define TW_KEY_O               ::TexWriter::Key::O
#define TW_KEY_P               ::TexWriter::Key::P
#define TW_KEY_Q               ::TexWriter::Key::Q
#define TW_KEY_R               ::TexWriter::Key::R
#define TW_KEY_S               ::TexWriter::Key::S
#define TW_KEY_T               ::TexWriter::Key::T
#define TW_KEY_U               ::TexWriter::Key::U
#define TW_KEY_V               ::TexWriter::Key::V
#define TW_KEY_W               ::TexWriter::Key::W
#define TW_KEY_X               ::TexWriter::Key::X
#define TW_KEY_Y               ::TexWriter::Key::Y
#define TW_KEY_Z               ::TexWriter::Key::Z
#define TW_KEY_LEFT_BRACKET    ::TexWriter::Key::LeftBracket   /* [ */
#define TW_KEY_BACKSLASH       ::TexWriter::Key::Backslash     /* \ */
#define TW_KEY_RIGHT_BRACKET   ::TexWriter::Key::RightBracket  /* ] */
#define TW_KEY_GRAVE_ACCENT    ::TexWriter::Key::GraveAccent   /* ` */
#define TW_KEY_WORLD_1         ::TexWriter::Key::World1        /* non-US #1 */
#define TW_KEY_WORLD_2         ::TexWriter::Key::World2        /* non-US #2 */

/* Function keys */
#define TW_KEY_ESCAPE          ::TexWriter::Key::Escape
#define TW_KEY_ENTER           ::TexWriter::Key::Enter
#define TW_KEY_TAB             ::TexWriter::Key::Tab
#define TW_KEY_BACKSPACE       ::TexWriter::Key::Backspace
#define TW_KEY_INSERT          ::TexWriter::Key::Insert
#define TW_KEY_DELETE          ::TexWriter::Key::Delete
#define TW_KEY_RIGHT           ::TexWriter::Key::Right
#define TW_KEY_LEFT            ::TexWriter::Key::Left
#define TW_KEY_DOWN            ::TexWriter::Key::Down
#define TW_KEY_UP              ::TexWriter::Key::Up
#define TW_KEY_PAGE_UP         ::TexWriter::Key::PageUp
#define TW_KEY_PAGE_DOWN       ::TexWriter::Key::PageDown
#define TW_KEY_HOME            ::TexWriter::Key::Home
#define TW_KEY_END             ::TexWriter::Key::End
#define TW_KEY_CAPS_LOCK       ::TexWriter::Key::CapsLock
#define TW_KEY_SCROLL_LOCK     ::TexWriter::Key::ScrollLock
#define TW_KEY_NUM_LOCK        ::TexWriter::Key::NumLock
#define TW_KEY_PRINT_SCREEN    ::TexWriter::Key::PrintScreen
#define TW_KEY_PAUSE           ::TexWriter::Key::Pause
#define TW_KEY_F1              ::TexWriter::Key::F1
#define TW_KEY_F2              ::TexWriter::Key::F2
#define TW_KEY_F3              ::TexWriter::Key::F3
#define TW_KEY_F4              ::TexWriter::Key::F4
#define TW_KEY_F5              ::TexWriter::Key::F5
#define TW_KEY_F6              ::TexWriter::Key::F6
#define TW_KEY_F7              ::TexWriter::Key::F7
#define TW_KEY_F8              ::TexWriter::Key::F8
#define TW_KEY_F9              ::TexWriter::Key::F9
#define TW_KEY_F10             ::TexWriter::Key::F10
#define TW_KEY_F11             ::TexWriter::Key::F11
#define TW_KEY_F12             ::TexWriter::Key::F12
#define TW_KEY_F13             ::TexWriter::Key::F13
#define TW_KEY_F14             ::TexWriter::Key::F14
#define TW_KEY_F15             ::TexWriter::Key::F15
#define TW_KEY_F16             ::TexWriter::Key::F16
#define TW_KEY_F17             ::TexWriter::Key::F17
#define TW_KEY_F18             ::TexWriter::Key::F18
#define TW_KEY_F19             ::TexWriter::Key::F19
#define TW_KEY_F20             ::TexWriter::Key::F20
#define TW_KEY_F21             ::TexWriter::Key::F21
#define TW_KEY_F22             ::TexWriter::Key::F22
#define TW_KEY_F23             ::TexWriter::Key::F23
#define TW_KEY_F24             ::TexWriter::Key::F24
#define TW_KEY_F25             ::TexWriter::Key::F25

/* Keypad */
#define TW_KEY_KP_0            ::TexWriter::Key::KP0
#define TW_KEY_KP_1            ::TexWriter::Key::KP1
#define TW_KEY_KP_2            ::TexWriter::Key::KP2
#define TW_KEY_KP_3            ::TexWriter::Key::KP3
#define TW_KEY_KP_4            ::TexWriter::Key::KP4
#define TW_KEY_KP_5            ::TexWriter::Key::KP5
#define TW_KEY_KP_6            ::TexWriter::Key::KP6
#define TW_KEY_KP_7            ::TexWriter::Key::KP7
#define TW_KEY_KP_8            ::TexWriter::Key::KP8
#define TW_KEY_KP_9            ::TexWriter::Key::KP9
#define TW_KEY_KP_DECIMAL      ::TexWriter::Key::KPDecimal
#define TW_KEY_KP_DIVIDE       ::TexWriter::Key::KPDivide
#define TW_KEY_KP_MULTIPLY     ::TexWriter::Key::KPMultiply
#define TW_KEY_KP_SUBTRACT     ::TexWriter::Key::KPSubtract
#define TW_KEY_KP_ADD          ::TexWriter::Key::KPAdd
#define TW_KEY_KP_ENTER        ::TexWriter::Key::KPEnter
#define TW_KEY_KP_EQUAL        ::TexWriter::Key::KPEqual

#define TW_KEY_LEFT_SHIFT      ::TexWriter::Key::LeftShift
#define TW_KEY_LEFT_CONTROL    ::TexWriter::Key::LeftControl
#define TW_KEY_LEFT_ALT        ::TexWriter::Key::LeftAlt
#define TW_KEY_LEFT_SUPER      ::TexWriter::Key::LeftSuper
#define TW_KEY_RIGHT_SHIFT     ::TexWriter::Key::RightShift
#define TW_KEY_RIGHT_CONTROL   ::TexWriter::Key::RightControl
#define TW_KEY_RIGHT_ALT       ::TexWriter::Key::RightAlt
#define TW_KEY_RIGHT_SUPER     ::TexWriter::Key::RightSuper
#define TW_KEY_MENU            ::TexWriter::Key::Menu
