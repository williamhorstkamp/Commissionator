#include "SQLiteHandler.h"
#include <string>
#include <vector>
#include <tuple>

using namespace SQLiter;

namespace Commissionator {

    /**
     *  Class that manages the SQLite database through an SQLiteHandler.
     *  Acts as the "model" in the programs MVC design.
     *  Provides a set of functions making it easier for the Controller to
     *  manipulate the database as well as request results of query functions.
     */
    class ComModel {
    private:
        SQLiteHandler *SQL;

        /**
         *  Builds the database schema into the currently managed database.
         *  Ran during the create function before prepared statements are
         *  dealt with.
         */
        void build();

        /**
         *  Prepares the prepared statements against the currently managed
         *  database. This command is ran during both the open and create
         *  functions.
         */
        void prepare();

    public:

        /**
         *  Default constructor
         */
        ComModel();

        /**
         *  Destructor cleans up database and prepared statements by deleting 
         *  it.
         */
        ~ComModel();

        /**
         *  Creates a database at the given file location/name. Then saves the
         *  contents of the SQL to disk.
         *
         *  @param fileName - C String containing file location and name
         */
        void save(const std::string fileName);

        /**
         *  Opens a database at the given file location/name. Then prepares
         *  the statements against the database.
         *
         *  @param fileName - C String containing file location and name
         */
        void open(const std::string fileName);

        /**
         *  Closes the database.
         */
        void close();

        /**
         *  Inserts a commissioner into the database with a given name.
         *
         *  @param comName - C String containing the name of the commissioner
         */
        void insertCommissioner(const std::string comName);

        /**
         *  Deletes a commissioner with a given id. Can not delete the 'None'
         *  commissioner (0)
         *
         *  @param id - int containing the id of the commissioner to delete
         */
        void deleteCommissioner(const int id);

        /**
         *  Renames a commissioner with a given id and name
         *
         *  @param id - int containing the id of the commissioner to rename
         *  @param comName - C string containing the new name of the
         *      commissioner
         */
        void setCommissionerName(const int id, const std::string comName);

        /**
         *  Returns a vector of tuples containing the data for all the
         *  commissioners stored in the database.
         *
         *  @return - A vector of <int, string> tuples. Each tuple represents
         *      one of the commissioners stored in the database.
         *      Order of the returned values is:
         *      Commissioner(id), Commissioner(name)
         */
        const std::vector<const std::tuple<const int, const std::string>> 
            getCommissioners();

        /**
         *  Returns the name of a commissioner given its id.
         *
         *  @param id - int representing Commissioner(id)
         *
         *  @return - String containing Commissioner(name) for 
         *      Commissioner(id) = id
         */
        const std::string getCommissioner(const int id);

        /**
         *  Inserts a contact type into the database with a given name.
         *
         *  @param typeName - C String containing the name of the type
         */
        void insertContactType(const std::string typeName);

        /**
        *  Deletes a contact type with a given id
        *
        *  @param id - int containing the id of the contact to delete
        */
        void deleteContactType(const int id);

        /**
         *  Renames a contact type with a given id and name
         *
         *  @param id - int containing the id of the contact name to rename
         *  @param typeName - C string containing the new name of the contact 
         *      name
         */
        void setContactTypeName(const int id, const std::string typeName);

        /**
         *  Returns a vector of tuples containing the data for all the
         *  contactTypes stored in the database.
         *
         *  @return - A vector of <int, string> tuples. Each tuple represents
         *      one of the contact types stored in the database.
         *      Order of the returned values is:
         *      ContactType(id), ContactType(type)
         */
        const std::vector<const std::tuple<const int, const std::string>> 
            getContactTypes();

        /**
         *  Returns the type of a contact type given its id.
         *
         *  @param id - int representing ContactType(id)
         *
         *  @return - String containing ContactType(id) for
         *      ContactType(id) = id
         */
        const std::string getContactType(const int id);

        /**
         *  Inserts a contact into the database given contact name, contact
         *  type, and the entry.
         *
         *  @param comName - C String containing the name of the commissioner
         *  @param typeName - C String containing the name of the type
         *  @param entry - C string containg the contact entry
         */
        void insertContact(const int comId, const int typeId,
            const std::string entry);
        
        /**
         *  Deletes a contact with a given id
         *
         *  @param id - int containing the id of the contact to delete
         */
        void deleteContact(const int id);

        /**
         *  Edits the type of a contact
         *
         *  @param contactId - int containing the id of the contact to edit
         *  @param typeId - int containing the id of the type to change to  
         */
        void setContactType(const int contactId, const int typeId);

        /**
         *  Edits the type of a contact
         *
         *  @param id - int containing the id of the contact to edit
         *  @param entry - C string containing the new entry
         */
        void setContactEntry(const int id, const std::string entry);

        /**
         *  Returns a vector of tuples containing the data for all the
         *  contacts stored in the database for a certain commissioner.
         *
         *  @param comId - int representing Commissioner(id)
         *
         *  @return - A vector of <int, int, string> tuples. Each tuple 
         *      represents one of the contacts stored in the database for the
         *      commissioner.
         *      Order of the returned values is:
         *      Contact(commissioner), Contact(type), Contact(entry)
         */
        const std::vector<const std::tuple<const int, const int, 
            const std::string>> getContacts(const int comId);

        /**
         *  Returns a tuple containing the data for the contact with the given
         *  id.
         *
         *  @param id - int representing Contact(id)
         *
         *  @return -  A <int, int, string> tuple.
         *      Order of the returned values is:
         *      Contact(commissioner), Contact(type), Contact(entry)
         */
        const std::tuple<const int, const int, const std::string> 
            getContact(const int id);

        /**
         *  Inserts a product into the database with a given name and price.
         *
         *  @param name - C String containing the name of thep product
         *  @param price - double representing the price of the product
         */
        void insertProduct(const std::string name, const double price);

        /**
         *  Deletes a product given its id by first reassinging all instances
         *  of that product to the generic product (0), then deleting it from
         *  the database. Can not delete the Generic product (0).
         *
         *  @param id - id of the product to delete
         */
        void deleteProduct(const int id);

        /**
         *  Changes the price of a product given its id.
         *
         *  @param id - id of the product to alter
         *  @param price - double representing new price of the product
         */
        void setProductPrice(const int id, const double price);

        /**
         *  Changes the name of a product given its id.
         *
         *  @param id - id of the product to alter
         *  @param name - C string containing the new name of the product
         */
        void setProductName(const int id, const std::string  name);

        /**
         *  Returns a vector of tuples containing the data for all the
         *  products stored in the database.
         *
         *  @return - A vector of <int, string, double> tuples. Each tuple 
         *      represents one of the products stored in the database.
         *      Order of the returned values is:
         *      Product(id), Product(name), Product(price)
         */
        const std::vector<const std::tuple<const int, const std::string, 
            const double>> getProducts();

        /**
        *  Returns a tuple containing the data for the product with the given
        *  id.
        *
        *  @param id - int representing the product id.
        *
        *  @return -  A <string, double> tuple.
        *      Order of the returned values is:
        *      Product(name), Product(price)
        */
        const std::tuple<const std::string, const double> getProduct(const int id);

        /**
         *  Inserts a piece into the database as part of a given commission,
         *  as a specific product, and with an optional description.
         *
         *  @param commissionId - the id of the commission that we are tying
         *      the piece to.
         *  @param productId - the id of the product that the peice is a unit
         *      of.
         *  @param description - C string containing product description
         */
        void insertPiece(const int commissionId, const int productId,
            const std::string description);

        /**
        *  Inserts a piece into the database as part of a given commission,
        *  and as a specific product.
        *
        *  @param commissionId - the id of the commission that we are tying
        *      the piece to.
        *  @param productId - the id of the product that the peice is a unit
        *      of.
        */
        void insertPiece(const int commissionId, const int productId);

        /**
         *  Deletes a piece given its id.
         *
         *  @param id - id of the piece to delete
         */
        void deletePiece(const int id);

        /**
        *  Deletes a piece given its commission id.
        *
        *  @param id - id of the piece to delete
        */
        void deletePieceByCommission(const int id);


        /**
         *  Changes the description of a piece given its id.
         *
         *  @param id - id of the product to alter
         *  @param description - C string containing new description
         */
        void setPieceDescription(const int id, const std::string description);

        /**
         *  Returns a vector of tuples containing the data for all the
         *  pieces stored in the database.
         *
         *  @return - A vector of <int, int, int, string> tuples. Each tuple
         *      represents one of the pieces stored in the database.
         *      Order of the returned values is:
         *      Piece(id), Piece(commissionId), Piece(productId), 
         *      Piece(description)
         */
        const std::vector <const std::tuple<const int, const int, const int, 
            const std::string>> getPieces();

        /**
         *  Returns a tuple containing the data for the piece with the
         *  given id.
         *
         *  @param paymentId - int representing the payment id
         *
         *  @return - A <int, int, string> tuple.
         *      Order of the returned values is:
         *      Piece(commissionId), Piece(productId),
         *      Piece(description)
         */
        const std::tuple<const int, const int, const std::string> 
            getPiece(const int id);

        /**
         *  Returns a vector of tuples containing the data for all the
         *  pieces stored in the database with contains description string.
         *
         *  @return - A vector of <int, int, int, string> tuples. Each tuple
         *      represents one of the pieces stored in the database.
         *      Order of the returned values is:
         *      Piece(id), Piece(commissionId), Piece(productId),
         *      Piece(description)
         */
        const std::vector<const std::tuple<const int, const int, const int, 
            const std::string>> searchPieces(const std::string description);

        /**
         *  Inserts a commission into the database with a given creation date
         *  and due date.
         *
         *  @param commissioner - int representing id of commissioner of the 
         *      commission
         *  @param createDate - C string containing creation date in the form
         *      of YYYY-MM-DD
         *  @param dueDate - C string containing creation date in the form
         *      of YYYY-MM-DD
         */
        void insertCommission(int commissioner, const std::string createDate, 
            const std::string dueDate);

        /**
         *  Deletes a commission with a given id.
         *
         *  @param id - id representing the commission to delete
         */
        void deleteCommission(const int id);

        /**
         *  Changes the due date of a commission given its id
         *
         *  @param id - id of the commission to alter
         *  @param description - C string containing new due date in the form
         *      of YYYY-MM-DD
         */
        void setCommissionDueDate(const int id, const std::string dueDate);

        /**
        *  Changes the paid date of a commission given its id
        *
        *  @param id - id of the commission to alter
        *  @param description - C string containing new paid date in the form
        *      of YYYY-MM-DD
        */
        void setCommissionPaidDate(const int id, const std::string paidDate);

        /**
         *  Returns a vector of tuples containing the data for all the
         *  pieces stored in the database.
         *
         *  @return - A vector of <int, string, string, string> tuples. Each 
         *      tuple represents one of the pieces stored in the database.
         *      Order of the returned values is:
         *      Commission(id), Commission(commissioner), Commission(createDate), 
         *      Commission(dueDate), Commission(paidDate)
         */
        const std::vector<const std::tuple<const int, const int, 
            const std::string, const std::string, 
            const std::string>>getCommissions();

        /**
         *  Returns a tuple containing the data for the commission with the 
         *  given id.
         *
         *  @param id - int representing the commission id.
         *
         *  @return -  A <string, string, string> tuple.
         *      Order of the returned values is:
         *      Commissioner(commissioner), Commission(createDate), 
         *      Commission(dueDate), Commission(paidDate)
         */
        const std::tuple<const int, const std::string, const std::string, 
            const std::string>getCommission(const int id);

        /**
         *  Inserts a payment method with given name
         *
         *  @param name - String containing the name of the new payment method
         */
        void insertPaymentMethod(const std::string name);

        /**
         *  Deletes a payment method with given id
         *
         *  @param id - int containing the id of the payment method to delete
         */
        void deletePaymentMethod(const int id);

        /**
         *  Sets the name of the payment method identified by id
         *
         *  @param id - int containing the id of the payment method to edit
         *  @param name - String containing the name of the payment method
         */
        void setPaymentMethodName(const int id, const std::string name);

        /**
         *  Returns a vector of tuples containing the data for all the
         *  payment methods stored in the database.
         *
         *  @return - A vector of <int, string> tuples. Each
         *      tuple represents one of the payment methods stored in the 
         *      database.
         *      Order of the returned values is:
         *      PaymentMethod(id), PaymentMethod(name)
         */
        const std::vector<const std::tuple<const int, const std::string>> 
            getPaymentMethods();

        /**
         *  Returns the name of the payment method given id
         *
         *  @param id - id of the payment method
         *
         *  @return - String containing the name of the payment method
         */
        const std::string getPaymentMethod(const int id);

        /**
         *  Inserts a payment with given commissioner, payment method, date,
         *  payment amount, and note.
         *
         *  @param commissionerId - int representing id of the commissioner
         *  @param commissionerId - int representing id of the payment method
         *  @param date - String containing the date the payment was made
         *  @param amount - int representing the dollar amount the payment was 
         *      for
         *  @param note - String containing a note about the payment
         */
        void insertPayment(const int commissionerId, const int paymentMethodId,
            const std::string date, const double amount, const std::string note);

        /**
         *  Inserts a payment with given commissioner, payment method, date,
         *  and payment amount.
         *
         *  @param commissionerId - int representing id of the commissioner
         *  @param commissionerId - int representing id of the payment method
         *  @param date - String containing the date the payment was made
         *  @param amount - int representing the dollar amount the payment was
         *      for
         */
        void insertPayment(const int commissionerId, const int paymentMethodId,
            const std::string date, const double amount);

        /**
         *  Sets the method of the payment identified by id
         *
         *  @param paymentId - int containing the id of the payment to edit
         *  @param methodId - int containing the id of the  method to change to
         */
        void setPaymentMethod(const int paymentId, const int methodId);

        /**
         *  Sets the date of the payment identified by id
         *
         *  @param paymentId - int containing the id of the payment to edit
         *  @param date - String containing the new date of the payment
         */
        void setPaymentDate(const int paymentId, const std::string date);

        /**
         *  Sets the payment amount of the payment identified by id
         *
         *  @param paymentId - int containing the id of the payment to edit
         *  @param methodId - int containing the value to change amount to
         */
        void setPaymentAmount(const int paymentId, const double amount);

        /**
         *  Sets the commissioner of the payment identified by id
         *
         *  @param paymentId - int containing the id of the payment to edit
         *  @param methodId - int containing the id of the commissioner to 
         *      change to
         */
        void setPaymentCommissioner(const int paymentId, 
            const int commissionerId);

        /**
         *  Returns a vector of tuples containing the data for all the
         *  payments stored in the database.
         *
         *  @return - A vector of <int, int, int, string, int, string> tuples. 
         *      Each tuple represents one of the payments stored in the 
         *      database.
         *      Order of the returned values is:
         *      Payment(id), Payment(commissioner), Payment(method), 
         *      Payment(date), Payment(fee), Payment(note)
         */
        const std::vector<const std::tuple<const int, const int, const int, 
            const std::string, const double, const std::string>> getPayments();

        /**
         *  Returns a tuple containing the data for the payment with the
         *  given id.
         *
         *  @param paymentId - int representing the payment id
         *
         *  @return - A <int, int, string, int, string> tuple.
         *      Order of the returned values is:
         *      Payment(commissioner), Payment(method),
         *      Payment(date), Payment(fee), Payment(note)
         */
        const std::tuple<const int, const int, const std::string, 
            const double, const std::string> getPaymentById(const int paymentId);

        /**
         *  Returns a vector of tuples containing the data for all the
         *  payments stored in the database for the given commissioner.
         *
         *  @return - A vector of <int, int, string, int, string> tuples.
         *      Each tuple represents one of the payments stored in the
         *      database.
         *      Order of the returned values is:
         *      Payment(id), Payment(method), Payment(date), Payment(fee), 
         *      Payment(note)
         */
        const std::vector<const std::tuple<const int, const int,
            const std::string, const double, const std::string >>
            getPaymentsByCommissioner(const int commissionerId);
    };
}