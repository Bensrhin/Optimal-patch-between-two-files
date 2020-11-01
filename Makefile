# Repertoires du projet
BIN = bin
SRC = src
OBJ = obj
DOC = doc

CFLAGS=-std=c99 -Wall -Wextra -g -lm
# option de compilation

# LATEXMK = pdflatex -output-directory $(RAPPORT)
# RAPPORT = rapport
# TARGET_FILES = rapport.pdf # À REMPLACER PAR rapport.pdf
#
# FILES = $(addprefix $(RAPPORT)/,$(TARGET_FILES))
all: $(BIN)/computePatchOpt doc #rapport
	@echo "\033[46mSUCCESS COMPILATION !\033[0m"

dirs:
	mkdir -p $(BIN)
	mkdir -p $(OBJ)

rapport: $(FILES)

%.aux: %.tex
	$(LATEXMK) $<

%.pdf: dirs
	$(LATEXMK) $(@:.pdf=.tex)
	cp -f $(OBJ_DIR)/$(basename $(@F)).pdf $@



$(OBJ)/computePatchOpt.o: $(SRC)/computePatchOpt.c dirs
	gcc -c -o $@ $< $(CFLAGS)

$(BIN)/computePatchOpt: $(OBJ)/computePatchOpt.o $(OBJ)/operations.o $(OBJ)/instruction.o $(OBJ)/parcoursInverse.o $(OBJ)/manageFile.o $(OBJ)/writePatch.o $(OBJ)/bellman.o
	gcc -o $@ $^ $(CFLAGS)

$(OBJ)/operations.o: $(SRC)/operations.c dirs
	gcc -c -o $@ $< $(CFLAGS)
$(OBJ)/instruction.o: $(SRC)/instruction.c dirs
	gcc -c -o $@ $< $(CFLAGS)
$(OBJ)/parcoursInverse.o: $(SRC)/parcoursInverse.c dirs
	gcc -c -o $@ $< $(CFLAGS)
$(OBJ)/manageFile.o: $(SRC)/manageFile.c dirs
	gcc -c -o $@ $< $(CFLAGS)
$(OBJ)/writePatch.o: $(SRC)/writePatch.c dirs
	gcc -c -o $@ $< $(CFLAGS)
$(OBJ)/bellman.o: $(SRC)/bellman.c dirs
	gcc -c -o $@ $< $(CFLAGS)


doc:
	doxygen Doxyfile

clean:
	rm -rf $(BIN)
	rm -rf $(DOC)
	rm -rf $(OBJ)
	rm -rf $(FILES)

.PHONY: clean all dirs doc rapport
