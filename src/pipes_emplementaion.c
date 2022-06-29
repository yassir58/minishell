#include "../includes/minishell.h"




   //     while (tmp)
    //     {
    //         if (tmp->builtin == true)
    //             builtin_routine (args, tmp);
    //         else
    //         {
    //             id = fork ();
    //             if (!id)
    //             {
    //                 if (tmp->next)
    //                 {
    //                     close (fds[indx][READ_END]);
    //                     dup2 (fds[indx][WRITE_END], STDOUT_FILENO);
    //                     close (fds[indx][WRITE_END]);
    //                 }
    //                 if (tmp->prev)   
    //                 {
    //                     close (fds[indx - 1][WRITE_END]);
    //                     dup2 (fds[indx - 1][READ_END], STDIN_FILENO) ;
    //                     close (fds[indx - 1][READ_END]);
    //                 }
    //                 exec_command (args, tmp);
    //                 printf ("indx:%d\n", indx);
    //             }
    //         }
    //         indx++;
    //         tmp = tmp->next;
    //     }
    // }