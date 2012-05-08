/*
    This file is part of VocabTrainer.

    VocabTrainer is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with VocabTrainer.  If not, see <http://www.gnu.org/licenses/>. 
*/
#include "Database.hpp"

using VocabTrainer::Database;


Database::Database()
{
    db = QSqlDatabase::addDatabase("QSQLITE");

}

Database::~Database()
{
    if(db.isOpen())
        db.close();
}


void Database::open(const char* file)
{
    if(db.isOpen())
        db.close();
    
    db.setDatabaseName(file);
    if (!db.open()) 
    {
        throw "cant open db";
    }
}
