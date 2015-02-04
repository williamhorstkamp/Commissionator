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
         *  Creates a database at the given file location/name. Then builds
         *  the schema within with build and prepare.
         *
         *  @param fileName - C String containing file location and name
         */
        void create(const char *fileName);

        /**
         *  Opens a database at the given file location/name. Then prepares
         *  the statements against the database.
         *
         *  @param fileName - C String containing file location and name
         */
        void open(const char *fileName);

        /**
         *  Closes the database.
         */
        void close();

        /**
         *  Inserts a commissioner into the database with a given name.
         *
         *  @param comName - C String containing the name of the commissioner
         */
        void insertCommissioner(const char *comName);

        /**
         *  Deletes a commissioner with a given id
         *
         *  @param id - int containing the id of the commissioner to delete
         */
        void deleteCommissioner(const int id);

        /**
         *  Renames a commissioner with a given id and name
         *
         *  @param id - int containing the id of the commissioner to rename
         *  @param comName - C string containing the new name of the commissioner
         */
        void renameCommissioner(const int id, const char *comName);

        /**
         *  Returns a vector of tuples containing the data for all the
         *  commissioners stored in the database.
         *
         *  @return - A vector of <int, string> tuples. Each tuple represents
         *      one of the commissioners stored in the database.
         *      Order of the returned values is:
         *      Commissioner(id), Commissioner(name)
         */
        const std::vector<std::tuple<int, std::string>> getCommissioners();

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
        void insertContactType(const char *typeName);

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
         *  @param typeName - C string containing the new name of the contact name
         */
        void renameContactType(const int id, const char *typeName);

        /**
         *  Returns a vector of tuples containing the data for all the
         *  contactTypes stored in the database.
         *
         *  @return - A vector of <int, string> tuples. Each tuple represents
         *      one of the contact types stored in the database.
         *      Order of the returned values is:
         *      ContactType(id), ContactType(type)
         */
        const std::vector<std::tuple<int, std::string>> getContactTypes();

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
            const char *entry);
        
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
        void editContactType(const int contactId, const int typeId);

        /**
         *  Edits the type of a contact
         *
         *  @param id - int containing the id of the contact to edit
         *  @param entry - C string containing the new entry
         */
        void editContactEntry(const int id, const char *entry);

        /**
         *  Returns a vector of tuples containing the data for all the
         *  contacts stored in the database for a certain commissioner.
         *
         *  @param comId - int representing Commissioner(id)
         *
         *  @return - A vector of <int, int, string> tuples. Each tuple represents
         *      one of the contacts stored in the database for the commissioner.
         *      Order of the returned values is:
         *      Contact(commissioner), Contact(type), Contact(entry)
         */
        const std::vector<std::tuple<int, int, std::string>> getContacts(const int comId);

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
        const std::tuple<int, int, std::string> getContact(const int id);

        void insertProduct(const char *name, const double price);

        void deleteProduct(const int id);

        void setProductPrice(const int id, const double price);

        void setProductName(const int id, const char * name);

        const std::vector<std::tuple<int, std::string, double>> getProducts();

        const std::tuple<std::string, std::string> getProduct(const int id);

        void insertPiece(const int commissionerId, const int productId,
            const char *description);

        void deletePiece(const int id);

        void setPieceDescription(const int id, const char *description);

        const std::vector < std::tuple<int, int, int, std::string>> getPieces();

        const std::vector<std::tuple<int, int, int, std::string>> searchPiece(
            const char *description);

        void insertCommission(const char *createDate, const char *dueDate);

        void deleteCommission(const int id);

        void setCommissionDueDate(const int id, const char *dueDate);

        void setCommissionPaidDate(const int id, const char *paidDate);

        const std::vector<std::tuple<int, std::string, 
            std::string, std::string>>getCommissions();

        const std::tuple<std::string, std::string, std::string>getCommission(
            const int id);
    };
}