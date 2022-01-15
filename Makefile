CC = gcc
#LIBS = -lm -fopenmp
LIBS = -lm -fopenmp -lpapi
INCLUDES = -I.

CFLAGS = -O2 -Wall -std=c99 -fno-omit-frame-pointer -g -I. -I/share/apps/papi/5.4.1/include -I$(INCDIR) -L. -L/share/apps/papi/5.4.1/lib

OBJDIR = obj
INCDIR = includes

OBJS = $(OBJDIR)/QuickSort.o $(OBJDIR)/InsertionSort.o $(OBJDIR)/BucketSort.o $(OBJDIR)/Utils.o $(OBJDIR)/BubbleSort.o
HEAD = $(INCDIR)/QuickSort.h $(INCDIR)/InsertionSort.h $(INCDIR)/BucketSort.h $(INCDIR)/Utils.h $(INCDIR)/BubbleSort.h $(INCDIR)/config.h

SEQUENTIAL_OBJS = $(OBJDIR)/Sequencial.o
PARALLEL_OBJS = $(OBJDIR)/Paralelo.o

default: Sequencial Paralelo

Sequencial: $(SEQUENTIAL_OBJS) $(OBJS)
	$(CC) $(CFLAGS) $(SEQUENTIAL_OBJS) $(OBJS) $(LIBS) -o Sequencial

Paralelo: $(PARALLEL_OBJS) $(OBJS)
	$(CC) $(CFLAGS) $(PARALLEL_OBJS) $(OBJS) $(LIBS) -o Paralelo

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c $< -o $@


clean: 
	rm -f $(OBJDIR)/*.o .a *~ Makefile.bak Sequencial Paralelo