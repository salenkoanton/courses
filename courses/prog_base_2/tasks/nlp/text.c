#include "text.h"
#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct text_s{
    list_t sentense;
};

struct sentense_s{
    list_t word;
};

struct word_s{
    char * word;
};

void text_print(text_t * text)
{
    list_t tmp_list;
        for (int i = 0; i < list_size(text->sentense); i++)
        {
            tmp_list = ((sentense_t *)list_get(text->sentense, i))->word;
            for (int j = 0; j < list_size(tmp_list); j++)
                printf("%s ", ((word_t *)list_get(tmp_list, j))->word);
            if (list_size(tmp_list))
                printf("\n");
        }
}

sentense_t * text_get_sentence(text_t * text, int pos)
{
    return (sentense_t *)list_get(text->sentense, pos);
}

word_t * sentence_del_word(sentense_t * sentense, int pos)
{
    return (word_t *)list_del(sentense->word, pos);
}

sentense_t * text_del_sentence(text_t * text, int pos)
{
    return (sentense_t *)list_get(text->sentense, pos);
}

char * word_get_str(word_t * word)
{
    return word->word;
}

word_t * sentence_get_word(sentense_t * sentense, int pos)
{
    return (word_t *)list_get(sentense->word, pos);
}

int text_sentence_count(text_t * text)
{
    return list_size(text->sentense);
}

int sentence_word_count(sentense_t * sentense)
{
    return list_size(sentense->word);
}

sentense_t * sentence_new()
{
    sentense_t * sen = malloc(sizeof(struct sentense_s));
    sen->word = list_new();
    return sen;
}

void process_sentence(char * sentense, sentense_t * list)
{
    int pos = 0;
    int dpos = 0;
    int word_pos = 0;
    word_t * data;
    char * tmp_word;
    char word[strlen(sentense)];
    while (sentense[pos] != '\0' && pos < strlen(sentense))
    {
        if (pos == word_pos && (sentense[pos] == '"' || sentense[pos] == '-'))
        {
            pos++;
            word_pos++;
            continue;
        }

        word[pos - word_pos] = sentense[pos];
        if (sentense[pos] == ' ')
        {
            dpos = 0;
            while (sentense[pos - dpos - 1] == '"' || sentense[pos - dpos - 1] == '.' || sentense[pos - dpos - 1] == '!' || sentense[pos - dpos - 1] == '?' || sentense[pos - dpos - 1] == ',')
                dpos++;
            if (pos - word_pos + 1 - dpos > 0)
            {

                tmp_word = malloc(sizeof(char) * (pos - word_pos + 1 - dpos));
                data = malloc(sizeof (struct word_s));
                data->word =tmp_word;
                for (int i = 0; i < pos - word_pos - dpos; i++)
                    tmp_word[i] = word[i];
                tmp_word[pos - word_pos - dpos] = '\0';
                list_add(list->word, data, list_size(list->word));
                //free(tmp_word);
                for (int i = 0; i < strlen(sentense); i++)
                    word[i] = ' ';
            }
            word_pos = pos + 1;
        }
        pos++;
    }

}
void process_buffer(char * buffer, list_t list)
{
    puts(buffer);
    sentense_t * sentense_list;
    char sentence[1000];
    char * tmp_sen;
    int pos = 0;
    int sen_pos = 0;
    for (int i = 0; i < 1000; i++)
    {
        sentence[i] = ' ';
    }
    while (pos < strlen(buffer) && buffer[pos] != '\0')
    {
        if (sen_pos == pos && buffer[pos] == ' ')
        {
            pos++;
            sen_pos++;
        }
        sentence[pos - sen_pos] = buffer[pos];
        if (buffer[pos] == '.' || buffer[pos] == '!' || buffer[pos] == '?')
        {
            sentense_list = sentence_new();
            list_add(list, sentense_list, list_size(list));
            tmp_sen = malloc(sizeof(char) * (pos - sen_pos + 3));
            for (int i = 0; i < pos - sen_pos + 1; i++)
                tmp_sen[i] = sentence[i];
            tmp_sen[pos - sen_pos + 1] = ' ';
            tmp_sen[pos - sen_pos + 2] = '\0';
            //puts(tmp_sen);
            process_sentence(tmp_sen, sentense_list);
            free(tmp_sen);
            for (int i = 0; i < 1000; i++)
            {
                sentence[i] = ' ';
            }
            sen_pos = pos + 1;
        }
        pos++;

    }
}

text_t * text_new(char * filename)
{
    text_t * text = malloc(sizeof(struct text_s));
    text->sentense = list_new();
    FILE * file_in = NULL;
    file_in = fopen(filename, "r");
    if (file_in == NULL)
        return NULL;
    char buffer[1000];
    while (fgets(buffer, sizeof buffer, file_in) != NULL)
    {
        process_buffer(buffer, text->sentense);
    }
    fclose(file_in);
    return text;
}

void text_free(text_t * text)
{
    sentense_t * tmp;
    for (int i = 0; i < text_sentence_count(text); i++)
    {
        tmp = text_get_sentence(text, i);
        for (int j = 0; j < sentence_word_count(tmp); j++)
        {
            free(word_get_str(sentence_get_word(tmp, j)));
            free(sentence_del_word(tmp, j));
        }
        list_free(tmp->word);
        free(text_del_sentence(text, i));
    }
    list_free(text->sentense);
    free(text);

}
