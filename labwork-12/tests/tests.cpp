#include "gtest/gtest.h"
#include "./lib/SQLClass.h"

TEST(SQLClass, CreateTable) {
    SQLClass s;
    std::string k = R"(
"create table use (
    "Age" integer PRIMARY KEY NOT NULL,
    name varchar(255),
    www float,
    qqq double,
    bbb bool
    );"
    )";
    s.ParsingRequest(k);
    EXPECT_EQ(s.GetSizeTable("use"), 0);
}

TEST(SQLClass, InsertInto) {
    SQLClass s;
    std::string k = R"(
"create table use (
    "Age" integer PRIMARY KEY NOT NULL,
    name varchar(255),
    www float,
    qqq double,
    bbb bool
    );
insert into use  values (19, "Ivan", 1.2, 1.2, true);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 18, 1.2, 1.2, false);"
select * from use;"
    )";
    s.ParsingRequest(k);
    EXPECT_EQ(s.GetSizeTable("use"), 2);
}

TEST(SQLClass, DropTable) {
    SQLClass s;
    std::string k = R"(
"create table use (
    "Age" integer PRIMARY KEY NOT NULL,
    name varchar(255),
    www float,
    qqq double,
    bbb bool
    );
insert into use  values (19, "Ivan", 1.2, 1.2, true);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 18, 1.2, 1.2, false);
select * from use;
drop table Use;"
    )";
    s.ParsingRequest(k);
    EXPECT_EQ(s.GetSizeTable("use"), 0);
}

TEST(SQLClass, Select) {
    SQLClass s;
    std::string k = R"(
"create table use (
    "Age" integer PRIMARY KEY NOT NULL,
    name varchar(255) NOT NULL,
    www float,
    qqq double,
    bbb bool
    );
insert into use  values (19, "Ivan", 1.2, 1.2, true);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 18, 1.2, 1.2, false);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 18, 1.2, 1.2, false);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 18, 1.2, 1.2, false);"
select * from use;"
    )";
    s.ParsingRequest(k);
}

TEST(SQLClass, Select2) {
    SQLClass s;
    std::string k = R"(
"create table use (
    "Age" integer PRIMARY KEY NOT NULL,
    name varchar(255) NOT NULL,
    www float,
    qqq double,
    bbb bool
    );
insert into use  values (19, "Ivan", 1.2, 1.2, true);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 18, 1.2, 1.2, false);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 20, 1.2, 1.2, false);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 22, 1.2, 1.2, false);"
select * from use where "Age" = 19;"
    )";
    s.ParsingRequest(k);
}

TEST(SQLClass, Select3) {
    SQLClass s;
    std::string k = R"(
"create table use (
    "Age" integer PRIMARY KEY NOT NULL,
    name varchar(255) NOT NULL,
    www float,
    qqq double,
    bbb bool
    );
insert into use  values (19, "Ivan", 1.2, 1.2, true);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 18, 1.2, 1.2, false);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 20, 1.2, 1.2, false);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 22, 1.2, 1.2, false);
select * from use;"
    )";
    s.ParsingRequest(k);
}

TEST(SQLClass, Select4) {
    SQLClass s;
    std::string k = R"(
"create table use (
    "Age" integer PRIMARY KEY NOT NULL,
    name varchar(255) NOT NULL,
    www float,
    qqq double,
    bbb bool
    );
insert into use  values (19, "Ivan", 1.2, 1.2, true);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 18, 1.2, 1.2, false);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 20, 1.2, 1.2, false);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 22, 1.2, 1.2, false);
select * from use where "Age" = 19;"
    )";
    s.ParsingRequest(k);
}

TEST(SQLClass, Select5) {
    SQLClass s;
    std::string k = R"(
"create table use (
    "Age" integer PRIMARY KEY NOT NULL,
    name varchar(255) NOT NULL,
    www float,
    qqq double,
    bbb bool
    );
insert into use  values (19, "Ivan", 1.2, 1.2, true);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 18, 1.2, 1.2, false);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 20, 1.2, 1.2, false);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 22, 1.2, 1.2, false);
select * from use where "Age" = 19 or "Age" = 20;
    )";
    s.ParsingRequest(k);
}

TEST(SQLClass, Select6) {
    SQLClass s;
    std::string k = R"(
"create table use (
    "Age" integer PRIMARY KEY NOT NULL,
    name varchar(255) NOT NULL,
    www float,
    qqq double,
    bbb bool
    );
insert into use  values (19, "Ivan", 1.2, 1.2, true);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 18, 1.2, 1.2, false);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 20, 1.2, 1.2, false);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 22, 1.2, 1.2, false);
select * from use where "Age" = 19 or "Age" = 20 and "Age" = 21;"
    )";
    s.ParsingRequest(k);
}

TEST(SQLClass, Select7) {
    SQLClass s;
    std::string k = R"(
"create table use (
    "Age" integer PRIMARY KEY NOT NULL,
    name varchar(255) NOT NULL,
    www float,
    qqq double,
    bbb bool
    );
insert into use  values (19, "Ivan", 1.2, 1.2, true);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 18, 1.2, 1.2, false);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 20, 1.2, 1.2, false);
select * from use where "Age" = 19 or "Age" = 20 and "Age" = 21;"
    )";
    s.ParsingRequest(k);
}

TEST(SQLClass, Select8) {
    SQLClass s;
    std::string k = R"(
"create table use (
    "Age" integer PRIMARY KEY NOT NULL,
    name varchar(255) NOT NULL,
    www float,
    qqq double,
    bbb bool
    );
insert into use  values (19, "Ivan", 1.2, 1.2, true);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 18, 1.2, 1.2, false);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 20, 1.2, 1.2, false);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 22, 1.2, 1.2, false);
delete from use where "Age" = 19 or "Age" = 20 and "Age" = 21;"
select * from use;"
    )";
    s.ParsingRequest(k);
}

TEST(SQLClass, Select9) {
    SQLClass s;
    std::string k = R"(
"create table use (
    "Age" integer PRIMARY KEY NOT NULL,
    name varchar(255) NOT NULL,
    www float,
    qqq double,
    bbb bool
    );
insert into use  values (19, "Ivan", 1.2, 1.2, true);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 18, 1.2, 1.2, false);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 20, 1.2, 1.2, false);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 22, 1.2, 1.2, false);
update use set name = "Misha" where "Age" = 19 or "Age" = 20 and "Age" = 21;"
select * from use;"
    )";
    s.ParsingRequest(k);
}

TEST(SQLClass, Select10) {
    SQLClass s;
    std::string k = R"(
"create table use (
    "Age" integer PRIMARY KEY NOT NULL,
    name varchar(255) NOT NULL,
    www float,
    qqq double,
    bbb bool
    );
create table use2 (
    "Age" integer PRIMARY KEY NOT NULL,
    name varchar(255) NOT NULL,
    home integer,
    www float,
    qqq double,
);
insert into use values (19, "Ivan", 1.2, 1.2, true);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 18, 1.2, 1.2, false);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 20, 1.2, 1.2, false);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 21, 1.2, 1.2, false);
insert into use (name, "Age", www, qqq, bbb) values ("Ivan", 22, 141, 1.2, false);
update use set name = "Misha" where "Age" > 3;
insert into use2 values (19, "Ivan", 154, 1.2, 1.2);
insert into use2 (name, "Age", home, www, qqq) values ("Ivan", 18, 1, 1.2, 1.2);
insert into use2 (name, "Age", home, www, qqq) values ("Ivan", 20, 2, 1.2, 1.2);
insert into use2 (name, "Age", home, www, qqq) values ("Ivan", 21, 3, 1.2, 1.2);
insert into use2 (name, "Age", home, www, qqq) values ("Ivan", 25, 4, 1.2, 1.2);
select * from use;
select * from use2;
select * from use join use2 on use."Age" = use2."Age";
    )";
    s.ParsingRequest(k);
}

TEST(SQLClass, Select11) {
    SQLClass s;
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
select "Age", name from use where "Age" > 20;
drop table use;
    )";
    s.ParsingRequest(k);
}

TEST(SQLClass, Select12) {
    SQLClass s;
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
    select use."Age", user."Age", use.name from use join user on user.Age = use.Age;
    select * from use;
    select * from user;
    drop table use;
    drop table user;
    )";
    s.ParsingRequest(k);
}

TEST(SQLClass, Select13) {
    SQLClass s;
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
select * from use left join user on user.Age = use.Age ;
drop table use;
    )";
    s.ParsingRequest(k);
}

TEST(SQLClass, Select14) {
    SQLClass s;
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
}
