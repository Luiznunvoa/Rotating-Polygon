#
# Copyright (c) 2024 Luiz Gabriel Moraes "Luiz".
#
# This file is part of SimpleChess_SDL.
#
# SimpleChess_SDL is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License, version 3
# as published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# SimpleChess_SDL is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>..
#

PROJECT_NAME = Rotating-Polygon
FILES = main app res polygon

SRC_DIR = src
BIN_DIR = bin

CC = gcc
ARGS = 

LIB = SDL2

ifeq ($(OS), Windows_NT)
	# Windows(configure here the path of the libraries)
    SEP = \\

    LIB_PATHS = # C:/SDL2-2.30.7/x86_64-w64-mingw32 (example)

    OS_LIBS =
   
    COPY = copy /Y
    DEL = del /Q
else
    OS := $(shell uname)
    ifeq ($(OS), Linux)
    	# Linux(configure here the path of the libraries)
        SEP = /

        LIB_PATHS = # /usr/local/lib/SDL2 (example)

        OS_LIBS = 

        COPY = cp
        DEL = rm -f
    else
        $(error Unknown Operational System: $(OS))
    endif
endif

INCLUDE_DIRS = $(foreach dir,$(LIB_PATHS),-I$(dir)$(SEP)include)
LIB_DIRS = $(foreach dir,$(LIB_PATHS),-L"$(dir)$(SEP)lib")
LIB_LINKERS = $(foreach lib,$(LIB),-l$(lib))
OS_LIB_LINKERS = $(foreach lib,$(OS_LIBS),-l$(lib))

SRC_FILES = $(addprefix $(SRC_DIR)$(SEP), $(addsuffix .c, $(FILES)))
OBJ_FILES = $(SRC_FILES:.c=.o)

ifeq ($(OS), Windows_NT)

DLL_FILES = $(foreach lib,$(LIB),$(firstword $(foreach dir,$(LIB_PATHS),$(wildcard $(dir)$(SEP)bin$(SEP)$(lib).dll))))
DLL_TARGET = $(foreach lib,$(LIB),$(BIN_DIR)$(SEP)$(lib).dll)

all: $(BIN_DIR)$(SEP)$(PROJECT_NAME) $(DLL_TARGET)

else

all: $(BIN_DIR)$(SEP)$(PROJECT_NAME)

endif

$(BIN_DIR)$(SEP)$(PROJECT_NAME): $(OBJ_FILES) | $(BIN_DIR)
	$(CC) $(INCLUDE_DIRS) -o $@ $(OBJ_FILES) $(LIB_DIRS) $(LIB_LINKERS) $(OS_LIB_LINKERS)
	@echo "Compilation successful"
	$(DEL) $(OBJ_FILES) 2>nul || true

ifeq ($(OS), Windows_NT)

$(DLL_TARGET): | $(BIN_DIR)
	@for %%F in ($(DLL_FILES)) do @( \
		$(COPY) "%%F" "$(BIN_DIR)" >nul && \
		echo %%~nF found! \
	)

endif

$(BIN_DIR):
	mkdir $(BIN_DIR)

%.o: %.c
	$(CC) $(ARGS) $(INCLUDE_DIRS) -c $< -o $@

run:
	$(BIN_DIR)$(SEP)$(PROJECT_NAME)

clean:
ifeq ($(OS), Windows_NT)
	$(DEL) $(OBJ_DIR)\* 2>nul
	$(DEL) $(BIN_DIR)\* 2>nul
	-rmdir $(OBJ_DIR) 2>nul
	-rmdir $(BIN_DIR) 2>nul
else
	rm -rf $(OBJ_DIR) $(BIN_DIR)
endif
	@echo "All files and directories have been deleted"