# SeaBattle project

**NEED TO CHECKING ON BOTH SYSTEMS AND SCRIPTS**

To **build** a project you need to run this command (for Linux):

```bash
cd scripts
sh build.sh
```

This command run cmake with arguments, and use make in build directory.

To run a program, go to build and run this commands:

```bash
cd ..
./build/bin/seabattle.out
```

You can pass arguments to the program

To clear build run this command:

```bash
sh clean_build.sh
```