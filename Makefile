CC=`which gcc`
LD=`which gcc`
RM=`which rm` -f
DOXYGEN=`which doxygen`
TAR=`which tar` -czvf

SRCDIR=src
INCDIR= -Iinclude

CFLAGS_DBG=$(CFLAGS) -g -DDEBUG -DVERBOSE
CFLAGS_RLS=$(CFLAGS)
CFLAGS= -Wall $(INCDIR)
LFLAGS= -lelf -lm -lreadline -lcurses

SRC=$(wildcard $(SRCDIR)/*.c)
OBJ_DBG=$(SRC:.c=.dbg.o)
OBJ_RLS=$(SRC:.c=.rls.o)

GARBAGE=*~ include/*~ *.orig include/*.orig src/*~ src/*.orig

ARCHNAME=`date +%d-%m-%y-%H-%M`-`whoami`.tgz
ARCHCONTENT=$(SRC) *file res include doc

#all : mips-load-test mips-load

debug   : $(OBJ_DBG)
	$(LD) $^ $(LFLAGS) -o simMips

release : $(OBJ_RLS)
	$(LD) $^ $(LFLAGS) -o simMips

#mips-load : mipself_test.rls.o mipself.rls.o
#	$(LD) $^ -o $@ $(LFLAGS) $(CFLAGS_RLS) $(INCDIR)

#mipself.dbg.o:	src/mipself.c
#	$(CC) $^ $(CFLAGS) $(CFLAGS_DBG) $(INCDIR) -c -o mipself.dbg.o

#mipself.rls.o:	src/mipself.c
#	$(CC) $^ $(CFLAGS) $(CFLAGS_RLS) $(INCDIR) -c -o mipself.rls.o

#mips-load-test : mipself_test.dbg.o mipself.dbg.o
#	$(LD) $^ -o $@ $(LFLAGS) $(CFLAGS_DBG) $(INCDIR)

%.rls.o : %.c
	$(CC) $< $(CFLAGS) $(CFLAGS_RLS) -c -o $(basename $<).rls.o

%.dbg.o : %.c
	$(CC) $< $(CFLAGS) $(CFLAGS_DBG) -c -o $(basename $<).dbg.o

clean : 
	$(RM) $(OBJ) $(GARBAGE) perso *.o simMips $(SRCDIR)/*.o

documentation : 
	$(DOXYGEN)

archive : 
	$(TAR) ../$(ARCHNAME) $(ARCHCONTENT) && mv ../$(ARCHNAME) .

hash_cmd.o : src/hash_cmd.c
	gcc -c src/hash_cmd.c $(CFLAGS) -o hash_cmd.o

lp.o : 	src/lp.c
	gcc -c src/lp.c $(CFLAGS) -o lp.o

parseAddr.o : src/parseAddr.c
	gcc -c src/parseAddr.c $(CFLAGS) -o parseAddr.o

parseHexa.o : src/parseHexa.c
	gcc -c src/parseHexa.c $(CFLAGS) -o parseHexa.o

perso	: perso.c hash_cmd.o lp.o parseAddr.o parseHexa.o
	gcc perso.c $(CFLAGS) hash_cmd.o lp.o parseAddr.o parseHexa.o -o perso
