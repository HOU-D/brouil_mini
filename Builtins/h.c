void	export_add(t_list *list, char *key, char *value)
{
	t_env	*new;

	new = env_new(key, value);
	envadd_back(&list->env, new);
}

void	help(t_env *tmp, char *key, char *value, int x)
{
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key) && x)
		{
			tmp->value = ft_strjoin(tmp->value, value);
			tmp->equals = 1;
			break ;
		}
		if (!ft_strcmp(tmp->key, key))
		{
			if (!value)
				break ;
			free(tmp->value);
			tmp->value = value;
			tmp->equals = 1;
			break ;
		}
		tmp = tmp->next;
	}
}



int	export_help(t_list *list, char *value, int i, int is_childe)
{
	t_env	*tmp;
	char	*key;
	int		x;

	tmp = list->env;
	if (check_identifier(list->cmdsp[i], is_childe, 0) && !wach_kayn(list,
			list->cmdsp[i]))
	{
		key = cat_equals(list->cmdsp[i], &x, 0);
		if (key)
			value = ft_substr(list->cmdsp[i], len_equal(list->cmdsp[i]) + 1,
					ft_strlen(list->cmdsp[i]));
		else
			key = ft_strdup(list->cmdsp[i]);
		if (wach_kayn(list, key))
			help(tmp, key, value, x);
		else
		{
			export_add(list, key, value);
			return (0);
		}
		free(key);
	}
	return (1);
}

void	export_(t_list *list, int is_childe)
{
	int	i;

	i = 1;
	while (list->cmdsp[i])
	{
		if (!export_help(list, NULL, i, is_childe))
			break ;
		i++;
	}
}