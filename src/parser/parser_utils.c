#include "minishell.h"

// count pipes
void    count_pipes(t_data *data)
{
    int count;
    int i;

    count = 0;
    i = 0;
    while (data->input[i++])
    {
        if (data->input[i] == '|')
            count++;
    }
    data->pipes = count;
}

// count arguments


// check pipe error line