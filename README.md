# SIMPLE CALENDAR

<br>

## Welcome to the Simple Calendar project!

This program is designed to help you manage deadlines in a minimalist way.
It comes with features such as creating new deadlines, deleting and editing existing ones, and marking them as finished or unfinished.
Additionally, it includes a countdown feature based on the current time to keep track of upcoming deadlines.

<br>

## How to install Simple Calendar on Windows:

1. Create a local repository and give it a name, such as SimpleCalendar.
2. Download the executable file (SimpleCalendar.exe) to the SimpleCalendar directory.
3. Try to run SimpleCalendar.exe file.
4. Windows Defender may try to shut it down. If this happens, allow the executable file to run on your machine.

<br>

## How to install Simple Calendar on Linux:

### Easy method
1. Create a local repository and give it a name, such as SimpleCalendar.
2. Download the executable file (SimpleCalendar.exe) to the SimpleCalendar directory.
3. Try to run the executable file.
4. If needed, allow the executable file to run on your machine.

### Alternative method
1. Clone the repository to your machine.
2. Compile the source code with GCC.
3. Run the program.

You can use the following commands in the terminal:

```bash
      sudo apt update                                           # make your system up to date
      sudo apt install gcc                                      # probaly understandable
      gcc --version                                             # check if gcc is available
      gcc main.c functions.c -i icon.o -o SimpleCalendar        # make sure that you are not compiling a virus
      .\SimpleCalendar                                          # run the program and enjoy your life
```

<br>

## Usage
### Here are the commands to the program:

```c
    h   or         help       // Print out the possible commands.
    n   or          new       // Add a new deadline.
    d   or       delete       // Delete a new deadline.
    o   or           ok       // Mark a deadline as finished.
   ic   or   incomplete       // Mark a deadline as incomplete.
    e   or         edit       // Edit a deadline.
   ls   or         list       // List remaining tasks.
  als   or        alist       // List all deadlines.
   cd   or    countdown       // Display a countdown of remaining tasks.
  acd   or   acountdown       // Display a countdown of all deadlines.
    c   or        clear       // Cleares the console so you never will get lost on the screen.
    s   or         save       // Saves deadlines in a local binary file.
   ex   or         exit       // Exit the program.
```
