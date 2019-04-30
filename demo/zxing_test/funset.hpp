#ifndef FBC_ZXING_FUNSET_HPP_
#define FBC_ZXING_FUNSET_HPP_

#include <Windows.h>
#include <string>

int test_Aztec_decode();
int test_DataMatrix_decode();
int test_Maxicode_decode();
int test_PDF417_decode();
int test_QRCode_decode();
int test_Codabar_decode();
int test_Code39_decode();
int test_Code93_decode();
int test_Code128_decode();
int test_EAN8_decode();
int test_EAN13_decode();
int test_ITF25_decode();
int test_RSS14_decode();
int test_RSS_Expanded_decode();
int test_UPC_A_decode();
int test_UPC_E_decode();

namespace {

std::string utf8_to_gbk(const char* utf8)
{
	char gbk[256];
	const int maxlen = 256;
	wchar_t unicode_str[maxlen];
	int outlen = MultiByteToWideChar(CP_UTF8, 0, utf8, strlen(utf8), unicode_str, maxlen);
	outlen = WideCharToMultiByte(CP_ACP, 0, unicode_str, outlen, gbk, 256, NULL, NULL);
	gbk[outlen] = '\0';

	std::string str;
	str.assign(gbk);
	return str;
}

}

#endif // FBC_ZXING_FUNSET_HPP_
