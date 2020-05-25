#include "MicroBit.h"

MicroBit uBit;

#define MES_AUDIO_CONTROL  9005

int connected = 0;

void onConnected(MicroBitEvent e)
{
    uBit.display.print("C");
    connected = 1;
}

void onDisconnected(MicroBitEvent e)
{
    uBit.display.print("D");
    connected = 0;
}

int getGesture() {
    int x = uBit.accelerometer.getX();
    int y = uBit.accelerometer.getY();
    return uBit.accelerometer.getGesture();
}

void onButton(MicroBitEvent e)
{
    if (connected == 0) {
        uBit.display.scroll("NC");
        return;
    }

    if (getGesture() == MICROBIT_ACCELEROMETER_EVT_FACE_UP || getGesture() == MICROBIT_ACCELEROMETER_EVT_NONE) {
        if (e.source == MICROBIT_ID_BUTTON_A) {
            MicroBitEvent evt(MES_AUDIO_CONTROL, 1);
        }

        if (e.source == MICROBIT_ID_BUTTON_B) {
            MicroBitEvent evt(MES_AUDIO_CONTROL, 2);
        }

        if (e.source == MICROBIT_ID_BUTTON_AB) {
            MicroBitEvent evt(MES_AUDIO_CONTROL, 3);
        }
        
    } else {
        
        if (e.source == MICROBIT_ID_BUTTON_A) {
            MicroBitEvent evt(MES_AUDIO_CONTROL, 4);
        }

        if (e.source == MICROBIT_ID_BUTTON_B) {
            MicroBitEvent evt(MES_AUDIO_CONTROL, 5);
        }

        if (e.source == MICROBIT_ID_BUTTON_AB) {
            MicroBitEvent evt(MES_AUDIO_CONTROL, 6);
        }
        
    }

}


int main()
{
    // Initialise the micro:bit runtime.
    uBit.init();

    uBit.display.scroll("AUDIO PRANK");
    
    uBit.messageBus.listen(MICROBIT_ID_BLE, MICROBIT_BLE_EVT_CONNECTED, onConnected);
    uBit.messageBus.listen(MICROBIT_ID_BLE, MICROBIT_BLE_EVT_DISCONNECTED, onDisconnected);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, onButton);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, onButton);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_AB, MICROBIT_BUTTON_EVT_CLICK, onButton);

    // If main exits, there may still be other fibers running or registered event handlers etc.
    // Simply release this fiber, which will mean we enter the scheduler. Worse case, we then
    // sit in the idle task forever, in a power efficient sleep.
    release_fiber();
}
