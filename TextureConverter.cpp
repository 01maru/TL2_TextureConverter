#include "TextureConverter.h"
#include <Windows.h>

void TextureConverter::LoadWICTextureFromFile(const std::string& filepath)
{
	std::wstring wfilepath = ConvertMultiByteStringToWString(filepath);
}

std::wstring TextureConverter::ConvertMultiByteStringToWString(const std::string& mString)
{
	int size = MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, nullptr, 0);
	std::wstring wString;
	wString.resize(size);

	MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, &wString[0], size);
	return wString;
}

void TextureConverter::ConvertTextureWICToDDS(const std::string& filepath)
{
	LoadWICTextureFromFile(filepath);
}
