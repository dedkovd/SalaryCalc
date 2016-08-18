create table  if not exists employees (id integer primary key, parent integer, name varchar(100) not null, base_salary int not null, date_of_employment date not null, type int not null);
delete from employees;
insert into employees(parent, name, base_salary, date_of_employment, type) values (null, 'Sales 1', 150, '2005-04-11', 2);
insert into employees(parent, name, base_salary, date_of_employment, type) values (1, 'Manager 1', 200, '2006-01-13', 1);
insert into employees(parent, name, base_salary, date_of_employment, type) values (2, 'Employee 1', 100, '2007-08-10', 0);
insert into employees(parent, name, base_salary, date_of_employment, type) values (2, 'Employee 2', 110, '2005-11-11', 0);
insert into employees(parent, name, base_salary, date_of_employment, type) values (2, 'Sales 2', 120, '2007-01-25', 2);
insert into employees(parent, name, base_salary, date_of_employment, type) values (5, 'Employee 3', 80, '2005-04-11', 0);
insert into employees(parent, name, base_salary, date_of_employment, type) values (1, 'Employee 4', 105, '2006-01-13', 0);
insert into employees(parent, name, base_salary, date_of_employment, type) values (1, 'Sales 3', 115, '2007-08-10', 2);
insert into employees(parent, name, base_salary, date_of_employment, type) values (8, 'Employee 5', 100, '2005-11-11', 0);
insert into employees(parent, name, base_salary, date_of_employment, type) values (8, 'Employee 6', 120, '2007-01-25', 0);