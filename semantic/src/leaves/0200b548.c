/* arm9:0200b548
 * *out = stream->end(0xc) - stream->pos(4), where stream is the pointer held at
 * obj+4. Returns 0. The first parameter is not used by this body.
 */
int stream_remaining(void *unused, void *obj, unsigned int *out)
{
    unsigned char *stream = *(unsigned char **)((unsigned char *)obj + 4);

    (void)unused;
    *out = *(unsigned int *)(stream + 0xc) - *(unsigned int *)(stream + 4);
    return 0;
}
