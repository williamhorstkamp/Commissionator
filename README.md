# **THIS PROGRAM IS A WORK IN PROGRESS**  
# **THIS README IS CURRENTLY MORE OF A PROJECT PLAN**  
# **A README DESIGNED FOR END-USERS WILL REPLACE THIS PAGE EVENTUALLY**  
  
  
# Commissionator
Commissionator is a multi-platform utility for artists to document and track their commissions.
It will allow sellers to index the type of products they sell, store information about their clients, 
document and track their progress on a piece from start to finish, and even keep track of payments and earnings.  
  
## Design Doodads
The program is designed in MV style and is written in C++11/14. The model will utilize SQLite through the Qt standard database systems to more easily connect to the Qt UI elements and remove the need to use a controller in the first place.  
The interface will be written in Qt before/alongside the model. The development process is outlined in "V4 and after" below.  
The target platforms are  
Windows, OSX, and GNU/Linux.  
  
## Who is this for?  
Commissionator is designed first for a group of artists who requested it, but also more broadly for anyone who needs a straightforward program for Windows, Mac, or Linux that will provide them the split functionality of address book and point-of-sale storefront specifically for use with online transactions. This functionality will be especially useful for keeping track of payments that can be made in a number of ways or contacts that may be held from a number of websites. An example would be if you sold commission based artwork on multiple sites at once (Etsy, DeviantArt, etc) and accepted multiple forms of payment (PayPal, BitCoin, etc) but wanted a single place to keep track of commission and payment history, as well as document commissioners who may be purchasing from you from several channels. The program will also contain functionality for things like price overriding and sales (50% off a specific product, buy 2 get 1 free, etc), as well keeping track of the different types of products you sell, if they have any optional features that may effect the price, and even keep track of references you find for your commissioned pieces.  
  
## Development and Testing process  
  
The program is written in C++ and uses SQLite as a saving and organizational format. QT will be used for UI and database work to allow the program to be multiplatform from the get-go. The entire program is being written in MSVS2013 with the Qt plugin, and will later be tested on Linux and Mac.  
 
Up to V3: Each version will first have its SQL written, then the C++ header and documentation, 
the tests will be written in Google Test, followed by finally writing, and then testing the source code. This will be repeated until all features of the Model Roadmap are complete, at which point development will move on to the interface.  
  
V3: First the model for this version will be finished, first by writing the SQL, then the C++ header and docs, then tests in Google Test, followed by writing source and testing it. After this is done, the UI will be created to reflect the program up to version 3.  
  
V4 and after: First changes to the UI will be made to reflect the new version (if necissary), this UI may then be shown to the client(s), who will request adjustments to be made. After the UI is deemed satisfactory the model will be updated to the new version, finishing that version.  
  
## Copyright Stuff
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
