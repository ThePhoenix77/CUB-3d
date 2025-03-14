# include "../../inc/linux_inc/cub3d.h"

void    ft_free_all(t_free *head)
{
    t_free    *current;
    t_free    *next;

    current = head;
    while (current)
    {
        next = current->next;
        free(current->add);
        current->add = NULL;
        free(current);
        current = next;
    }
    head = NULL;
}

t_free    *addnew_free(void *add)
{
    t_free    *new;

    new = malloc(sizeof(t_free));
    if (!new)
        return (NULL);
    new->add = add;
    new->next = NULL;
    return (new);
}

void    addback_free(t_free **head, t_free *new)
{
    t_free    *tmp;

    tmp = *head;
    if (!tmp)
    {
        *head = new;
        return ;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

void    *ft_malloc(int size, int status)
{
    static t_free    *head;
    t_free            *tmp;
    void            *rt;

    if (status == ALLOC)
    {
        rt = malloc(size);
        if (!rt)
            exit(0);
        tmp = addnew_free(rt);
        if (!tmp)
        {
            ft_free_all(head);
            exit(0);
        }
        addback_free(&head, tmp);
        return (rt);
    }
    else
        return (ft_free_all(head), head = NULL);
}