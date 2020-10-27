# Memory - the Final Frontier

> Raw memory.
> These are the voyages of the OS hacker.
> Deep into the bytes, driven by the knowledge they may bring.
> To boldly go where no typecast has gone before.

![High-flying memory!](enterprise_nx-01_memory.jpg)

Today, we explore in the bits forgotten, and the bits yet to be seen!
Memory manipulation can be difficult, and to understand real memory allocators, you need to be comfortable thinking in terms of pointers, arrays, references, and typecasts.
A few things to remember:

- When you dereference a pointer of type `type *p`, you're accessing the next `N` bytes where `N = sizeof(type)`.
- When you *add* to a pointer `p`, the new pointer is at the numerical address `p + sizeof(*p)`.
- Doing pointer math such as `p + 4` is the *same* as `&p[4]` -- and most people find the array syntax to be more clear than pointer math.

Now that you're equipped to plunge into the depths of the virtual address space, dodging stray `NULL`s, while seeking out the wisdom of the storied `0xdeadbeef` alien race.
They are known to have in their possession the meaning of life, the universe, and everything, and we must know!

Our primary equipment is quite capable.
View its glory:

```
$ make
$ ./bin README.md
```

But first, we must voyage to the planet of the elfs.
Update `main.c` by plotting a course to `SCANELF`.
Starting survey!

```
$ make
$ ./bin bin
```

`bin` is now operating on itself!
But what is it doing?

## Elf Format

Now we dive deep into the exotic, yet exceedingly common [Elf format](https://en.wikipedia.org/wiki/Executable_and_Linkable_Format).
It is the format for each of our programs and is a well-defined standard.

The Elf file format has a header at the start of the file that has a well-formed and defined structure.
We have encoded this strange beast in `elf_dump.c`.
Scattered throughout the elf are a number of `offset`s.
These specify an `offset` into the file (i.e. from the start of the file).
Observe how we have already used the elf header to find the **Program Headers**.

See what those look like with the professional scanning tools:

```
$ objdump -x bin | head -n 27
```

We can see the address at which the binary is supposed to start execution (`start address`), and the program headers.
These are the ranges of memory that are loaded by the OS into memory to execute the program.
Notice again the `off` "offsets" that represent the offset into the file/memory at which that section's memory exists!

Note the symmetry between the `objdump` output and that of `./bin bin`.
The program headers line up!

## Finding the Key to Everything!

We have every indication that within a `LOADABLE` section that includes both readable and writeable data (see objdump output), they to everything is awaiting discovery!

In `elf_dump`, we have found the appropriate section.
What we must now do, is find where `0xDEADBEEF` exists in memory in the loadable, read/write section.
Once we find it, we must find the second instance of `0xDEADBEEF`.
Between the two flanking `0xDEADBEEF`s is the key to everything.

Go forth and find the key to everything, and report back for the greater good of humanity!
