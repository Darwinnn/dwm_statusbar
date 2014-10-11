#define CHARGE_FULL "/sys/class/power_supply/BAT0/charge_full"
#define CHARGE_NOW "/sys/class/power_supply/BAT0/charge_now" 
#define STATUS "/sys/class/power_supply/BAT0/status"

typedef enum {
    CHARGING,
    DISCHARGING,
    UNKNOWN,
    FULL,
} bstate_t;

float get_battery_percentage(char *bar);
bstate_t get_status();

