#include "pch.h"
#include "PDFParser.h"
#include <podofo/podofo.h>

using namespace PoDoFo;

PDFParser::PDFParser() {

}

PDFParser::~PDFParser() {

}

void PDFParser::load(std::wstring* path) {
	PdfMemDocument pdf(path->c_str());
	std::vector<PdfVariant> vars;
	for (int pn = 0; pn < pdf.GetPageCount(); ++pn) {
		PoDoFo::PdfPage* page = pdf.GetPage(pn);
		PoDoFo::PdfContentsTokenizer tok(page);
		const char* token = nullptr;
		PoDoFo::PdfVariant var;
		PoDoFo::EPdfContentsType type;
		PdfVariant das;

		while (tok.ReadNext(type, token, var)) { 

			switch (type) {
			case PoDoFo::ePdfContentsType_Keyword:
				// process token: it contains the current command
				//   pop from var stack as necessary
				//var = vars.back();
				if (var.IsString()) {
					const char * buffer = var.GetString().GetString();
					wchar_t text1[300];
					mbstowcs(text1, buffer, strlen(buffer) + 1);
					LPCWSTR test = text1;
					OutputDebugString(test);
						 
					// do something with a[i].GetString()

				}
				//vars.pop_back();
				break;
			case PoDoFo::ePdfContentsType_Variant:
				// process var: push it onto a stack
				vars.push_back(var);
				
				break;
			default:
				// should not happen!
				break;
			}
		}
		
	}

}