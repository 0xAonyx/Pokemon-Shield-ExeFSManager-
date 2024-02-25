//includes ascii art, check if enabled, color coded output, bool allowing input
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <switch.h>
#include <sys/stat.h>

#include "otter.h"

//check if file was properly renamed
bool Rename(const char *src_path, const char *dest_path) {
    if (rename(src_path, dest_path) != 0) {
        printf("Failed to rename %s to %s.\n", src_path, dest_path);
        return false;
    }
    return true;
}

bool fileExists(const char* filePath) {
    struct stat buffer;
    int exist = stat(filePath, &buffer);
    if(exist == 0) {
        return true; //enabled
    } else {
        return false; //disabled
    }
}

int main(int argc, char **argv) {
    consoleInit(NULL);
    const char* state;
    bool enabled = false;
    printf("ExeFS Manager - Pokemon Shield v1.01 (By Aonyx)\n");
    //printf("Please reach out on discord (aonyx2) with any questions!\n")
    //otter ascii
    printf("\n");
    printf("%s\n", otter);
    printf("\n");
    
    //check if it is enabled
    if(fileExists("/atmosphere/contents/01008DB008C2C000/exefs")) {
            state = "ENABLED";
            enabled = true;
            printf("ExeFS are currently: \033[32m%s\033[0m\n", state);
        } else if (fileExists("/atmosphere/contents/01008DB008C2C000/inactive_exefs")) {
            state = "DISABLED";
            enabled = false;
            printf("ExeFS are currently: \033[31m%s\033[0m\n", state);
        }else{
            state = "NOT FOUND";
            printf("ExeFS are currently: \033[33m%s\033[0m\n", state);
        }
    
    printf("Press 'A' to Enable ExeFS Mods\n");
    printf("Press 'B' to Disable ExeFS Mods\n");
    printf("Press '+' to Exit\n");
    
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);
    PadState pad;
    padInitializeDefault(&pad);

    while(appletMainLoop()) {
        padUpdate(&pad);
        u64 kDown = padGetButtonsDown(&pad);
        if((kDown & HidNpadButton_A) && !enabled) {
            if(!Rename("/atmosphere/contents/01008DB008C2C000/inactive_exefs", "/atmosphere/contents/01008DB008C2C000/exefs")) {
                printf("Error enabling ExeFS Mods.\n");
            } else {
                printf("ExeFS Mods Enabled.\n");
                enabled = true;
            }
        }
        if((kDown & HidNpadButton_B) && enabled) {
            if(!Rename("/atmosphere/contents/01008DB008C2C000/exefs", "/atmosphere/contents/01008DB008C2C000/inactive_exefs")) {
                printf("Error disabling ExeFS Mods.\n");
            } else {
                printf("ExeFS Mods Disabled.\n");
                enabled = false;
            }
        }
        if(kDown & HidNpadButton_Plus) break;
        consoleUpdate(NULL);
    }

    consoleExit(NULL);
    return 0;
}
