NAME = pipex

CC = gcc
CFLAGS = -Wall -Wextra

INTERNAL_LIBS = -lft
EXTERNAL_LIBS = -lm

VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -q --tool=memcheck

LIBFT = libft.a
LIBFT_PATH = $(LIBS_PATH)/libft
LIBFT_ARCHIVE = $(ARCHIVES_PATH)/$(LIBFT)

INPUT_FILE = input_file
CMD1 = "ls -l"
CMD2 = "tr x '\'\'\'"

OUTPUT_FILE = output_file

MAKE_EXTERNAL = make -C
SAFE_MKDIR = mkdir -p

COPY = cp -p

REMOVE = rm -rf

OBJECTS_PATH = ./objects
SOURCES_PATH = ./sources
INCLUDES_PATH = ./includes
LIBS_PATH = ./libs
ARCHIVES_PATH = ./archives
BINS_PATH = ./bin

HEADER_FILE = pipex.h
HEADER = $(addprefix $(INCLUDES_PATH)/,$(HEADER_FILE))

SOURCE_FILES =	main.c\
				rules.c\
				getters.c\
				setters.c\
				parsers.c\
				free.c\
				handlers.c\

SOURCES = $(addprefix $(SOURCES_PATH)/,$(SOURCE_FILES))

OBJECTS = $(addprefix $(OBJECTS_PATH)/,$(subst .c,.o,$(SOURCE_FILES)))

all: $(NAME)

$(NAME): build_libft $(OBJECTS) $(HEADER)
	@$(CC) $(CFLAGS) -w -g $(OBJECTS) -o $(NAME) -L $(ARCHIVES_PATH) -I $(INCLUDES_PATH) $(EXTERNAL_LIBS) $(INTERNAL_LIBS)

$(OBJECTS_PATH)/%.o: $(SOURCES_PATH)/%.c $(HEADER)
	@$(SAFE_MKDIR) $(OBJECTS_PATH)
	@$(CC) $(CFLAGS) -g -I $(INCLUDES_PATH) -o $@ -c $< $(EXTERNAL_LIBS)

local_mkdir:
	@$(SAFE_MKDIR) $(BINS_PATH)

build_libft:
	@$(MAKE_EXTERNAL) $(LIBFT_PATH)
	@$(SAFE_MKDIR) $(ARCHIVES_PATH)
	@$(COPY) $(LIBFT_PATH)/$(LIBFT) $(ARCHIVES_PATH)

libft_clean:
	$(MAKE_EXTERNAL) $(LIBFT_PATH) fclean
	$(REMOVE) $(LIBFT_ARCHIVE)


run: $(NAME)
	./$(NAME) $(INPUT_FILE) $(CMD1) $(CMD2) $(OUTPUT_FILE)


valgrind: $(NAME)
	@$(VALGRIND) ./$(NAME) $(INPUT_FILE) $(CMD1) $(CMD2) $(OUTPUT_FILE)

re:	fclean all

archives_clean:
	$(REMOVE) $(ARCHIVES_PATH)

clean:
	$(REMOVE) $(OBJECTS_PATH)

fclean: clean archives_clean libft_clean
	$(REMOVE) $(NAME)

.PHONY: all run valgrind re fclean clean archives_clean libft_clean
