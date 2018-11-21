# TTK4155 - Embedded and Industrial Computer Systems and Design
These are the source files for the lab project in TTK4155 in 2018. 

The system consists of two nodes: 
Node 1:
  - ATmega162
  - MAX233
  - MCP2551
  - MCP2515
  - GAL16V8D-15QP
  - SN74ALS573
  - IDT 7164S20TPG
  - ADC0844CNN
  - NimronP1000 (http://nimron.net/P1000/)
  
Node2:
  - ATmega2560
  - MCP2551
  - MCP2515
  - DAC
  - I2C
  - MCP620
  - Motor driver with encoder
  
  
The main objective was to play a game of mechanical pong. Reading user inputs on the NimronP1000, 
the user navigates through a menu on the OLED mounted on the NimronP1000. The user chooses a 
game mode, node 1 communicates inputs and game mode to node 2 over CAN, and node 2 operates 
a game board with a motor (over I2C), servo and a solenoid.

The files in this repository have not been altered since code submission. Because a great deal
of last minute adittions of misc. modules, functionality, and parameter tuning, the code quality
is not top notch.
