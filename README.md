# Pipex

Pipex is a 42 project of proto implementations of the shell pipe and redirection commands a.k.a. `|`, `>`,`>>`, etc.

## How to run

- Clone the repository
- Compile with `make`
- (Optional) you can compile with `make run` to run the tests and `make valgrind` to run the tests with valgrind and check for memory leaks

## How to use

Allow pipex to be executed as a command.

```sh
chmod +x pipex
```

### Execute commands with `pipex`

The pipex commands should be surrounded by double quotes to be properly read as arguments.

```sh
./pipex input_file "<cmd 1>" "<cmd 2>" ... "<nth-cmd>" output_file
```

Should be equivalent to

```sh
< input_file <cmd 1> | <cmd 2> | ... | <nth-cmd> > output_file
```

Pipex commands are also able to handle flags.

### Here documents `<<` and `>>`

```sh
./pipex here_doc <LIMITER> "<cmd 1>" "<cmd 2>" ... output_file
```

Should be equivalent to

```sh
<< <LIMITER> <cmd 1> | <cmd 2> | ... >> output_file
```

e.g.

```sh
./pipex here_doc EOF "grep -i here" "wc -w" output_file
This is a here document
EOF
```

Should output `1\n` in the output file.
