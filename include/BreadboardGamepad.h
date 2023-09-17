#pragma once
#include <BleGamepad.h>

class BluetoothGamepad
{
    public:
    BleGamepad bleGamepad;

    BluetoothGamepad()
    {

    }

    void begin(std::string deviceName, uint16_t num_buttons = 2)
    {
        BleGamepadConfiguration config;

        config.setAxesMin(-100);
        config.setAxesMax(100);
        config.setWhichAxes(true, true, false, false, false, false, false, false);

        config.setButtonCount(num_buttons);

        bleGamepad.deviceName = deviceName;

        bleGamepad.begin(&config);
    }

    #define BUTTON_TEMPLATE(BUTTON_NAME, PRESS_CMD, RELEASE_CMD)    \
    bool state_##BUTTON_NAME = false;                               \
    void press_##BUTTON_NAME()                                      \
    {                                                               \
        if (state_##BUTTON_NAME)                                    \
            return;                                                 \
        state_##BUTTON_NAME = true;                                 \
        if (!bleGamepad.isConnected())                              \
            return;                                                 \
        PRESS_CMD;                                                  \
    }                                                               \
    void release_##BUTTON_NAME()                                    \
    {                                                               \
        if (!state_##BUTTON_NAME)                                   \
            return;                                                 \
        state_##BUTTON_NAME = false;                                \
        if (!bleGamepad.isConnected())                              \
            return;                                                 \
        RELEASE_CMD;                                                \
    }                                                               \
    void set_##BUTTON_NAME(bool pressed)                            \
    {                                                               \
        if (state_##BUTTON_NAME == pressed)                         \
            return;                                                 \
        state_##BUTTON_NAME = pressed;                              \
        if (!bleGamepad.isConnected())                              \
            return;                                                 \
        if (pressed)                                                \
            PRESS_CMD;                                              \
        else                                                        \
            RELEASE_CMD;                                            \
    }


    BUTTON_TEMPLATE(a, bleGamepad.press(BUTTON_1), bleGamepad.release(BUTTON_1))
    BUTTON_TEMPLATE(b, bleGamepad.press(BUTTON_2), bleGamepad.release(BUTTON_2))
    BUTTON_TEMPLATE(c, bleGamepad.press(BUTTON_3), bleGamepad.release(BUTTON_3))
    BUTTON_TEMPLATE(d, bleGamepad.press(BUTTON_4), bleGamepad.release(BUTTON_4))
    BUTTON_TEMPLATE(e, bleGamepad.press(BUTTON_5), bleGamepad.release(BUTTON_5))
    BUTTON_TEMPLATE(f, bleGamepad.press(BUTTON_6), bleGamepad.release(BUTTON_6))
    BUTTON_TEMPLATE(g, bleGamepad.press(BUTTON_7), bleGamepad.release(BUTTON_7))
    BUTTON_TEMPLATE(h, bleGamepad.press(BUTTON_8), bleGamepad.release(BUTTON_8))
    BUTTON_TEMPLATE(start, bleGamepad.pressStart(), bleGamepad.releaseStart())
    BUTTON_TEMPLATE(select, bleGamepad.pressSelect(), bleGamepad.releaseSelect())
    BUTTON_TEMPLATE(up, setAxes(), setAxes())
    BUTTON_TEMPLATE(down, setAxes(), setAxes())
    BUTTON_TEMPLATE(left, setAxes(), setAxes())
    BUTTON_TEMPLATE(right, setAxes(), setAxes())

    bool getAnyPressed()
    {
        return state_a | state_b | state_c | state_d | state_e | state_f | state_g | state_h | state_up | state_down | state_left | state_right | state_start | state_select;
    }

    bool isConnected()
    {
        return bleGamepad.isConnected();
    }

    void setAxes()
    {
        int16_t x = 0;
        int16_t y = 0;
        signed char hat = HAT_CENTERED;

        if (state_up)
        {
            y -= 100;            
        }
        if (state_down)
        {
            y += 100;
        }
        if (state_left)
        {
            x -= 100;
        }
        if (state_right)
        {
            x += 100;
        }

        if (state_up)
        {
            if (state_right)
                hat = HAT_UP_RIGHT;
            else if (state_left)
                hat = HAT_UP_LEFT;
            else
                hat = HAT_UP;
        }
        else if (state_down)
        {
            if (state_right)
                hat = HAT_DOWN_RIGHT;
            else if (state_left)
                hat = HAT_DOWN_LEFT;
            else
                hat = HAT_DOWN;
        }
        else
        {
            if (state_right)
                hat = HAT_RIGHT;
            else if (state_left)
                hat = HAT_LEFT;
            else
                hat = HAT_CENTERED;
        }

        bleGamepad.setHat1(hat);
        bleGamepad.setAxes(x, y);
    }

};