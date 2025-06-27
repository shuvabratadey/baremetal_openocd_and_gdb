# openocd_and_gdb
This README provides a comprehensive guide on using OpenOCD for programming and debugging ESP32 and STM32 microcontroller boards. It includes links to video tutorials and provides download links for OpenOCD. The guide covers essential commands for both ESP32 and STM32 boards, including programming, erasing, and debugging using OpenOCD and GDB. Additionally, it offers instructions on connecting GDB and Telnet with OpenOCD for efficient debugging. Commonly used OpenOCD commands and tips for modifying configurations are also included.


## Tutorial Links
- [Youtube Video Tutorial](https://www.youtube.com/watch?v=_1u7IOnivnM)
- [Full Tutorial Playlist](https://www.youtube.com/watch?v=qWqlkCLmZoE&list=PLERTijJOmYrDiiWd10iRHY0VRHdJwUH4g)

## Download Links
[![](https://img.shields.io/badge/OpenOCD-blue?style=for-the-badge)](https://gnutoolchains.com/arm-eabi/openocd/)

[![](https://img.shields.io/badge/Arm_GNU_Toolchain-blue?style=for-the-badge)](https://developer.arm.com/downloads/-/gnu-rm)
</br>
#### Alternatively, you can use the ESP32 OpenOCD where you got the ESP32 gdb also (if esp-idf installed in your system):
#### Path: `C:\Users\{user_name}\.espressif\tools\openocd-esp32\v0.12.0-esp32-20230419\openocd-esp32\bin\openocd.exe`

##  For ESP32 Board
<img src="https://github.com/shuvabratadey/openocd_and_gdb/blob/main/Pictures/ESP32_ESP-PROG_CONNECTION.png" width="500"/></br>
### Replace Driver of ESP-PROG using Zadig Software, So follow this steps after install Zadig Software.
[![](https://img.shields.io/badge/Download_Zadig_Software-blue?style=for-the-badge)](https://zadig.akeo.ie/)
<img src="https://github.com/shuvabratadey/openocd_and_gdb/blob/main/Pictures/how_to_replace_driver_esp-prog.png" width="1000"/></br>
### OpenOCD Commands
- **Command:** `openocd -f board/esp32-wrover-kit-3.3v.cfg`
- **Programming or Erasing using OpenOCD:**
  - **Example Commands:**
    - **Erase Full Flash:** `openocd -f board/esp32-wrover-kit-3.3v.cfg -c "flash init; init; halt; flash erase_sector 0 1 last; exit"`    
    - **Program Flash:** ${\textsf{\color{red}program filename [preverify] [verify] [reset] [exit] [offset]}}$</br>
      `openocd -f board/esp32-wrover-kit-3.3v.cfg -c "program blink.bin reset 0x10000; halt"`
      </br>or</br>
      `openocd -f board/esp32-wrover-kit-3.3v.cfg -c "program bootloader/bootloader.bin reset 0x1000; program partition_table/partition-table.bin reset 0x8000; program blink.bin reset 0x10000; halt"`      
      or</br>
    - `openocd -f board/esp32-wrover-kit-3.3v.cfg -c "program_esp blink.bin 0x10000 verify exit"`
### GDB Commands
- **Command:** `xtensa-esp32-elf-gdb blink.elf`

## For STM-32 Blue-Pill Module
<img src="https://github.com/shuvabratadey/openocd_and_gdb/blob/main/Pictures/stlink-with-bluepill.jpeg" width="1000"/></br>
### OpenOCD Commands
- **Command:** `openocd -f board/stm32f3discovery.cfg`
- **Alternative Command:**
  - `openocd -f interface/stlink-v2.cfg -f target/stm32f1x.cfg` **(Note: Requires modification of "stm32f1x.cfg" file)**
### GDB Commands
> [!TIP]
>  ${\textsf{\color{blue}open command-prompt with this .elf file location.}}$
- **Command:** `arm-none-eabi-gdb stm32_blink.ino.elf`

## Connecting GDB with OpenOCD
- **After initiating GDB, connect to OpenOCD using:**
  - Command: `target remote localhost:3333` or `target extended-remote localhost:3333`

## Connecting Telnet with OpenOCD
- **Open a Telnet Connection using Putty:**
> [!NOTE]
> open putty 🠊 select "other" & set "Telnet" 🠊 Set Port "4444" 🠊 set host "localhost" 🠊 click open
> 
  - **Set Port:** `4444`
  - **Set Host:** `localhost`

# Follow this steps for Debug
## Step-1: To debug a program, open the command prompt at the location of your build file
<img src="https://github.com/shuvabratadey/openocd_and_gdb/blob/main/Pictures/openocd_gdb_connection/pic-1.png" width="800"/></br>

## Step-2: Execute openocd as instructed by the provided figure
<img src="https://github.com/shuvabratadey/openocd_and_gdb/blob/main/Pictures/openocd_gdb_connection/pic-2.png" width="800"/></br>

## Step-3: Open another terminal and execute the gdb with the *.elf file, After gdb initiate, run the connect command to communicate gdb with openocd
<img src="https://github.com/shuvabratadey/openocd_and_gdb/blob/main/Pictures/openocd_gdb_connection/pic-3.png" width="800"/></br>

## Step-4: Now the gdb is ready to accept your debugging commands
<img src="https://github.com/shuvabratadey/openocd_and_gdb/blob/main/Pictures/openocd_gdb_connection/pic-4.png" width="800"/></br>

## Openocd and GDB Commands
> [!TIP]
>  ${\textsf{\color{blue}If gdb is used then must specify the}}$ ${\textsf{\color{red}'monitor'}}$ ${\textsf{\color{blue}keyword before the openocd command}}$

- **Commands:**
  - `monitor reset init`: Reset the board
  - `monitor reset halt`: Halt the board after reset
  - `monitor flash erase_address 0x10000 0x2000`: Erase flash memory region
  - `monitor flash write_image erase stm32_blink.ino.elf`: Erase and flash the device using .elf file
  - `monitor flash write_image blink.bin 0x10000`: Flash the device using .bin file from a specific address
  - `shell cls`: Clear the screen from GDB
  - `tui enable` | `tui disable` or press <b>Ctrl+X+A</b>: for enable/disable the text user interface [Only works in `xtensa-esp32-elf-gdb`]
    - `lay next` or `lay prev`: To change the tabs
    - `layout asm` To see what assembly tab
    - `layout reg` To see what register tab
    - To enable split screen, press <b>Ctrl+X</b> then press <b>2</b>
    - enter `focus cmd` to switch focus to the command line gdb
    - <b>Ctrl+P</b> To iterate through previous instructions in gdb
  - `b loop`: Set breakpoint in the loop()
  - `b blink_example_main.c:19`: Set breakpoint in specific file for ESP32 board  ${\textbf{\color{red}Format:}}$ ${\textsf{\color{blue}b [file-name]:[line no]}}$
  - `b stm32_blink.ino:8`: Set breakpoint in specific file for STM32 board
  - `info <topic>` : is used to display a wide range of information about the program being debugged.
    - `info b` or `info breakpoints`: Lists all breakpoints, watchpoints, and catchpoints.
    - `info wat` or `info watchpoints`: Lists all active watchpoints.
    - `info var` or `info variables`: Lists global and static variable names.
    - `info func` or `info functions`: Lists all functions in the program.
    - `info scope <function>`: Lists the variables in scope for a function.
    - `info reg` or `info registers` or `info all-registers`: Lists CPU register contents.
    - `info threads`: Lists all threads.
      - `info thread <num>`: Displays detailed info about a specific thread.
    - `info frame`: Details about the current stack frame.
    - `info stack`: Shows the current call stack.
    - `info sources`: Lists all source files that GDB has debug information for.
    - `info files` or `info target`: Gives information about the symbol file and executable loaded.
    - `info line`: Shows the current source line and associated machine instructions.
    - `info address <symbol>`: Shows the memory address of a symbol (function or variable). `ex: info address main`
    - `info symbol <address>`: Shows which symbol (if any) is at the given memory address. `ex: info symbol 0x8002136`
  - `d`: Delete all breakpoints
  - `d loop`: Delete loop() breakpoint
  - `c`: Continue execution (Press Ctrl+C to exit execution)
  - `s`: or `step` (Step In) executes the next line of source code, entering any function calls encountered
  - `fin`: or `finish` (Step Out) executes the prev line of source code, out from any function calls encountered
  - `n`: or `next`  (Step Over) executes the next line of source code without entering any function calls encountered
  - `where`: Show the next statement that will be executed
  - `p [variable_name]`: (Print Variable) Print the value of a variable, No matter if the variable is a buffer, it prints the whole buffer.
  - `x`: Displays the memory contents at a given address using the specified format.
    - x <`Address_Expression`>
    - x /[`Format`] <`Address_Expression`>
    - x /[`Length`] [`Format`] <`Address_Expression`>
    - x/[`Length`] [`Format`] [`Size`] <`Address_Expression`>
      - `x` = examine memory
      - `Length` = how many items to display
      - `Format` = how to display them (char, hex, int, etc.)
      - `Size` = how big each item is (byte, word, etc.)
      - `Address_Expression` = the memory address or variable name you want to inspect
    - <b>✅ Examples :</b></br>
      - `x/10cb buf`: View 10 bytes at address `buf` as chars
      - `x/16dw some_array`: View 16 integers at address `some_array`
      - `x/8xb 0x20000000`: View memory at an address in hex
      - `x/5i main`: Disassemble 5 instructions at `main`
  - `dump`: writes the memory between the two addresses to a binary file.
    - dump <`type`> <`filename`> <`args`>
      -  Where <`type`> is one of the following:
         - `memory`: Dumps raw memory to a binary file
         - `binary`: Alias for memory
         - `i`:	Dumps instructions (disassembly)
         - `s`:	Dumps a string
         - `value`:	Dumps the value of a variable/expression
    - <b>✅ Examples :</b></br>
      - ✅ Dumping Memory:
        - dump memory <`filename`> <`start-address`> <`end-address`>
        - dump memory buf_dump.bin 0x20000000 0x20000064
        - dump memory buf_dump.bin buf buf+10
      - 🧠 Dump Disassembly:
        - dump i asm my_asm.txt main main+100
      - 📄 Dump a String:
        - dump s my_string.txt buf
      - 🧪 Dump a Value:
        - dump value var_dump.txt varname
  - `if`: use `if` statements inside GDB to run commands conditionally.
    - <b>✅ Basic if Syntax in GDB:</b> You can include multiple commands between the `if` and `end`.
    ```
    if <condition>
      <commands>
    end
    ```
    - <b>✅ Conditional Print:</b>
    ```
    if buf[0] == 'A'
      print "buf starts with A"
    end
    ```
    - <b>✅ Checking a variable:</b> else is allowed too, but else if is not (just nest another if block inside). ⚠️
    ```
    if state == 1
      print "LED is ON"
    else
      print "LED is OFF"
    end
    ```
    - <b>✅ Conditional Breakpoint Commands:</b> You can also attach conditions to breakpoint commands
    ```
    break loop
    commands
      if state == 1
          print "State is 1"
      end
    end
    ```
    - <b>🛠 GDB Conditional Breakpoints (Alternative):</b> If you just want to stop only when a condition is true
    ```
    break loop if state == 1
          or
    break main.c:6 if i == 5
    ```
  - `list`: Displays the next 10 lines of source code (starting from the beginning, or where the last list command left off).
    - `list main`: Lists the first 10 lines of the `main` function.
    - `list 25`: Lists 10 lines centered around line 25 (i.e. lines 20–29).
    - `list 30,40`: Lists lines 30 through 40.
    - `list myfile.c:50`: Lists lines around line 50 in `myfile.c`.
    - <b>Shortcut</b>: keep typing `list` or just press `Enter` after using `list` once to continue listing the next lines.
  - `watch <expression>`: is used to monitor the value of a variable and stop execution when it changes. This is different from a breakpoint, which stops execution when a specific line of code is reached.
    - `watch x`: This stops the program whenever the value of variable `x` is modified.
    - `info watchpoints`: Lists all active watchpoints.
    - `delete <n>`: Deletes watchpoint number `n`.
    - `disable <n>`: Disables watchpoint `n` without deleting it.
    - `enable <n>`: Enables a previously disabled watchpoint.
    - <b>Types of Watchpoints</b>:
      - `watch`: Triggers when the expression is `written to`.
      - `rwatch`: Triggers when the expression is `read`.
      - `awatch`: Triggers when the expression is `either read` or `written`.
  - `q`: quit gdb

## Here are some commonly used OpenOCD commands:
1. **help**: Displays a list of available commands and their descriptions.
   
2. **init**: Initializes OpenOCD.

3. **targets**: Lists the available targets on the connected hardware.

4. **reset**: Resets the target device.

5. **halt**: Halts the execution of the target device.

6. **resume**: Resumes the execution of the target device.

7. **flash write**: Writes data to the flash memory of the target device.

8. **flash erase**: Erases a specified region of the flash memory.

9. **flash protect**: Sets or clears the protection on flash sectors.

10. **program**: Programs the target device with a specified file.

11. **verify**: Verifies the programming of the target device against a specified file.

12. **gdb_port**: Sets the port for GDB (GNU Debugger) connection.

13. **jtag scan_chain**: Scans the JTAG chain and displays the detected devices.

14. **jtag newtap**: Creates a new JTAG tap.

15. **jtag_rclk**: Sets the JTAG RCLK frequency.

16. **adapter_khz**: Sets the JTAG adapter speed.

17. **transport select**: Selects the transport used to communicate with the target device (e.g., jtag, swd).

18. **poll off/on**: Turns on or off the target state polling.

19. **reset_config srst_only/none/hard/hard_and_srst**: Configures the reset behavior.

20. **adapter driver**: Sets the JTAG adapter driver.

## Silicon Labs Debugging with J-Link

This section outlines the use of SEGGER's J-Link GDB Server for debugging Silicon Labs devices.

<img src="https://github.com/shuvabratadey/baremetal_openocd_and_gdb/blob/main/Pictures/si917.avif" width="500"/></br>

### Starting J-Link GDB Server
You can start the J-Link GDB server using the command below. Adjust `<DeviceName>`, `<Interface>`, `<Speed>`, and `<PortNumber>` to match your setup:

```bash
JLinkGDBServerCL -device <DeviceName> -if <Interface> -speed <Speed> -port <PortNumber>
```

### Example: Launching GDB Server for a Silicon Labs Device
```bash
JLinkGDBServerCL -select usb=440285686 -if swd -device siwg917m111mgtba -endian little -speed 1000 -port 2331 -swoport 2332 -telnetport 2333 -ir -localhostonly 1 -log C:\SiliconLabs\SimplicityStudio\v5\developer\adapter_packs\exx32\gdb_20250417_131058.log -singlerun -strict -timeout 0 -nogui
```

- `-select usb=440285686`: Select the connected J-Link by USB serial number  
- `-if swd`: Use SWD interface  
- `-device siwg917m111mgtba`: Silicon Labs device  
- `-speed 1000`: Set debug speed to 1000 kHz  
- `-port 2331`: GDB server port  
- `-swoport 2332`: SWO port (optional)  
- `-telnetport 2333`: Telnet port  
- `-log`: Specifies log output path  
- `-singlerun`: GDB server exits after a single session  
- `-strict -timeout 0 -nogui`: Additional options for headless operation

### Launching GDB and Connecting to the Target
After starting the GDB server, run the following from the directory where your build output resides:

```bash
arm-none-eabi-gdb <program_name>.axf
```

Then, within GDB, connect to the running J-Link server:
```gdb
target remote localhost:2331
```

Once connected, you can proceed with standard GDB debugging operations (e.g., `b`, `c`, `s`, `n`, `info`, `print`, etc.).

----------------------------------------------------------------------------
> [!NOTE]
> ## For Changing the configuration of stm32 board for chinese blue-pill module:
1. After installing openocd, open cmd and type 🠊 ```"where openocd"```

2. Go to this openocd location and search for 🠊 ```\share\openocd\scripts\target\stm32f1x.cfg```</br>
**Exaple:** ```C:\Users\{user_name}\.espressif\tools\openocd-esp32\v0.12.0-esp32-20230419\openocd-esp32\share\openocd\scripts\target\stm32f1x.cfg```

3. Change the line no 44 from ```"0x1ba01477"``` to ```"0x2ba01477"```  From this ```set _CPUTAPID 0x1ba01477``` to ```set _CPUTAPID 0x2ba01477``` [Or make it '0' so it will not check any chip-id].
