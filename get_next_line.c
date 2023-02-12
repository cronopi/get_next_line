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
	char	*str;
	int		number;
	int		check;
	static char	*aux;
	int i;

	str = 0;
	number = 0;
	check = 1;
	i = 0;
	char buf[BUFFER_SIZE + 1];//preguntar si buffer tiene que ser dinámico o estático
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	/*
	necesito copiar todo el contenido de aux en temp pero yo no se cual
	será el tamaño de temp
	*/
	if (aux != 0)
	{
		str = ft_strjoin(str, aux);
		check = get_line(str);
		check = get_line(aux);
		if (check == 2)
		{
			//char *temp;
			char *temp= &aux;
			free(aux);
			aux = 0;
			aux = ft_strchr(temp, '\0');
			if(aux != 0 && aux[0] == '\0')
			{
				free(aux);
				aux = 0;
			}
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
			while(buf[i] != '\0')
				i++;
			if (buf[i] == '\0')
				i++;
			aux = ft_strjoin(aux, &buf[i]);
		}
		str = ft_strjoin(str, buf);
		if(number == 2)
		{
			str = ft_strjoin(str, "\n");
			if(aux != 0 && aux[0] == '\0')
			{
				free(aux);
				aux = 0;
			}
			return (str);
		}
	}
	if(aux != 0)
	{
		free(aux);
		aux = 0;
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
el nbyte hace referencia al número de bytes(chars o posiciones) que va a avanzar/leer(copiar al buffer).
el buffer es un bloque de memoria, buffer debe tener un tamaño de memoria asignado con anterioridad.

Open lo hace es hacer accesible para el programa el archivo.
con fd estamos crando una forma de identificar/describir el archivo

Al hacer open he creado un puntero a la primera posicion (de la letra del archivo)/del archivo.


con "" es un string, con '' es un char
______________________________________________________





	aux = "\npear"

	si yo encuntro un \n

	lo de abajo es similar a lo de arriba, eso peude ayuar da solucionarlo.
*/
