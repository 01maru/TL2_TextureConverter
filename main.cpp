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

	//	Initialize COM Lib
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	TextureConverter converter;

	//	•ÏŠ·
	converter.ConvertTextureWICToDDS(argv[kFilePath]);

	//	End Com Lib
	CoUninitialize();
	
	system("pause");
	return 0;
}