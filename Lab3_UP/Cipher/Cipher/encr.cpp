#include "stdafx.h"
#include "encr.h"
#include <string>

void encrypt(char* after, char* before, char* key, char* language, char* alphabet, char* notletter)
{
	const int word_size = std::strlen(before);
	auto i = 0, j = 0;
	auto index_before = 0, index_key = 0;
	j = std::strlen(key);
	while (word_size > j)
	{
		key[j] = key[i];
		i++;
		j++;
	}
	key[j] = '\0';
	i = 0;
	for (i = 0, j = 0; i < word_size; i++, j++)
	{
		if (std::strchr(alphabet, before[i]) == nullptr)
		{
			if (std::strcmp(notletter, "Delete") == 0)
			{
				j--;
			}
			else if (std::strcmp(notletter, "Nothing") == 0)
			{
				after[i] = before[i];
			}
			else
			{
				after[i] = before[i] + 1;
			}
			continue;
		}
		index_before = std::strchr(alphabet, before[i]) - alphabet;
		index_key = std::strchr(alphabet, key[i]) - alphabet;
		if (alphabet[index_before + index_key] == '\0')
		{
			index_before++;
		}
		if (index_before + index_key > std::strlen(alphabet))
		{
			after[j] = alphabet[index_before + index_key - strlen(alphabet)];
		}
		else
		{
			after[j] = alphabet[index_before + index_key];
		}
	}
	after[j] = '\0';
}