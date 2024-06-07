#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

long hash_string(const char *str)
{
    long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    if (hash < 0)
        hash *= -1;
    return hash;
}

HASH_RESULT hash_add_int(HashTable *table, const char *key, int value)
{
    long hash = hash_string(key);

    int index = hash % table->size;

    HashEntry *hashPtr = table->bucket[index];
    // HashEntry *prev = NULL;
    while (hashPtr)
    {
        if (strcmp(hashPtr->key.str_value, key) == 0)
        {
            if (hashPtr->value.int_value == value)
                return HASH_ALREADY_ADDED;
            else
            {
                hashPtr->value.int_value = value;
                return HASH_REPLACED_VALUE;
            }
        }
        // prev = hashPtr;
        hashPtr = hashPtr->next;
    }

    HashEntry *newEntry = (HashEntry *)malloc(sizeof(HashEntry));
    if (newEntry == NULL)
    {
        table->last_error = HASH_ERROR;
        return HASH_ERROR;
    }
    newEntry->key.str_value = strdup(key);
    newEntry->value.int_value = value;
    // newEntry->next = NULL;
    newEntry->next = table->bucket[index];
    table->bucket[index] = newEntry;
    // if (prev == NULL)
    //     table->bucket[index] = newEntry;
    // else
    //     prev->next = newEntry;
    return HASH_ADDED;
}

HashTable *create_hash(int size)
{
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    if (table == NULL)
        return NULL;
    memset(table, 0, sizeof(HashTable));

    table->bucket = (HashEntry **)malloc(sizeof(HashEntry *) * size);
    if (table->bucket == NULL)
    {
        free(table);
        return NULL;
    }
    table->size = size;

    memset(table->bucket, 0, sizeof(HashEntry *) * size);
    return table;
}

int hash_get_int(HashTable *table, const char *key)
{
    // 计算键的哈希值
    long hash = hash_string(key);

    // 确定桶的索引
    int index = hash % table->size;

    // 在哈希表中查找该键对应的条目
    HashEntry *entry = table->bucket[index];
    while (entry != NULL)
    {
        if (strcmp(entry->key.str_value, key) == 0)
        {
            // 如果找到相同的键，则返回其值
            return entry->value.int_value;
        }
        entry = entry->next;
    }

    // 如果没有找到相同的键，则返回一个默认值，或者抛出错误
    return 0; // 默认返回 0
}
int main()
{
    // 创建一个哈希表
    HashTable *table = create_hash(4); // 假设创建哈希表的函数是 create_hash_table，参数是哈希表的大小

    // 向哈希表中添加一些元素进行测试
    hash_add_int(table, "zcaln", 849);
    hash_add_int(table, "aozge", 410);
    hash_add_int(table, "shzpn", 416);
    hash_add_int(table, "ylhhw", 247);

    // 测试查找元素
    printf("Value of apple: %d\n", hash_get_int(table, "zcaln")); // 假设 hash_get_int 函数用于查找元素的值
    printf("Value of banana: %d\n", hash_get_int(table, "ylhhw"));
    printf("Value of orange: %d\n", hash_get_int(table, "shzpn"));
    printf("Value of orange: %d\n", hash_get_int(table, "aozge"));

    // 测试添加重复键
    HASH_RESULT result = hash_add_int(table, "apple", 15);
    if (result == HASH_ALREADY_ADDED)
    {
        printf("Failed to add apple, it's already in the table.\n");
    }

    // 销毁哈希表
    // destroy_hash_table(table); // 假设 destroy_hash_table 函数用于销毁哈希表

    return 0;
}