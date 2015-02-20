#Model Roadmap
This is a short roadmap for how the ComModel class is going to develop.
The Commissionator Model, or ComModel, is the model in Commissionator's MVC
design, and as such it needs to provide a set of functions for easily modifying
and accessing the SQLite database.
  
This document is not finalized  
  
##Roadmap Format  
  
###Version Number: New Features
A short description of what this version of the model will add over the previous one.  
- [x] a function that has been added to the branch 
- [ ] a list of functions to be added  
  
###V1: Contact type, Commissioner, Contact tables.
- [x] insert contact type
- [x] delete contact type
- [x] rename contact type
- [x] get list of types
- [x] get type by id
- [x] insert commissioner
- [x] delete commissioner
- [x] rename commissioner
- [x] get list of commissioners
- [x] get commissioner by id
- [x] insert contact
- [x] delete contact
- [x] edit contact entry
- [x] edit contact type
- [x] get list of contacts by commissioner
- [x] get contact by id
  
###V2: Product, Commission, Piece tables.
- [x] insert product
- [x] delete product
- [x] set product price
- [x] set product name
- [x] get list of products
- [x] get product by id
- [x] insert piece with description
- [x] insert piece without description
- [x] delete piece
- [x] delete piece by commission id
- [x] set piece description
- [x] get piece list
- [x] get piece by description
- [x] insert commission
- [x] delete commission
- [x] set commission pay due date
- [x] set commission paid date
- [x] get commission list
- [x] get commission by id
  
###V3: Payment Method, Payment tables.
- [ ] insert payment method
- [ ] delete payment method
- [ ] rename payment method
- [ ] get payment method list
- [ ] get payment method by id
- [ ] insert payment
- [ ] set payment method
- [ ] set payment date
- [ ] set payment amount
- [ ] set payment to commission
- [ ] get payment list
- [ ] get payment by id
  
###V4:Product Options, Piece Options
- [ ] insert product option
- [ ] delete product option
- [ ] set product option name
- [ ] set product option price
- [ ] toggle if product option is binary or an integer
- [ ] get list of product options for a product id
- [ ] get product option by id
- [ ] insert piece option
- [ ] delete peice option
- [ ] set piece option field
- [ ] get piece options by piece
- [ ] get piece option by id
  
###V5:References, Product Event, Piece Event
- [ ] insert reference
- [ ] delete reference
- [ ] set reference to piece/set reference description
- [ ] get reference list
- [ ] get reference list by piece id
- [ ] get reference description by piece id and reference id
- [ ] insert event type
- [ ] delete event type
- [ ] set event type to product
- [ ] get event type list
- [ ] get event types by product id
- [ ] insert piece event
- [ ] delete piece event
- [ ] set piece event type
- [ ] set piece event start date
- [ ] set piece event end date
- [ ] get piece events by piece id
  
###V6:Sales, Deals, Price override
//unfinished
- [ ] insert sale
- [ ] delete sale
- [ ] alter sale start date
- [ ] alter sale end date
- [ ] override/alter the price of a given commission

###V7:Bits and pieces
- [ ] update system
- [ ] date sanitization