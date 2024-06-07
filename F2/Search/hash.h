typedef enum
{
    HASH_OK,
    HASH_ERROR,
    HASH_ADDED,
    HASH_REPLACED_VALUE,
    HASH_ALREADY_ADDED,
    HASH_DELETED,
    HASH_NOT_FOUND,
} HASH_RESULT;

typedef struct __HashEntry HashEntry;
struct __HashEntry
{
    union
    {
        char *str_value;
        double dbl_value;
        int int_value;
    } key;
    union
    {
        char *str_value;
        double dbl_value;
        int int_value;
        long long_value;
        void *ptr_value;
    } value;
    HashEntry *next;
};

struct __HashTable
{
    HashEntry **bucket;
    int size;
    HASH_RESULT last_error;
};
typedef struct __HashTable HashTable;

// 向哈希表中添加元素，其中键类型为char*， 元素类型为int。
HASH_RESULT hash_add_int(HashTable *table, const char *key, int value);
