#pragma once

#include <string>


class PDFParser
{
public:
	PDFParser();
	~PDFParser();

	void load(std::wstring* path);
};

