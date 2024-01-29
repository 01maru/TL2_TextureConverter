#pragma once
#include <string>
#include <DirectXTex.h>

class TextureConverter
{
private:
	//	画像情報
	DirectX::TexMetadata metadata_;
	//	画像イメージコンテナ
	DirectX::ScratchImage scratchImg_;

	std::wstring dirpath_;	//	ディレクトリ
	std::wstring filename_;
	std::wstring fileExt_;	//	拡張子

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
	/// <summary>
	/// フォルダパスとファイル名を分離
	/// </summary>
	/// <param name="filepath"></param>
	void SeparateFilePath(const std::wstring& filepath);
	/// <summary>
	/// DDSテクスチャ年てファイル書き出し
	/// </summary>
	void SaveDDSTextureToFile(int numOptions, char* options[]);
public:
	/// <summary>
	/// 使用方法を出力(表示)する
	/// </summary>
	static void OutputUsage();
	/// <summary>
	/// Texture WIC -> DDS 変換
	/// </summary>
	/// <param name="filepath"></param>
	void ConvertTextureWICToDDS(const std::string& filepath
		, int numOptions = 0, char* options[] = nullptr);
};

