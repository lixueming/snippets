static struct node
{
    int key, info;
    struct node *l, *r;
};

static struct node *t, *head, *z;

int tree_search(int v)
{
    struct node *x = head->r;

    z->key = v;
    while (v != x->key)
        x = (v < x->key) ? x->l : x->r;
    return x->info;
}

void tree_initialize(void)
{
    z = (struct node *) malloc(sizeof *z);
    z->l = z;
    z->r = z;
    z->info = -1;
    head = (struct node *) malloc(sizeof *head);
    head->r = z;
    head->key = 0;
}

void tree_insert(int v, int info)
{
    struct node *p, *x;

    p = head;
    x = head->r;
    while (x != z)
    {
        p = x;
        x = (v < x->key) ? x->l : x->r;
    }
    x = (struct node *) malloc(sizeof *x);
    x->key = v;
    x->info = info;
    x->l = z;
    x->r = z;
    if (v < p->key)
        p->l = x;
    else
        p->r = x;
}

void tree_print(void)
{
    tree_printr(head->r);
}

void tree_printr(struct node *x)
{
    if (x != z)
    {
        tree_printr(x->l);
        print_node(x);
        tree_printr(x->r);
    }
}

void tree_delete(int v)
{
    struct node *c, *p, *x;

    z->key = v;
    p = head;
    x = head-r;
    while (v != x->key)
    {
        p = x;
        x = (v < x->key) ? x->l : x->r;
    }
    t = x;
    if (t->r == z)
        x = x->l;
    else
        if (t->r->l == z)
        {
            x = x->r;
            x->l = t->l;
        }
        else
        {
            c = x->r;
            while (c->l->l != z)
                c = c->l;
            x = c->l;
            c->l = x->r;
            x->l = t->l;
            x->r = t->r;
        }
    free(t);
    if (v < p->key)
        p->l = x;
    else
        p->r = x;
}
