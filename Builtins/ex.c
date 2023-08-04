#include "builtins.h"
#include "../include/minishell.h"

int	env_len(t_env *env)
{
	int	len;

    len = 0;
    while (env)
	{
		len++;
		env = (env)->next;
	}
    return (len);
}

char	*come_max(t_env *env)
{
	char	*max;
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->index == 0)
			max = tmp->key;
		tmp = tmp->next;
	}
	while (env)
	{
		if (ft_strcmp(max, env->key) < 0)
		{
			if (env->index == 0)
				max = env->key;
		}
		env = env->next;
	}
	return (max);
}

void	sort_export(t_env *env, int j, int size)
{
	char	*max;
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		tmp->index = 0;
		tmp = tmp->next;
	}
	size = env_len(env);
	while (j <= size)
	{
		tmp = env;
		max = come_max(env);
		while (1)
		{
			if (ft_strcmp(max, tmp->key) == 0)
			{
				tmp->index = j;
				j++;
				break ;
			}
			tmp = tmp->next;
		}
	}
}

void	print(t_env *env, t_env *tmp, int size)
{
	size = env_len(env);
	while (size > 0)
	{
		tmp = env;
		while (tmp)
		{
			if (tmp->index == size)
			{
				if (tmp->val && ft_strcmp(tmp->key, "_"))
					printf("declare -x %s=\"%s\"\n", tmp->key, tmp->val);
				else if (ft_strcmp(tmp->key, "_"))
					printf("declare -x %s%c\n", tmp->key, '\0');
				size--;
				break ;
			}
			tmp = tmp->next;
		}
	}
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (0);
	return (1);
} 

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (0);
	return (1);
}

int	check_identifier(char *av)
{
	int i;
	
	i = 1;
	if (ft_isalpha(av[i]) == 0 && av[i] != '_')
	{
		ft_error("minishell: export: '", av, "': not a valid identifier", 1);
		t_info.exit_status = 1;
		return 1;
	}
	i++;
	while (av[i])
	{
		if (ft_isalpha(av[i]) || ft_isdigit(av[i]))
			i++;
		else if (av[i] == '=' || (av[i] == '+' && av[i + 1] == '='))
			return (1);
		else
		{
			ft_error("minishell: export: '", av, "': not a valid identifier", 1);
			t_info.exit_status = 1;
			break ;
			return 0;
		}
	}
	return (1);
}

char	*give_key(char *av)
{
	int		len;
	char	*key;
	int flag;
	int i;

	flag = 0;
	len = 0;
	while (av[len] && av[len] != '=' && av[len] != '+')
		len++;
	key = malloc(len + 2);
	i = 0;
	while (av[i])
	{
		p[i] = av[i];
		i++;
		if (av[i] == '=' || av[i] == '+')
		{
			key[i] = '\0';
			if (av[i] == '+')
				flag = 1;
			return (key);
		}
	}
	if (key)
		free(key);
	return (NULL);
}

int	len_equal(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '=')
		i++;
	return (i);
}

 void	exp(char **av, t_env	*env)
 {
	 int i;
	 char *key;
	 char *val;
	 t_env	*temp;
	 int flag = 0;

	 i = 1;
	 temp = env;
	 while (av[i])
	 {
		 if (searching_key(env, key) == NULL  && check_identifier(av) == 0)
		 {
			key =  give_key(av);
			if (key != NULL)
			{
				val = ft_substr(av[i], len_equal(av[i]) + 1, ft_strlen(av[i]));
			}
			else
				key = ft_strdup(av[i]);
			if (searching_key(env, key))
			{
				i = 0;
				while (key[i])
					{
							if (key[i] == '+')
								flag = 1;
							i++;
					}
				while (temp)
				{
					if (ft_strcmp(temp->key, key) == 0 && flag)
					{
						temp->val = ft_strjoin(temp->val, val);
						break ;
					}
					if (!ft_strcmp(temp->key, key))
					{
						if (!val)
							break ;
						free(temp->val);
						temp->val = val;
						break ;
					}
					temp = temp->next;
				}
			}
		    }
			else
			{
				add_node(env, new_node(key, val));
				return (0);
			}
		    free(key);
			return (1)		
		}
 }
 
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*st;

	j = 0;
	if (!s)
		return (0);
	if (start >= ft_strlen((char *)s))
		return (ft_strdup(""));
	if (len > ft_strlen((char *)s) - start)
		len = ft_strlen((char *)s) - start;
	st = (char *)malloc(len + 1);
	if (!st)
		return (NULL);
	i = start;
	while (start < len + i && s[start] != '\0')
	{
		st[j] = s[start];
		j++;
		start++;
	}
	st[j] = '\0';
	return (st);
}
 
void    ft_export(char **av, t_env *env)
{
	int	size;

	size = 0;
	if (av[1] == NULL)
	{
		sort_export(env, 1, 0);
		print(env, NULL, 0);
	}
 	else
		exp(av, env);
}


void	exp(char **av, t_env	*env)
{
   int i;
	 char *key;
	 char *val;
	 t_env	*temp;
	 int flag = 0;

	 i = 1;
	 temp = env;
	while (av[i])
	{
    if (check_identifier(av) && searching_key(env, key) == NULL)
	  {
		  key =  give_key(av);
		if (key != NULL)
				val = ft_substr(av[i], len_equal(av[i]) + 1, ft_strlen(av[i]));
		else
				key = ft_strdup(av[i]);
		if (searching_key(env, key))
    {
        i = 0;
				while (av[i])
					{
							if (av[i] == '+')
								flag = 1;
							i++;
					}
       while (env)
         {
           if (ft_strcmp(env->key, key) == 0 && flag)
           {
             env->val = ft_strjoin(env->val, val);
						break ;
           }
           if (!ft_strcmp(temp->key, key))
					 {
						if (!val)
							break ;
						free(temp->val);
						temp->val = val;
						break ;
					}
					temp = temp->next;
			 	}
       }
        else 
      {
				add_node(env, new_node(key, val));
				return (0);
			}
		  free(key);
  
    return (1);
}
