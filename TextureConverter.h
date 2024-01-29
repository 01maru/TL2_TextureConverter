#pragma once
#include <string>
#include <DirectXTex.h>

class TextureConverter
{
private:
	//	�摜���
	DirectX::TexMetadata metadata_;
	//	�摜�C���[�W�R���e�i
	DirectX::ScratchImage scratchImg_;

	std::wstring dirpath_;	//	�f�B���N�g��
	std::wstring filename_;
	std::wstring fileExt_;	//	�g���q

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
	/// �t�H���_�p�X�ƃt�@�C�����𕪗�
	/// </summary>
	/// <param name="filepath"></param>
	void SeparateFilePath(const std::wstring& filepath);
	/// <summary>
	/// DDS�e�N�X�`���N�ăt�@�C�������o��
	/// </summary>
	void SaveDDSTextureToFile(int numOptions, char* options[]);
public:
	/// <summary>
	/// �g�p���@���o��(�\��)����
	/// </summary>
	static void OutputUsage();
	/// <summary>
	/// Texture WIC -> DDS �ϊ�
	/// </summary>
	/// <param name="filepath"></param>
	void ConvertTextureWICToDDS(const std::string& filepath
		, int numOptions = 0, char* options[] = nullptr);
};

