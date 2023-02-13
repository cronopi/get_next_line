/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastano <rcastano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:54:31 by rcastano          #+#    #+#             */
/*   Updated: 2023/02/13 15:21:56 by rcastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	/*
	necesito copiar todo el contenido de aux en temp pero yo no se cual
	será el tamaño de temp y hacer lo mismo con str en el while antes y despues 
	de number = 2
	*/
#include "get_next_line.h"

void	clean_up(char *clean)
{
	free(clean);
	clean = 0;
}

int	get_line(char *buf)
{
	int	i;

	i = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] == '\n')
		{
			buf[i] = '\0';
			return (2);
		}
		i++;
	}
	return (1);
}

char	*get_next_line(int fd)
{
	char		*str;
	int			number;
	int			check;
	static char	*aux;
	int			i;
	char		buf[BUFFER_SIZE + 1];
	char		tmp[999];

	str = 0;
	number = 0;
	check = 1;
	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (aux != 0)
	{
		str = ft_strjoin(str, aux);
		check = get_line(str);
		check = get_line(aux);
		if (check == 2)
		{
			strcpy(tmp, aux);
			free(aux);
			aux = 0;
			aux = ft_strchr(tmp, '\0');
			free(tmp);
			if (aux != 0 && aux[0] == '\0')
				clean_up(aux);
			str = ft_strjoin(str, "\n");
			return (str);
		}
	}
	while ((i = read(fd, buf, BUFFER_SIZE)) != 0)
	{
		if (i == -1)
			return (NULL);
		if (aux != 0)
			free(aux);
		aux = 0;
		buf[i] = '\0';
		number = get_line(buf);
		i = 0;
		if (number == 2 && BUFFER_SIZE != 1)
		{
			while (buf[i] != '\0')
				i++;
			if (buf[i] == '\0')
				i++;
			aux = ft_strjoin(aux, &buf[i]);
			//printf("imprime el contenido de aux:%s\n", aux);
		}
		str = ft_strjoin(str, buf);
		if (number == 2)
		{
			strcpy(tmp, str);
			//printf("imprime temporal para saber que es:%s\n", tmp);
			//printf("imprimeme str:%s\n", str);
			free(str);
			str = 0;
			str = ft_strjoin(tmp, "\n");
			printf("imprime str1:%s\n", str);
			free(tmp);
			if (aux != 0 && aux[0] == '\0')
				clean_up(aux);
			return (str);
		}
	}
	if (aux != 0)
		clean_up(aux);
	return (str);
}

int	main(void)
{
	int		fd;
	char	*str;

	fd = open("filename.txt", O_RDONLY);
	str = get_next_line(fd);
	printf("esto es el main:%s\n", str);
	free(str);
 	str = get_next_line(fd);
	printf("esto es el main:%s\n", str);
	free(str);
	str = get_next_line(fd);
	printf("esto es el main:%s\n", str);
	free(str);
	str = get_next_line(fd);
	printf("esto es el main:%s\n", str);
	free(str);
 	str = get_next_line(fd);
	printf("esto es el main:%s\n", str);
	free(str);
	str = get_next_line(fd);
	printf("esto es el main:%s\n", str);
	free(str);
	close(fd);
	system("leaks a.out");
	return (0);
}

/*
open("multiple_nlx5", O_RDONLY);

read(int fd, void *buf, size_t nbyte);
el nbyte hace referencia al número de bytes(chars o posiciones)
que va a avanzar/leer(copiar al buffer). el buffer es un bloque 
de memoria, buffer debe tener un tamaño de memoria asignado con anterioridad.

Open lo hace es hacer accesible para el programa el archivo.
con fd estamos crando una forma de identificar/describir el archivo

Al hacer open he creado un puntero a la primera posicion
(de la letra del archivo)/del archivo.

*/
