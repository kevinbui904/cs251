# Change "no" to "yes" to use our binaries
USE_BINARIES = no

ifeq ($(USE_BINARIES),yes)
  SRCS = lib/linkedlist.o lib/talloc.o lib/tokenizer.o lib/parser.o \
				 main.c interpreter.c
  HDRS = lib/parser.h lib/linkedlist.h lib/talloc.h lib/tokenizer.h \
	       lib/value.h interpreter.h
else
  SRCS = linkedlist.c talloc.c main.c tokenizer.c parser.c interpreter.c \
         eval_if.c eval_let.c look_up_symbol.c eval_quote.c eval_define.c \
		 eval_lambda.c apply.c

  HDRS = tokenizer.h linkedlist.h talloc.h parser.h value.h interpreter.h \
  		eval_if.h eval_let.h look_up_symbol.h eval_quote.h eval_define.h \
		  eval_lambda.h apply.h
endif

CC = clang
CFLAGS = -g

OBJS = $(SRCS:.c=.o)

.PHONY: interpreter
interpreter: $(OBJS)
	$(CC)  $(CFLAGS) $^  -o $@
	rm -f *.o
	rm -f vgcore.*

.PHONY: phony_target
phony_target:

%.o : %.c $(HDRS) phony_target
	$(CC)  $(CFLAGS) -c $<  -o $@

clean:
	rm -f *.o
	rm -f interpreter

