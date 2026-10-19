/* arm9:0203be84
 * Decodes one node of a tagged list.  A clear tag bit means an inline form:
 * the seven bit payload packed beside the tag is returned and the caller's
 * cursor is advanced past the single header byte.  A set tag bit means the
 * header word is followed by a value and a link word, which are returned and
 * stored for the caller.
 */
typedef struct {
    unsigned int tag : 1;
    unsigned int payload : 7;
} Packed;

unsigned int node_read(Packed *node, unsigned int **cursor, unsigned int *out)
{
    unsigned int value;

    if (node->tag == 0) {
        unsigned char *bytes = (unsigned char *)node;

        value = ((unsigned int)bytes[0] << 24) >> 25;
        *cursor = (unsigned int *)(bytes + 1);
    } else {
        *cursor = (unsigned int *)((unsigned int *)node)[2];
        value = ((unsigned int *)node)[1];
    }
    *out = value;
    return value;
}
