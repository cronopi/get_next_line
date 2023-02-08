/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastano <rcastano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 12:02:22 by rcastano          #+#    #+#             */
/*   Updated: 2023/02/08 11:58:55 by rcastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_line(char *buf)
{
	int i;

	i = 0;
	while(buf[i] != '\0')
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
	int		buff_size;
	char	*str;
	int		number;
	int		check;
	static char	*tmp;
	int i;

	str = 0;
	buff_size = 9999;
	number = 0;
	check = 1;
	i = 0;
	if (fd < 0 || buffer_size <= 0)
		return (NULL);
	char buf[buff_size + 1];
	//printf("esto es tmp en el inicio:%s\n", tmp);
	if (tmp != 0)
	{
		//printf("esto es tmp al entrar al if:%s\n", tmp);
		//printf("esto es str al entrar al if:%s\n", str);
		str = ft_strjoin(str, tmp); //pearmelon\nwatermelon\0
		check = get_line(str);		//pearmelon\0watermelon\0
		check = get_line(tmp);		//pearmelon\0watermelon\0
		if (check == 2)
			tmp = ft_strchr(tmp, '\0'); // watermelon\0
		//printf("esto es tmp despues:%s\n", tmp);
		if (check == 2)
			return (str);
	}
	while (read(fd, buf, buff_size) != 0)
	{
		tmp = 0;
		//printf("entras?:%s\n", tmp);
		buf[buff_size] = '\0';		// apple__\0					// \npear\0					// \nwate\0
		//printf("imprimiendo buf:%s\n", buf);
		number = get_line(buf);		// apple\0  number = 1		// \0pear\0 number = 2		// \0wate\0	number = 2
		//printf("cual es number%i\n", number);
		if (number == 2)
		{
			//printf("estas aqui?\n");
			while(buf[i] != '\0')
				i++;
			if (buf[i] == '\0')
				i++;
			tmp = ft_strjoin(tmp, &buf[i]);
		}
		//printf("esto es tmp en el bucle:%s\n", tmp);
		str = ft_strjoin(str, buf);// apple\0					// apple\0					// \0
		//printf("esto es tmp en el bucle al terminar :%s\n", tmp);
		if (number == 2)
				return (str);									//apple\0 primera línea		// \0
		
	}
	return (str);
}

/* int	main(void)
{
	int		fd;
	char	*str;

	fd = open("filename.txt", O_RDONLY);
	str = get_next_line(fd);
	printf("esto es el main:%s\n", str);
	str = get_next_line(fd);
	printf("esto es el main:%s\n", str);
	str = get_next_line(fd);
	printf("esto es el main:%s\n", str);
	close(fd);
	free(str);
	return (0);
} */

/*

open("filename.txt", O_RDONLY);

read(int fd, void *buf, size_t nbyte);
el nbyte hace referencia al número de bytes(chars o posiciones) que va a avanzar/leer(copiar al buffer).
el buffer es un bloque de memoria, buffer debe tener un tamaño de memoria asignado con anterioridad.

Open lo hace es hacer accesible para el programa el archivo.
con fd estamos crando una forma de identificar/describir el archivo

Al hacer open he creado un puntero a la primera posicion (de la letra del archivo)/del archivo.


con "" es un string, con '' es un char
______________________________________________________





	tmp = "\npear"

	si yo encuntro un \n


*/
