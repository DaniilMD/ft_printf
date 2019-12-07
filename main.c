#include "ft_printf.h"

int		main()
{
   //ft_printf("My printf: aa%%aaa123||||||||||||||%x||||||111111abc123", 42);
	//printf("\nLibc ones: aa%%aaa123||||||||||||||%x||||||111111abc123\n\n", 42);

	/*ft_printf("\n% +d", 42);
	ft_printf("\n%+ d", 42);
	ft_printf("\n%  +d", 42);
	ft_printf("\n% ++d", 42);
	ft_printf("\n%0+5d", 42);
	ft_printf("\nwtfwtf%05d", -42);
	ft_printf("\n%+d", -42);
	ft_printf("\n%d", -4242);


	ft_printf("\n%-05d", 42);
	ft_printf("\n%-05d", -42);
	ft_printf("\n%-05o", 2500);
	ft_printf("\n%-10.5d", 4242);
	//printf("\n%x", -42);
	ft_printf("\n%-05d", 42);
	ft_printf("\n%05d", 42);


	ft_printf("\n%03.2d", 1);*/


	ft_printf("\n%.2s is a string", "this");
	ft_printf("\n%-5.2s is a string", "");
	ft_printf("\n%s %s %s", "this", "is", "a");
	ft_printf("\n%s %s %s %s string. gg!", "this", "is", "a", "multi", "string");
	ft_printf("\n%s %s%s%s%s", "this", "is", "a", "multi", "string");
	ft_printf("\n@moulitest: %#.x %#.0x", 0, 0);
	ft_printf("\n@moulitest: %5.o %5.0o", 0, 0);
	ft_printf("\n@moulitest: %#.o %#.0o", 0, 0);
	ft_printf("\n@moulitest: %c", 0);
	ft_printf("\n%s", NULL);

	return (0);
}

