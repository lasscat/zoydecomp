typedef struct {
    unsigned char pad0[0x50c];
    unsigned char flag;
    unsigned char pad1[0x526 - 0x50d];
    unsigned short pending;
    unsigned short state;
    unsigned short mode;
} BattleState;

typedef struct {
    int pad0;
    int pad1;
    int pad2;
    BattleState *state;
} BattleRoot;

int battle_running(void)
{
    BattleRoot *root = (BattleRoot *)0x02100bf0;
    int running = 0;
    int slot_free = 0;
    int mode_ready = 0;

    if (root->state->state == 1 && root->state->flag == 0)
        mode_ready = 1;
    if (mode_ready && root->state->pending == 0)
        slot_free = 1;
    if (slot_free && root->state->mode != 0)
        running = 1;
    return running;
}
