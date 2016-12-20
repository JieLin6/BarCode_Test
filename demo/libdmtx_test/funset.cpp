#include "funset.hpp"
#include <assert.h>
#include <iostream>
#include <string>
#include "dmtx.h"

int data_matrix_encode()
{
	std::string str = "ÖÐ¹ú_abc_DEF_123_@#$£¡";

	/* 1) ENCODE a new Data Matrix barcode image (in memory only) */
	DmtxEncode* enc = dmtxEncodeCreate();
	assert(enc != NULL);
	int ret = dmtxEncodeDataMatrix(enc, strlen(str.c_str()), (unsigned char*)str.c_str());
	assert(ret == 1);

	/* 2) COPY the new image data before releasing encoding memory */
	int width = dmtxImageGetProp(enc->image, DmtxPropWidth);
	int height = dmtxImageGetProp(enc->image, DmtxPropHeight);
	int bytesPerPixel = dmtxImageGetProp(enc->image, DmtxPropBytesPerPixel);

	unsigned char* pxl = (unsigned char *)malloc(width * height * bytesPerPixel);
	assert(pxl != NULL);
	memcpy(pxl, enc->image->pxl, width * height * bytesPerPixel);

	dmtxEncodeDestroy(&enc);

	/* 3) DECODE the Data Matrix barcode from the copied image */
	DmtxImage* img = dmtxImageCreate(pxl, width, height, DmtxPack24bppRGB);
	assert(img != NULL);

	DmtxDecode* dec = dmtxDecodeCreate(img, 1);
	assert(dec != NULL);

	std::string dst;
	DmtxRegion* reg = dmtxRegionFindNext(dec, NULL);
	if (reg != NULL) {
		DmtxMessage* msg = dmtxDecodeMatrixRegion(dec, reg, DmtxUndefined);
		if (msg != NULL) {
			/*fputs("output: \"", stdout);
			fwrite(msg->output, sizeof(unsigned char), msg->outputIdx, stdout);
			fputs("\"\n", stdout);*/
			dst = std::string(reinterpret_cast<const char*>(msg->output));
			dmtxMessageDestroy(&msg);
		}
		dmtxRegionDestroy(&reg);
	}

	std::cout << "source string : " << str << std::endl;
	std::cout << "dst    string : " << dst << std::endl;

	dmtxDecodeDestroy(&dec);
	dmtxImageDestroy(&img);
	free(pxl);

	return 0;
}

int data_matrix_decode()
{


	return 0;
}

