
#lufer
#Preparar tudo
#----------------------------------

# 1. Compilar a biblioteca
gcc -c Calc.c -o Calc.o // objeto
ar rcs libcalc.a Calc.o // biblioteca estática

# 2. Compilar o programa com a biblioteca
gcc Calculus.c -L. -lcalc -o Calculus.exe -mconsole

# 3. Executar
Calculus.exe

#----------------------------------
# usar Makefiles

#1 ficheiro makefile
make

#2 ficheiro makefile2
make -f makefile2

#3 definir na licha de comando o valor de SIZE
make SIZE=300
