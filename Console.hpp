#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <iostream>
#include <string>
#include <Windows.h>
#include <locale>

class Console {
private:
	struct BoxCharSet {
		std::string topLeft;
		std::string topRight;
		std::string bottomLeft;
		std::string bottomRight;
		std::string horizontal;
		std::string vertical;
	};
public:
	enum class Color {
		Default = 39,
		Black = 30,
		Red = 31,
		Green = 32,
		Yellow = 33,
		Blue = 34,
		Magenta = 35,
		Cyan = 36,
		White = 37
	};

	enum class Style {
		Reset = 0,
		Bold = 1,
		Underline = 4,
		Reversed = 7
	};

	enum class BoxStyle 
	{
		Single,
		Double,
		Broad,
		Dashed,
		Rounded
	};

	Console() {
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hOut != INVALID_HANDLE_VALUE) {
			DWORD dwMode = 0;
			GetConsoleMode(hOut, &dwMode);
			dwMode |= 0x0004; // ENABLE_VIRTUAL_TERMINAL_PROCESSING
			SetConsoleMode(hOut, dwMode);
		}
		SetConsoleOutputCP(CP_UTF8);
		setlocale(LC_ALL,".OCP.utf8");
	}

	// Set text color
	Console& setColor(Color color) {
		int code = (int)color;
		if (code >= 0)
			std::cout << "\033[" << code << "m";
		return *this;
	}

	// Set text style
	Console& setStyle(Style style) {
		std::cout << "\033[" << static_cast<int>(style) << "m";
		return *this;
	}

	// Move cursor to (x, y)
	Console& moveCursor(int x, int y) {
		std::cout << "\033[" << y << ";" << x << "H";
		return *this;
	}

	// Clear the entire screen
	Console& clearScreen() {
		std::cout << "\033[2J\033[H";
		return *this;
	}

	// Clear the current line
	Console& clearLine() {
		std::cout << "\033[2K\r";
		return *this;
	}

	// Print text
	Console& print(const std::string& text) {
		std::cout << text;
		return *this;
	}

	// Print int
	Console& print(int value) { std::cout << value; return *this; }

	// Print float with optional precision (default 2)
	Console& print(float value, int precision = 2) {
		std::cout.setf(std::ios::fixed);
		std::cout.precision(precision);
		std::cout << value;
		return *this;
	}

	// Print double with optional precision (default 2)
	Console& print(double value, int precision = 2) {
		std::cout.setf(std::ios::fixed);
		std::cout.precision(precision);
		std::cout << value;
		return *this;
	}

	// Print boolean value
	Console& printBool(bool value) {
		if (value) std::cout << "true";
		else std::cout << "false";
		return *this;
	}

	// Print a centered title at the top of the console
	Console& printTitle(const std::string& title) {
		clearScreen();

		int consoleWidth = 80; // Default width if detection fails

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		if (GetConsoleScreenBufferInfo(hStdout, &csbi)) {
			consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		}

		int padding = (consoleWidth - static_cast<int>(title.length())) / 2;
		if (padding < 0) padding = 0;

		moveCursor(padding + 1, 1);
		print(title);

		return *this;
	}

	// Print a centered title in a box at the top of the console
	// Print a centered title in a box at the top of the console using box-drawing characters
	Console& printTitleBox(const std::string& title, Console::BoxStyle style = Console::BoxStyle::Single)
	{
		clearScreen();

		BoxCharSet charSet;
		switch (style) {
		case BoxStyle::Single: charSet = { "┌", "┐", "└", "┘", "─", "│" }; break;
		case BoxStyle::Double: charSet = { "╔", "╗", "╚", "╝", "═", "║" }; break;
		case BoxStyle::Broad: charSet = { "┏", "┓", "┗", "┛", "━", "┃" }; break;
		case BoxStyle::Dashed: charSet = { "┌", "┐", "└", "┘", "┄", "┆" }; break;
		case BoxStyle::Rounded: charSet = { "╭", "╮", "╰", "╯", "─", "│" }; break;
		default: charSet = { "+", "+", "+", "+", "-", "|" }; break;
		}

		int consoleWidth = 80; // Default if detection fails

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		if (GetConsoleScreenBufferInfo(hStdout, &csbi)) {
			consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		}

		// Calculate padding
		int padding = (consoleWidth - static_cast<int>(title.length())) / 2;
		if (padding < 0) padding = 0;

		// Top border: ╔════════════════════════════╗
		moveCursor(1, 1);
		std::cout << charSet.topLeft;
		for (int i = 0; i < consoleWidth - 2; ++i) std::cout << charSet.horizontal;
		std::cout << charSet.topRight;

		// Title line: ║      title               ║
		moveCursor(1, 2);
		std::cout << charSet.vertical;
		int spaceBefore = padding - 1;
		int spaceAfter = consoleWidth - 2 - spaceBefore - title.length();
		if (spaceAfter < 0) spaceAfter = 0;
		if (spaceBefore < 0) spaceBefore = 0;
		for (int i = 0; i < spaceBefore; ++i) std::cout << " ";
		std::cout << title;
		for (int i = 0; i < spaceAfter; ++i) std::cout << " ";
		std::cout << charSet.vertical;

		// Bottom border: ╚════════════════════════════╝
		moveCursor(1, 3);
		std::cout << charSet.bottomLeft;
		for (int i = 0; i < consoleWidth - 2; ++i) std::cout << charSet.horizontal;
		std::cout << charSet.bottomRight;

		return *this;
	}

	// Reset color and style
	Console& reset() {
		std::cout << "\033[0m";
		return *this;
	}

	// Flush output
	Console& flush() {
		std::cout.flush();
		return *this;
	}

	//função de input pra caputrar texto do usuário..
	std::string input(const std::string& prompt = "") {
		if (!prompt.empty()) {
			std::cout << prompt;
		}
		std::string value;
		std::getline(std::cin, value);
		return value;
	}

	// Read integer input with optional prompt
	int inputInt(const std::string& prompt = "") {
		while (true) {
			if (!prompt.empty()) {
				std::cout << prompt;
			}
			std::string value;
			std::getline(std::cin, value);
			try {
				return std::stoi(value);
			}
			catch (const std::invalid_argument&) {
				std::cout << "Invalid integer. Please try again.\n";
			}
			catch (const std::out_of_range&) {
				std::cout << "Number out of range. Please try again.\n";
			}
		}
	}

	// Read float input with optional prompt
	float inputFloat(const std::string& prompt = "") {
		while (true) {
			if (!prompt.empty()) {
				std::cout << prompt;
			}
			std::string value;
			std::getline(std::cin, value);
			try {
				return std::stof(value);
			}
			catch (const std::invalid_argument&) {
				std::cout << "Invalid float. Please try again.\n";
			}
			catch (const std::out_of_range&) {
				std::cout << "Number out of range. Please try again.\n";
			}
		}
	}

	// Read double input with optional prompt
	double inputDouble(const std::string& prompt = "") {
		while (true) {
			if (!prompt.empty()) {
				std::cout << prompt;
			}
			std::string value;
			std::getline(std::cin, value);
			try {
				return std::stod(value);
			}
			catch (const std::invalid_argument&) {
				std::cout << "Invalid double. Please try again.\n";
			}
			catch (const std::out_of_range&) {
				std::cout << "Number out of range. Please try again.\n";
			}
		}
	}

	Console& drawBox(int x, int y, int width, int height, Console::BoxStyle style = Console::BoxStyle::Single) {
		if (width < 2) width = 2;   // largura mínima pra desenhar borda
		if (height < 2) height = 2; // altura mínima

		BoxCharSet charSet;
		switch (style) {
		case BoxStyle::Single: charSet = { "┌", "┐", "└", "┘", "─", "│" }; break;
		case BoxStyle::Double: charSet = { "╔", "╗", "╚", "╝", "═", "║" }; break;
		case BoxStyle::Broad: charSet = { "┏", "┓", "┗", "┛", "━", "┃" }; break;
		case BoxStyle::Dashed: charSet = { "┌", "┐", "└", "┘", "┄", "┆" }; break;
		case BoxStyle::Rounded: charSet = { "╭", "╮", "╰", "╯", "─", "│" }; break;
		default: charSet = { "+", "+", "+", "+", "-", "|" }; break;
		}

		// Top border
		moveCursor(x, y);
		std::cout << charSet.topLeft;
		for (int i = 0; i < width - 2; ++i) std::cout << charSet.horizontal;
		std::cout << charSet.topRight;

		// Sides
		for (int row = y + 1; row < y + height - 1; ++row) {
			moveCursor(x, row);
			std::cout << charSet.vertical;
			moveCursor(x + width - 1, row);
			std::cout << charSet.vertical;
		}

		// Bottom border
		moveCursor(x, y + height - 1);
		std::cout << charSet.bottomLeft;
		for (int i = 0; i < width - 2; ++i) std::cout << charSet.horizontal;
		std::cout << charSet.bottomRight;

		return *this;
	}
};


#endif // !CONSOLE_HPP

