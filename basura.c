/*char *get_content(int fd)
{
    int i;
    int j;
    char *line;
    char *text;
    int len;

    i = 0;
    text = malloc(100 * sizeof(char));
    while (1)
    {
        line = get_next_line(fd);
        if (line == NULL)
            break;
        len = ft_strlen(line);
        if (len + i > 100)
            resize_char();
        j = 0;
        while(line[j] != '\0')
            text[i++] = line[j++];
        free(line);
    }
    return (text);
}*/