#Model Roadmap
This is a short roadmap for how the ComModel class is going to develop.
The Commissionator Model, or ComModel, is the model in Commissionator's MVC
design, and as such it needs to provide a set of functions for easily modifying
and accessing the SQLite database.
  
This document is not finalized  
  
##Roadmap Format  
  
###Version Number: New Features
A short description of what this version of the model will add over the previous one.  
*a list of functions to be added  
  
  
###V1: Contact type, Commissioner, Contact tables. Struct to use as return type for
functions requesting more than one column or row.
*insert contact type
*delete contact type
*rename contact type
*get list of types
*get type by id
*insert commissioner
*delete commissioner
*rename commissioner
*get list of commissioners
*get commissioner by id
*insert contact
*delete contact
*edit contact entry
*edit contact type
*get list of contacts by commissioner
*get contact by id

###V2: Product, Commission, Piece tables.
*insert product
*delete product
*set product price
*set product name
*get list of products
*get product by id
*insert piece
*delete piece
*set piece description
*get piece list
*get piece by description
*insert commission
*delete commission
*set commission pay due date
*set commission paid date
*get commission list
*get commission by id

###V3: Payment Method, Payment tables.
*insert payment method
*delete payment method
*rename payment method
*get payment method list
*get payment method by id
*insert payment
*set payment method
*set payment date
*set payment amount
*set payment to commission
*get payment list
*get payment by id

###V4:Product Options, Piece Options
*insert product option
*delete product option
*set product option name
*set product option price
*toggle if product option is binary or an integer
*get list of product options for a product id
*get product option by id
*insert piece option
*delete peice option
*set piece option field
*get piece options by piece
*get piece option by id

###V5:References, Product Event, Piece Event
*insert reference
*delete reference
*set reference to piece/set reference description
*get reference list
*get reference list by piece id
*get reference description by piece id and reference id
*insert event type
*delete event type
*set event type to product
*get event type list
*get event types by product id
*insert piece event
*delete piece event
*set piece event type
*set piece event start date
*set piece event end date
*get piece events by piece id

###V6:Sales, Deals
//unfinished
*insert sale
*delete sale
*alter sale start date
*alter sale end date