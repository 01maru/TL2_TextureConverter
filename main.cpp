#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <DirectXTex.h>

#include "TextureConverter.h"

enum Argument {
	kApplicationPath,
	kFilePath,

	NumArgument,
};

int main(int argc, char* argv[]) {

	assert(argc >= NumArgument);

	if (argc < NumArgument) {
		TextureConverter::OutputUsage();
		return 0;
	}

	//	Initialize COM Lib
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	TextureConverter converter;

	int numOptions = argc - NumArgument;
	char** options = argv + NumArgument;

	//	•ÏŠ·
	converter.ConvertTextureWICToDDS(argv[kFilePath], numOptions, options);

	//	End Com Lib
	CoUninitialize();
	
	//system("pause");
	return 0;
}