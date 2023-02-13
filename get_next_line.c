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
	de check = 2
	*/
#include "get_next_line.h"

void	clean_up(char *clean)
{
	free(clean);
	clean = 0;
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
	//char		tmp[999];

	str = 0;
	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (aux != 0)
	{
		//printf("esto es aux:%s\n", aux);
		str = ft_strjoin(str, aux);
		check = get_line(aux);
		if (check != NULL)
		{
			/*aux = malloc(1);
			aux[0] = '\0'; */
			aux = ft_strjoin(aux, check);
			if (aux != 0 && aux[0] == '\0')
				clean_up(aux);
			return (str);
		}
	}
	while ((i = read(fd, buf, BUFFER_SIZE)) != 0)
	{
		if (i == -1)
			return (NULL);
		if (aux != 0)
			free(aux);
		aux = 0; // no le veo sentido
		buf[i] = '\0';
		check = get_line(buf);
		//i = 0;
		if (check != NULL && BUFFER_SIZE != 1)
			aux = ft_substr(check, 0, i - (check - buf));
			//aux = ft_substr(buf, check - buf, i);
		str = ft_strjoin(str, buf);
		if (check != NULL)
		{
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
	//system("leaks a.out");
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
