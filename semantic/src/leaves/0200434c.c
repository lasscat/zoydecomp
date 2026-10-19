typedef void (*HookEntry)(int, void *);

void run_entry(void)
{
    ((HookEntry)0x020042a4)(0x02ffffe0, (void *)0x02004368);
}
