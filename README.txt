README

Contact Information:

Authors: Kyle Edgette, Manan Hora, Brandon Willett
Course: CSC 173 FALL 2016
Assignment: Project 04 - Relational Data Model


How To Run:

1) Change directory to the appropriate directory of the source code
2) Use "make" command to compile code
3) Use "./output" to run code

Example:

KEdgette1$ make
KEdgette1$ ./output

Collaborators:

Kyle Edgette, Manan Hora, Brandon Willett

Description:

We have a .c file for each relation in our database. For example, csg.c contains all the operations on the Course-StudentID-Grade
relation. Each relation is implemented as a hashtable of linked lists. There is a variety of hash functions, which one is used to
insert is based on the key for the relation, that calculates the index for the tuple that is to be inserted. If the head of the
linked list is filled, the tuple is inserted at the end of the list.

For lookup, again we use the hash function to find the correct bucket in the table. If the head of the linked list does not match
the provided tuple, then we search the bucket/linked list. If any nodes match, then the tuple exists, other wise the provided tuple
does not exist in the relation.

For delete, we use a similar implementation to lookup, except that if we find the tuple in the bucket we erase it's contents, otherwise
no changes are made to the relation.

Each relation has a method that prints it to file. The files that contain the output of the relations are formatted as CSG.txt, CR.txt, etc.

Each relation also has a method that reads a sample relation from file and creates a new table from the data. The input files are named CSGInput.txt,
CRInput.txt, etc.

For Part 2, we created a selectSNAPbyName() method that returns a tuple of SNAP that matches the specified name field. Then we extract
the Student ID from that tuple and use the specified course and that ID to find the tuple in CSG that matches the fields. Then the grade
from that row is the desired result.

To find the room that a specified student is at a given day/time, again we use selectSNAPByName() to
find the Student ID of the given student. Then we find a Linked List of courses that the student takes.
Then we iterate through the Linked List, using lookupCDH to see if the current course title meets at the
specified day and time. If we find a course that meets, then we return that course.

For Part 3, the project method takes an array of attributes to project the CSG relation on. Boolean variables are used to keep track of which
attributes to project on. A new CSG relation is created and the appropriate attributes are copied in based on the boolean variables.

The join method for part 3 uses a new struct, CRDH (course-room-day-hour) and copies the entries that match into the new CRDH table.

All of our implementations are tested in main.c. Please note that the delete operations for part 1 are tested last, so we don't
accidentally delete a tuple that we need for Part 2 or 3.
