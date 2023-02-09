#ifndef GET_NEXT_LINE_H
 #define GET_NEXT_LINE_H


 # ifndef BUFFER_SIZE

#  define BUFFER_SIZE 42

# endif


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *str, int c);
char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
