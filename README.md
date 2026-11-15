# OBD-II over CAN with Arduino (university project, 2023)

A four-person project for the course *Logičko projektovanje računarskih sistema 2* (Logic Design of Computer Systems 2) at the Faculty of Technical Sciences, University of Novi Sad. It builds on the course template by Miloš Subotić.

The goal was to read a car's state over the OBD-II port, with the diagnostic side of the system running on an Arduino. The project title was "Detection if a car is locked over the OBD2 port". Another student team built the ECU side (the part that answers requests), and this team's job was to play the diagnostic application: send a request for a specific parameter, receive the answer, and show what it means and its value.

## Hardware and protocol

- Arduino boards with Seeed CAN-BUS Shield V2.0 and V3 boards (MCP2515 CAN controller, MCP2551 transceiver)
- OBD2 and DB9 connectors
- ISO 15765-4 CAN: 11-bit identifiers, 500 kbit/s
- Pinouts in [`HW/`](HW)

## What's in the repository

| Path | Contents |
|---|---|
| `FW/ODB2_Diagnostic/` | Diagnostic-side sketches: a random-PID sender, CAN and OBD-II send/receive tests, and a skeleton of the diagnostic application that was not finished. See `readme.txt` there. |
| `FW/ECU_Simulation/` | ECU-side sketch used for testing, kept in sync with the ECU team's work |
| `FW/ODB2_Diagnostic/libs/` | Third-party CAN and OBD-II Arduino libraries we tried (MCP_CAN, arduino-CAN, arduino-OBD2, arduino-mcp2515, SparkFun CAN-Bus and others), with their own licences |
| `SW/UART_Bridge/` | C++ UART code from the course template |
| `Common/`, `FW/Template/`, `FW/resources/`, `waf` | Course build scaffolding and examples |
| `Dokumentacija.docx` | Project report (Serbian) |

## Outcome

The project did not reach a working end-to-end diagnostic. Messages sent from one Arduino were never received by the other once a V3 shield was in the setup, although the other team's earlier V2 setup had worked. The team narrowed it down by:

- comparing which shield and library combinations worked in a test matrix,
- tracing which TX/RX registers became active on each board,
- trying nine different CAN and OBD-II libraries and their examples,
- comparing signals with an oscilloscope.

The report concludes that the V3 and V2 shields could not communicate with each other, and suggests using two V2 shields instead.

## Build

Sketches are Arduino `.ino` files. Open one in the Arduino IDE, install the CAN library it includes from `FW/ODB2_Diagnostic/libs/`, and upload. The C++ in `SW/` uses the course's `waf` build.

MIT licensed (course template by Miloš Subotić).
