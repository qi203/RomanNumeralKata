## Process this file with automake to produce Makefile.in

TESTS = check_calc
check_PROGRAMS = check_calc
check_calc_SOURCES = check_calc.c $(top_builddir)/src/calc.h
check_calc_CFLAGS = @CHECK_CFLAGS@
check_calc_LDADD = $(top_builddir)/src/libcalc.la @CHECK_LIBS@
