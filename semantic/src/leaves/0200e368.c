/* Unknown date-like record helper: reads {field0, field1, field2}, treats field0
 * as a year offset, field1 as a month and field2 as a day, folds the month into
 * a 12-month cycle that starts in March (borrowing one year for January and
 * February) and returns a small index in 0..6 derived from the resulting day
 * count. Record identity and field meanings are unknown; only the observed DS
 * value effect is modeled. Independently reconstructed from BWBE-r0 ARM9
 * 0x0200e368. */
int pvz_0200e368_leaf(const int *p)
{
    int year = p[0] + 2000;
    int month = p[1] - 2;
    int day = p[2];
    int century;
    int rest;
    int total;

    if (month < 1) {
        year -= 1;
        month += 12;
    }
    century = year / 100;
    rest = year % 100;
    total = day + (26 * month - 2) / 10 + rest + rest / 4 + century / 4
            + century * 5;
    return total % 7;
}
