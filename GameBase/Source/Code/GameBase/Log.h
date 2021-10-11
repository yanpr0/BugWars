#pragma once

// Basic log. std::format style
#define Log(fmt, ...) \
{ \
	std::stringstream ss; \
	ss << std::format("{}({},{}): ", __FILE__, __LINE__, 0); \
	ss << std::format(fmt, __VA_ARGS__); \
	ss << '\n'; \
	std::cout << ss.str() << std::endl; \
	OutputDebugStringA(ss.str().c_str()); \
}

// Zero alloc log. Printf style
#define LogZA(fmt, ...) \
{ \
	char message[2048]; \
	sprintf_s(message, 2048, fmt, __VA_ARGS__); \
	char file_line_message[2048]; \
	sprintf_s(file_line_message, 2048, "%s(%i,0): %s\n", __FILE__, __LINE__, message); \
	printf(file_line_message); \
	OutputDebugStringA(file_line_message); \
}
