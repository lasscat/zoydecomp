/* arm9:0200e04c - validate a date record and convert it to an absolute day number. */

int date_to_day(const unsigned int *d)
{
    const unsigned int *month_days = (const unsigned int *)0x020e0558u;
    const unsigned int *entry;
    unsigned int year = d[0];
    unsigned int month = d[1];
    unsigned int day = d[2];
    int weekday = (int)d[3];
    unsigned int offset;

    if (year >= 100u || month < 1u || month > 12u || day < 1u || day > 31u
        || weekday >= 7 || month < 1u || month > 12u)
        return -1;

    entry = month_days;
    entry += month;
    offset = *entry + (day - 1u);
    if (month >= 3u && (year & 3u) == 0u)
        offset = offset + 1u;

    return (int)(year * 365u + offset + ((year + 3u) >> 2));
}
