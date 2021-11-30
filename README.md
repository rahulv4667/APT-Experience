# A.P.T Portfolio Interview Experience

[Interview 1](./Interview1.md)\
[Interview 2](./Interview2.md)

## Written Test

You have 5 components in your system: CPU, Memory Controller, RAM, NIC, PCIE

Design a virtual computer which takes a stream of bytes as input from `Wire` through NIC and outputs sorted data when you encounter delimiters.

WKT, a byte can hold values 0-255. Out of these 254 represents start of frame and 255 represents end of frame. You will be given input as 
```
254
4
2
89
67
43
34
255
```

The output for above would be
```
254
2
4
34
43
67
89
255
```

It is not necessary that the input will always start with 254 and end with 255. You need to keep looking for these start and end delimiters.

Furthermore, they provided information about how system should interact. The flow of execution is as follows:
- CPU should allocate a few blocks of free memory and provide it for NIC
- NIC, on receiving the stream of bytes, starts writing to the blocks of memory given.
- Once it encounters a `255`(end of frame), it should send an interrupt to CPU to process the data
- CPU should sort the input(either in place or not), and send interrupt to NIC so that it can send info back on wire.
- All communication to RAM should be done through Memory Controller. 
- RAM can be divided into different size of blocks/segments


[Link](./coding_test.cpp) to code that I wrote from what I could remember.

I didn't completely write the program. I didn't even run the code once since it was incomplete. But I guess they were ok with just the OOP part of it. I used publisher-subscriber model(Observer pattern) for PCIE interrupt handling and also used a superclass for `NIC`called `Peripheral`. This was to make things more generic and extensible.


