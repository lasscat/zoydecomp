/* Unvalidated ov000:0x021fd1ac lookup. Independent DS reconstruction.
 * Root/record ownership and field meanings are unknown. Corrected after
 * review: selector is record+0x10, not the first draft's +0x14. This
 * corrected source has not been compiler-compared or behavior-tested.
 */
typedef unsigned int u32;
typedef unsigned char u8;

struct UnknownRecord {
    u32 unknown_000;
    u32 flags_004;
    u32 unknown_008;
    u32 key_00c;
    u32 selector_010;
    u8 unknown_014_through_13b[0x128];
};

struct UnknownTable {
    u8 unknown_prefix[0x4b8];
    struct UnknownRecord records[24];
};

struct UnknownRecord *ov000_find_active_record(struct UnknownTable *table, u32 key, u32 selector)
{
    unsigned int index;
    for (index = 0; index < 24; ++index) {
        struct UnknownRecord *record = &table->records[index];
        if ((record->flags_004 & 1u) != 0 && record->key_00c == key &&
            (selector == 0xffffffffu || record->selector_010 == selector))
            return record;
    }
    return (struct UnknownRecord *)0;
}
