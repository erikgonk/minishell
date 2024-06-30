
int main(int argc, char **argv, char **envp)
{
    t_data  data;
    char    **tmp;

    if (argc != 1 || argv[1])
    {
        printf("This program does not take arguments\n");
        exit(0);
    }
    tmp = dup_env(envp);
    add_shellvl(tmp); //increase shelllvl every time user starts program again
    data.envp = dup_env(envp);
    data.exp_env = dup_env(envp); //for expanded variables 
    data.in = dup(STDIN_FILENO);
    data.out = dup(STDOUT_FILENO);
    current_pwd(&data); // to get the current pwd at beginning of program
    data.g_exit = 0; // to keep track of which error/exit integer we should return
    init_data(&data);
    mini_loop(&data);
    return (0);
}