/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastano <rcastano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:54:31 by rcastano          #+#    #+#             */
/*   Updated: 2023/02/14 13:42:07 by rcastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*clean_up(char *clean)
{
	free(clean);
	clean = 0;
	return (clean);
}

static char	*get_line(char *buf)
{
	int	i;

	i = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] == '\n')
			return (&buf[i + 1]);
		i++;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*str;
	char		*check;
	static char	*aux;
	int			i;
	char		buf[BUFFER_SIZE + 1];

	str = 0;
	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	//en la segunda entrada auxiliar tiene contenido por lo que está entrando en el if
	if (aux != 0)
	{
		str = ft_strjoin(str, aux);
		check = get_line(aux);
			//printf("testcheck: %s\n", check);
			//printf("testaux: %s\n", aux);
		if (check != NULL)
		{
			aux = 0;
			aux = ft_strjoin(aux, check);
			if (aux != 0 && aux[0] == '\0')
				clean_up(aux);
			return (str);
		}
/* 		if (aux != 0)
			clean_up(aux);
		return (str); */
		aux = 0;
		return (str);
		//con esto no me salta el error pero siempre me imprime la ultima llamada que le hago
	}
	while ((i = read(fd, buf, BUFFER_SIZE)) != 0)
	{
		if (i == -1)
			return (NULL);
		if (aux != 0)
			free(aux);
		aux = 0;
		buf[i] = '\0';
		//printf("que contiene buffer:%s\n", buf);
		check = get_line(buf); //que sentido tiene igualarlo a check, por qué no directamente a aux
		//i = 0;
		if (check != NULL && BUFFER_SIZE != 1)
			aux = ft_substr(check, 0, i - (check - buf));
		str = ft_strjoin(str, buf);
		if (check != NULL)
		{
			if (aux != 0 && aux[0] == '\0')
			{
				aux = clean_up(aux);
			}
			return (str);
		}
	}
	if (aux != 0)
		clean_up(aux);
	return (str);
}

/* int	main(void)
{
	int		fd;
	char	*str;

	fd = open("42_with_nl", O_RDONLY);
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
	//system("leaks a.out");
	return (0);
} */

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

//aux = ft_substr(buf, check - buf, i);
*/
