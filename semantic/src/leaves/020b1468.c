/* arm9:020b1468
 * Programs a transfer command reachable through two pointer hops: sets the
 * halfword mode field at +0x100 to 2 and clears the two word fields at +0x18C
 * and +0x190.
 */
typedef struct {
    unsigned char pad0[0x100];
    unsigned short mode;      /* 0x100 */
    unsigned char pad1[0x8A];
    unsigned int first;       /* 0x18C */
    unsigned int second;      /* 0x190 */
} Command;

typedef struct {
    unsigned char pad[0x688];
    Command *command;         /* 0x688 */
} ChannelState;

typedef struct {
    ChannelState *state;      /* 0x0 */
} Controller;

void command_reset(Controller *ctrl)
{
    ctrl->state->command->mode = 2;
    ctrl->state->command->first = 0;
    ctrl->state->command->second = 0;
}
