#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>
#include <malloc.h>
#include <stdint.h>

#include <string.h>

char *
file_read(const char *path, int *size)
{
	struct stat fst;
	unsigned int sz;
	char *filedata;
	FILE *fd = fopen(path, "rb");

	if (!fd) return NULL;

	fstat(fileno(fd), &fst);
	sz = fst.st_size;

	filedata = malloc(sz);
	assert(filedata);

	if (fread(filedata, 1, sz, fd) != sz) {
		fclose(fd);
		free(filedata);
		return NULL;
	}
	fclose(fd);
	*size = sz;

	return filedata;
}































uint64_t _d[] = {0xDEADBEEF66666666, 0x2f2f3a7370747468, 0x772e64616f6c7075, 0x616964656d696b69, 0x6b69772f67726f2e, 0x632f616964657069, 0x352f736e6f6d6d6f, 0x77736e412f36352f, 0x694c5f6f745f7265, 0x2020676e702e6566, 0x66666666DEADBEEF};
