/*
 * Check: a unit test framework for C
 * Copyright (C) 2001, 2002 Arien Malec
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#ifndef CALC_H
#define CALC_H

typedef struct  Variable Variable;

Variable *var_create(char *arg1, char *arg2);
char *result_add(Variable *v);
char *result_subtract(Variable *v);
char *operation(Variable *v, int opcode);
int *Enum(char *arg);
char *Extend(char *var);
char *Group(char *var);
char *Combine(char *var);
char *CrossOutSymbolsSub(int *arg1, int *arg2);
int ConvertLetterToInt(char arg);
int CheckValidArg(char *arg);
int ConvertRomanToInt(char *arg);
char *calc_arg(Variable *v, int x);
void var_free(Variable *v);

#endif /* MONEY_H */

