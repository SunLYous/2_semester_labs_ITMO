#include <iostream>
#include "./lib/AbstractValueType.h"
#include "./lib/SQLClass.h"
#include "./lib/CreateTableRequest.h"
#include "./lib/WhereParser.h"

int main() {
    SQLClass s;
    std::string r = "aaa";
    std::string k = R"(
"create table use (
    "Age" integer PRIMARY KEY NOT NULL,
    name varchar(255),
    www float,
    qqq double,
    bbb bool
    );
insert into use values (19, "Ivan", 1.2, 1.2, true);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 18, 1.2, 1.2, false);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 20, 1.2, 1.2, false);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 21, 1.2, 1.2, false);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 22, 1.2, 1.2, false);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 23, 1.2, 1.2, false);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 24, 1.2, 1.2, false);
insert into use values (25, "Ivan", 1.2, 1.2, true);
insert into use values (26, "Ivan", 1.2, 1.2, true);
insert into use values (27, "Ivan", 1.2, 1.2, true);
update use set name = "Misha", www = 1.3, qqq = 1.3, bbb = false where Age >17;
select * from use where Age > 23;
create table user (
    "Age" integer PRIMARY KEY NOT NULL,
    name varchar(255),
    www float,
    qqq double,
    bbb bool
    );
insert into user values (19, "Ivan", 1.2, 1.2, true);
insert into user (name, "Age", www, qqq, bbb) values ("Ivan", 18, 1.2, 1.2, false);
insert into user (name, "Age", www, qqq, bbb) values ("Ivan", 20, 1.2, 1.2, false);
insert into user (name, "Age", www, qqq, bbb) values ("Ivan", 21, 1.2, 1.2, false);
insert into user (name, "Age", www, qqq, bbb) values ("Ivan", 22, 1.2, 1.2, false);
select * from use right join user on use.Age = user.Age;
drop table use;
    )";
    s.ParsingRequest(k);
    return 0;
}
