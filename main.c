#define SCANELF 1
//#define FILEDUMP 1

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

#include <file_read.h>
#include <elf_dump.h>

void
print_file(char *file)
{
	char *filedata;
	int sz;

	filedata = file_read(file, &sz);
	assert(filedata);

	printf("%s\n", filedata);
	free(filedata);

	return;
}

int
main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Usage: %s <filename>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

#ifdef FILEDUMP
	print_file(argv[1]);
#endif
#ifdef SCANELF
	elf_dump(argv[1]);
#endif

	return 0;
}
