#include "TextureConverter.h"
#include <Windows.h>

using namespace DirectX;

void TextureConverter::LoadWICTextureFromFile(const std::string& filepath)
{
	//	型変換
	std::wstring wfilepath = ConvertMultiByteStringToWString(filepath);

	//	WICテクスチャのロード
	HRESULT hr = LoadFromWICFile(wfilepath.c_str(), WIC_FLAGS_NONE, &metadata_, scratchImg_);
	assert(SUCCEEDED(hr));
	
	SeparateFilePath(wfilepath);
}

std::wstring TextureConverter::ConvertMultiByteStringToWString(const std::string& mString)
{
	int size = MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, nullptr, 0);
	std::wstring wString;
	wString.resize(size);

	MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, &wString[0], size);
	return wString;
}

void TextureConverter::SeparateFilePath(const std::wstring& filepath)
{
	size_t pos1;
	std::wstring exceptExt;

	//	'.'の一番最後を検索
	pos1 = filepath.rfind('.');

	if (pos1 != std::wstring::npos) {
		//	'.'の後ろを拡張子とする
		fileExt_ = filepath.substr(pos1 + 1, filepath.size() - pos1 - 1);
		//	'.'の前まで抜き出す
		exceptExt = filepath.substr(0, pos1);
	}
	else {
		fileExt_ = L"";
		exceptExt = filepath;
	}

	pos1 = exceptExt.rfind('\\');
	if (pos1 != std::wstring::npos)
	{
		dirpath_ = exceptExt.substr(0, pos1 + 1);
		filename_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		return;
	}

	pos1 = exceptExt.rfind('/');
	if (pos1 != std::wstring::npos)
	{
		dirpath_ = exceptExt.substr(0, pos1 + 1);
		filename_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		return;
	}

	dirpath_ = L"";
	filename_ = exceptExt;
}

void TextureConverter::SaveDDSTextureToFile()
{
	metadata_.format = MakeSRGB(metadata_.format);

	HRESULT hr;

	//	出力ファイル名設定
	std::wstring filepath = dirpath_ + filename_ + L".dds";

	hr = SaveToDDSFile(scratchImg_.GetImages(), scratchImg_.GetImageCount(), metadata_,
		DDS_FLAGS_NONE, filepath.c_str());
	assert(SUCCEEDED(hr));
}

void TextureConverter::ConvertTextureWICToDDS(const std::string& filepath)
{
	LoadWICTextureFromFile(filepath);

	SaveDDSTextureToFile();
}
