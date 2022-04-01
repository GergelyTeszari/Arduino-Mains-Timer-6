# Arduino-Mains-Timer-6
Six-hole mains hub timer with configurable timing per socket.

Each plug can be timed from thirty minutes to three hours.
When all timers have expired, the Arduino can turn itself off. (if power of the Arduino is connected to a relay controlled by pin A4)
Wiring diagram can be found as plug.png, but it has a little error, which is that the buttons should not be connected directly to vcc but to a pull-down configuration. All you have to do is connect a resistor between vcc and gnd so that the button completes the circuit, and after the button but in front of the resistor you have to connect the wire that goes to the analog inputs.

# Function description:
Note: Arduino can write to the serial monitor what's going on inside.

When an Aruino running this program is turned on, the program enters standby mode after the deactivation relay is turned on. It turns on the first relay (pin 2) to indicate that it is waiting to be set. In this case, you can use the "plus" button to increase the timing time in half-hour increments. If it is increased by half an hour, it indicates it on the number display LEDs (pins 8-13). For each increment, the number of LEDs lit for three seconds is thirty minutes. If you increase the value more than six times for thirty minutes, the counter will jump again to one times thirty minutes.

If the waiting time of the given relay is set, the "next" button can be used to move to the next relay. In this case, the "OK" LED flashes, then the previously proigrammed relay switches off and the next one switches on. If you press the "next" button after the sixth relay, the program will jump back to the first relay.
When you have finished programming, you can start the timer with the "start" button. The "OK" LED will flash and the relays, where a non-zero timing has been set, will turn on.

The "start" and "next" buttons can be pressed at any time, eg. you do not have to press the relays from two to six if you only want to switch on the first relay.
The deactivation relay is a separate switch, that - when properly configured - can turn off the Arduino after all the timers expire.
Proper configuration: Before the 5-volt transformer of the Arduino, the phase must be interrupted and then the broken wire must be connected to the normally open connection of the deactivating relay, and a pushbutton must be connected in parallel to start the Arduino. Thus, the button is used to supply power to the Arduino, and then the program starts, which turns on the deactivating relay so that the button can be released.

When the timers expire, the relays turn off. If all relays are off, the "OK" LED will flash and the deactivating relay will turn off, de-energizing the Arduino. If the deactivation relay has not been configured, so the Arduino is still receiving power, the "OK" LED will flash every second to indicate that the program is over. In this case, you can either unplug the Arduino and plug it in again or press the "Reset" button to restart the program.
