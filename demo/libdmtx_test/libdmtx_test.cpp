#include <iostream>
#include "funset.hpp"

int main(int argc, char* argv[])
{
	int ret = data_matrix_encode();

	if (ret == 0) fprintf(stderr, "test success\n");
	else fprintf(stderr, "test fail: %d\n", ret);

	return 0;
}

