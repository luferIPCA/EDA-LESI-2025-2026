
#lufer
#makefile "generalizada"
#executar com "make SIZE=N"
#-----------------------------

# Nomes
LIB_NAME = calc
LIB_FILE = lib$(LIB_NAME).a
OBJ_LIB = Calc.o
SRC_LIB = Calc.c
SRC_MAIN = Calculus.c
TARGET = Calculus.exe

# Compilador
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Regra padrão
all: $(TARGET)

# Criar biblioteca estática
$(LIB_FILE): $(OBJ_LIB)
	ar rcs $@ $^

# Compilar objeto da biblioteca
$(OBJ_LIB): $(SRC_LIB) Calc.h
	$(CC) $(CFLAGS) -c $< -o $@

# Compilar executável
# -DSIZE permite controla valor de SIZE sem editar o código
$(TARGET): $(SRC_MAIN) $(LIB_FILE)
	$(CC) $(CFLAGS) $< -L. -l$(LIB_NAME) -o $@ -mconsole -DSIZE=$(or $(SIZE),10)

# Limpar arquivos gerados
clean:
	del /Q *.o *.a $(TARGET)


doc:
	@echo "Generating Doxygen documentation..."
	doxygen Doxyfile
	@echo "Compiling LaTeX PDF using MiKTeX..."
	cd latex && pdftex refman.tex && pdflatex refman.tex
	@echo "Documentation PDF generated at latex/refman.pdf"
