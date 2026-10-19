/*
 * Unvalidated research draft for arm9/ov000:0x021e0b7c. Layout names are
 * unknown; padding expresses only DS offsets. The external ARM9 helper at
 * 0x02039734 owns the actual coordinate-output behavior. No behavior test
 * or matching compilation has been performed for this source.
 */
typedef unsigned int uint32_t;
typedef signed int int32_t;
typedef unsigned short uint16_t;
typedef signed short int16_t;
typedef unsigned char uint8_t;

typedef struct CoordinateSource {
    uint8_t unknown_000_007[8];
    int32_t x_at_008;
    int32_t y_at_00c;
} CoordinateSource;

typedef struct ObjectState {
    uint8_t unknown_000_167[0x168];
    CoordinateSource *coordinate_source;
} ObjectState;

typedef struct GameplayObject {
    uint32_t unknown_000;
    ObjectState *state;
} GameplayObject;

extern void coordinate_output_helper(void *output, int16_t x, int16_t y,
                                     int mode, int extent);

void ov000_read_coordinates(void *output, const GameplayObject *object)
{
    const ObjectState *state;
    const CoordinateSource *source;
    int16_t x;
    int16_t y;

    state = object->state;
    source = state->coordinate_source;
    x = (int16_t)(uint16_t)((uint32_t)source->x_at_008 + 0x1d8u);
    y = (int16_t)(uint16_t)source->y_at_00c;
    coordinate_output_helper(output, x, y, 0x5d, 0x50);
}
