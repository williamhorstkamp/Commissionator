#include "SQLiteHandler.h"
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
         *  Inserts a contact into the database given contact name, contact
         *  type, and the entry.
         *
         *  @param comName - C String containing the name of the commissioner
         *  @param typeName - C String containing the name of the type
         *  @param entry - C string containg the contact entry
         */
        void insertContact(const char *comName, const char *typeName,
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
    };
}