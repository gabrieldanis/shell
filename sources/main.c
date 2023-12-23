/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:48:10 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/23 16:11:19 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	g_signal = 0;

void	handle_sig1(int sig, siginfo_t *info, void *ucontext)
{
	(void)sig;
	(void)info;
	(void)ucontext;
	write(1, "a", 1);
	printf("\n"); // Move to a new line
    	rl_on_new_line(); // Regenerate the prompt on a newline
    	rl_replace_line("", 0); // Clear the previous text
    	rl_redisplay();
	g_signal = 1;
}

void	handle_sig2(int sig, siginfo_t *info, void *ucontext)
{
	(void)sig;
	(void)info;
	(void)ucontext;
	struct termios	old_tsettings;
	struct termios	new_tsettings;

    if (tcgetattr(STDIN_FILENO, &old_tsettings) == -1) {
        perror("tcgetattr");
        return ;
    }

	new_tsettings = old_tsettings;
    // Disable the ISIG flag for SIGQUIT
	new_tsettings.c_lflag &= ~(ECHOCTL);

    // Set the modified terminal attributes
    if (tcsetattr(STDIN_FILENO, TCSANOW, &new_tsettings) == -1) {
        perror("tcsetattr");
        return ;
    }
    // Your program logic goes here

    	rl_on_new_line(); // Regenerate the prompt on a newline
    	rl_redisplay();

    if (tcsetattr(STDIN_FILENO, TCSANOW, &old_tsettings) == -1) {
        perror("tcsetattr (restore)");
        return ;
    }
	//printf("\033[K");
}

int	main(int argc, char **argv, char **envp)
{
	t_parsed	*plist;
	t_token		*list;
	char		**s_envp;
	char		*str;
	struct sigaction	sig1;
	struct sigaction	sig2;

	s_envp = dup_envp(envp);
	(void) argc;
	(void) argv;
	sig2 = (struct sigaction){0};
	//sig2.sa_sigaction = &handle_sig2;
	sig2.sa_handler = SIG_IGN;
	sigemptyset(&sig2.sa_mask);
    	sig2.sa_flags = 0;
    	sigaction(SIGQUIT, &sig2, NULL);


	sig1 = (struct sigaction){0};
	sig1.sa_sigaction = &handle_sig1;
	sig1.sa_flags = SA_SIGINFO;
	if (sigaction(SIGINT, &sig1, NULL) == -1)
		exit (1);

	str = NULL;
	while (1)
	{
		str = readline("💻 minishell > ");
		if (str && str[0] != '\0')
		{
			add_history(str);
			list = tokenizer(str);
			plist = parser(list);
			plist = expander(plist);
			/*
			print_parsed_list(plist);
			plist = type_parsed_list(plist);
			plist = info_parsed_list(plist);
			*/
			execute_parsed_list(plist, &s_envp, list);
			free_token_list(list);
			free_parsed_list(plist);
		}
		if (!str)
			free_and_exit(0, NULL, NULL, NULL);
		free(str);
	}
    // Restore the original terminal attributes (optional)
}
