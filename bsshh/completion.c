#include "minishell.h"

//char *cmnd_generator(const char *text, int state)
//{
//  static int list_index;
//  static size_t len;
//  char *name;
//  char *custom_cmnds[] = {
//    "echo",
//    "emacs",
//    "cd",
//    "exit",
//    "setenv",
//    "unsetenv",
//    "env",
//    NULL
//  };
//
//  if (!state)
//    {
//      list_index = 0;
//      len = ft_strlen(text);
//    }
//  while ((name = custom_cmnds[list_index++]))
//    {
//      if (ft_strncmp(name, text, len) == 0)
//	return (ft_strdup(name));
//
//    }
//  return NULL;
//}
//
//char **cmnd_completion(const char *text, int start, int end)
//{
//  rl_attempted_completion_over = 1;
//  start = 0;
//  end = 0;
//  return (rl_completion_matches(text, cmnd_generator));
//}
