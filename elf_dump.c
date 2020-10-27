#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <malloc.h>

#include <file_read.h>

/* We're ignoring all the _* fields */
struct elf_header {
	uint32_t magic;
	uint8_t  _filler1[20];	/* important information, but we're ignoring it! */
	uint64_t entry_address;
	uint64_t prog_header_offset;
	uint8_t  _filler2[14];	/* important information, but we're ignoring it! */
	uint16_t prog_headers_sz;
	uint16_t num_prog_headers;
} __attribute__((packed)); 	/* all fields should be right after each other */

#define ELF_TYPE_LOADABLE 1

#define ELF_FLAG_EXECUTABLE 1
#define ELF_FLAG_WRITABLE   2
#define ELF_FLAG_READABLE   4

struct elf_prog_header {
	uint32_t type; 		/* 1 == loadable memory */
	uint32_t flags;
	uint64_t file_offset;
	uint64_t _filler2[2];
	uint64_t size;
	uint64_t _filler3[2];
} __attribute__((packed));

void
elf_dump(char *bin)
{
	int sz;
	char *file;
	struct elf_header *h;
	struct elf_prog_header *ph;
	int i;

	file = file_read(bin, &sz);
	assert(file);

	h = (struct elf_header *)file;

	printf("Entry address %lx\nNum headers %d\nHeader size %d\n",
	       h->entry_address, h->num_prog_headers, h->prog_headers_sz);

	assert(sizeof(struct elf_prog_header) == h->prog_headers_sz);

	ph = (struct elf_prog_header *)(file + h->prog_header_offset);
	for (i = 0; i < h->num_prog_headers; i++) {
		if (ph[i].type != ELF_TYPE_LOADABLE) continue; /* is this not loadable memory? Ignore! */
		printf("program header flags %x, offset %lx, size 0x%lx\n",
		       ph[i].flags, ph[i].file_offset, ph[i].size);
		printf("flags key: x = 1, w = 2, r = 4, rw = 6, xr = 5\n");

		if (ph[i].flags != (ELF_FLAG_READABLE | ELF_FLAG_WRITABLE)) continue;

		printf("Here we must boldly go!\nSeek out the 0xDEADBEEF, and find the answer!\n"
			"We know its offset into the memory, the size of the section, and we must seek out the knowledge flanked by 0xDEADBEEF.\n");
	}

	printf("\n");

	free(file);

	return;
}
