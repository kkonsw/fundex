// Copyright 2021 Kuznetsov Konstantin
/**
 * @file table.h
 * Header for template ORM for Database tables.
 */
#ifndef SRC_DB_TABLE_H_
#define SRC_DB_TABLE_H_

#include <vector>
#include <memory>

#include "db/database.h"
#include "db/db_manager.h"

namespace fundex {

/** Base ORM for Database tables.
  *
  */
template <typename T>
class Table {
 public:
    Table();
    virtual ~Table();

    /** Adds row to table.
     *  \returns ID from Database.
     */
    virtual int add(const T& row);

    /** Removes row from table.
     *
     */
    virtual void remove(int id);

    /** Returns row with requested id from table.
     *  Returns nullptr if row with requested id is not found.
     */
    virtual std::unique_ptr<T> get(int id) const;

    /** Removes all rows from table.
     *
     */
    virtual void remove_all();

    /** Returns all rows from table.
     *
     */
    virtual std::vector<T> get_all() const;

    /** Returns table size.
     *
     */
    virtual std::size_t size() const;

    /** Id for non-existent record.
     *
     */
    static const int invalid_id = -1;

 protected:
    /// sqlite_orm storage.
    Database* db;
};

template <typename T>
const int Table<T>::invalid_id;

template <typename T>
Table<T>::Table():
    db(DBManager::get_database()) {
    if (db == nullptr) {
        throw std::runtime_error("Database is not initialized!");
    }
}

template <typename T>
Table<T>::~Table() {
}

template <typename T>
int Table<T>::add(const T &row) {
    int id = db->insert(row);
    return id;
}

template <typename T>
void Table<T>::remove(int id) {
    db->remove<T>(id);
}

template <typename T>
std::unique_ptr<T> Table<T>::get(int id) const {
    return db->get_pointer<T>(id);
}

template <typename T>
void Table<T>::remove_all() {
    db->remove_all<T>();
}

template <typename T>
std::vector<T> Table<T>::get_all() const {
    return db->get_all<T>();
}

template<typename T>
std::size_t Table<T>::size() const {
    return get_all().size();
}

};  // namespace fundex

#endif  // SRC_DB_TABLE_H_
