module;

#include "../include.h"

export module util;

#include <format>

export enum LogType_t {
	LOG_INFO,
	LOG_DEBUG,
	LOG_WARNING,
	LOG_ERROR
};

export namespace Util {
	HANDLE consoleHandle = nullptr;

	template<typename... Args>
	std::string Fmt(std::string_view fmt, Args&&... args) {
		return std::vformat(fmt, std::make_format_args(args...));
	}

	template<LogType_t type = LOG_INFO, typename... Args>
	inline void Log(const std::string& fmt, Args&&... args) {
		if (!consoleHandle)
			return;

		switch (type)
		{
		case LOG_INFO:
			SetConsoleTextAttribute(consoleHandle, 15);
			std::cout << "[+] ";
			break;
		case LOG_DEBUG:
			SetConsoleTextAttribute(consoleHandle, 2);
			std::cout << "[*] ";
			break;
		case LOG_WARNING:
			SetConsoleTextAttribute(consoleHandle, 14);
			std::cout << "[!] ";
			break;
		case LOG_ERROR:
			SetConsoleTextAttribute(consoleHandle, 12);
			std::cout << "[-] ";
			break;
		default:
			break;
		}

		SetConsoleTextAttribute(consoleHandle, 7);
		std::cout << std::vformat(fmt, std::make_format_args(args...)).c_str() << std::endl;
	}
}