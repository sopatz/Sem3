Programming assignments for Operating Systems course at Kent State:

Producer-Consumer problem with shared memory using threads and semaphores.

Code is in one C code file called "producerConsumer.c".

Compiled using "gcc producerConsumer.c -pthread" then running "./a.out".

Normally, both producer and consumer would loop forever, but for example purposes, I limited the times looped through each function to 10.

Problems faced:

-Figuring out how to create/join the threads (arguments, semantics, etc)

-Nothing was being consumed until I made producer sleep()

-Slides were helpful for figuring out what to do, as figuring out where to start was a struggle
