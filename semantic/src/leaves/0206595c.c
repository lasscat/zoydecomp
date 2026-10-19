/* Reports whether the mode word at +0x5ae4 of the state record is one of the
 * list-like modes 1, 3, 5, 6 or 8. */
struct UnknownState {
    unsigned char unknown_0x00_0x5ae3[0x5ae4];
    unsigned int mode_0x5ae4;
};

int pvz_0206595c_is_list_mode(struct UnknownState *state)
{
    unsigned int mode = state->mode_0x5ae4;

    return mode == 1 || mode == 3 || mode == 5 || mode == 6 || mode == 8;
}
