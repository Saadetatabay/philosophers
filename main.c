#include "philo.h"

int check_num(char **args)
{
    int i;
    int j;

    i = 1;
    while (args[i])
    {
        j = 0;
        while (args[i][j])
        {
            if (!(args[i][j] >= '0' && args[i][j] <= '9'))
                return (0);
            j++;
        }
        i++;
    }
    return 1;
}

int main(int argc, char *argv[])
{
    t_data data;
    if ((argc == 5 || argc == 6) && check_num(argv))
    {
        init_tdata(&data, argv);
    }
    else
    {
        printf("yanlis arg");
    }
}