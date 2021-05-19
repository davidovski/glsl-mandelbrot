PROG=brotshader
CC=gcc
FLAGS=-lm `pkg-config -libs raylib`

${PROG}: ${PROG}.c
	${CC} ${PROG}.c -o ${PROG} ${FLAGS}

run: ${PROG}
	./${PROG} 

