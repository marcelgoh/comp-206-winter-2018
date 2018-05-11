CC=gcc

INCDIR=include
OBJDIR=obj

SRCS=src/movie_recommender.c src/preferences.c src/distances.c
HEADERS=${INCDIR}/preferences.h ${INCDIR}/distances.h
OBJS=${SRCS:src/%.c=${OBJDIR}/%.o}
EXEC=movie_recommender
TRASH=${OBJDIR} ${EXEC}

CFLAGS=-I${INCDIR}

$(shell mkdir -p ${OBJDIR})

${EXEC}: ${OBJS}
	${CC} ${CFLAGS} ${SRCS} -o $@
${OBJDIR}/%.o: src/%.c ${HEADERS}
	${CC} ${CFLAGS} -c -o $@ $<
.PHONY: clean
clean:
	rm -rf ${TRASH}
