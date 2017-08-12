# CMDLINE

Library for parsing command line arguments

## Version

Now **stable** version is _1.0_

## Use

For use in main file include one file _cmdline.hpp_

CMDLINE use namespace cmdline. 

For add commands for parsing try this:
```c++
cmdline::add('c', "config");
```

##### Arguments
- 'c' - short name of command (in v 1.0 use for write in cmd) [-YOUR_SHORT_NAME_HERE=...]
- "config" - full name of command (*not realised yes*) [--YOUR_FULL_NAME_HERE=...]

Before this, you need, to make start parsing arguments.
This this:
```c++
cmdline::CMDLINE cmdArgs(argc, argv);
```

##### Arguments
- argc - count argc [int]
- argv - arguments of cmd [char *]

For getting arguments try this:
```c++
cmdArgs.getString("config");
```

##### Arguments
- "config" - full name of your command

{You can also use getString by short name}
```c++ 
cmdArgs.getString('c');
```

##### Arguments
- 'c' - short name of your command
-