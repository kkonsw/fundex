# fundex

Simple CLI Expense Tracker written with C++.

*WORK IN PROGRESS*

## Dependencies

| lib          | usage                |
|--------------|----------------------|
| `sqlite_orm` | ORM                  |
| `Catch2`     | testing              |
| `libfort`    | pretty tables        |
| `CLI11`      | command line parsing |

## Build

`libsqlite3` is required!

```sh
mkdir build
cd build
cmake ..
make
```

## Database ER Diagram

![](ER.png)

## Examples

List Transactions:

```sh
fundex show --all

+----+-----------+-------------+----------------+--------+
| ID | Category  | Date        | Note           | Amount |
+----+-----------+-------------+----------------+--------+
| 4  | Food      | 21 Jan 2021 | coffee house   | 7      |
| 5  | -         | 21 Jan 2021 | random         | 10     |
| 6  | Transport | 21 Jan 2021 | taxi from work | 5      |
+----+-----------+-------------+----------------+--------+
|                                         Total | 22     |
+-----------------------------------------------+--------+
```

List Categories:

```sh
fundex --list_cat

+----+---------------+
| ID | Category      |
+----+---------------+
| 1  | Bills         |
| 2  | Food          |
| 3  | Leisure       |
| 4  | Homeneeds     |
| 5  | Transport     |
| 6  | Healthcare    |
| 7  | Miscellaneous |
+----+---------------+
```

Add, Remove Transactions:

```sh
fundex add 12 --note "new transaction" --cat 7
fundex rm --all
```
