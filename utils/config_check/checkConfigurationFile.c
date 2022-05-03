#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "configParser.h"

/* Debugging option */

#define SHOW_FULL_DATA_STRUCTURE            true

/* Configuration file read constant */

#define MAX_FILE_READ_CHARACTERS            8192

#define FILE_READ_BUFFER_LENGTH             128

/* Configuration buffer */

static char fileReadBuffer[FILE_READ_BUFFER_LENGTH];

/* Code entry point */

int main(int argc, char *argv[]) {

    if (argc != 2) { puts("Usage: checkConfigurationFile FILENAME"); return 0; }

    FILE *fptr = fopen(argv[1], "r");

    if (fptr == NULL) { puts("ERROR - Could not open file."); return 0; }

    char ch;

    uint32_t count = 0;

    CP_parserStatus_t status = CP_WAITING;

    CP_configSettings_t tempConfigSettings;

    if (SHOW_FULL_DATA_STRUCTURE) {
    
        static CP_configSettings_t defaultConfigSettings = {
            .timezoneHours = 0,
            .timezoneMinutes = 0,
            .enableLED = 1,
            .enableMagneticSwitch = 1,
            .enableEdgeImpulseModel = 0,
            .disableSleepRecordCycle = 0,
            .enableTimeSettingFromGPS = 1,
            .batteryLevelDisplayType = BATTERY_LEVEL,
            .sleepDuration = 5,
            .recordDuration = 55,
            .minimumTriggerDuration = 0,
            .activeStartStopPeriods = 1,
            .startStopPeriods = {
                {.startMinutes = 0, .stopMinutes = 1440},
                {.startMinutes = 0, .stopMinutes = 1440},
                {.startMinutes = 0, .stopMinutes = 1440},
                {.startMinutes = 0, .stopMinutes = 1440},
                {.startMinutes = 0, .stopMinutes = 1440}
            },
            .earliestRecordingTime = 0,
            .latestRecordingTime = 0
        };

        tempConfigSettings = defaultConfigSettings;

    }

    while (count < MAX_FILE_READ_CHARACTERS) {

        if (count % FILE_READ_BUFFER_LENGTH == 0) {

            uint32_t bytes = fread(fileReadBuffer, sizeof(char), FILE_READ_BUFFER_LENGTH, fptr);

            if (bytes == 0) { puts("ERROR - Reached end of file."); return 0; }

        }

        ch = fileReadBuffer[count % FILE_READ_BUFFER_LENGTH];

        if (status == CP_PARSING || ch == '{') printf("%c", ch);

        status = ConfigParser_parse(ch, &tempConfigSettings);

        if (status == CP_CHARACTER_ERROR || status == CP_VALUE_ERROR || status == CP_SUCCESS) break;

        count += 1;

    }
   
    if (status == CP_SUCCESS) {

        puts("\nOKAY");

    } else if (status == CP_VALUE_ERROR) {
        
        printf("\nPARSE ERROR: Value error.\n");

    } else if (status == CP_CHARACTER_ERROR) {

        printf("\nPARSE ERROR: Character error reading '%c'.\n", ch);

    } else {

        printf("\nPARSE ERROR: Reached limit of %d characters.\n", MAX_FILE_READ_CHARACTERS);

    }

    if (SHOW_FULL_DATA_STRUCTURE) {

        printf("\n");
        printf("timezoneHours: %d\n", tempConfigSettings.timezoneHours);
        printf("timezoneMinutes: %d\n", tempConfigSettings.timezoneMinutes);
        printf("enableLED: %d\n", tempConfigSettings.enableLED);
        printf("enableMagneticSwitch: %d\n", tempConfigSettings.enableMagneticSwitch);
        printf("enableEdgeImpulseModel: %d\n", tempConfigSettings.enableEdgeImpulseModel);
        printf("disableSleepRecordCycle: %d\n", tempConfigSettings.disableSleepRecordCycle);
        printf("enableTimeSettingFromGPS: %d\n", tempConfigSettings.enableTimeSettingFromGPS);  
        printf("batteryLevelDisplayType: %d\n", tempConfigSettings.batteryLevelDisplayType);
        printf("sleepDuration: %d\n", tempConfigSettings.sleepDuration);
        printf("recordDuration: %d\n", tempConfigSettings.recordDuration);        
        printf("minimumTriggerDuration: %d\n", tempConfigSettings.minimumTriggerDuration);
        printf("activeStartStopPeriods: %d\n", tempConfigSettings.activeStartStopPeriods);

        for (uint32_t i = 0; i < tempConfigSettings.activeStartStopPeriods; i += 1) {
            printf("startStopPeriods[%d]: %d, %d\n", i, tempConfigSettings.startStopPeriods[i].startMinutes, tempConfigSettings.startStopPeriods[i].stopMinutes);               
        }

        printf("earliestRecordingTime: %d\n", tempConfigSettings.earliestRecordingTime);
        printf("latestRecordingTime: %d\n\n", tempConfigSettings.latestRecordingTime);

    }

    fclose(fptr);

}
