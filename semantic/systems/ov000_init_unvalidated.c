/*
 * Research reconstruction of ov000:0x021de5e0.
 * The caller passes an aligned object pointer. Field names remain unknown;
 * accesses below retain observed byte offsets. The first object word is read
 * as a pointer to a game context, not inferred from a desktop layout.
 *
 * UNVALIDATED: the caller consumes r0 but this first draft declares void.
 * Cross-module dependencies and behavior remain unresolved. Not strict-ready.
 */
typedef unsigned int u32;
typedef signed short s16;
typedef unsigned char u8;

typedef struct {
    u8 bytes[0x148];
} GameplayObject;

typedef struct {
    s16 x;
    s16 y;
} CoordinatePair;

typedef int (*ContextPredicate)(u32 context);
typedef void (*ReadCoordinates)(CoordinatePair *out, GameplayObject *object);
typedef void (*RequestResource)(int category, int index);
typedef float (*ConvertCoordinate)(s16 coordinate);
typedef float (*LookupParameter)(float coordinate, float scale);
typedef u32 (*CreateChild)(u32 context, float x, float y, u32 flags,
                           int category, int index);
typedef u32 (*FinalizeChild)(u32 context);

static u32 load_word(const GameplayObject *object, unsigned int offset)
{
    return *(const u32 *)(object->bytes + offset);
}

static void store_word(GameplayObject *object, unsigned int offset, u32 value)
{
    *(u32 *)(object->bytes + offset) = value;
}

static void store_half(GameplayObject *object, unsigned int offset,
                       unsigned short value)
{
    *(unsigned short *)(object->bytes + offset) = value;
}

static void store_byte(GameplayObject *object, unsigned int offset, u8 value)
{
    object->bytes[offset] = value;
}

void ov000_gameplay_object_init(GameplayObject *object)
{
    const u32 *context_slot = (const u32 *)0x021069f4;
    const u32 context = *context_slot;
    const u32 resource = *(const u32 *)(context + 0x5fc);
    const u32 minus_one = 0xffffffffu;
    unsigned int group;
    unsigned int slot;

    store_word(object, 0x00, context);
    store_word(object, 0x04, resource);
    store_byte(object, 0x08, 0);
    store_word(object, 0x0c, 0);
    store_word(object, 0x10, 0);
    store_word(object, 0x58, 0);
    store_word(object, 0x60, 0);
    store_word(object, 0x5c, 0);
    store_word(object, 0xa0, 0);
    store_word(object, 0x54, 0);
    store_byte(object, 0xa4, 0);
    store_word(object, 0xa8, minus_one);
    store_word(object, 0xac, 0);
    store_word(object, 0xb0, 0);
    store_word(object, 0xb4, 0);
    store_word(object, 0xe8, 0);
    store_word(object, 0xec, 0);
    store_word(object, 0xf0, 0);
    store_word(object, 0x50, 0);
    store_word(object, 0xf4, 0);
    store_word(object, 0xf8, 0);
    store_byte(object, 0x80, 0);
    store_word(object, 0x70, 0);
    store_word(object, 0x78, minus_one);
    store_word(object, 0x7c, minus_one);
    store_byte(object, 0x6c, 0);

    /* Nine groups each contain six byte-sized slot states. */
    for (group = 0; group != 9; ++group) {
        for (slot = 0; slot != 6; ++slot)
            object->bytes[group * 6 + slot + 0x14] = 0;
    }
    for (slot = 0; slot != 3; ++slot)
        object->bytes[slot + 0x4a] = 0;

    /* Optional resource-dependent child setup; exact field meanings unknown. */
    if (((ContextPredicate)0x0206e844)(context)) {
        CoordinatePair coordinates;
        ((ReadCoordinates)0x021e0b7c)(&coordinates, object);
        ((RequestResource)0x020501ec)(0x66, 1);
        const float x = ((LookupParameter)0x01ffa084)(
            ((ConvertCoordinate)0x01ff9220)(coordinates.x),
            376.0f);
        const float y = ((LookupParameter)0x01ffa084)(
            ((ConvertCoordinate)0x01ff9220)(coordinates.y),
            20.0f);
        u32 child;

        child = ((CreateChild)0x0206edd4)(context, x, y, 0, 0x66, -1);
        store_byte((GameplayObject *)child, 0x68, 1);
        store_word((GameplayObject *)child, 0x0c, 0);
        store_word(object, 0xb4, ((FinalizeChild)0x0206ee14)(context));
    }

    store_word(object, 0x74, 1000);
    store_byte(object, 0x64, 0);
    store_word(object, 0x68, 0);
    store_word(object, 0x9c, 0);

    for (group = 0; group != 2; ++group) {
        for (slot = 0; slot != 3; ++slot)
            store_word(object, group * 0x0c + slot * 4 + 0x84, minus_one);
    }
    for (slot = 0; slot != 10; ++slot)
        store_word(object, slot * 4 + 0xfc, 0);

    store_half(object, 0x12a, 0);
    store_half(object, 0x128, 0);
    store_half(object, 0x134, 0);
    store_word(object, 0x124, 0);
    store_word(object, 0x138, 0);
    store_word(object, 0x13c, 0);
    store_word(object, 0x140, 0x3f800000u);
    store_word(object, 0x144, 0);
}
