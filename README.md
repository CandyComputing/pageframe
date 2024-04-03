
CS 540 Operating systems

Programming Assignment 3

04/02/2024


This Program will introduce the workings of a simple Page Frame Table in a memory management system.

The key functionalities demonstrated by this program are:

    Set Page Frame Mapping
    Get Frame Number
    Translate Logical Address to Physical Address

The program operates by initiating a PageFrameTable object and utilizing its methods to simulate address translation and page frame mapping:

    If the operation is setting a page frame mapping, the program assigns a frame number to a specific page number.
    If retrieving a frame number, it fetches this data for a given page.
    For address translation, it converts logical addresses to physical addresses, detailing the process involved.

The main function exemplifies these functionalities by establishing a PageFrameTable, configuring mappings, and translating a set of predefined logical addresses to their corresponding physical addresses.
