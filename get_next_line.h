#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdliv.>

# ifndef BUFFER_SIZE
#   define BUFFER_SIZE = 42

typedef struct  s_list
{
    char            *content;
    struct s_list   *next;
}               t_list;
