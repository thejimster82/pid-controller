# CC3220 PID Controller

Source code for simple PID controller meant for heating and lighting applications via phase control.

**What is it?**
---------------
Our Capstone idea is a phase control dimmer meant for heating applications with incandescent bulbs, such as reptile cages. The code does the following:
- Reads from a temperature sensor periodically via ADC read bursts.
- Digitally filters temperature readings via an averaging filter.
- Calculates the PID Control output with the temperature readings relative to a setpoint.
- Increases / decreases the duty cycle of a hardware PWM timer based on the PID output.
- Checks for zero-crossings to stay in phase with the 60 Hz, 120 VAC line voltage from an outlet.
- Enables the timer at zero crossings for phase control of a triac gating the power to the lamp.

**Why?**
--------
One of the biggest issues with incandescent bulbs is their massive inrush current and extremely high wattage requirements. This generates a lot of heat and significantly reduces the lifespan of the filaments because of electromigration. Our project aims to intelligently regulate power to these lamps to improve their lifespan, power savings, and heating efficiency.
