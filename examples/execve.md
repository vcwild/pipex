The following program is designed to be execed by the second
program below.  It just echoes its command-line arguments, one
per line.
```c
/* myecho.c */

#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
	for (int j = 0; j < argc; j++)
		printf("argv[%d]: %s\n", j, argv[j]);

	exit(EXIT_SUCCESS);
}
```
This program can be used to exec the program named in its
command-line argument:

```c
/* execve.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
	char *newargv[] = { NULL, "hello", "world", NULL };
	char *newenviron[] = { NULL };

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <file-to-exec>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	newargv[0] = argv[1];

	execve(argv[1], newargv, newenviron);
	perror("execve");   /* execve() returns only on error */
	exit(EXIT_FAILURE);
}
```

We can use the second program to exec the first as follows:

```sh
$ cc myecho.c -o myecho
$ cc execve.c -o execve
$ ./execve ./myecho
argv[0]: ./myecho
argv[1]: hello
argv[2]: world
```

We can also use these programs to demonstrate the use of a script
interpreter.  To do this we create a script whose "interpreter"
is our myecho program:

```sh
$ cat > script
#!./myecho script-arg
^D
$ chmod +x script
```

We can then use our program to exec the script:

```sh
$ ./execve ./script
argv[0]: ./myecho
argv[1]: script-arg
argv[2]: ./script
argv[3]: hello
argv[4]: world
```