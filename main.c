#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct date_time_info
{
    // Date
    union
    {
        struct { int y, m, d; };
        int values[3];
    };
};

enum moon_phase
{
    NEW_MOON = 0,
    WAXING_CRESCENT,
    FIRST_QUARTER,
    WAXING_GIBBOUS,
    FULL_MOON,
    WANING_GIBBOUS,
    THIRD_QUARTER,
    WANING_CRESCENT,

    MOON_PHASE_COUNT
};

#include "moon_ascii.h"

static const char *MOON_PHASE_NAMES[] =
{
    [NEW_MOON]        = "New Moon",
    [WAXING_CRESCENT] = "Waxing Crescent",
    [FIRST_QUARTER]   = "First Quarter",
    [WAXING_GIBBOUS]  = "Waxing Gibbous",
    [FULL_MOON]       = "Full Moon",
    [WANING_GIBBOUS]  = "Waning Gibbous",
    [THIRD_QUARTER]   = "Third Quarter",
    [WANING_CRESCENT] = "Waning Crescent",
};

inline const double
julian_day(struct date_time_info *t)
{
    int y = t->y;
    int m = t->m;

    // Subtract 1 from year and add 12 to months, if month is January or
    // February
    if (m < 3)
    {
        --y;
        m += 12;
    }

    int a = y / 100;
    int b = a / 4;
    int c = 2 - a + b;
    int e = (int)(365.25 * (y + 4716.0));
    int f = (int)(30.6001 * (m + 1.0));

    return c + t->d + e + f - 1524.5;
}

int
main(int argc, char **argv)
{
    // New moon on this day
    static const struct date_time_info nmoon_t =
    {
        .y = 2000, .m = 1, .d = 6
    };
    const double nmoon = julian_day(&nmoon_t);

    struct date_time_info t;
    bool north = false;
    int value_count = 0;
    for (++argv; *argv != NULL; ++argv)
    {
        if (strcmp(*argv, "--north") == 0)
        {
            north = true;
            continue;
        }

        // Already got all the values we need
        if (value_count >= 3) continue;

        // Parse year/month/day numbers
        char *endptr;
        long val = strtol(*argv, &endptr, 10);
        errno = 0;
        if (endptr == *argv ||
            ((val == LONG_MAX || val == LONG_MIN) && errno == ERANGE))
        {
            // Failed to parse, just skip
            fprintf(stderr, "lunar: invalid argument '%s'\n", *argv);
            continue;
        }
        t.values[value_count++] = (int)val;
    }

    // Just some simple validation
    if (value_count == 3 &&
        (t.m > 12 ||
        t.m <= 0 ||
        t.y <= 0 ||
        t.d > 31))
    {
        fprintf(stderr, "lunar: invalid date\n");
        return -1;
    }

    if (value_count != 3)
    {
        // Just use current date
        time_t tt = time(NULL);
        struct tm tm = *localtime(&tt);
        t.y = tm.tm_year + 1900;
        t.m = tm.tm_mon + 1;
        t.d = tm.tm_mday;
    }

    printf("it is %d-%02d-%02d\n", t.y, t.m, t.d);

    // Get lunar phase
    double jd = julian_day(&t);
    double diff = jd - nmoon;
    double newmoons = diff / 29.530588853f;
    double norm = newmoons - (int)newmoons;
    double days_in_cycle = norm * 29.530588853f;

    printf("%.1f days since new-moon\n", days_in_cycle);

    // Calculate phase index
    enum moon_phase phase = (enum moon_phase)round(
        norm * (MOON_PHASE_COUNT - 1));
    if (!north)
    {
        phase = MOON_PHASE_COUNT - phase;
        if (phase == 8) phase = 0;
    }

    printf("moon phase is %s (from %s hemisphere)\n",
        MOON_PHASE_NAMES[phase],
        north ? "Northern" : "Southern");

    // Print artwork
    printf("%s\n", MOON_PHASE_ART[phase]);

    return 0;
}
