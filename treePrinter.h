int _print_t(node *tree, int is_left, int offset, int depth, char s[20][255])
{
        char b[20];
        int width = 9;

        if (!tree) return 0;

        sprintf(b, "(%01d|%03d|%01d)", tree->l_height, tree->data, tree->r_height);

        int left  = _print_t(tree->left,  1, offset,                depth + 1, s);
        int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);

#ifdef COMPACT
        for (int i = 0; i < width; i++)
                s[depth][offset + left + i] = b[i];

        if (depth && is_left) {

                for (int i = 0; i < width + right; i++)
                        s[depth - 1][offset + left + width/2 + i] = '-';

                s[depth - 1][offset + left + width/2] = '.';

        } else if (depth && !is_left) {

                for (int i = 0; i < left + width; i++)
                        s[depth - 1][offset - width/2 + i] = '-';

                s[depth - 1][offset + left + width/2] = '.';
        }
#else
        for (int i = 0; i < width; i++)
                s[2 * depth][offset + left + i] = b[i];

        if (depth && is_left) {

                for (int i = 0; i < width + right; i++)
                        s[2 * depth - 1][offset + left + width/2 + i] = '-';

                s[2 * depth - 1][offset + left + width/2] = '+';
                s[2 * depth - 1][offset + left + width + right + width/2] = '+';

        } else if (depth && !is_left) {

                for (int i = 0; i < left + width; i++)
                        s[2 * depth - 1][offset - width/2 + i] = '-';

                s[2 * depth - 1][offset + left + width/2] = '+';
                s[2 * depth - 1][offset - width/2 - 1] = '+';
        }
#endif

        return left + width + right;
}

void print_t(node *tree)
{
        char s[20][255];
        for (int i = 0; i < 20; i++)
                sprintf(s[i], "%80s", " ");

        _print_t(tree, 0, 0, 0, s);

        for (int i = 0; i < 20; i++)
                printf("%s\n", s[i]);
}
