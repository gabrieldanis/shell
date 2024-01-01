/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 22:10:54 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/31 09:06:54 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_signal(t_shell *s)
{
	struct sigaction	sig1;
	struct sigaction	sig2;

	sig1 = (struct sigaction){0};
	sig2 = (struct sigaction){0};
	sig2.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sig2, NULL) == -1)
		free_and_exit(1, s);
	sig1.sa_sigaction = &handle_sig1;
	sig1.sa_flags = SA_SIGINFO;
	if (sigaction(SIGINT, &sig1, NULL) == -1)
		free_and_exit(1, s);
}

void	handle_sig1(int sig, siginfo_t *info, void *ucontext)
{
	(void)sig;
	(void)info;
	(void)ucontext;
	printf("\n"); // Move to a new line
    	rl_on_new_line(); // Regenerate the prompt on a newline
    	rl_replace_line("", 0); // Clear the previous text
    	rl_redisplay();
}
void	handle_sig2(int sig, siginfo_t *info, void *ucontext)
{
	(void)sig;
	(void)info;
	(void)ucontext;
}
