#include "../../inc/minishell.h"
#include "../../inc/exec.h"

void	close_pipes(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

t_node	*ft_get_path(t_data *data, char **cmd)
{
        t_node  *lst;
        lst = get_env_lst("PATH", data->env->start);
        if (!lst)
        {
                ft_printf("bash: %s: No such file or directory\n", cmd[1], 2);
                return (127);
        }
        return (lst);
}
