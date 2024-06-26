# CARE-PCR

CARE-PCR is a polymerase chain reaction (PCR) thermal cycler for DNA amplification, developed at the Center for Air Research in Urban Environments (CARE) at UP Diliman. Inspired by the OpenPCR design, it is a standalone device that does not require a connection to a computer or mobile device for configuration and operation. Additionally, CARE-PCR is portable or battery-powered, making it an excellent resource for educational and research use with limited resources **anywhere at anytime**. The CARE-PCR design is open-source and available for developers interested in assembling their own units and further improve it.

<img src="./img/carepcr-outside.jpg" width="200" />

## Platform IO Setup

The microcontroller that CARE-PCR uses is the Arduino MEGA 2560. The microcontroller code is built and compiled as a C++ file located at `main.cpp` using **PlatformIO**. Follow the steps below to install PlatformIO:

1. Install Visual Studio Code (VSCode).
2. Open the VSCode Extension Manager.
3. Search for the official PlatformIO IDE extension.
4. Install the PlatformIO IDE extension.

Once all the required IDEs are installed, `platform.ini` file will automatically integrate and configure the system.

## Integrating Wokwi with VSCode

Microcontrollers and some of their components can be simulated online at a website called **Wokwi**. It can be integrated into VSCode for a **trial run that lasts one month**. Follow the steps below to integrate Wokwi with your code. Ensure that you are signed into your Wokwi account before starting.

### Installation and License Activation

1. Install the Wokwi for VSCode extension in VSCode.
2. Press F1 and select "Wokwi: Request a new License".
3. VSCode will prompt you to confirm opening the Wokwi website in your browser. Confirm by clicking "Open".
4. On the Wokwi website, click the button that says "GET YOUR LICENSE".
5. The browser will ask for confirmation to send the license to VSCode. Confirm this action.
6. If you see a message in VSCode that says "License activated for [your name]", the integration is successful.

### Setup (make sure Platform IO is integrated before doing this)

1. At `wokwi.toml` file, you will see a text called firmware. Copy the path of firmware indicated as a `firmware.hex` file. It is located at `.pio\build\[microcontroller]\`.
2. Copy the path of elf indicated as a `firmware.elf` file. It is located at `.pio\build\[microcontroller]\`.

## Folder

The folder and files not mentioned here are boilerplate stuff produced by Platform IO

### Folders

src: codebase of CARE-PCR

mechanical_design_files: 3D drawings and design files used to build the mechanical assembly

pcb: PCB schematic and gerber files used for CARE-PCR

img: CARE-PCR thermocycler images

### Files

CARE-PCR_BOM.xlsx: Bill of materials (BOM) for CARE-PCR

CARE-PCR_UserManual.pdf: User manual for operating CARE-PCR

CARE-PCR_ProposedActions.pdf: points for recommendation and proposed plan of actions for CARE-PCR

## SRC Folder

SRC Folder is where the code in production being compiled and build. The codebase of CARE-PCR inherently follows the MVC pattern but is not strictly adheres to it.

1. Pages: where different pages seen at the LCD like main menu is coded. It acts as the View part of the MVC pattern.
2. Controller: global variables used. PageManager is for navigating pages and houses global variables that is used in the codebase. LCDManager for the LCD and its library. KeypadHandler for the keypad and its library, RTCManager for the real-time clock module and its library. It acts as the Controller part of the MVC pattern.
3. Thermocycler: main operation of the codebase or its behind the scenes. It also where the thermocyclerArray, which acts as the data structure of thermocycling experiment (thermocycler object produced by the class Thermocycler at Thermocycler.cpp) is built and formulated. It houses up to 3 thermocycler operations. This is where the PID and ADC code is also happening. It acts as the Model part of the MVC pattern.

The code will be easier to understand if you start at `main.cpp`. **Run the code first before studying it.**

## Credits

CARE-PCR is a CoE 199 project started by Alzter Aquino and Ezekiel Mendoza for the CARE research group at the Electrical and Electronics Engineering Institute (EEEI) at UP Diliman. Feel free to reach us at this email account: `alztr2908@gmail.com`.
