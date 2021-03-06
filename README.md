# modularOS 

> A bootstrap framework for OS Development

You need linux and the following:

	apt-get install gcc
	apt-get install nasm
	apt-get install xorriso
	apt-get install grub
	apt-get install qemu

To compile & emulate your kernel (found in Build/)
```sh
git clone https://github.com/carlosascari/modularOS.git
cd modularOS/
chmod +x Start.sh
./Start.sh
```

I suddently felt like jumping into OS dev after watching [Julia Evans](
https://www.youtube.com/watch?v=0IQlpFWTFbM) video, this wasn't the first time I tried. Theres something about OS development that leaves it so cryptic in plain sight, that after a while of reading, you simply feel there is no visible end, like staring up next to a sky scraper, the view is daunting.

Furthermore, there is a visible difference in documentation for higher level programming, such as PHP, angular.js, Twitter Bootstrap, Go, Node.js, etc. There is a much richer developer experience, in reading from theses APIs. The world of OS dev, wich goes hand in hand with linux and driver development, generally does not offer the same cozy experience.

> OS development is easy, practical OS development is hard..
> lets not be practical ... maybe a little.

[modularOS](https://github.com/carlosascari/modularOS.git) is a DIY OS framework focusing on clean and easy to digest, code and documentation. The kernel will be kept small in code size and complexity. Also, an api and pattern will be presented, so as to keep everyones contribution consistent.

### Overview

**Start.sh**
Bash script that compiles the kernel and creates a bootable ISO with grub, then emulates the bootable ISO with qemu. You should take a look.

**Build/**
This is where your bootable ISO will be created.

**Source/**
This is the source code folder for the modularOS kernel and kernel modules. Inside you will find:

- **Kernel.s**
The entry point for the kernel, it has to be in assembly since we have to write a [multiboot](http://www.gnu.org/software/grub/manual/multiboot/multiboot.html#OS-image-format) header, which grub uses to find your operating system's entry point. This module simply calls `KernelMain()`, found in `Kernel.c`.
It was written for NASM assembler.

- **Kernel.c**
This is your kernel. May the force be with you.

- **Linker.ld**
This is a linker file that is used to specify the layout of the kernel code. Executable, Writeable and Read Only code is generally sectioned into their own chunks of data.
This file will help you tweak how your binary (kernel.bin) will organize its raw data. You don't need to edit this file, and you should read up on linker scripts before fiddleling.
**BTW** The kernel entry point, which is the `main` label (which is also the binary offset) found in `Kernel.s` is specified here, in case you want to change it. 

-----------------

## Lets talk about the kernel modules

Checkout `lib/modules/*.h` and `.c` counterparts.

Awesome, now I get to explain how the module pattern works.

A single kernel module is made up of at least two files:

1. A header (.h) file
2. A c lang (.c) file

both, MUST have the same name. e.g see `lib/modules/string.h` and `lib/modules/string.c`

### Header File Pattern

```h 
#ifndef STRING_H
#define STRING_H

#include "types.h"

typedef struct __String
{
    uint16 (*length)(string);
} _String;

extern _String String;

static uint16 length(string);

#endif
```

1. `#ifndef`, `#define` and `#endif` guards are required.
This because since each module is compiled to a relocatable object file, everytime there is a `#include "<HEADER_FILE>"`, the linker tries to basically copy and paste the header code in each module that references it, and thus defines it more than once. This way, they are only defined once.

2. `static <FUNCTION_PROTOTYPE>;`
C-lang has no notion of private variables, but that doesnt mean we can't shim up some modularity here. Every function that is defined here SHOULD use the `static` keyword, this locks the method's scope to File Scope, or the module itself, otherwise functions defined will be global scoped.


2. `typedef struct __MODULE_NAME { ..exposed methods.. } _MODULE_NAME;`
`extern _MODULE_NAME MODULE_NAME;`
That my friend, is you defining an object in C, congratulations.
The `extern` keyword is required so the Object is only initialized once. It gets defined here, and initialized in its `.c` counterpart.
**Function Pointers**
In `lib/modules/string.h`
You will find that the contents of the module is a single **function pointer**, that is, a pointer of type: *function with one argument of type string and return of type uint16*.
```c
uint16 (*length)(string);
```
It is a pointer for the private method `length`, whose prototype is defined as:
```c
static uint16 length(string);
```
Notice the similarities between the function prototype and the function pointer. They MUST have the same number and type of arguments and return type.
In this case `length` is the name of the function as well as the property name of the method that will be exposed by the module `String`. You can change the name of the property if you want.

### C File Pattern

```c
#include "string.h"

_String String = {
    .length = length
};

uint16 length(string character)
{
    uint16 i = 1;
    while(character[i++]);  
    return --i;
}

```

1. `_MODULE_NAME MODULE_NAME = { .. exposed methods/properties .. };`
Here our module object is initialized, using the *designated initializer* way, which simply means we specify the property name of the variable being initialized, as oppose to [other ways of initializing a struct](http://en.cppreference.com/w/c/language/struct_initialization). The `.<METHOD NAME>` is defined in the `.h` file counterpart, and the value set is the private function defined in the same file, `length` in this case.

### Using a kernel module

The kernel main (kernel.c), shows an example of using a module, the `Screen` module in particular. 

Like nodejs' `require()`, we include a module using the `#include` directive. Unlike nodejs, the module is included at compile time, becoming one with your kernel. Also, the module and any modules the module `#includes` is also exposed, globally. I'll explain

Take `lib/kernel.c` for example.

```c
#ifndef KERNEL_C
#define KERNEL_C

#include "modules/screen.h"

kmain()
{
	String.length("hello");
	Screen.clear();
	Screen.print("modularOS");
	// ...
}

#endif
```

1. `#include "modules/screen.h"` exposes the `Screen` object, however since the Screen module header file references `#include "modules/string.h"` in its header, the `String` object is also exposed globally.
This is unfortunate, since it leaks unexpected variables onto the global scope, however one Module instance is better than exposing all functions defined, in the c-world, this is plenty good enough IMO without adding more complexity.

> Keep in mind that any module that gets compiled along your kernel, will have its module Object exposed globally.


-----------------

## Code Style

> Object Oriented C, inspired by nodejs modules

- Filenames are upper CamelCase.
- Modules are upper CamelCase.
- Submodules (namespaces) are upper CamelCase
- Module properties are lower camelCase 
- Module methods are lower camelCase 
- Types and Typedefs are upper CamelCase.
- Constants are ALL_UPPER_CASE.
- API functions are upper CamelCase
- Static variables are upper CamelCase
- Static methods are upper CamelCase
- Global variables are upper CamelCase
- Local variables are lower camelCase

Modules are either:
	- Class where multiple instances can be created
	- Singleton that may initialize with a method named `initialize`

The idea is to work in a low level enviroment using methodlogies usually found in higher level enviroments.
A PrivateKernelMemory is reserved inside the kernel (~8Kb) to be used to instanciate modules that are classes.

*See /Source/Modules for examples*

## Sources 

[OS Dev Wiki](http://http://wiki.osdev.org)
[IKnow Channel](https://www.youtube.com/channel/UCofr5KcAmI_CB_tCYpVzZEw)

## LICENSE 

MIT

