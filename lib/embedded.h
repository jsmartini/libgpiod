#ifndef EMBEDDED_H
#define EMBEDDED_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//uses gpiod kernel api
/*

Gpiod works by echoing flags into sysfs files to manipulate hardware pins
these files usually start at base directory /sys/class/gpio

*/
#define gpio_export "/sys/class/gpio/export"
#define gpio_unexport "sys/class/gpio/unexport"
#define gpio_base "/sys/class/gpio/gpio"
#define in "in"
#define out "out"

char* pin_file(int pin_id, char mode[40])
{
    //modes
    //I hate C strings with a passion
    static char buffer[255];
    strcat(buffer, gpio_base);
    char buffer2[5];
    sprintf(buffer2, "%d", pin_id);
    strcat(buffer, buffer2);
    strcat(buffer, mode);
    return buffer;
}

void toggle_pin(int pin_id, int mode)
{ //sets pin to high or low
    FILE *pin;
    pin = fopen(pin_file(pin_id, "/value"), "w");
    fprintf(pin, "%d", mode);
    fclose(pin);
}

void togglePinIO(int pin_id, char io)
{
    //io takes either char literal 'i' for input or 'o' for output
    FILE *pin;
    pin = fopen(pin_file(pin_id, "/direction"), "w");
    if(io == 'i'){
    fprintf(pin, "%s", in);
    printf("Pin:/t%d/tDirection Toggled Input", pin_id);
    }else if (io = 'o')
    {
    fprintf(pin, "%s", out);
    printf("Pin:/t%d/tDirection Toggled Output", pin_id);
    }else{
        printf("IO ERROR PIN:/t%d\nEXITING . . .", pin_id);
        exit(-1);
    }
    fclose(pin);
}

void export_pin(int pin_id)
{
    FILE *pin; //file pointer for pin out (EVERYTHING IS A FILE IN UNIX/LINUX)
    pin = fopen(gpio_export, "w");
    fprintf(pin, "%d", pin_id);
    fclose(pin);
    printf("Initialized Pin:\t%d\n", pin_id);
}

void unexport_pin(int pin_id)
{ //remove control of pin when finished
    FILE *pin;
    pin = fopen(gpio_unexport, "w");
    fprintf(pin, "%d", pin_id);
    printf("Unexported Pin:\t%d\n", pin_id);
    fclose(pin);
}

#endif // 
