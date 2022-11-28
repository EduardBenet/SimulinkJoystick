/**
* https://www.kernel.org/doc/Documentation/input/joystick-api.txt
*/
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/joystick.h>
#include <ps3joystick.h>

/**
* Reads a joystick event from the joystick device.
*
* Returns 0 on success. Otherwise -1 is returned.
*/
int read_event(int fd, struct js_event *event)
{
    ssize_t bytes;

    bytes = read(fd, event, sizeof(*event));

    if (bytes == -1)
        return 0;

    if (bytes == sizeof(*event))
        return 1;

    printf("Unexpected bytes from joystick:%d\n", bytes);

    /* Error, could not read full event. */
    return -1;
}

/**
 * Current state of an axis.
 */
struct axis_state {
    short x, y;
};

/**
 * Keeps track of the current axis state.
 *
 * NOTE: This function assumes that axes are numbered starting from 0, and that
 * the X axis is an even number, and the Y axis is an odd number. However, this
 * is usually a safe assumption.
 *
 * Returns the axis that the event indicated.
 */
size_t get_axis_state(struct js_event *event, struct axis_state axes[3])
{
    size_t axis = event->number / 2;

    if (axis < 3)
    {
        if (event->number % 2 == 0)
            axes[axis].x = event->value;
        else
            axes[axis].y = event->value;
    }

    return axis;
}


/*
Setup joystick
*/
int joystickSetup()
{
    int js;
    const char *device;

    device = "/dev/input/js0";
    js = open(device, O_RDONLY | O_NONBLOCK);

    if (js == -1)
        perror("Could not open joystick");

}

void readJoystick(int fd, joystick_state *j_state ) {

    struct js_event event;
    struct axis_state axes[3] = {0};
    size_t axis;

    while (read_event(fd, &event) > 0) 
    {
        switch (event.type)
        {
            case JS_EVENT_BUTTON:
                j_state->buttons[event.number] = event.value;
                break;
            case JS_EVENT_AXIS:
                if (event.number % 2 == 0) {
                    j_state->axis[event.number] = event.value;
                } else {
                    j_state->axis[event.number] = -event.value;
                }
                break;
            default:
                break;
        }

    }

    return;
}

int joystickTerminate(int fd)
{
    close(fd);
    return(0);
}