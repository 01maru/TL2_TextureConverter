#include "TextureConverter.h"
#include <Windows.h>

using namespace DirectX;

void TextureConverter::LoadWICTextureFromFile(const std::string& filepath)
{
	//	�^�ϊ�
	std::wstring wfilepath = ConvertMultiByteStringToWString(filepath);

	//	WIC�e�N�X�`���̃��[�h
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

	//	'.'�̈�ԍŌ������
	pos1 = filepath.rfind('.');

	if (pos1 != std::wstring::npos) {
		//	'.'�̌����g���q�Ƃ���
		fileExt_ = filepath.substr(pos1 + 1, filepath.size() - pos1 - 1);
		//	'.'�̑O�܂Ŕ����o��
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

void TextureConverter::SaveDDSTextureToFile(int numOptions, char* options[])
{
	HRESULT hr;
	size_t mipLevel = 0;
	for (int i = 0; i < numOptions; i++)
	{
		if (std::string(options[i]) == "-ml") {
			mipLevel = std::stoi(options[i + 1]);
			break;
		}
	}
	//	�~�j�}�b�v����
	ScratchImage mipChain{};
	hr = GenerateMipMaps(
		scratchImg_.GetImages(), scratchImg_.GetImageCount(), scratchImg_.GetMetadata(),
		TEX_FILTER_DEFAULT, mipLevel, mipChain);

	if (SUCCEEDED(hr)) {
		scratchImg_ = std::move(mipChain);
		metadata_ = scratchImg_.GetMetadata();
	}

	ScratchImage converted;
	hr = Compress(scratchImg_.GetImages(), scratchImg_.GetImageCount(), metadata_,
		DXGI_FORMAT_BC7_UNORM_SRGB, TEX_COMPRESS_BC7_QUICK | TEX_COMPRESS_SRGB_OUT |
		TEX_COMPRESS_PARALLEL, 1.0f, converted);

	if (SUCCEEDED(hr)) {
		scratchImg_ = std::move(converted);
		metadata_ = scratchImg_.GetMetadata();
	}

	metadata_.format = MakeSRGB(metadata_.format);

	//	�o�̓t�@�C�����ݒ�
	std::wstring filepath = dirpath_ + filename_ + L".dds";

	hr = SaveToDDSFile(scratchImg_.GetImages(), scratchImg_.GetImageCount(), metadata_,
		DDS_FLAGS_NONE, filepath.c_str());
	assert(SUCCEEDED(hr));
}

void TextureConverter::OutputUsage()
{
	printf("�摜�t�@�C����WIC�`������DDS�`���ɕϊ����܂��B\n");
	printf("\n");
	printf("TextureConverter [�h���C�u:][�p�X][�t�@�C����] [-ml level]\n");
	printf("\n");
	printf("[�h���C�u:][�p�X][�t�@�C����]: �ϊ�������WIC�`���̉摜�t�@�C�����w�肵�܂��B\n");
	printf("\n");
	printf("[-ml level]: �~�b�v���x�����w�肵�܂��B0���w�肷���1x1�܂ł̃t���~�b�v�}�b�v�`�F�[���𐶐����܂��B\n");
}

void TextureConverter::ConvertTextureWICToDDS(const std::string& filepath, int numOptions, char* options[])
{
	LoadWICTextureFromFile(filepath);

	SaveDDSTextureToFile(numOptions, options);
}
