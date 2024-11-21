This project includes the Arduino code to run a motorized curtain opener in the form factor of a normal curtain rod. The prototype opens and closes a set of drape-style curtains on a user programmable schedule via a BLDC motor. The electronic components of the prototype include an Arduino Nano, BLDC motor, ESC, DS3131 RTC clock module, 433Mhz digital transmitter/reciever pair, 7.4V LiPo battery, and a 16x2 LCD.

The time and programming menu are displayed on an LCD set on the side of the electronics and motor housing. The motor and LCD menu are controlled via the remote control with three buttons: up, down, and set. Pressing the up or down button opens or closes the curtains respectively. Pressing the down button launches a menu with the options "Set open/close" and "Set time." These options are navigated using the up/down buttons that controls a cursor on the LCD display. Pressing the set button selects the option indicated by the cursor. Selecting the "Set open/close" option launches a submenu with the options to schedule when the curtains will be automatically opened/closed; selecting either of these options launches programming menu to set the open/close schedule respectively. Selecting the "Set time" option from the main menu launches the programming menu to set the clock time. 

Once in one of the programming menus, the first line will display which set time menu is selected ("Set Open:", "Set Close:", or "Set time:"), and the second line will display the time in XX:XX AM/PM format. Pressing the up/down button changes the hour/minute/period, and pressing the set button navigates to the next option (hour -> minute -> period). Once set is pressed a third time (after changing period), the menu is closed, and the current time is displayed on the LCD.
