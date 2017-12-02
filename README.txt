John Williams
105201054
CSCI 2412 
Data structures final project 
based on a database 


DESCRIPTION:
This program was written with much time and effort in understanding a few concepts that, until now, have been treaded on lightly
in my classes in intermediate programming. The main concepts in this program are to facilitate user access to, and manipulation of, 
data for a contact file of a person in a company or what have you. This program containts a templated binary search tree, a vector of vectors, 
and a gross amount of maniplulation, on my part, to facilitate the assignement's demands.

THis program facilitates the mainipulateion of the data for the use of the database as spelled out in the assignment, to the best of 
my knowledge. Many of the classes, and some of the implamentation involve a switch soas to facilitate allowing the user to 
stick with the field of data that they wish to work with at the present moment. This makes the situations of viewing the code
rather irksome, but I ask the reader to see it much like a skewer inside a sandwich. it allows for a flexible platform, and is the only 
way that I can see fit to do such a exercise. if you have a better solution, I am all ears. 

SOURCE FILES:
main.cpp:
	Housing the main call to a function nested in the database class, this file suffices as a simple start to this program.

database.h: 
	This file houses the declaration of the database class with each submenu and the main menu for the program. this class acts as 
	a driver fro the etire program and facilitates each of the specific actions that the program has as specified in the origional assignment.
	
database.cpp:
	This file houses the member functions of the database class and their implamentations.

data.h: 
	Here in this file are housed the declaration of the data class and some of its implamentations. this class is soley responcible 
	for the housing of the data for each client seperate from the affiliates of the client, which respectively are housed inside the affiliate 
	class.

data.cpp:
	Here are housed the majority of the implamentations for the data class, small though they are.

node.h:
	Here are housed the declaration and the implamentations for the Node class that are used in directo correlation with the 
	Binary searh tree. it seemed trivial to move these implamentations to a new file because of the size of the implamentations,
	being very small and for the sake of the arguement that these implamentations were given to me by Dr Augustine. I rewrote 
	much of the node class for personal experience and then proceeded to template this class for the sake of learning about templates
	and for the flexibility that it bought me.

BST.h:
	Hese is housed the binary search tree that has been templated as well and rewritten for the sake of experience. 
	I take little credit for most of the functionality of this class other than templating it, traversing it, and searching it
	in the various methods that I have written into it. 


affiliate.h:
	this class houses the implamentations for the the affiliates of each contact and has its use in the data class inside a vector


TESTING AND IMPLAMENTATION:

	
   The program compiles runs successfully on visual studions 2015 using 
   windows 10 with a 64 bit system with no logic or runtime errors.  
   
   The program was tested on gnu g++ 4.4.2.  It  
   compiled and ran successfully with no logic or runtime errors. 
   





