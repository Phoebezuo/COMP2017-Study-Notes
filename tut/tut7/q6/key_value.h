typedef struct KeyValue {
    unsigned int key;
    const char* value;
} KeyValue;

void set_key_values(KeyValue * const new_key_values,
                    const unsigned int new_number_of_key_values);

KeyValue* find_item_by_value(const char * const value);

void sort_items_by_key(void);
