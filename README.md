# TM4C123 UART LED Controller

A bare-metal UART and GPIO project for the **Texas Instruments TM4C123GH6PM** microcontroller. Control the RGB LED from a PC serial terminal (e.g. PuTTY) with single-character commands.

## Features

* Bare-metal C, no RTOS or third-party framework
* UART0 communication with a PC (9600 baud, 8N1)
* Single-character command interface: red, green, blue, all off, help
* Help text and invalid-command handling
* Onboard RGB LED by default, optional external LEDs on Port B
* Modular HAL layers for UART, LED and UI

## Quick Start

1. Open `UART_Tiva_C.uvprojx` in Keil uVision.
2. Build (**Project → Build Target**) and flash to the board.
3. Open a serial terminal on the board's COM port at **9600 baud, 8N1**.
4. Reset the board and type `h` for help.

## Hardware

Target MCU: **TM4C123GH6PM** (developed for a Tiva C / TM4C123 LaunchPad-style board).

### Onboard RGB LED (default)

| LED   | GPIO Pin |
| ----- | -------- |
| Red   | PF1      |
| Blue  | PF2      |
| Green | PF3      |

### UART0

| Function | GPIO Pin |
| -------- | -------- |
| UART0 RX | PA0      |
| UART0 TX | PA1      |

On LaunchPad boards, UART0 is bridged through the on-board debugger to a **virtual COM port** over the same USB cable used for programming. Look for a "Stellaris Virtual Serial Port" / ICDI port in Device Manager (Windows) or `/dev/ttyACM*` (Linux).

### External LEDs (optional)

To use external LEDs on Port B, uncomment this line in `src/config.h`:

```c
#define USE_EXTERNAL_LEDS
```

| LED   | GPIO Pin |
| ----- | -------- |
| Red   | PB2      |
| Blue  | PB3      |
| Green | PB4      |

Wire each LED in series with a current-limiting resistor (typically 220–330 Ω) between the GPIO pin and GND (pin → resistor → LED anode, LED cathode → GND).

When `USE_EXTERNAL_LEDS` is not defined, the firmware uses the onboard LEDs on Port F.

## Serial Settings

| Setting   | Value  |
| --------- | ------ |
| Baud rate | `9600` |
| Data bits | `8`    |
| Parity    | None   |
| Stop bits | `1`    |

UART0 is clocked from the PIOSC, with the corresponding integer and fractional baud-rate divisors.

## Commands

| Command | Action                |
| ------- | --------------------- |
| `r`     | Turn on red LED       |
| `g`     | Turn on green LED     |
| `b`     | Turn on blue LED      |
| `f`     | Turn off all LEDs     |
| `h`     | Show help             |

> **Note:** Color commands only turn the selected LED **on**. They do not turn the others off, so `r` followed by `g` leaves both red and green lit. Use `f` to clear all LEDs.

### Example Session

```text
Enter 'r', 'g', 'b', 'f' or 'h' for help: h
For turning red LED use     'r'
For turning green LED use   'g'
For turning blue LED use    'b'
For turn LEDs off use       'f'

Enter 'r', 'g', 'b', 'f' or 'h' for help: r

Enter 'r', 'g', 'b', 'f' or 'h' for help: b

Enter 'r', 'g', 'b', 'f' or 'h' for help: f
```

An invalid character prints:

```text
Please enter valid command!
```

## Project Structure

```text
tm4c123-uart/
├── HAL/
│   ├── LED/
│   │   ├── LED.c
│   │   └── LED.h
│   ├── UART/
│   │   ├── UART.c
│   │   └── UART.h
│   └── UI/
│       ├── UI.c
│       └── UI.h
├── RTE/
│   └── Device/
│       └── TM4C123GH6PM/
├── src/
│   ├── config.h
│   ├── constants.h
│   └── main.c
└── UART_Tiva_C.uvprojx
```

## Software Architecture

```text
   PC / PuTTY
       │  UART
       ▼
   ┌─────────┐
   │  UART0  │
   └────┬────┘
        ▼
   ┌─────────┐
   │   UI    │  prompt, help, invalid-command messages
   └────┬────┘
        ▼
   ┌─────────┐
   │ main.c  │  command decode
   └────┬────┘
        ▼
   ┌─────────┐
   │   LED   │
   └────┬────┘
        ▼
     RGB LED
```

Startup in `main.c`: LED init → UART pin setup → UART0 init → endless command loop (blocking read, then dispatch).

### Modules

**`src/config.h`**: GPIO port definitions, UART register masks and pin config, baud-rate settings, LED pin assignments, command characters, and the internal/external LED selection.

**`src/constants.h`**: shared constants (peripheral ready/not-ready states, success return code, combined RGB LED mask).

**`HAL/UART`**: low-level UART interface. Reads are blocking.

```c
void UART_pins_setup(void);
void UART0_setup(void);

char UART0_read_char(void);
void UART0_write_char(char c);
void UART0_write_string(char *c);
```

**`HAL/LED`**: LED abstraction. Operations are masked against the configured RGB pins, so only valid LED bits are modified.

```c
int LED_setup(void);

void LED_on(uint32_t led_mask);
void LED_off(uint32_t led_mask);
```

**`HAL/UI`**: terminal interaction, kept separate from the hardware drivers.

```c
char UI_prompt(void);
void UI_help(void);
void UI_invalid(void);
```

## Requirements

* TM4C123GH6PM development board (e.g. Tiva C LaunchPad)
* Keil MDK / uVision (project targets ARM Cortex-M4, ARM Compiler 6.21)
* Keil TM4C123 device support package (CMSIS)
* USB cable with debug connection to the board
* Serial terminal such as PuTTY

## Building and Flashing

```bash
git clone https://github.com/Ivan-Jalovenko/tm4c123-uart.git
cd tm4c123-uart
```

1. Open `UART_Tiva_C.uvprojx` in Keil uVision.
2. Build with **Project → Build Target**.
3. Connect the board and flash with Keil's download function.
4. Open PuTTY (or similar), select the board's COM port, and set 9600 baud, 8 data bits, no parity, 1 stop bit.
5. Reset the board. The prompt appears.

## Design Notes

* Polling-based UART (no interrupts)
* One character per command
* LED state is controlled directly through GPIO registers
* No external dependencies beyond CMSIS and the device support package


## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
