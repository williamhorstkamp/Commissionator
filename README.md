#**THIS PROGRAM IS A WORK IN PROGRESS**  
#**THIS README IS CURRENTLY MORE OF A PROJECT PLAN**  
#**A README DESIGNED FOR END-USERS WILL REPLACE THIS PAGE EVENTUALLY**  
  
  
# Commissionator
Commissionator is a multi-platform utility for artists to document and track their commissions.
It will allow sellers to index the type of products they sell, store information about their clients, 
document and track their progress on a piece from start to finish, and even keep track of payments and earnings.  
  
## Design Doodads
The program is being designed in an MVC-style and is written in C++11/14. The model will utilize SQLiter, an SQLite3 wrapper for C++11, to create
and manage a database containing all the of store's information. The interface will be created in qt after the model is finished and tested.  Finally, the controller will be created to bridge the two sides together.   
The target release platforms are
Windows, OSX, and GNU/Linux.
  
## Development and Testing process
Each version will first have its header and documentation written, 
then the tests will be written in google test, followed by finally writing, and then testing the source code. This will be repeated until all features of the Model Roadmap are complete, at which point development will move on to the interface. The roadmap will be followed for the most part for the initial test cases, however some additional features may pop up from time to time as new issues are discovered or new features are thought up and implemented.
  
##Copyright Stuff
Copyright (c) 2015 William Horstkamp  
william.horstkamp@gmail.com  
MIT LICENSE  
License info can be found at license.txt  

The latest version of this code can always be found at  
https://github.com/williamhorstkamp/Commissionator

This code uses my SQLite3 wrapper as a base. It can always be found at
https://github.com/williamhorstkamp/SQLiterForCpp11

This code is dependant on the SQLite3 interface for C, which can be found at
https://www.sqlite.org/download.html
