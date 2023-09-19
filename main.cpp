#include <iostream>
#include <sqlite_orm/sqlite_orm.h>
#include "Model/User.cpp"

using namespace sqlite_orm;
using namespace std;
/*
 CREATE TABLE users (id integer primary key autoincrement, first_name text not null, last_name text not null,
 birth_date integer not null, image_url text, type_id integer not null)

CREATE TABLE user_types (id integer primary key autoincrement, name text not null DEFAULT 'name_placeholder')
 */

int main() {
    auto storage = make_storage(
            "/Documents/db.sqlite",
            make_table("users",
                       make_column("id", &User::id, primary_key().autoincrement()),
                       make_column("first_name", &User::firstName),
                       make_column("last_name", &User::lastName),
                       make_column("birth_date", &User::birthDate),
                       make_column("image_url", &User::imageUrl),
                       make_column("type_id", &User::typeId)),
            make_table("user_types",
                       make_column("id", &UserType::id, primary_key().autoincrement()),
                       make_column("name", &UserType::name, default_value("name_placeholder"))));

    std::cout << "Insert" << std::endl;

    User user{-1, "Jonh", "Doe", 664416000, std::make_unique<std::string>("url_to_heaven"), 3};

    auto insertedId = storage.insert(user);
    cout << "insertedId = " << insertedId << endl;      //  insertedId = 8
    user.id = insertedId;

    User secondUser{-1, "Alice", "Inwonder", 831168000, {}, 2};
    insertedId = storage.insert(secondUser);
    secondUser.id = insertedId;

    try {
        std::cout << "Select" << std::endl;
        auto user = storage.get<User>(insertedId);
        cout << "user = " << user.firstName << " " << user.lastName << endl;
    } catch (system_error e) {
        cout << e.what() << endl;
    } catch (...) {
        cout << "unknown exeption" << endl;
    }
    return 0;
}
