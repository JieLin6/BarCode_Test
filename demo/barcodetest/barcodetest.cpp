#include <iostream>
#include <assert.h>
#include <string>
#include "dmtx.h"

using namespace std;

int main(int argc, char* argv[])
{
	size_t          width, height, bytesPerPixel;
	string str = "ÖÐ¹ú_abc_DEF_123_@#$£¡";
	string dst;
	unsigned char  *pxl;
	DmtxEncode     *enc;
	DmtxImage      *img;
	DmtxDecode     *dec;
	DmtxRegion     *reg;
	DmtxMessage    *msg;

	//fprintf(stdout, "input:  \"%s\"\n", str);
	cout<<"str : "<<str<<endl;

	/* 1) ENCODE a new Data Matrix barcode image (in memory only) */
	enc = dmtxEncodeCreate();
	assert(enc != NULL);
	//dmtxEncodeDataMatrix(enc, strlen(str), str);
	dmtxEncodeDataMatrix(enc, strlen(str.c_str()), (unsigned char*)str.c_str());

	/* 2) COPY the new image data before releasing encoding memory */
	width = dmtxImageGetProp(enc->image, DmtxPropWidth);
	height = dmtxImageGetProp(enc->image, DmtxPropHeight);
	bytesPerPixel = dmtxImageGetProp(enc->image, DmtxPropBytesPerPixel);

	pxl = (unsigned char *)malloc(width * height * bytesPerPixel);
	assert(pxl != NULL);
	memcpy(pxl, enc->image->pxl, width * height * bytesPerPixel);

	dmtxEncodeDestroy(&enc);

	/* 3) DECODE the Data Matrix barcode from the copied image */
	img = dmtxImageCreate(pxl, width, height, DmtxPack24bppRGB);
	assert(img != NULL);

	dec = dmtxDecodeCreate(img, 1);
	assert(dec != NULL);

	reg = dmtxRegionFindNext(dec, NULL);
	if(reg != NULL) {
		msg = dmtxDecodeMatrixRegion(dec, reg, DmtxUndefined);
		if(msg != NULL) {
			/*fputs("output: \"", stdout);
			fwrite(msg->output, sizeof(unsigned char), msg->outputIdx, stdout);
			fputs("\"\n", stdout);*/
			dst = string(reinterpret_cast<const char*>(msg->output));
			dmtxMessageDestroy(&msg);
		}
		dmtxRegionDestroy(&reg);
	}

	cout<<"dst : "<<dst<<endl;

	dmtxDecodeDestroy(&dec);
	dmtxImageDestroy(&img);
	free(pxl);

	cout<<"ok!"<<endl;
	return 0;
}

