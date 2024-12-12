/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:18:45 by mkakizak          #+#    #+#             */
/*   Updated: 2024/12/12 13:43:29 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**ft_env_split(char const *str)
{
	char	**result;
	char	*equal_sign;

	result = malloc(3 * sizeof(char *));
	if (!result)
		return (NULL);
	result[0] = NULL;
	result[1] = NULL;
	result[2] = NULL;
	equal_sign = ft_strchr(str, '=');
	if (!equal_sign)
	{
		result[0] = ft_strdup(str);
		return (result);
	}
	result[0] = ft_strtrim(str, equal_sign);
	result[1] = ft_strdup(equal_sign + 1);
	return (result);
}

// XDG_DATA_DIRS=/usr/share/ubuntu:/usr/share/gnome:/usr/local/share:/usr/share:/var/lib/snapd/desktop
// LC_NUMERIC=ja_JP.UTF-8
// LC_PAPER=ja_JP.UTF-8
// VTE_VERSION=6800
// GLIBCXX_FORCE_NEW=1
// LD_PRELOAD=/usr/libexec/valgrind/vgpreload_core-amd64-linux.so:/usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so
// ccolin@c4r3s5.42tokyo.jp:~/Desktop$ export TEST=test
// ccolin@c4r3s5.42tokyo.jp:~/Desktop$ echo $TEST
// test
// ccolin@c4r3s5.42tokyo.jp:~/Desktop$ echo $?
// 0
// ccolin@c4r3s5.42tokyo.jp:~/Desktop$ asdasd
// asdasd: command not found
// ==388328== 
// ==388328== HEAP SUMMARY:
// ==388328==     in use at exit: 213,973 bytes in 450 blocks
// ==388328==   total heap usage: 1,080 allocs, 630 frees, 346,666 bytes allocated
// ==388328== 
// ==388328== 34 (24 direct, 10 indirect) bytes in 1 blocks are definitely lost in loss record 22 of 82
// ==388328==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==388328==    by 0x403435: ft_env_split (in /home/ccolin/minishell/minishell)
// ==388328==    by 0x401D88: exe_export (in /home/ccolin/minishell/minishell)
// ==388328==    by 0x401396: built_in_cmds (in /home/ccolin/minishell/minishell)
// ==388328==    by 0x40465D: handle_command_execution (in /home/ccolin/minishell/minishell)
// ==388328==    by 0x4046DE: pipeline (in /home/ccolin/minishell/minishell)
// ==388328==    by 0x40562B: minishell_loop (in /home/ccolin/minishell/minishell)
// ==388328==    by 0x4056B8: main (in /home/ccolin/minishell/minishell)
// ==388328== 
// ==388328== LEAK SUMMARY:
// ==388328==    definitely lost: 24 bytes in 1 blocks
// ==388328==    indirectly lost: 10 bytes in 2 blocks
// ==388328==      possibly lost: 0 bytes in 0 blocks
// ==388328==    still reachable: 213,939 bytes in 447 blocks
// ==388328==         suppressed: 0 bytes in 0 blocks
// ==388328== Reachable blocks (those to which a pointer was found) are not shown.
// ==388328== To see them, rerun with: --leak-check=full --show-leak-kinds=all
// ==388328== 
// ==388328== For lists of detected and suppressed errors, rerun with: -s
// ==388328== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
// ccolin@c4r3s5.42tokyo.jp:~/Desktop$ 
// exit
// ==388084== 
// ==388084== HEAP SUMMARY:
// ==388084==     in use at exit: 213,886 bytes in 448 blocks
// ==388084==   total heap usage: 1,056 allocs, 608 frees, 350,268 bytes allocated
// ==388084== 
// ==388084== 34 (24 direct, 10 indirect) bytes in 1 blocks are definitely lost in loss record 21 of 80
// ==388084==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==388084==    by 0x403435: ft_env_split (in /home/ccolin/minishell/minishell)
// ==388084==    by 0x401D88: exe_export (in /home/ccolin/minishell/minishell)
// ==388084==    by 0x401396: built_in_cmds (in /home/ccolin/minishell/minishell)
// ==388084==    by 0x40465D: handle_command_execution (in /home/ccolin/minishell/minishell)
// ==388084==    by 0x4046DE: pipeline (in /home/ccolin/minishell/minishell)
// ==388084==    by 0x40562B: minishell_loop (in /home/ccolin/minishell/minishell)
// ==388084==    by 0x4056B8: main (in /home/ccolin/minishell/minishell)
// ==388084== 
// ==388084== LEAK SUMMARY:
// ==388084==    definitely lost: 24 bytes in 1 blocks
// ==388084==    indirectly lost: 10 bytes in 2 blocks
// ==388084==      possibly lost: 0 bytes in 0 blocks
// ==388084==    still reachable: 213,852 bytes in 445 blocks
// ==388084==         suppressed: 0 bytes in 0 blocks
// ==388084== Reachable blocks (those to which a pointer was found) are not shown.
// ==388084== To see them, rerun with: --leak-check=full --show-leak-kinds=all
// ==388084== 
// ==388084== For lists of detected and suppressed errors, rerun with: -s
// ==388084== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
