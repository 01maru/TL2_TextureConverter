#pragma once
#include <string>

class TextureConverter
{
private:
	/// <summary>
	/// LoadTextureFile
	/// </summary>
	/// <param name="filepath"></param>
	void LoadWICTextureFromFile(const std::string& filepath);
	/// <summary>
	/// Convert MultiByte -> Wide String
	/// </summary>
	/// <param name="mString"></param>
	/// <returns></returns>
	static std::wstring ConvertMultiByteStringToWString(const std::string& mString);
public:
	/// <summary>
	/// Texture WIC -> DDS •ÏŠ·
	/// </summary>
	/// <param name="filepath"></param>
	void ConvertTextureWICToDDS(const std::string& filepath);
};

