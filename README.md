# Debugger Commands

**Table of Content**

* [**Help command**](#help-command)
* [**!analyze -v command**](#!analyze-v-command)
* [**Sympath command**](#sympath-command)
* [**Setting symbol path**](#setting-symbol-path)
* [**Debugger extensions**](#debugger-extensions)
* [**x command**](#x-command)
* [**ln command**](#ln-command)
* [**r command**](#r-command)
* [**k command**](#k-command)
* [**e command**](#e-command)
* [**u command**](#u-command)
* [**dc command**](#dc-command)
* [**dt command**](#dt-command)
* [**dv command**](#dv-command)
* [**'s' command**](#'s'-command)
* [**bp command**](#bp-command)
* [**t command**](#t-command)
* [**p command**](#p-command)
* [**gu command**](#gu-command)
* [**wt command**](#wt-command)
* [**.logopen command**](#t,p,.logopen-command)
* [**ChildEBP,retAddr,argstochild**](#childebp,retaddr,argstochild)
* [**Address Range**](#address-range)
* [**pipe command**](#pipe-command)
* [**version,vertarget commands**](#version,vertarget-commands)

## **Help command**

The Help command has the information about other commands.

we can launch help content in two ways.

**1. By clicking on help button.**

* Launch windbg application and select Local help button ,opens the Debugging Tools for Windows documentation.

![Windbg-Intro](image/img1.PNG)

* If you specify Text, the debugger opens the Index panel in the documentation and searches for Text as a keyword in the index.

![Windbg-Intro](image/img2.PNG)

**2. By .hh command**

* To use `.hh` command , Attach an notepad process to the debug(to attach notepad launch the notepad first).

* Click on File -> Attach to process -> notepad.exe -> attach 

![Windbg-Intro](image/img3.PNG)

* use `.hh` command to open the Debugging Tools for Windows documentation.

```markdown
.hh
```

![Windbg-Intro](image/img4.PNG)

* If you specify Text, the debugger opens the Index panel in the documentation and searches for Text as a keyword in the index.

![Windbg-Intro](image/img2.PNG)

**Example:**

```text
 Attach Process: 
        load notepad example

    > .hh
        Debugging Tools for Windows documentation

    > qd
        detach the process

```

## **!analyze -v command**

[click here for reference program](https://github.com/PadmanabhanSaravanan/windbg_Intro/tree/master/HelloWorld)

The `!analyze -v` command in WinDbg is a powerful automated debugging command that performs an analysis of the current state of the program being debugged, typically after an exception or crash.

```markdown
!analyze -v
```

Here's a breakdown of the command:

* **!analyze**: This is the basic automated analysis command. It performs an initial analysis of the state of the program.
* **-v**: This is an option that stands for "verbose". When you use -v with !analyze, the command provides more detailed output.

In the context of crash dump analysis, !analyze -v is often the first command you'd run after loading the crash dump.

![Windbg-Intro](image/img7.PNG)

**1. The first thing you see is a statistics of the debugging session**

![Windbg-Intro](image/img8.PNG)

**2. Global flag, a debugging flag which is associated with the user**

![Windbg-Intro](image/img9.PNG)

**3. Some of the debugging related information comes here**

![Windbg-Intro](image/img10.PNG)

**4. Exception record gives you information about the exception which has occurred**

![Windbg-Intro](image/img11.PNG)

**5. Thread ID of the faulting thread and exception code**

![Windbg-Intro](image/img12.PNG)

**6. Call stack gives you the picture of how the code path reached the exception point**

![Windbg-Intro](image/img13.PNG)

**Example:**

```text
open executable:
    open helloworld executable(.exe)

    > g
        continue and we have a breakpoint.

    > !analyze -v
        performs an analysis of the current state.

    > ~0s ; .cxr ; kb  (stack command.)
         ~0s switching the thread to zero thread.
         .cxr setting the context to exception context.
         kb call stack command

    > .dump /ma pathofdump
        take dump of the application
        /ma full dump
        pathofdump example "c:\path_to_dmp_file\abc.dmp"

    > qd 
        detach the executable.

    > attach dump 
            open the crash dump from the file path it is saved.

    > lm 
        list of modules.

    > !analyze -v 
        performs an analysis of the current state of the dump.

    > qd 
        detach the dump.
```

## **Sympath command**

The sympath command in WinDbg is used to display or set the symbol file path for the debugger. The symbol path tells the debugger where to find the symbol files (.pdb files) that correspond to the executable files (.exe, .dll files) that you are debugging.

1. **`.sympath` -> To display the current symbol path**

```markdown
.sympath
```

![Windbg-Intro](image/img14.PNG)

2. **.sympath, say "C:/temp" , it will set the symbol path to "C:/temp".**

* `.sympath "C:/temp"`

```markdown
.sympath "C:/temp"
```

![Windbg-Intro](image/img15.PNG)

3. **again check symbol path it will be set to c:/temp**

![Windbg-Intro](image/img16.PNG)

Example:

```text
attach dump 
    open the crash dump from the file path it is saved.

    > .symapath 
        To display the current symbol path

    > .sympath "C:/temp"
        set the symbol path to "C:/temp"

    > .sympath
        check the symbol is set to the defined path

    > qd 
        detach the dump
```

## **Setting symbol path**

* Open a execuatble file, file -> launch executable -> select the .exe file -> open.

![Windbg-Intro](image/img5.PNG)

* `lm` command -> loaded modules, if we check the module has a pdb symbol and the symbol is present in this particular path.

![Windbg-Intro](image/img6.PNG)

* take a copy **.pdb** file and save it for further reference

* next we will **rename .pdb file** from the project and **delete the cache** from the mentioned module path. i.e., **C:\ProgramData\Dbg\sym\HelloWorld.pdb\09F43444E582442E929DEDF81F87033D6\HelloWorld.pdb**

* now check the modules the symbol folder will not be loaded.

![Windbg-Intro](image/img50.PNG)

* To load the symbol file,create new folder in project named cssym(custom symbol path).

![Windbg-Intro](image/img49.PNG)

* paste the .pdb file in cssym folder ,which was copied before.

![Windbg-Intro](image/img51.PNG)

* copy the file path were .pdb file is pasted and load the sympath and use lm command to check symbols are loaded.

```markdown
.sympath srv*;D:\StudentRequest_ForDren\WindbgIntro\HelloWorld\cssym
```

![Windbg-Intro](image/img52.PNG)

**Note**

Executable file and symbol file time stamp should be same.

**Example:**

```text
open executable:
    open helloworld executable(.exe)

    > g
        continue and we have a breakpoint

    > lm 
        loaded modules(scroll to left we cans see the symbols present and it's path)

    > .hh 
        - open windbg documentation in index search msdl
        - you can see where default cache symbol path will be stored

    > .sympath 
        you can see where default cache is coming from

    > qd 
        detach the executable.

    > go to the project folder and rename the symbol file(.pdb) , before renaming take a copy of the file.
            symbol file will be present where executable file is present.

    > delete the cache 
            - take the file path from the loaded module and delete the symbol file.

open executable:
    open helloworld executable(.exe)

    > g
        continue and we have a breakpoint

    > k 
        list of call stack (we cannot see any function names)

    > lm 
        loaded modules(scroll to left we cannot see symbols present)

    > qd 
        detach the executable.

    > create a file name cssym(custom symbol path) to the project.

    > paste the symbol file(.pdb) to the cssym folder.

open executable:
    open helloworld executable(.exe)

    > g
        continue and we have a breakpoint

    > .sympath srv*;path of symbol
        srv* the debugger uses a symbol server to get symbols from the default symbol store.
        path of symbol C:/helloworld/cssym

    > lm 
        loaded modules(scroll to left we cans see the symbols present and it's path)
        defered means it has not tried to load the symbols
        no symbols means that it tried to load the symbols and it didn't get the symbols
     
    > lmvm HelloWorld
        we can see whether the symbols are there or not.

    > qd 
        detach the executable.
```

## **Debugger extensions**

Debugger extensions in WinDbg are powerful tools that can extend the basic capabilities of the debugger. They provide additional commands and utilities for specific debugging tasks.

Extensions are plugins to the Debugger, so they add functionality to the Debugger or the base functionality is extended using the Extension commands.

**.chain command**

* The `.chain` command in WinDbg displays the list of all loaded debugger extensions. When you issue this command, WinDbg will show you a list of all debugger extensions that have been loaded into the current debugging session, including their load addresses and versions.

```markdown
.chain
```

![Windbg-Intro](image/img17.PNG)

**.load command**

* To load an extension in WinDbg, you can use the .load command, followed by the path to the extension DLL. For example, to load the SOS extension.

```markdown
.load C:\Windows\Microsoft.NET\Framework\v4.0.30319\SOS.dll
```

* check the extension file loaded using `.chain` command.

![Windbg-Intro](image/img18.PNG)

**.unload command**

The .unload command in WinDbg is used to unload a debugger extension DLL.

```markdown
.unload C:\Windows\Microsoft.NET\Framework\v4.0.30319\SOS.dl
```

![Windbg-Intro](image/img48.PNG)

**Example:**

```text
open executable:
    open helloworld executable(.exe)

    > .chain
        current extensions loaded

    > .load C:\Windows\Microsoft.NET\Framework\v4.0.30319\SOS.dll
        - C:\Windows\Microsoft.NET\Framework\v4.0.30319\SOS.dll - .NET installation path

    > .chain 
        we can see the .NET extension loaded

    > !help 
        it will show you the latest loaded extensions

    > !sos.help
        it will also show the extension details

    > .extmatch /D /e dbghelp *
        These are the different commands which are available in the debug Help extension
        - in the list of loaded extensions, click on the extension you can see the different commands which are available.
    
    > .unload C:\Windows\Microsoft.NET\Framework\v4.0.30319\SOS.dl
        unload the extension

    > .chain
        to check whether extension is unloaded.

    > qd 
        detach the executable.
```

## **x command**

* The x command is used to display symbols that match a specific pattern. 

* It has the following syntax:

```markdown
x [Options] Module!Symbol
```

```markdown
x HelloWorld!*main*
```

![Windbg-Intro](image/img19.PNG)

**Note**

```text
If commands not executing properly or symbols files not loaded then to do this setting in visual studio
            open project - right click on project - properties - linker - debugging - Generate debug info - Generate debug information optimized for sharing and pulishing

```

**Example:**

```text
open executable:
    open helloworld executable(.exe)

    > g 
        continue and we have a breakpoint

    > x HelloWorld!*main*
        it'll give you addresses of the matched symbols.
        HelloWorld - name of the binary.
        *main* - display main function inside the binary

    > lm 
        load modules 
        all these addresses are in this particular range of the binary

    > bp HelloWorld!wmain
        breakpoint
        we can put breakpoints from address which are listed

    > x HelloWorld!?main
        This will give a little more fine grained result

    > qd 
        detach the executable
```

## **ln command**

* The ln command is used to display the symbol nearest to a given address. It is typically used to determine what code or data is at a particular address. 

* It has the following syntax:

```markdown
ln [Address]
```

![Windbg-Intro](image/img20.PNG)

**Example:**

```text
open executable:
    open helloworld executable(.exe)

    > g 
        continue and we have a breakpoint

    > lm 
        loaded modules

    > x HelloWorld!?main
        This will give a little more fine grained result

    > ln address
        address from the main 

    > qd 
        detach the executable
```

## **r command**

* The r command in WinDbg is used to display or modify the contents of registers. 

* It has the following syntax:

```markdown
r [Register [= [Expression]]]
```

**The command can be used in several ways:**

**1. Display all registers:**

* If you use the `r` command without any arguments, it displays the contents of all registers.

* This command will show the contents of all the registers for the current thread, including general-purpose registers, segment registers, flags, instruction pointer, and more.

```markdown
r
```

![Windbg-Intro](image/img21.PNG)

**2. Display a specific register**: 

* You can use the r command followed by a register name to display the contents of a specific register. For example, to view the contents of the eax register.

```markdown
r eax
```

![Windbg-Intro](image/img22.PNG)

**3. Modify a register:** 

* You can also use the r command to modify the contents of a register. To do this, you provide the register name followed by the new value. For example, to set the eax register to 0.

```markdown
r eax = 0
```

![Windbg-Intro](image/img23.PNG)


The `~*r` command in WinDbg displays the register context for all threads in the system.

```markdown
~*r
```

**Example:**

```text
open executable:
    open helloworld executable(.exe)

    > g 
        continue and we have a breakpoint

    > r 
         displays the contents of all registers

    > r eax
        view the contents of the eax register

    > r eax = 0
        modify the contents of a register

    > .hh r
        documentaion of the register
    
    > ~
        all the thread

    > ~1s 
        switch to the thread number 1

    > r
        different set of registers because the thread context has changed

    > ~*r 
        displays the register context for all threads in the system

    > qd 
        detach the executable
```

## **k command**

* The k command in WinDbg displays a stack trace of the current thread. It shows the sequence of function calls that the thread has made up to the point where it currently is.

```markdown
k
```

![Windbg-Intro](image/img24.PNG)

* The `.frame` command in WinDbg is used to set or display the current local context to a specific frame number.

```markdown
.frame <frame-number> ;dv
```

![Windbg-Intro](image/img25.PNG)

* `kvn` this command will show you the arguments to the child as well.

```markdown
kvn
```

![Windbg-Intro](image/img26.PNG)

* `kf` this command will show you the memory offset size for each frame.

```markdown
kf
```

![Windbg-Intro](image/img27.PNG)

* `~*k` command in WinDbg displays a stack trace for all threads in the system.

```markdown
~*k
```

**Example:**

```text
open executable:
    open helloworld executable(.exe)

    > g 
        continue and we have a breakpoint

    > k
        list of call stack of current thread

    > ~1s 
        switch to the thread number 1

    > k 
        list of call stack of thread 1

    > click on the dml that is frame number
        displays local variable

    >.frame 05;dv
        .frame 05 select the frame number
        dv - displays local variable

    >.frame 05;dv /V
        /V - gives more information about the stack

    > kvn 
        show you the arguments to the child as well

    > kf 
        show you the memory offset size for each frame

    > .hh k
        documentation of k command

    > ~*k
        displays a stack trace for all threads in the system

    > qd 
        detach the executable
```

## **e command**

The `e` command in WinDbg is used to enter values into memory at a specified location. It has the following syntax:

```markdown
e[d|q|p|a|u|f] [Address] [List]
```

-> e is the basic command for entering values into memory. By itself, e enters 4-byte hexadecimal values.

-> The optional character after e specifies the format of the data to enter:

* d enters 4-byte decimal integers.
* q enters 8-byte hexadecimal integers.
* p enters a pointer value.
* a enters an ASCII string.
* u enters a Unicode (UTF-16) string.
* f enters floating-point values.

-> Address is the memory location where you want to start entering data.

-> List is the data you want to enter, separated by spaces. The data should be in the format specified by the character after e.

**Example:**

* setting breakpoint in mytest function

```markdown
bp helloworld!MyTestFunc
```

* use `g` command to continue and it breaks at the breakpoint and step into the printf line.

![Windbg-Intro](image/img28.PNG)

* use `k` command to view the particular stack frame.

![Windbg-Intro](image/img29.PNG)

* click frame number 00 you can see there the string is helloworld.

![Windbg-Intro](image/img31.PNG)

* now i'm changing hello string to jack using `e` command

```markdown
ea 0x008eee58 "jack"
```

* and use the previous command to check it is edited.

![Windbg-Intro](image/img30.PNG)

```text
open executable:
    open helloworld executable(.exe)

    > bp helloworld!MyTestFunc
        setting break point on MyTestFunc

    > g 
        continue and we have a breakpoint

    > p
        step over

    > k 
        stack frame

    > click frame number 00 you can see there the string is hello world and it's address

    > ea address "jack"
        ea edit ascii
        address - address of the string helloworld
        "jack" editing hello world to jacko world

    > again click frame number 00 you can see there the string as been changed to jacko world.

    > g 
        continue you see in console jacko world

    > .hh e
        documentation on edit memory

    > qd 
        detach the executable
```

## **u command** 

The u command in WinDbg is used to disassemble and display a range of memory as CPU instructions (i.e., assembly code). This command is typically used to inspect the instructions that a program will execute.

![Windbg-Intro](image/img32.PNG) 

**ub command:**

The ub command in WinDbg is used to disassemble and display a range of memory as CPU instructions in reverse order. The command stands for "unassemble backward".

![Windbg-Intro](image/img33.PNG)

**uf command**

The uf command in WinDbg is used to disassemble and display a complete function in assembly language. This command stands for "unassemble function".

![Windbg-Intro](image/img34.PNG)

```text
open executable:
    open helloworld executable(.exe)

    > g 
        continue and we have a breakpoint

    > u 
        assemble a bunch of instructions starting from the current eip

    > r
        check whether it is starting from current eip

    > u address L20
        address - specify the address from the u command
        L value argument
        20 means 20 dwords , dwords*4 = 80 bytes

    > ub address L20
        displays in backward

    > uf HelloWorld!wmain
        HelloWorld!wmain - function
        assembly instruction for that particular function

    > uf /c HelloWorld!wmain
        /c it will show you all the call outs

    > qd 
        detach the executable
```

## **dc command**

The **dc command** in WinDbg is used to display memory in a formatted view. The dc command stands for "Display Memory as Double Words with ASCII characters". Double words are 4 bytes long, so each line of the output shows a sequence of double words, and also their ASCII interpretations.

```markdown
dc <Address>
```

![Windbg-Intro](image/img35.PNG)

**dps command**

The dps command in WinDbg is used to display memory, interpret data as both symbols and hexadecimal values, and display the resulting ASCII strings. The dps command stands for "Display Pointer-sized values with Symbols".

![Windbg-Intro](image/img37.PNG)

**Example:**

```text
open executable:
    open helloworld executable(.exe)

    > g 
        continue and we have a breakpoint

    > dc address
        address - specify address where you need to display memory

    > dc staring_address end_address
        displays memory between staring_address & end_address

    > dc address L20
        L20 - 20 means 20 dwords , dwords*4 = 80 bytes.

    > dv 
        local variable 

    > dc address
        address - local variable string address
        you can see the ascii value

    > db address
        address - local variable string address
        it will show information in bytes

    > dps address
        it will show you the pointer sized value of the address with symbols

    > !teb 
        displays stack limit and stack base

    > dps stackbase stacklimit
        raw dumping of the stack

    > qd 
        detach the executable
```

## **dt command**

[click here for reference program](https://github.com/PadmanabhanSaravanan/windbg_Intro/tree/master/Structdt)

The dt command in WinDbg is used to display type information, which includes the structure of data types and the values of variables or data structures. This command is especially useful for inspecting complex data types like structures, unions, classes, and so on.

![Windbg-Intro](image/img38.PNG)

![Windbg-Intro](image/img39.PNG)

**Recursive Dumping**

The term "recursive dumping" in WinDbg refers to the process of inspecting or displaying the contents of complex data structures that may include other nested data structures. This process involves not just displaying the top-level structure, but also displaying the contents of any nested structures.

**Example:**

```text
open executable:
    open structdt executable(.exe)

    > g 
        continue and we have a breakpoint

    > dv 
        display local variables

    > click on mystr
         It evaluates expressions and displays the results in a variety of formats

    > dt kcmd!MY_STRUCT
        display the type information

    > dt kcmd!MY_STRUCT address
        address - pmystr address(information from dv)

    > !peb
        process environment block
        The PEB is a data structure in the Windows operating system that contains data related to the executable image of a process, such as its image base address, command line, start-up information, data structures for the program's image loader, and more.

    > dt address ntdll!_PEB
        address - address from !peb (mentioned in first line)
        ntdll!_PEB - Process Environment Block (PEB) data structure in the ntdll

    > dt -r4 address ntdll!_PEB
        -r recursively displaying nested structures
        4 - 4 level deep recursive dumping

    > qd 
        detach the executable
```

## **dv command**

[click here for reference program](https://github.com/PadmanabhanSaravanan/windbg_Intro/tree/master/StackFrame)

The dv command in WinDbg is used to display local variables and their values for the current function in the call stack.

![Windbg-Intro](image/img36.PNG)

**Example:**

```text
open executable:
    open stackframe executable(.exe)

    > g
        continue and we have a breakpoint

    > k 
        list of call stack frames

    > .frame 03
        switch into that particular frame

    > dv /V 
        we can see all the required information

    > qd 
        detach the executable
```

## **'s' command**

The s command in WinDbg is used to search memory in a range of addresses for a pattern.

The command has the following syntax

```markdown
s [-[w|d|q|a|u|f]] Range Pattern
```

* -w specifies 2-byte word values.
* -d specifies 4-byte double word values.
* -q specifies 8-byte quad-word values.
* -a specifies ASCII string.
* -u specifies Unicode (UTF-16) string.
* -f specifies floating-point number.

Range specifies the range of memory to search, and Pattern is the data you are looking for.

Example:

```markdown
s -a 0 L?7fffffff "hello"
```

![Windbg-Intro](image/img40.PNG)

**Example:**

```text
open executable:
    open helloworld executable(.exe)

    > g
        continue and we have a breakpoint

    > s -a 0 L?7fffffff "hello"
        s - search
        a - ascii
        0 - 0th address
        ? - to search very large range of address
        7fffffff - entire user mode address range
        "hello" - ascii value to search 
    
    > dv 
        see address of the local variable and check whether it is there in the search

    > .hh s 
        documentation on search

    > qd 
        detach the executable
```

## **bp command**

The bp command in WinDbg is used to set a breakpoint at a specified location. Breakpoints are a common debugging tool that allow you to pause the execution of a program at a specific point, so you can inspect the state of the program at that point.

```markdown
bp [options] [Address [Passes] [CommandString]]
```

* options are optional parameters that control how the breakpoint behaves.
* Address is the memory address where you want to set the breakpoint. This can also be a function name or a source line, if you have symbol and source information.
* Passes is the number of times the breakpoint should be ignored before it triggers. This is optional.
* CommandString is a command or sequence of commands that WinDbg should execute when the breakpoint triggers.

```markdown
bp HelloWorld!wmain
```

![Windbg-Intro](image/img41.PNG)

```text
open executable:
    open helloworld executable(.exe)

    > x HelloWorld!*main*
        this will give us all the potential mains

    > bp HelloWorld!wmain
        break point at main function

    > g
        you can see break point is hit

    > bl
        list the break point 

    > bc 0 
        remove break point.

    > qd
        detach the executable

    > make changes in code(add the below code) 
        int a = 0;
        int b = 0;
        int c = a/b;

    > build the executable file

open executable:
    open helloworld executable(.exe)

    > bp HelloWorld!MyTestFunc "dv /V;k;gc"
        dv /V - displays local variable
        k - call stack
        gc - go from conditional breakpoint

    > g
        throws a exception divide by 0
        you can see the local variables and call stack

    > bl 
        list of breakpoints

    > bd *
        disable all the breakpoints(even we can mention breakpoint number instead of *)

    > be * 
        enable all the breakpoints(even we can mention breakpoint number instead of *)

    > qd 
        detach the executable
```

## **t command**

The t command in WinDbg is used to execute a single instruction and then pause, also known as "step into". This allows you to follow the execution of a program line by line, and it will also follow execution into called functions.

```markdown
t
```

![Windbg-Intro](image/img42.PNG)

**Example:**

```text
open executable:
    open helloworld executable(.exe)

    > x HelloWorld!*main*
        this will give us all the potential mains

    > bp HelloWorld!wmain
        break point at main function

    > g
        you can see break point is hit

    > t 
        step into
    
    > qd
        detach the executable
```

## **p command**

The p command in WinDbg is used to "step over" a function or instruction. This means it will execute a single line or instruction in your code, but if that instruction is a function call, it will execute the entire function and then pause, rather than stepping into the function.

```markdown
p
```

![Windbg-Intro](image/img43.PNG)

**Example:**

```text
open executable:
    open helloworld executable(.exe)

    > x HelloWorld!*main*
        this will give us all the potential mains

    > bp HelloWorld!wmain
        break point at main function

    > g
        you can see break point is hit

    > p 
        step over
    
    > qd
        detach the executable
```

## **gu command**

The gu command in WinDbg stands for "Go Up", which executes until the current function is complete and returns,also known as "step out".

```markdown
gu
```

**Example:**

```text
open executable:
    open helloworld executable(.exe)

    > x HelloWorld!*main*
        this will give us all the potential mains

    > bp HelloWorld!wmain
        break point at main function

    > g
        you can see break point is hit

    > gu 
        step out
    
    > qd
        detach the executable
```

![Windbg-Intro](image/img44.PNG)

## **wt command**

The wt command in WinDbg stands for "Watch and Trace". This command executes the specified function, or the function at the current instruction pointer if no function is specified, and then provides a summary of the function's execution.

```markdown
wt
```

**Example:**

```text
open executable:
    open helloworld executable(.exe)

    > g
        continue and we have a breakpoint

    > wt 
        displays watch trace
    
    > qd
        detach the executable
```

![Windbg-Intro](image/img45.PNG)

## **.logopen command**

The .logopen command in WinDbg is used to start logging all debugger input and output to a specified file.

**Syntax:**

```markdown
.logopen FileName
```

```markdown
.logopen D:\Windbg\op.txt
```

use .logclose command to close the file

```markdown
.logclose
```

![Windbg-Intro](image/img46.PNG)

![Windbg-Intro](image/img47.PNG)

```text
open executable:
    open helloworld executable(.exe)

    > g
        continue and we have a breakpoint

    > .logopen filepath
        filepath D:\example\log.txt
        creates the file and enters the log

    > wt 
        displays watch trace

    > k
        call stack

    > .logclose 
        close the log file
    
    > qd
        detach the executable

    > open log.txt and you can see logs will be printed
```

## **ChildEBP,retAddr,argstochild**

While looking at call stack we will these three values i.e., **ChildEBP , retAddr and argstochild**.

![Windbg-Intro](image/img53.PNG)

**ChildEBP**

* ChildEBP is nothing but the saved ebp, with this we can get a lot of information,all the stack frame is accessed using the ebp, that is the ChildEBP.
* EBP is a register in the x86 architecture which stands for "Extended Base Pointer". This register is typically used to hold the base address of the current stack frame.
* When a function is called in a program, a new stack frame is created to hold the function's local variables and some other information. The EBP register is set to point to the base of this stack frame, which allows the function to correctly reference its local variables and arguments.

**retAddr**

* retAddr, short for "Return Address", typically refers to the memory address to which a function is supposed to return control after it finishes executing.
* When a function is called in a program, the address of the instruction immediately following the call is pushed onto the stack. This is the return address. After the function completes, it pops this address off the stack and jumps to it, thereby returning control to the point in the code where it was called.

**argstochild**

* argstochild typically refers to the arguments that are passed from a parent function to a child function in a function call.
* When a function is called in a program, the arguments to the function are typically pushed onto the stack, in reverse order (from last to first). These become the argstochild for the function being called (the child function).

## **Address Range**

The term "Address Range" generally refers to a contiguous block of addresses in memory, specified by a starting address and an ending address.

In the context of programming or debugging, an address range could be used to represent various things, such as:

* The range of addresses occupied by a function or a block of code.
* The range of addresses allocated for a buffer or an array.
* The range of addresses covered by a memory mapping.

**!teb** - this is a command to get the stack base and stack limit, so this is a property of the thread.

```markdown
!teb
```

![Windbg-Intro](image/img54.PNG)

we can check difference between stack base and stack limit

```markdown
?stackbase-stacklimit
```

![Windbg-Intro](image/img55.PNG)

I got 12288, this many bytes is the difference between these two addresses.

Example:

```text
open executable:
    open helloworld executable(.exe)

    > g
        continue and we have a breakpoint

    > !teb 
        thread environment block
        it displays stack base and stack limit
    
    > ?stack_base-stack_limit
        we can check difference between stack base and stack limit
    
    > qd
        detach the executable
```

## **pipe command**

* pipe command will show you information about the debuggee.

```markdown
|
```

![Windbg-Intro](image/img56.PNG)

* this is the binary which is being debugged.

* double pipe command gives mode of debugging.

```markdown
||
```

![Windbg-Intro](image/img57.PNG)

**Example:**

```text
open executable:
    open helloworld executable(.exe)

    > g
        continue and we have a breakpoint

    > | 
        information about the debuggee

    > || 
        mode of debugging
    
    > qd
        detach the executable
```

## **version,vertarget commands**

The **version** command in WinDbg provides information about the version of the debugging tools being used, as well as the version of the target being debugged.

```markdown
version
```

![Windbg-Intro](image/img58.PNG)

The **vertarget** command in WinDbg provides information about the target system being debugged.

```markdown
vertarget
```

![Windbg-Intro](image/img59.PNG)

**Example:**

```text
open executable:
    open helloworld executable(.exe)

    > g
        continue and we have a breakpoint

    > version 
        information about the version of the debugging tools being used

    > vertarget 
        information about the target system being debugged
    
    > qd
        detach the executable
```

## Looping- foreach command

The .foreach command in WinDbg is a powerful command used to iterate over a set of data or objects and execute a command or series of commands on each.

Here's the basic syntax of the .foreach command:

```markdown
.foreach ( PlaceHolder { Command } ) { Commands }
```

* PlaceHolder is a name that holds the value of the current object in the iteration.
* The first Command is used to get the set of objects to iterate over. This command should return a list of values or addresses.
* The Commands inside the second pair of curly braces are the commands to be executed for each object in the set. You can refer to the current object using the PlaceHolder name.

```markdown
.foreach /f (place "D:\Test.txt") { .echo place }
```

create text file name Test.txt and run the command

![Windbg-Intro](image/img62.PNG)

![Windbg-Intro](image/img60.PNG)

```markdown
.foreach /f (place "D:\Test.txt") { dc place }
```

![Windbg-Intro](image/img64.PNG)

![Windbg-Intro](image/img63.PNG)

```markdown
.foreach /f (place "D:\Test.txt") { .echo new start; .echo place ;dc place }
```

![Windbg-Intro](image/img66.PNG)

![Windbg-Intro](image/img65.PNG)

**!for_each**

In WinDbg, !for_each is a very useful command that can be used to iterate over a set of elements and execute commands for each element. However, please note that !for is not a standalone command, it's usually used in the context of other commands.

Here is the syntax for the !for_each command:

```markdown
!for_each [frame | local | global] <VariableName> <CommandString>
```

```markdown
!for_each_frame !for_each_local dt @#Local
```

![Windbg-Intro](image/img67.PNG)

**Example:**

```text
open stackframe executable(.exe)

    > g
        continue and we have a breakpoint

    > .hh
        opens documentation window

    > in index search .foreach you can see syntax and usage.

    > create a text file and write random text and save(Test.txt).

    > .foreach /f (place "D:\Test.txt") { .echo place }
        this command iterates and output text present in the file

    > k
        list of call stack

    > in the created text file add the address of the stack.

    > .foreach /f (place "D:\Test.txt") { dc place }
        command will display the memory

    > .foreach /f (place "D:\Test.txt") { .echo new start; .echo place ;dc place }
        this command will iterate according to the command

    > .hh
        opens documentation window

    > in index search !for you can see syntax and usage.

    > !for_each_frame !for_each_local dt @#Local
        command displays all local variables for the current stack

    > !for_each_module .echo @#Base @#End
        this command will display loaded modules
        @#Base base address
        @#End end 
        
    > lm 
        list of modules
        cross verify the above value with the lm command output
    
    > qd
```

# Additional Breakpoints

* [**Conditional Breakpoint**](#conditional-breakpoint)
* [**Symbol breakpoint**](#symbol-breakpoint)
* [**Breakpoint Unresolved**](#breakpoint-unresolved)
* [**Break on Access**](#break-on-access)

## **Conditional Breakpoint**

* Breaks only if a condition is true
* Use to filter out the unnecessary breaks of bp, bm, bu, ba variant.
* A small “program” is given with the breakpoint command which decide to break or not.
* We can even use the program to print the stack on break and just “go”
* Its always better to use gc than g to go from a conditional break.

```markdown
bp HelloWorld!MyTestFunc ".if ( poi(testVar)>0n1500) {} .else {gc} "
```

* bp – breakpoint command
* HelloWorld!MyTestFunc – function argument ,where breakpoint should be applied.
* .if & .else – if else statement
* poi - Pointer-sized data from the specified address
* gc - command resumes execution from a conditional breakpoint

Example:

```text
open helloworld executable(.exe)

    > dt testVar
        check the initial Variable value

    > bp HelloWorld!MyTestFunc ".if ( poi(testVar)>0n1500) {} .else {gc} "
        break only if test var is greater than 1500 or continue

    > g 
        comtinue

    > dt testVar
        check the initial Variable value

    > testVar value is greater than 1500 and it is breked.

    > .restart
        restart the application

    > bp HelloWorld!MyTestFunc ".if ( poi(testVar)>0n1500) {} .else { k;gc } "
        this command will print call stack when breakpoint is hit

    > qd

```

## **Symbol breakpoint**

Symbolic breakpoints(bm) are particularly useful when you don't have a specific address to break on, but you do know the name of the function or method where you want execution to stop.

The syntax for the bm command is as follows:

```markdown
bm [Options] Symbol
```

```markdown
bm kmcd!fun*
```

![Windbg-Intro](image/img68.PNG)

Example:

```text
open stackframe executable(.exe)

    > bm kmcd!fun*
        All the fun* symbols, it has put breakpoint on

    > x kcmd!fun*
        we will get all the function variable

    > g
        continue and it hits breakpoint on fun

    > qd

```

## **Breakpoint Unresolved**

The bu command in WinDbg is used to set an unresolved breakpoint. This is particularly useful when you want to set a breakpoint on a function or method in a module (DLL or EXE) that has not been loaded yet.

Breakpoint unresolved will anticipate a binary load and will put a breakpoint in advance

The syntax for the bu command is as follows:

```markdown
bu [Options] Address [Passes] ["CommandString"]
```

```markdown
bu comdlg32!DllMain
```

* breakdown on the unloaded binary

Here:

* Address is the memory address or symbol where you want to set the breakpoint.
* Options, Passes, and CommandString are optional parameters.

**Example:**

```text
 Attach Process: 
        load notepad

    > you can see the binary which are loaded

    > g 
        continue

    > open notedpad file -> open in windbg you can see the binary are loading suddenly(these are the unloaded binary)

    > I will use the first dll which is getting loaded when I open the file open dialog box

    > break (Alt + Delete)

    > qd 
        deatch the process

    Attach Process again: 
        load notepad

    > bu comdlg32!DllMain
        breakpoint on the unloaded binary

    > g
        continue

    > open notedpad file -> open
        we can see the breakpoint is it.

    > k
        I will see the loading call path,so this is how the handler of that button so it is starting from winproc to all the way from combase to load library.

    > kvn 
        to check the dll load

    > qd
        detach the process

```

## **Break on Access**

The ba command in WinDbg stands for "Break on Access". It sets a breakpoint at a specified location in memory. This command is especially useful when you want to stop execution when a specific memory location is accessed or modified.

The syntax for the ba command is as follows:

```markdown
ba [Options] Access Size Address [Passes] ["CommandString"]
```

Here:

* Access specifies the type of memory access that causes the breakpoint to be triggered: e (execute), r (read), or w (write).
* Size is the size of the memory range that's being watched.
* Address is the memory address at which the breakpoint is set.

**Example:**

```text
open helloworld executable(.exe)

    > bp HelloWorld!wmain
        breakpoint on main function.

    > g
        continue and breakpoint hit

    > dv /V
        we address of the variable

    > ba r4 address
        address - address of initi variable
        r - read or write
        4 - four bytes

    > g
        continue and it will hit a break point on the variable
        it is not exactly breaking there is because the CPU is executing the instructions out of order

    > g
        getting the correct instruction here

    > ?ebp-014h
        we can see where the breakpoint is hitting (that is the breakpoint on the variable address)

    > qd

```

# Call Stack and Thread Analysis

* [**Understanding the call stack and stack frames**](#understanding-the-call-stack-and-stack-frames)
* [**Viewing and navigating the call stack**](#viewing-and-navigating-the-call-stack)
* [**Thread**](#thread)
* [**Analyzing thread information**](#analyzing-thread-information)

## **Understanding the call stack and stack frames**

**Call Stack**

* The call stack is a fundamental concept in debugging that provides valuable information about the sequence of function calls and their associated return addresses during program execution. 
* It allows developers to trace the flow of execution, understand the order of function calls, and identify the path leading to the current point of code execution.

**stack frames**

A call frame, or stack frame, is a data structure that contains information about a single function call. Each time a function is called, a new call frame is created on the call stack to store relevant information such as local variables, function parameters, and the return address.

![Windbg-Intro](image/img69.png)

## **Viewing and navigating the call stack**

**call stack**

view the call stack using k command.

![Windbg-Intro](image/img74.PNG)

use kvn command to view Args to Child

![Windbg-Intro](image/img75.PNG)

**Stack frame**

Switching into stack frame (.frame )

![Windbg-Intro](image/img76.PNG)

use the dv (Display Local Variables) command to view the local variables and function arguments for that function

![Windbg-Intro](image/img77.PNG)

**Example:**

```text
Launch Executable:
    launch helloworld executable(release)

    > bp HelloWorld!wmain
        breakpoint on main function

    > g 
        conitnue and breakpoint hit

    > k 
        list of stacks

    > kvn
        display a stack trace with frame numbers, module names, function names, and source line 
        numbers for each call on the stack.

    > .frame 00
        switch into particular frame

    > dv /V 
        view the local variables and function arguments for that function

    > qd
        detach the executable

```

## **Thread**

* Threads are  nothing but a  group of CPU instruction  guaranteed  to execute in  the order we  are giving.
* Thread stack help to maintain  the  order of  execution and have  local variables.


![Windbg-Intro](image/img70.png)

## **Analyzing thread information**

[click the link for reference program](https://github.com/PadmanabhanSaravanan/windbg_Intro/tree/master/Threads)

**~ (Tilde) Command:**

The tilde command lists all the threads in the target process, along with their thread IDs (TIDs) and processor (CPU) affinity.

![Windbg-Intro](image/img71.PNG)

**~*k Command:**

This command will list all the threads with call stack.

![Windbg-Intro](image/img72.PNG)

**~*r Command:**

This command will list all the threads with registers.

![Windbg-Intro](image/img73.PNG)

**!teb command**

Thread environment block:

The Thread Environment Block (TEB) is a data structure in Windows operating systems that contains information related to the currently running thread, including thread-local storage, structured exception handling, stack bounds, and more.

![Windbg-Intro](image/img78.PNG)

**Example:**

```text
Launch Executable:
    launch thread executable(release)

    > ~ 
        lists all the threads in the target process

    > *k
        list all the threads with call stack

    > *r
        list all the threads with registers

    > !teb
        thread environment block

    > bp Threads!printNumbers ".if ( poi(isEven)=1) {} .else {gc} "
        put breakpoint if isEven = true

    > qd 
        detach the process

```

# Assembly Language

* [**Assembly**](#assembly)
* [**Understanding Assembly Launguage**](#understanding-assembly-launguage)

## **Assembly**

**Why do we need?**

* Reverse engineering or understand the flow in other modules and functions.
* Finding the arguments from stack

-> Sparingly used.

-> Tedious and time consuming but at time in evitable.

-> Last resort.

-> Only some 10% or small subset of it is needed for our purpose.

-> How the stack is maintained is one off the major focus.

## **Understanding Assembly Launguage 32bit**

* [**Registers**](#registers)
* [**Basic instructions**](#basic-instructions)
* [**Stack handling of windows compiler**](#stack-handling-of-windows-compiler)
* [**Calling conventions**](#calling-conventions)
* [**Demo**](#demo)

![Windbg-Intro](image/img69.png)

### **Registers**

Registers are a small amount of storage available as part of a computer's CPU (Central Processing Unit). They are used to quickly store and retrieve data during a program's execution. The number and type of registers vary depending on the architecture of the CPU, but they often include:

**1. General-Purpose Registers:** These can be used for any data manipulation operation. Examples include EAX, EBX, ECX, EDX in the x86 architecture.

**2. Instruction Pointer:** Also called a program counter, this register points to the next instruction to be executed. EIP (Extended Instruction Pointer) is used in x86.

**3. Stack Pointer:** This points to the top of the current stack frame. ESP (Extended Stack Pointer) is used in x86.

**4. Base Pointer:** Also called a frame pointer, this points to a fixed location within a stack frame. EBP (Extended Base Pointer) is used in x86.

![Windbg-Intro](image/img79.PNG)

**Example**

```text
Use StackFrame program

    > first we need to make some changes to the program
        - in fun3 add __stdcall (void __stdcall fun3(int i,int j){ }).  __stdcall is the calling covention.
        - In project properties C/C++ -> Optimization -> diabled & Inline Function Expansion -> disabled(platform 32)
        - build it in release mode 32bit for debugging.

Launch Executable:
    launch stackframe executable(release)

    > bp kcmd!wmain
        breakpoint to the main function

    > g
        continue and breakpoint hits

    > r 
        to see the registers
```

### **Basic instructions**

use uf command to see the assemby instruction.

```markdown
uf kcmd!wmain
```

the example shows the machine-level representation of the wmain function from the kCmd module in your program.

![Windbg-Intro](image/img80.PNG)

**Understand the assemby instruction**

**1. push ebp**: This is the start of the function prologue. It's saving the old base pointer value onto the stack so that it can be restored later. The base pointer is used to reference local variables and function arguments.

**2. mov ebp, esp**: This is the second part of the function prologue. It's setting the base pointer to the current stack pointer, which effectively creates a new stack frame for this function.

**3. push 8Bh, push 12Ch, push 0C8h, push 64h**: These instructions are pushing the hex values 8B, 12C, 0C8, and 64 onto the stack. These are likely arguments to the function fun1.

**4. call kCmd!fun1**: This instruction is calling the fun1 function, passing it the arguments that were just pushed onto the stack.

**5. add esp,10h**: This instruction is cleaning up the stack after the call to fun1. It's adding 0x10 (or 16 in decimal) to the stack pointer, effectively removing the four arguments that were pushed onto the stack before the fun1 call.

**6. xor eax,eax**: This instruction is setting the eax register to 0. The xor operation is a common way to zero a register in assembly. The eax register is typically used to hold a function's return value, so this could be setting the return value of wmain to 0.

**7. pop ebp**: This is the start of the function epilogue. It's restoring the old base pointer value from the stack, returning us to the parent stack frame.

**8. ret**: This is the end of the function. It's returning control to the function that called wmain, popping the return address from the stack and jumping to it.

```text
Launch Executable:
    launch stackframe executable(release)

    > bp kcmd!wmain
        breakpoint to the main function

    > g
        continue and breakpoint hits

    > uf kcmd!wmain 
        to see the assembly instructions

```

### **Stack handling of windows compiler**

When a function is called in a C or C++ program on Windows, the function's prologue and epilogue handle setting up and tearing down the stack frame for that function. Here's how it generally works:

In the above assemby instruction first two line is function prologue and last two line is function epilogue.

**Function Prologue:**

* **Push Old Base Pointer onto Stack:** The function starts by saving the old base pointer (ebp on x86, rbp on x64) onto the stack with a push instruction. This allows the function to be reentrant or recursive, and allows for the previous state to be restored later.

* **Set New Base Pointer:** Next, the function sets the base pointer to the current stack pointer (esp on x86, rsp on x64) with a mov instruction. This establishes a fixed reference point in the stack for accessing function parameters and local variables.

* **Allocate Space for Local Variables:** The function then adjusts the stack pointer by subtracting the total size of local variables from it. This allocates space on the stack for local variables.

**Function Epilogue:**

* **Deallocate Local Variables:** The function starts its cleanup by moving the stack pointer back to the base pointer. This effectively deallocates the space that was used for local variables.

* **Restore Old Base Pointer:** The function then pops the old base pointer value from the stack, restoring the stack state to what it was before the function was called.

* **Return to Caller:** Finally, the function executes a ret instruction, which pops the return address from the stack and jumps to it. This transfers control back to the function that made the call.

### **Calling conventions**

Calling convention is all about how the function call is being made and how the arguments are passed from one function to the other function. So there is callee and caller.

* callee is the function which is being called and caller is the function calls the callee.

In 32-bit Windows Compiler, there are majorly two types of calling convention one is [cdecl calling convention](#cdecl-calling-convention) and another is [standard calling convention](#standard-calling-convention).

#### **cdecl calling convention** 

This is the default calling convention for C and C++ programs. In __cdecl, function arguments are pushed onto the stack in right-to-left order. The caller is responsible for cleaning up the stack after the function returns. This allows for variable-argument functions (like printf), but it can lead to larger code size when many functions are called due to the frequent stack cleanup code.

```markdown
uf kcmd!fun1
```

![Windbg-Intro](image/img81.PNG)

* **mov eax, dword ptr [ebp+14h]; mov ecx, dword ptr [ebp+10h]; lea edx,[ecx+eax+1Eh]:** These instructions are preparing arguments for the call to fun2. It's loading function arguments into registers and calculating the value of one of the arguments (ecx+eax+1Eh).

* **push edx; push eax; push ecx:** These instructions are pushing the calculated values onto the stack in reverse order, preparing for the function call to fun2.

* **call kCmd!fun2:** This instruction is calling the fun2 function with the arguments that were just pushed onto the stack.

* **add esp, 0Ch:** This instruction is cleaning up the stack after the call to fun2. It's adding 0Ch (or 12 in decimal) to the stack pointer, which removes the three arguments that were pushed onto the stack before the fun2 call.

```text
Launch Executable:
    launch stackframe executable(release)

    > bp kcmd!wmain
        breakpoint to the main function

    > g
        continue and breakpoint hits
    
    > t
        step into

    > uf kmcd!fun1
        assembly of the func 1

```

#### **Standard calling convention**

__stdcall: This is the standard calling convention for Win32 API functions. The arguments are pushed onto the stack in right-to-left order, like __cdecl, but the function itself cleans up the stack before returning. This results in smaller code size when many functions are called, but it does not allow for variable-argument functions.

uf kcmd!fun2

uf kcmd!fun3

![Windbg-Intro](image/img82.PNG)

* function3 is Standard calling convention
* function2 is calling the function3 we will not be seeing this add instructions uf kcmd!fun2. After the call we can't see an add instruction right here, but still we have push instructions.
* fun3 , in the final ret we can see this eight is mentioned, this ret8 what it means is that this much stack deallocation has to be done, after the execution of this function, which means that this is where we are cleaning up the stack, this is equal to add esp,8, then ret. This is doing that in the single instruction right here, this is where we are deallocating the memory we have allocated in the previous function.

```text
Launch Executable:
    launch stackframe executable(release)

    > bp kcmd!wmain
        breakpoint to the main function

    > g
        continue and breakpoint hits
    
    > t
        step into

    > uf kmcd!fun2
        assembly of the func 2

    > uf kmcd!fun3
        assembly of the func 3
```

# Exception Handling

WinDbg, you can control how the debugger handles exceptions by event filter tool or by using the sxe, sxd, sxn, and sxi commands followed by the exception code. These commands allow you to specify whether the debugger breaks, outputs a message, or ignores the exception when it occurs.

| **_Command_** |           **_Status name_**          |                                                                                                                                    **_Description_**                                                                                                                                    |
|:-------------:|:------------------------------------:|:---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------:|
|     [sxe](#sxi)       |     Break(Enabled)                   |     When this exception occurs, the target immediately breaks into the debugger before any other error handlers are activated. This kind of handling is called first chance handling.                                                                                                   |
|     [sxd](#sxd)       |     Second chance break(Disabled)    |     The debugger does not break for a first-chance exception of this type(although a message is   displayed). If other error handlers do not address this exception, execution stops and the target breaks into the debugger.This kind of handling is called second chance handling.    |
|     sxn       |     Output(Notify)                   |     When this exception occurs, the target application does not break into the debugger at all.However, a message is displayed that notifies theuser of this exception.                                                                                                                 |
|     [sxi](#sxi)      |     Ignore                           |     When this exception occurs. the   target application does not break into the debugger at all, and no message is   displayed                                                                                                                                                         |

**Example:**

In helloworld program make cahnges that the program causes exception integer-divide by zero

```text
Open Executable:
    open helloworld executable.

    > g
        continue and breaks Integer divide by zero.

    > In Toolbar go to Debug -> event filters
        you can see Integer divide by zero is defaulty enabled(execution enabled).

    > I'm going to enable it and close event filters and going to restart.
    
    > .restart
        restart the application

    > g
        Integer divide by zero first chance,we got it first chance and it broke into the Debugger.

    > we can go and change the event filters to disabled(execution disabled)

    > .restart
        restart the application

    > g
        Integer divide by zero exception broke at second chance into the Debugger.

    > we can go and change the event filters to output(execution output)

    > .restart
        restart the application

    > g
        you can see the application is not breaking into debugger

    > manually break

    > we can go and change the event filters to ignore(execution ignore)

    > .restart
        restart the application

    > g
        debugger will ignore the exception and it will not break and will not print any message.

    > manually break

    > qd 
        detach

```

# Remote Debugging

* [**Remote Debugging Visual Studio**](#remote-debugging-visual-studio)
* [**Remote Debugging Windbg**](#remote-debugging-windbg)
* [**Kernel Mode Debugging Windbg**](#kernel-mode-debugging-windbg)

## **Remote Debugging Visual Studio**

Remote debugging is a feature in Visual Studio that allows you to run and debug code on a different machine than where Visual Studio is running. You might use remote debugging to debug a problem on a production server, a user's machine, or a test machine without having to install a full version of Visual Studio in those environments.

* [**Install the Remote Tools on the Target Machine**](#install-the-remote-tools-on-the-target-machine)
* [**Configure the Remote Debugger**](#configure-the-remote-debugger)
* [**Attach to the Remote Process**](#attach-to-the-remote-process)

### **Install the Remote Tools on the Target Machine**

* On the machine where the application you want to debug is running, download and install the appropriate version of Remote Tools for Visual Studio from the official Microsoft website. The version should match the version of Visual Studio on your host machine.

* [click on link to download remote tool](https://visualstudio.microsoft.com/downloads/#remote-tools-for-visual-studio-2022)

![Windbg-Intro](image/img95.png)

### **Configure the Remote Debugger**

The first time you start the remote debugger (or before you have configured it), the Remote Debugging Configuration dialog box appears.

![Windbg-Intro](image/img96.png)

* If the Windows Web Services API is not installed, which happens only on Windows Server 2008 R2, select the Install button.
* Select at least one network type you want to use the remote tools on. If the computers are connected through a domain, you must choose the first item. If the computers are connected through a workgroup or homegroup, choose the second or third item as appropriate.
* Select Configure remote debugging to configure the firewall and start the remote debugger.
* When configuration is complete, the Remote Debugger window appears.

![Windbg-Intro](image/img97.png)

* The remote debugger is now waiting for a connection. Use the server name and port number shown to set the remote connection configuration in Visual Studio.

### **Attach to the Remote Process**

Back in Visual Studio on your host machine, go to **"Debug" > "Attach to Process"**. In the **"Connection target"** field, enter the name or IP address of the target machine. You should then see a list of processes running on the target machine. Select the process of your application and click "Attach".

![Windbg-Intro](image/img98.png)

## **Remote Debugging Windbg**

WinDbg is a multipurpose debugger for the Microsoft Windows computer operating system, distributed by Microsoft. Debugging Tools for Windows supports debugging of applications, services, drivers, and the Windows kernel.

To set up remote debugging with WinDbg, you'll need two machines: a "host" machine (where you'll be running WinDbg), and a "target" machine (where the code you're debugging is running).

[refer this link for remote debugging](https://learn.microsoft.com/en-us/windows-hardware/drivers/debugger/remote-debugging-using-windbg)

**Here are the steps to setup remote debugging using WinDbg:**

**1.** On the host computer, open WinDbg and establish a kernel-mode debugging session with a target computer.

**2.** Break in by choosing Break from the Debug menu or by pressing CTRL-Break.

**3.** In the Debugger Command Window, enter the following command.

```markdown
.server tcp:port=5005
```

Note :The port number 5005 is arbitrary. The port number is your choice.

**4.** WinDbg will respond with output similar to the following.

```markdown
Server started.  Client can connect with any of these command lines
0: <debugger> -remote tcp:Port=5005,Server=YourHostComputer
```

**5.** On the remote computer, open WinDbg, and choose Connect to Remote Session from the File menu.

**6.** Under Connection String, enter the string,which is given by host machine.

```markdown
tcp:Port=5005,Server=YourHostComputer
```

where YourHostComputer is the name of your host computer, which is running the debugging server.

Select **OK**.

## **Kernel Mode Debugging Windbg**

Kernel mode debugging allows you to debug the Windows operating system itself, which can be invaluable when diagnosing certain types of problems like driver issues, system crashes (Blue Screen of Death), and performance problems at the OS level.

[refer this link for kernel debugging using VM](https://learn.microsoft.com/en-us/windows-hardware/drivers/debugger/attaching-to-a-virtual-machine--kernel-mode-)

* [**Configure VirtualBox for Debugging**](#configure-virtualbox-for-debugging)
* [**Connect WinDbg**](#connect-windbg)

### **Configure VirtualBox for Debugging**

* Shut down the VM, and in VirtualBox, select the VM and go to 'Settings'.
* Go to the 'Serial Ports' section. Here, enable a serial port and set the 'Port Mode' to 'Host Pipe'.
* Check the 'Create Pipe' option, and for the 'Port/File Path', provide a path for the named pipe. The format can be something like \\.\pipe\mypipe.
* Click 'OK' to save the settings.

![Windbg-Intro](image/img99.PNG)

### **Connect WinDbg** 

On your host machine, start WinDbg and select 'Kernel Debug'. In the COM tab, enter the pipe name in the 'Pipe' field and check the 'Reconnect' box. The settings should look something like:

```markdown
Baud Rate: 115200
Resets: 0
Pipe: \.\pipe\mypipe
Reconnect
```

![Windbg-Intro](image/img100.PNG)

# Use Cases

* [**01.Simple Crash**](#01.simple-crash)
* [**02.AccessViolation**](#02.accessviolation)
* [**03.HeapCorruption**](#03.heapcorruption)
* [**04.Bad Exception Handler**](#04.bad-exception-handler)
* [**05.NormalHang**](#05.normalhang)
* [**06.Deadlock**](#06.deadlock)
* [**07.Mutex**](#07.mutex)
* [**08.HeapCorruption**]

## **01.Simple Crash**

[click the link for reference program](https://github.com/PadmanabhanSaravanan/windbg_Intro/tree/master/01.SimpleCrash)

When a simple crash occurs, the operating system typically stops the program and generates an error report, which may include a core dump or a minidump. This report can be analyzed with a debugger to understand the state of the program at the time of the crash and hopefully determine what caused it.

* [**Generate an error report**](#generate-an-error-report)
* [**Demo Simple Crash**](#demo-simple-crash)

### **Generate an error report**

* we will set path to save the crash dump using windows error reporting.

* open run app and type ‘regedit’, this command will open register editor.

![Windbg-Intro](image/img87.PNG)

* Go to this file path `Computer\HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\Windows Error Reporting`

![Windbg-Intro](image/img88.PNG)

* Create a new folder LocalDumps in windows error reporting folder(**right click on Windows Error Reporting -> New -> Key**)

![Windbg-Intro](image/img89.PNG)

* Create dump folder in LocalDumps by **right click on LocalDumps -> New -> Expandable String Value**. name it has DumpFolder and **right click on DumpFolder -> Modify -> In Value data** specify the file path to save the dump and click OK.

![Windbg-Intro](image/img90.PNG)

* Create dump type in LocalDumps by **right click on LocalDumps -> New -> DWORD** and name it has DumpType and **right click on DumpFolder -> Modify -> In Value data** specify the number 2.

![Windbg-Intro](image/img91.PNG)

### **Demo Simple Crash**

* After setting the file path ,run the executable file .
* Disappearance of an application without standard closing  methods is a crash.
* when it is crashed a dump file will be saved at the file path specified.
* Take the dump file and starting analyzing issue.
 
![Windbg-Intro](image/img92.PNG)

* In Event viewer we can look any application as crashed.

* run -> eventvwr -> windows logs -> application , in the log we can see the error .

![Windbg-Intro](image/img93.PNG)

**Note:**

The .ecxr command in WinDbg is used to display the context record for an exception. The context record includes the state of all the registers at the time when the exception occurred. This can be extremely useful when debugging an exception because it allows you to see exactly what the CPU was doing when the exception happened

```text
Open Crash Dump:
    open the dump.

    > lm 
        executable modules will be loaded.

    > if the dump is collected by the WER or the Windows Error Reporting, 
        it is guaranteed to be a second chance exception

    > !analyze -v
        -it give the analyze of the dump.
        -there is a default exception handler in this particular function actually,
            that is the one which is launching the WER.
        look into stack_text you can see the handler(ntdll!_RtlUserThreadStart+0x1b)

    > stack_command(~0s; .ecxr ; kb)
        stack command from !analyze -v

    > dv 
        to check the local variable and we can see the values where it is throwing exception.
```

## **02.AccessViolation**

[click the link for reference program](https://github.com/PadmanabhanSaravanan/windbg_Intro/tree/master/02.AccessViolation)

An Access Violation, also known as a segmentation fault, is a specific kind of error that occurs when a program tries to access a memory location that it's not allowed to access, or tries to perform an operation (like write) that it's not allowed to perform on a particular memory location.

![Windbg-Intro](image/img94.png)

### **AccessViolation demo1**

```c
    int a[10] = { 0 };
	for (int i = 0; i < 1111111; i++)
	{
		a[-i] = 100;
		if (i == 11111111)
			printf("value of i = %d", i);
	}
```

* declare an array a of 10 integers and initialize all elements to 0.
* You enter a loop that goes from 0 to 1111111.
* In each iteration of the loop, you try to write the value 100 to the position -i of the array. For i=0, it's just the last element of the array (a[0]). But for i=1 and higher, you're accessing memory before the start of the array, which is not allocated for your use.

```text
Open executable 
    open access violation executable.

    > g 
        breaks at a point.
    
    > r
        see the registers

    > !teb
        for thread environment block

    > r esp 
    
    > compare the esp value with stack limit.(it is not close)

    > Lets look at the instruction value which is causing the problem

    > ?[instruction]

    > let check the stack limit with instrction value ,it is very close to stack limit

    > we accessing stack illegally, because you are not supposed to access any value lower than esp value.

    > qd
```

### **AccessViolation demo2**

```c
    int* ptr = 0;
	*ptr = 100;
```

* int* ptr = 0; creates a pointer to an integer and initializes it to null (0).
* *ptr = 100; tries to write the value 100 to the memory location pointed to by ptr. But since ptr is null, this is trying to write to memory location 0, which is not a valid or accessible location in modern operating systems.

```text
Open executable 
    open access violation executable.

    > g 
        throws an access violation.
    
    > r
        see the registers

    > see the instructor we trying to access eax,check eax value in registers that is equal to zero

    > we cannot access at zero so it is throwing access violation.

    > qd
```

### **AccessViolation demo3**

```c
    int a = 0;
	int ptr1 = 0;
	ptr1 = (int)&a;
	__asm call ptr1
```

Trying to call a function at a memory address obtained from the address of an integer variable, which will cause an Access Violation.

* int a = 0; declares an integer variable a and initializes it to 0.
* int ptr1 = 0; declares an integer variable ptr1 and initializes it to 0.
* ptr1 = (int)&a; sets ptr1 to the memory address of a. This is an unsafe operation because it's casting a pointer to an int, which may not be able to hold the value of a pointer on all systems (especially on systems with 64-bit pointers and 32-bit integers).
* __asm call ptr1 tries to make an assembly language call to the memory address stored in ptr1, treating that memory location as if it contains the start of a function.


```text
Open executable 
    open access violation executable.

    > g 
        throws an access violation.
    
    > k
        there is no proper stack value,this is not a valid address inside a binary.

    > dc address
        unknow binary address in stack
        it is not getting a valid code.

    > uf address
        unknow binary address in stack
        it is not valid assembly

    > qd
```

## **03.StackOverflow**

[click the link for reference program](https://github.com/PadmanabhanSaravanan/windbg_Intro/tree/master/03.StackOverflow)

Stack overflow occurs when a program's call stack exceeds its maximum size limit. The call stack is a special region of computer's memory that stores information about the active subroutines or functions in a program. This information typically includes return addresses, passed parameters, and local variables.

When a function is called, a new stack frame is pushed onto the call stack. The stack frame contains the return address, the function's parameters, and space for its local variables. When the function returns, its stack frame is popped from the call stack. If a program calls functions in a way that the call stack grows beyond its maximum limit, this results in a stack overflow.

### **StackOverflow demo**

```c
void MyBadFun()
{
	int a[1000] = { 0 };
	MyBadFun();
	return;
}


int _tmain(int argc, _TCHAR* argv[])
{
	MyBadFun();
	return 0;
}
```

MyBadFun() calls itself indefinitely, with each call adding a new stack frame that includes the a[1000] array. Because each stack frame consumes a significant amount of memory (at least 1000 integers * 4 bytes/int = 4000 bytes), and because there's no limit to the recursion, the stack eventually runs out of space and a stack overflow occurs.

```text
Open Executable
    open stackoverflow executable.

    > g
        stackoverflow exception(Stack overflow - code c00000fd (first chance))

    > !analyze -v 
        -it is trying to tells us that there is an stackoverflow
        (FAILURE_BUCKET_ID:  STACK_OVERFLOW_c00000fd_StackOverflow.exe!wmain)
        -ERROR_CODE: (NTSTATUS) 0xc00000fd - A new guard page for the stack cannot be created.

    > k 
        to see the stack

    > kf
        having one more information is that each frame, how much is the size of each frame
        kf to understand who is taking more memory on the stack, which frame
        this kf is very useful, just like any other, you can go into the code and see how the recursion happens 
        and who is allocating on the stack (clicking on the frame)

```

## **04.Bad Exception Handler**

[click the link for reference program](https://github.com/PadmanabhanSaravanan/windbg_Intro/tree/master/04.BadExceptionHandler)

A bad exception handler is one that does not properly manage exceptions when they occur. Exception handling is used to respond to the occurrence of exceptions, which are anomalies that occur during the execution of a program.

The Ostrich Algorithm is a concept in computer science used for dealing with errors or exceptions in a system. The name is derived from the behavior of ostriches, which are said to bury their heads in the sand when they sense danger.

In the context of system design and computing, the Ostrich Algorithm implies ignoring potential errors or problems under the assumption that the cost of detecting and handling these exceptions would exceed the cost of dealing with a system crash if it happens.

### **Bad Exception Handler Demo**

```c
int main()
{
    __try
    {
        std::cout << "Hello World!\n";

        int* ptr = 0;

        std::cout << "We are happy so far. But still long way to go.\n";

        *ptr = 100;

        std::cout << "Yes we did it.\n";
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        exit(1);
    }
}
```

The program creates a null pointer ptr and attempts to dereference(To access the value or object located in a memory location stored in a pointer or another value interpreted as such) it to assign the value 100. This results in a memory access violation because it's trying to write to memory location 0, which is not allowed.

```text
Open Executable
    open badexceptionhandler executable.

    > g
        continue and throws access violation

    > g
        again continue.

    > k 
        check the call stack you can see the process is terminating.
        ntdll!NtTerminateProcess

    > .restart
        restart the application.

    > g
        continue and throws access violation

    > !exchain
        to see the different exception handlers available
        BadExceptionHandler!_except_handler4 this is exception handler from the program.

    > bp BadExceptionHandler!_except_handler4
        put breakpoint on the exception handler

    > g

    > k
        - you can see that ntdll!KiUserExceptionDispatcher is being called from the main, 
        if you look into the main, this function is never getting called from main
        - there was an interrupt came while we were executing the main and the operating system 
        took control

    > all the interrupts are handled inside the operating system, inside the kernel the kernel handler 
    got executed and then it called different functions in user mode
```

* It is causing an interrupt, as part of the interrupt handling,it is calling this particular user mode function from the kernel and finally the handler. That is how the interrupt handling works

* why it is showing in the same stack, because this part of the code is executing in the context of exact same thread because of that, it is sharing the stack or the stack is same for this part of the code and this,that is why it is getting displayed in the same call stack. It doesn't mean that this function is calling this function.

## **05.NormalHang**

An application "hangs" when it becomes unresponsive to user input. There are various reasons why an application might hang, including but not limited to:

* Deadlocks
* Infinite loops
* Heavy Processing
* External Resource Usage
* UI Thread Blocking

[click the link for reference program](https://github.com/PadmanabhanSaravanan/windbg_Intro/tree/master/05.NormalHang)

```python
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                Sleep(30000);
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
```

In the above Example i will make the application to sleep or pause for 30,000 milliseconds, or 30 seconds. This is likely to cause a "hang" or unresponsive state, as it blocks the UI thread from processing other messages.

### **NormalHang Demo**

```text
Open Executable:
    open WindowsAppNormal executable(.exe)

    > g
        you can see that application as started.

    > break manually

    > ~*k 
        - first command to execute is ~*k, we need to see all the threads and the stack
         of all the threads
        - click on the winmain frame,it is waiting for get message  USER32!GetMessageW
            we can see in the stack
    
    > x WindowsAppNormal!*proc*
        request to list all the symbols that contain the string "proc" in the 
        module "WindowsAppNormal

    > bp WindowsAppNormal!WndProc "dv /V;gc"
        breakpoint on wndproc
        
    > g
        we can see the message that are passing when we move cursor on the app

    > qd

Run WindowsApp Normal application
    - click on help and select about the about the application gets hung
    - while clicking on about it is gonna sleep for 30 sec and send message to 
        the winproc , so the application hang.
    - still that 30 sec there will not contact with winproc function
    - Now application Hang quickly attach to the windbg / we can take dump
    - for hang application WER will not work so we have to take dump manually
    - we can use procdump / attach and take it in windbg

Attach the process
    attach the hang application to windbg(i.e., WindowsAppNormal)

    > ~*k 
        - first command to execute is ~*k, we need to see all the threads and the stack
         of all the threads.
        - for hang application or dump !analyze -v does not properly
        - In stack you can see that winmain is calling dispatch message and ultimately 
        getting called winproc.Having the winproc on the stack itself is a suspicious sign.
        - the top of the stack is sleepy x.

    > ~*kvn
        for more details.

    > ?<sleep_address>
        sleep_address from the stack argument to see how many seconds it id gonna sleep
```

The windows will generate messages to the message pump and that messages has to be processed by the winproc in a timely manner. So if that is not happening that window will be marked as hung, the clicks the keyboard interrupt all will be stuck and the application looks unresponsive. Instead of this sleep, this could be anything, it can be wait for a lock, it could be wait for a event, it could be wait for single object,it could be anything, other than functions which process messages.

## **06.Deadlock**

A deadlock is a specific condition where two or more tasks are unable to progress because each is waiting for the other to release a resource. Deadlocks can occur in many different contexts, including multiprocessing, multithreading, and distributed systems.

[click the link for reference program](https://github.com/PadmanabhanSaravanan/windbg_Intro/tree/master/06.DeadLock)

Example: 

* Process 1 holds Resource 1 and requests Resource 2.
* Process 2 holds Resource 2 and requests Resource 1.

![Windbg-Intro](image/img101.PNG)

### **Deadlock Demo**

```text
Open Executable
    open deadlock executable (.exe)

    > g
        we can see that program is not printing anything on console.

    > break manually

    > ~*k
        main thread is waiting on multiple objects(KERNELBASE!WaitForMultipleObjects)
        
    > ~*kvn
        take the starting address of ERNELBASE!WaitForMultipleObjects and we will 
        see what is it waiting for.

    > dc address L2
        we will dump to check what is the object it is waiting for
        we will get the object address

    > !handle address 0xf
        address - object first address from dc command
        we can see that it is waiting for a thread.
        we will get thread id (example 6bb8.6a14, where 6bb8 is process id and
        6a14 is thread id)

    > |
        to check process id is correct

    > ~
        to which thread it is waiting for

    > !handle address 0xf
        address - object second address from dc command

    > ~~[thread_id]s
        we will switch into thread and see what the thread is doing.

    > k 
        what this particular thread is doing
        thread is waiting to enter into a critical session
        we will see even what the other thread is doing.

    > ~~[thread_id]s
        swithched into other thread

    > k 
        we will check what it is doing
        the both threads are similar and even this waiting to enter
        critical session.
        next we will find out what that thread is doing by owning the critical session.

    > ~*kvn
        i will take the critical session argument address(ntdll!RtlEnterCriticalSection)

    > !cs address
        this is a command to dump out the critical session inside a process
        we will get the owning thread id and we will see who is the owner
    
    > ~~[thread.id]s
        we will switch into the thread which is owning.

    > kvn  
        we can see which function is owning a thread
        and it is even trying to enter critical section and we will see
        who is owning and other lock ,where this thread trying to enter

    > !cs address
        address : critical session argument address(ntdll!RtlEnterCriticalSection)
        we will get owning thread id
    
    > ~~[thread.id]s
        switching into thread 

    > kvn
        we can see that both functions owning the lock and waiting for thread to release
        this scenario is know as deadlock.

    > !locks
        we can even use this command to see which thread is locked.
```

## **07.Mutex**

Mutual Exclusion (mutex) is a program object that prevents multiple threads from accessing the same shared resource simultaneously. A shared resource in this context is a code element with a critical section, the part of the code that should not be executed by more than one thread at a time.

[click the link for reference program](https://github.com/PadmanabhanSaravanan/windbg_Intro/tree/master/07.Mutex)

* In the given example, two threads are created and each attempts to write to a hypothetical database. The access to the database is controlled by a mutex, ghMutex. This mechanism ensures that only one thread at a time can write to the database.
* However, in the WriteToDatabase function, there is a Sleep(30000) function call that causes the current thread to sleep for 30000 milliseconds (or 30 seconds) while holding the mutex. This is problematic because the other thread will be blocked for this duration, waiting for the mutex to be released and this application slow and we will see how it will look windbg.

### **Mutex Demo**

```text
Run Mutex Application
    we can see that application is to slow

    > Attach to process
        load mutex to analyze

    > ~*k
        first we will see that what is your main thread doing and it is waiting for multiple objects.
        we will see what are the objects it is waiting for.

    > ~0s
        switching into main thread.

    > kvn
        we will take the starting address which is waiting for objects.

    > dc address L2
        gives the object that are waiting 2 dwords

    > !handle address 0xf
        address : first dword
        we can see the object is thread and we will see what is thread doing

    > ~~[thread_id]s
        switching into the thread

    > k
        we can see that thread is in sleep.

    > kvn 
        take first address of the sleep

    > ?address
        we can see that it is in sleep mode for 30sec.

    > !handle address 0xf
        address : 2nd dword
        it will give thread id and status

    > ~~[thread.id]s
        switch into the thread

    > k
        we can see the thread is waiting for single object.

    > kvn
        we will see what is it waiting on.

    > !handle address 0xf
        we can see that object is mutant.
        we will see who is owning mutant.

    > ~~[thread.id]s
        switching into thread
    
    > k
        we can see that owining thread is sleeping.

    > qd
```

## **08.HeapCorruption**

Heap corruption is a common problem in programs written in languages like C or C++, which allow for direct manipulation of memory. It occurs when a program damages the heap data structure

```c
#include "stdafx.h"
#include <stdlib.h>


int _tmain(int argc, _TCHAR* argv[])
{
	char*ptr1 = (char*)malloc(4);
	char*ptr2 = (char*)malloc(4);
	char*ptr3 = (char*)malloc(4);

	for ( int i = 0; i < 200; i++ )
	{
		*(ptr2+i) = 0;
	}


	free ( ptr1 );
	free ( ptr2 );
	free ( ptr3 );

	return 0;
}
```

* allocate three blocks of memory on the heap using malloc(4), each capable of storing four characters.
* Then, you have a loop that writes a zero into 200 consecutive memory locations, starting at ptr2
* Because ptr2 only points to a block of 4 bytes, this loop writes well beyond the end of that block. This is known as a buffer overflow. The fact that you're writing 200 bytes means you're likely overwriting other data in the heap, including the blocks pointed to by ptr1 and ptr3, as well as potentially the heap's own management data.

### **HeapCorruption Demo**

```text
Open the Executable
    open the heap corruption exe 

    > g
        i got a crash
    
    > k 
        the crash is happening exactly at the free ptr(ucrtbase!free)
        - click main function stack frame to see local variables
        - The free function is used to deallocate or free a block of memory that was 
        previously allocated with malloc

    > !analyze -v
        there is a heap corruption(Failure Bucket Id)
        - the first signature for heap corruption is the crash is happening on one of the 
        heap functions,in this case it is RtlFreeHeap.(look in stack)
        - You can see in additional debug text Enable Pageheap/AutoVerifer

    > filepath> "gflags /p /enable HeapCorruption.exe full"
        open filepath (C:/Program Files (x86)/Windows Kits/10/Debuggers/x86) run command prompt
        use above command  to enable special heap debugging options for the specified executable

    > .restart

    > g
        we can see the crash is happening(access violation)

    > k
        we can see crash is happening then and there itself
        it is crashing right here in the main itself

    > r 
        we can see that there is a byte ptr copy is going on and the target is eax.

    > !gflag
        this will give us information about what is the heap flag we have enabled in gflags, 
        where the page heap is enabled or not. So in this case we have hpa

    > dv 
        we can see the local variables

    > r 
        we can see that the local variable is nearby to eax ,where the crash is happening

    > !address eax
        we can see that, it is reserve 

    > !address argv
        argv from dv command
        we can see that it is MEM_Commit
        commit address is very close to crash address

    > qd
```

# Debugging Managed Code .NET

Debugging managed code in the .NET Framework involves using tools and features designed specifically for the .NET runtime. 

**Example: Simple Crash**

```c
namespace HelloWorld
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
            throw new Exception("Test");
        }
    }
}
```

* It prints the string "Hello World!" to the console.
* It then throws an exception with the message "Test".

The throw new Exception("Test") line will cause the application to terminate abruptly because the exception is unhandled. When an exception is thrown and not caught by any enclosing catch block, it is considered an unhandled exception, and by default, causes the application to terminate.

* [**Generate an error report .NET**](#generate-an-error-report-.net)
* [**Debugging Managed Code .NET Demo**](#debugging-managed-code-.net-demo)

## **Generate an error report .NET**

* we will set path to save the crash dump using windows error reporting.

* open run app and type ‘regedit’, this command will open register editor.

![Windbg-Intro](image/img87.PNG)

* Go to this file path `Computer\HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\Windows Error Reporting`

![Windbg-Intro](image/img88.PNG)

* Create a new folder LocalDumps in windows error reporting folder(**right click on Windows Error Reporting -> New -> Key**)

![Windbg-Intro](image/img89.PNG)

* Create dump folder in LocalDumps by **right click on LocalDumps -> New -> Expandable String Value**. name it has DumpFolder and **right click on DumpFolder -> Modify -> In Value data** specify the file path to save the dump and click OK.

![Windbg-Intro](image/img90.PNG)

* Create dump type in LocalDumps by **right click on LocalDumps -> New -> DWORD** and name it has DumpType and **right click on DumpFolder -> Modify -> In Value data** specify the number 2.

![Windbg-Intro](image/img91.PNG)

## **Debugging Managed Code .NET Demo**

```text
Run the Helloworld exe
    the helloworld application will print helloworld and terminates automatically
    Dump will be created in specified path

Open Crash Dump
    open dump which is create while application crash

    > ~*k
        to see the stack of all the threads
        In stack we can see clr handler so we need to load the .NET extension

    > .loadby SOS clr
        this command will load .net extension for debugging managed code 

    > ~*e!clrstack
        will load managed call stacks for all threads

    > !dso
        all the managed objects found on the stack of the current thread
        we can see the exception object

    > !pe address
        address - address of the exception object.
        prints the details of a specific exception
        we can see the message coming from exception object
        click on the exception address we can see the raw dump.

    > !do address
        address - address of the message object from the raw dump
        it dumps a representation of a managed object at that memory address.
```

**why we need to load SOS.dll?**

* The .loadby sos clr command in WinDbg is used to load the SOS debugging extension. The SOS debugging extension (SOS.dll) helps you debug managed programs in WinDbg by providing information about the internal common language runtime (CLR) environment.
* If you don't load the SOS debugging extension with .loadby sos clr, you won't be able to use the SOS commands that provide insights into the managed .NET aspects of the dump you're investigating. This includes inspecting managed objects, call stacks, exceptions, threading information, and more.
* Without the SOS extension, you'll be limited to the native debugging capabilities of WinDbg, which won't provide as much valuable information for debugging managed .NET applications.

**~*****e!clrstack**

* The ~*e!clrstack command in WinDbg is a powerful way to view managed call stacks for all threads in a .NET application.
* This command is particularly useful when debugging issues like deadlocks or race conditions where you need to see what all threads in the application were doing at a certain point in time.

**!dso**

* The !dso command in WinDbg, where dso stands for "DumpStackObjects", is part of the SOS debugging extension used for debugging managed code in .NET applications.
* When you run !dso, it enumerates all the managed objects found on the stack of the current thread. This includes method parameters, local variables, and any temporary objects that .NET is using internally on that thread.

**!pe address**

* The !pe command in WinDbg, where pe stands for "PrintException", is part of the SOS debugging extension used for debugging managed code in .NET applications.
* When you run !pe, it prints the details of the last exception on the current thread, if there is one. The information includes the exception type, message, and stack trace, among other things.
* You can also use !pe with an exception object's address to print the details of a specific exception, like so: !pe <address>.

**!do address**

* The !do command in WinDbg stands for "DumpObject". It's part of the SOS debugging extension, which is used for debugging managed code in .NET applications.
* When you run !do followed by an address, it dumps a representation of a managed object at that memory address. The output includes the object's type, size, and value for each field in the object.

# Summary 

**Commands** <!-- style="font-size:25px" -->

**1. analyze**

* `!analyze`: This performs an automatic analysis of the current exception or bug check.
* `!analyze -v`: This performs verbose analysis, providing more detailed output. 

**2. Thread**

The ~ command in WinDbg is used for thread manipulation and inspection. It can list all threads in a process, switch between threads, freeze and thaw threads, and much more. 

* `~`: Lists all threads in the current process.
* `~*`: Applies a command to all threads. For example, ~*k displays a stack trace for each thread.
* `~N s`: Switches the debugger context to the specified thread N.
* `~N f`: Freezes the specified thread N. It won't run when you execute the g (go) command.
* `~N u`: Unfreezes the specified thread N. It will run when you execute the g (go) command.
* `~~[ThreadID]s`: Switches the debugger context to the thread with the specified thread ID.
* `~N kd`: Sets default register context to the specified thread N.
* `~* kv`: Displays a call stack with frame numbers and return addresses for all threads.
* `~N k`: Displays a call stack for the specified thread N.

**3. Stack Trace**

The k command in WinDbg are used to display a stack trace.

* `k`: Displays a basic stack trace. Each line shows a single stack frame with the return address, the function name, and the source line if the symbols are loaded properly.
* `kb`: Displays a stack trace with the parameters to the functions. This command is very useful when trying to understand what values were passed to the function when the program crashed or hanged.
* `kc`: Just like kb but omits the first column that represents the frame numbers.
* `kd`: Similar to kb but only displays the return addresses in the call stack.
* `kp`: Displays the stack frame, return address, function name, source file name, and line number within the source file, and parameters passed to the functions.
* `kP`: Similar to kp but displays the stack frame pointer instead of the frame number.
* `kv`: Similar to kp, but also displays the local variables in each stack frame.
* `kvn`: Similar to kv but includes the frame number in hexadecimal format, as well as the displacement from the start of the function to the point of execution.
* `kf`: Displays a stack trace along with the size of the parameters in bytes.

**4. Resume execution**

* `g`: Resumes execution of the program. If no breakpoints are hit, the program will run to completion or until an exception occurs.
* `gu`: Go up. Continues execution and breaks at the return from the current function.
* `gc`: It's used to continue execution of the program after it's been halted at a breakpoint.

**5. Breakpoint**

* `bp`: This command is used to set a breakpoint at a specific location in the code. Variations:
* `bp module!function`: Sets a breakpoint at a specific function.
* `bp module!function "commands"`: Sets a breakpoint and executes specified commands when the breakpoint is hit.
* `bu`: Sets an unresolved breakpoint, which is resolved each time it's hit.
* `bl`: This command lists all breakpoints. No variations.
* `bm`: This command sets a breakpoint on all functions that match a specified pattern.
* `ba`: This command sets a breakpoint on access (read/write) to a specified memory 
* `be`: This command enables a breakpoint that has been previously disabled.
* `bd`: This command disables a breakpoint, but does not remove it.
* `bc`: This command clears a breakpoint.

**6. Memory**

* **dd, da, du, dc**: These commands are used to inspect the contents of memory at a specific address.
* `dd Address L?Length`: Displays memory as double words (32 bits).
* `da Address L?Length`: Displays memory as ASCII.
* `du Address L?Length`: Displays memory as Unicode.
* `dc Address L?Length`: Displays memory as hex and ASCII.
* `dps Address L?Length`: Displays pointer-sized values with symbols.

**7. Variavles**

`dv`: This command displays local variables and parameters. Variations:

* `dv /t`: Displays the type of variables.
* `dv /v`: Displays the value of variables.
* `dv /i`: Displays the type information for variables.

`dt`: This command displays a local or global variable, or a data type.

**8. Registers**

* `r`: The r command without any arguments displays the content of all registers.
* `rm`: This command modifies the value of one or more registers.
* `r <register_name>`: This command followed by a specific register name will show the content of that register.

**9. Symbols**

* `.reload:` This command reloads symbol information. 
* `.reload /f`: Forces an immediate symbol reload, regardless of the timestamp.
* `.reload /v`: Verbose mode.
* `ln`: Displays the list the nearest symbols to an address.
* `x:` command examines symbols.
* `.sympath`: This command sets or displays the symbol path.
* `.symfix`: This command sets the symbol path to the default Microsoft Symbol Server path.
* `!sym noisy`: This command enables noisy symbol loading which will output detailed information about the debugger's search for symbols.
* `!sym quiet`: This command disables noisy symbol loading.
* `.sympath+`: This command adds a new path to the existing symbol path.

**10. Debugger Extensions**

* `!peb`: This command displays the Process Environment Block (PEB) of a process.
* `!heap`: This command is used to display information about a process heap, which can be useful for tracking down memory leaks or heap corruption.
* `!locks`: This command can display information about locks in the system, which can be useful for debugging deadlock situations.
* `.load / .unload`: These commands load or unload a specific debugger extension DLL.
* `.chain`: Displays a list of all loaded debugger extensions.

**11. Editing Memory**

* `eb`: Edit memory in bytes.
* `ew`: Edit memory in words (2 bytes).
* `ed`: Edit memory in double words (4 bytes).
* `eq`: Edit memory in quad words (8 bytes).
* `ea`: Edit memory in ASCII.
* `eu`: Edit memory in Unicode.

**12. Search**

* `s`: Search memory for a specific byte.
* `sa`: Search memory for an ASCII string.
* `su`: Search memory for a Unicode string.
* `sd`: Search memory for a specific doubleword. 
* `sq`: Search memory for a specific quadword.

**13. Stepping Techniques**

* `t`: execute a single instruction and then pause, also known as "step into".
* `p`: execute a single line or instruction in your code, also known as "step over".
* `gu`: executes until the current function is complete and returns,also known as "step out".