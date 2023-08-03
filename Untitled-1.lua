1. Attach Process: 
        load notepad example

    > k
        list call stack
    > ~ 
        threads of the process
    > ~1s 
        connect to one thread
    > k 
        list call stack
    > ~0s
        connect to 0 thread


2. Memory Dump: 

    > dx
        local variables

3. Application Dump 

> .dump /ma pathofdump
    take dump of the application
    /ma full dump
    pathofdump example "c:\path_to_dmp_file\abc.dmp" 

open the dump from menu and load it:
    > k
    > r
        list all the data in the dump files 

4.  > lm 
        load the modules

    > lmvm Helloworld
        Helloworld - name of the binary.
        the gives start and end address of the binary (imp)
        it will display where from symbol files is loaded

    > !lmi Helloworld
        it gives same information of the above command but in different format