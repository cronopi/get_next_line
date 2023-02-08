#include "get_next_line.h"
/* 
con buffersize 3
	hace un primer malloc para guardar str = "app", cuando vuelvo a llamar al
	malloc para introducir app + lee\n a str se pierde la direccion de memoria de str que apunta a app y por lo tanto tenemos un leak de memoria

	solución(?): en el momento en el que str haya sido devuelto hacer un free a la funcion.
 */
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
	char	*str;
	int		number;
	int		check;
	static char	*tmp;
	int i;
	
	str = 0;
	number = 0;
	check = 1;
	i = 0;
	char buf[BUFFER_SIZE + 1];
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (tmp != 0)
	{
		str = ft_strjoin(str, tmp);
		check = get_line(str);
		check = get_line(tmp);
		if (check == 2)
			tmp = ft_strchr(tmp, '\0');
		if (check == 2)
			return (str);
	}
	while ((i = read(fd, buf, BUFFER_SIZE)) != 0)
	{
		//if (tmp)
			free(tmp);
		tmp = 0;
		buf[i] = '\0';
		number = get_line(buf);
		i = 0;
		if (number == 2)
		{
			while(buf[i] != '\0')
				i++;
			if (buf[i] == '\0')
				i++;
			tmp = ft_strjoin(tmp, &buf[i]);
		}
		str = ft_strjoin(str, buf);
		if (number == 2)
				return (str);
	}
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
	close(fd);
	system("leaks a.out");
	return (0);
}

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
