static char sqla_program_id[292] = 
{
 172,0,65,69,65,78,65,73,70,65,105,70,79,97,71,99,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,8,0,66,75,82,65,86,67,
 72,69,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,8,0,66,73,66,65,85,84,72,79,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0
};

#include "sqladef.h"

static struct sqla_runtime_info sqla_rtinfo = 
{{'S','Q','L','A','R','T','I','N'}, sizeof(wchar_t), 0, {' ',' ',' ',' '}};


static const short sqlIsLiteral   = SQL_IS_LITERAL;
static const short sqlIsInputHvar = SQL_IS_INPUT_HVAR;


#line 1 "bibauthor.sqC"
#include <iostream>
#include "util.h"
#include <stdlib.h>
#include <vector>
#include <string.h>

using namespace std;


/*
EXEC SQL INCLUDE SQLCA;
*/

/* SQL Communication Area - SQLCA - structures and constants */
#include "sqlca.h"
struct sqlca sqlca;


#line 9 "bibauthor.sqC"
 

int main(int argc, char *argv[]) {
	char * getpass();
	string myLine;
    vector <string> listOfPublications;

	
/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 16 "bibauthor.sqC"

	char db[6] = "cs348";
    char result[100];
   
    sqlint32 pk;
    char charPk[10];
    char name[22];
    char url[42];

    char title[70];
    char publisher[50];
    char appearsin[10];
    sqlint32 author;
    sqlint32 order;
    sqlint32 year;
    sqlint32 startpage;
    sqlint32 endpage;
    sqlint32 volume;
    sqlint32 number;
    
    
	
/*
EXEC SQL END DECLARE SECTION;
*/

#line 37 "bibauthor.sqC"

   
	
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 39 "bibauthor.sqC"

	
/*
EXEC SQL CONNECT TO :db;
*/

{
#line 40 "bibauthor.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 40 "bibauthor.sqC"
  sqlaaloc(2,1,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 40 "bibauthor.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 6;
#line 40 "bibauthor.sqC"
      sql_setdlist[0].sqldata = (void*)db;
#line 40 "bibauthor.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 40 "bibauthor.sqC"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 40 "bibauthor.sqC"
  sqlacall((unsigned short)29,4,2,0,0L);
#line 40 "bibauthor.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 40 "bibauthor.sqC"
  sqlastop(0L);
}

#line 40 "bibauthor.sqC"
   
   
    getline(cin,myLine);
    
    
    strcpy(name,myLine.c_str());
    
    
    
/*
EXEC SQL 
    DECLARE C1 CURSOR FOR
    
    select d.pubid from 
    ((select pubid, year from proceedings) union (select pubid, year from journal) union (select pubid, year from book)) c 
    right join 
    (select a.pubid, a.title, b.firstAuthor 
     from (select pubid, title from publication where pubid in (select pubid from author, wrote where author.name = :name and author.aid = wrote.aid)) a, 
     (select author.name as firstAuthor, pubid from author, wrote where aorder = '1' and author.aid = wrote.aid) b 
     where a.pubid = b.pubid) d 
    on c.pubid = d.pubid 
    order by d.firstAuthor, c.year;
*/

#line 59 "bibauthor.sqC"
    
    
    
/*
EXEC SQL 
    OPEN C1;
*/

{
#line 62 "bibauthor.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 62 "bibauthor.sqC"
  sqlaaloc(2,1,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 62 "bibauthor.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 22;
#line 62 "bibauthor.sqC"
      sql_setdlist[0].sqldata = (void*)name;
#line 62 "bibauthor.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 62 "bibauthor.sqC"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 62 "bibauthor.sqC"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 62 "bibauthor.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 62 "bibauthor.sqC"
  sqlastop(0L);
}

#line 62 "bibauthor.sqC"

    
    for( ;; ) {
        
        
/*
EXEC SQL
        FETCH C1 INTO :result;
*/

{
#line 67 "bibauthor.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 67 "bibauthor.sqC"
  sqlaaloc(3,1,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 67 "bibauthor.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 100;
#line 67 "bibauthor.sqC"
      sql_setdlist[0].sqldata = (void*)result;
#line 67 "bibauthor.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 67 "bibauthor.sqC"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 67 "bibauthor.sqC"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 67 "bibauthor.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 67 "bibauthor.sqC"
  sqlastop(0L);
}

#line 67 "bibauthor.sqC"

        if (SQLCODE == 100) break;
        else if (SQLCODE < 0 ) break;
        string resultString = result;
        listOfPublications.push_back(resultString);
        
    }
    
    
/*
EXEC SQL 
    CLOSE C1;
*/

{
#line 76 "bibauthor.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 76 "bibauthor.sqC"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 76 "bibauthor.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 76 "bibauthor.sqC"
  sqlastop(0L);
}

#line 76 "bibauthor.sqC"

    
    
    for (int i = 0; i < listOfPublications.size(); i++){
        
        string typeOfPublication;
        
        strcpy(charPk,listOfPublications[i].c_str());
        
        cout << "Pubid: " << listOfPublications[i] << endl;
        
  
        
/*
EXEC SQL
            SELECT pubid into :result
            FROM journal
            WHERE pubid = :charPk;
*/

{
#line 91 "bibauthor.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 91 "bibauthor.sqC"
  sqlaaloc(2,1,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 91 "bibauthor.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 91 "bibauthor.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 91 "bibauthor.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 91 "bibauthor.sqC"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 91 "bibauthor.sqC"
  sqlaaloc(3,1,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 91 "bibauthor.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 100;
#line 91 "bibauthor.sqC"
      sql_setdlist[0].sqldata = (void*)result;
#line 91 "bibauthor.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 91 "bibauthor.sqC"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 91 "bibauthor.sqC"
  sqlacall((unsigned short)24,2,2,3,0L);
#line 91 "bibauthor.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 91 "bibauthor.sqC"
  sqlastop(0L);
}

#line 91 "bibauthor.sqC"

        
        if (SQLCODE != 100){
            typeOfPublication = "journal";
        }
        
        
/*
EXEC SQL
        SELECT pubid into :result
        FROM article
        WHERE pubid = :charPk;
*/

{
#line 100 "bibauthor.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 100 "bibauthor.sqC"
  sqlaaloc(2,1,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 100 "bibauthor.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 100 "bibauthor.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 100 "bibauthor.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 100 "bibauthor.sqC"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 100 "bibauthor.sqC"
  sqlaaloc(3,1,7,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 100 "bibauthor.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 100;
#line 100 "bibauthor.sqC"
      sql_setdlist[0].sqldata = (void*)result;
#line 100 "bibauthor.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 100 "bibauthor.sqC"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 100 "bibauthor.sqC"
  sqlacall((unsigned short)24,3,2,3,0L);
#line 100 "bibauthor.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 100 "bibauthor.sqC"
  sqlastop(0L);
}

#line 100 "bibauthor.sqC"

        
        if (SQLCODE != 100){
            typeOfPublication = "article";
        }
        
/*
EXEC SQL
        SELECT pubid into :result
        FROM book
        WHERE pubid = :charPk;
*/

{
#line 108 "bibauthor.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 108 "bibauthor.sqC"
  sqlaaloc(2,1,8,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 108 "bibauthor.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 108 "bibauthor.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 108 "bibauthor.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 108 "bibauthor.sqC"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 108 "bibauthor.sqC"
  sqlaaloc(3,1,9,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 108 "bibauthor.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 100;
#line 108 "bibauthor.sqC"
      sql_setdlist[0].sqldata = (void*)result;
#line 108 "bibauthor.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 108 "bibauthor.sqC"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 108 "bibauthor.sqC"
  sqlacall((unsigned short)24,4,2,3,0L);
#line 108 "bibauthor.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 108 "bibauthor.sqC"
  sqlastop(0L);
}

#line 108 "bibauthor.sqC"

        
        if (SQLCODE != 100){
            typeOfPublication = "book";
        }
        
/*
EXEC SQL
        SELECT pubid into :result
        FROM proceedings
        WHERE pubid = :charPk;
*/

{
#line 116 "bibauthor.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 116 "bibauthor.sqC"
  sqlaaloc(2,1,10,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 116 "bibauthor.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 116 "bibauthor.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 116 "bibauthor.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 116 "bibauthor.sqC"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 116 "bibauthor.sqC"
  sqlaaloc(3,1,11,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 116 "bibauthor.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 100;
#line 116 "bibauthor.sqC"
      sql_setdlist[0].sqldata = (void*)result;
#line 116 "bibauthor.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 116 "bibauthor.sqC"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 116 "bibauthor.sqC"
  sqlacall((unsigned short)24,5,2,3,0L);
#line 116 "bibauthor.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 116 "bibauthor.sqC"
  sqlastop(0L);
}

#line 116 "bibauthor.sqC"

        
        if (SQLCODE != 100){
            typeOfPublication = "proceedings";
        }
        
        cout << "Type: " << typeOfPublication << endl;
        
        
        cout << "Authors: ";
        
        
/*
EXEC SQL
            DECLARE C2 CURSOR FOR
            SELECT author.name
            FROM author, wrote 
            WHERE author.aid = wrote.aid
            AND wrote.pubid = :charPk 
            ORDER BY aorder;
*/

#line 133 "bibauthor.sqC"

        
        
/*
EXEC SQL 
        OPEN C2;
*/

{
#line 136 "bibauthor.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 136 "bibauthor.sqC"
  sqlaaloc(2,1,12,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 136 "bibauthor.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 136 "bibauthor.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 136 "bibauthor.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 136 "bibauthor.sqC"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 136 "bibauthor.sqC"
  sqlacall((unsigned short)26,6,2,0,0L);
#line 136 "bibauthor.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 136 "bibauthor.sqC"
  sqlastop(0L);
}

#line 136 "bibauthor.sqC"

        
        string resultString;
        int resultInt; 
        
        for( ;; ) {
            
            
/*
EXEC SQL
            FETCH C2 INTO :result;
*/

{
#line 144 "bibauthor.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 144 "bibauthor.sqC"
  sqlaaloc(3,1,13,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 144 "bibauthor.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 100;
#line 144 "bibauthor.sqC"
      sql_setdlist[0].sqldata = (void*)result;
#line 144 "bibauthor.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 144 "bibauthor.sqC"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 144 "bibauthor.sqC"
  sqlacall((unsigned short)25,6,0,3,0L);
#line 144 "bibauthor.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 144 "bibauthor.sqC"
  sqlastop(0L);
}

#line 144 "bibauthor.sqC"

            if (SQLCODE == 100) break;
            else if (SQLCODE < 0 ) break;
            resultString = result;
            cout << resultString;
        }
        
        cout << endl;
        
        
/*
EXEC SQL 
        CLOSE C2;
*/

{
#line 154 "bibauthor.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 154 "bibauthor.sqC"
  sqlacall((unsigned short)20,6,0,0,0L);
#line 154 "bibauthor.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 154 "bibauthor.sqC"
  sqlastop(0L);
}

#line 154 "bibauthor.sqC"

        
        
/*
EXEC SQL
            SELECT title into :result
            FROM publication
            WHERE pubid = :charPk;
*/

{
#line 159 "bibauthor.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 159 "bibauthor.sqC"
  sqlaaloc(2,1,14,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 159 "bibauthor.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 159 "bibauthor.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 159 "bibauthor.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 159 "bibauthor.sqC"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 159 "bibauthor.sqC"
  sqlaaloc(3,1,15,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 159 "bibauthor.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 100;
#line 159 "bibauthor.sqC"
      sql_setdlist[0].sqldata = (void*)result;
#line 159 "bibauthor.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 159 "bibauthor.sqC"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 159 "bibauthor.sqC"
  sqlacall((unsigned short)24,7,2,3,0L);
#line 159 "bibauthor.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 159 "bibauthor.sqC"
  sqlastop(0L);
}

#line 159 "bibauthor.sqC"

        
        
        resultString = result;
        cout << "Title: " << resultString << endl; 
        
        
        if (typeOfPublication == "book"){
            
/*
EXEC SQL
                SELECT publisher, year into :publisher, :year
                FROM book
                WHERE pubid = :charPk;
*/

{
#line 170 "bibauthor.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 170 "bibauthor.sqC"
  sqlaaloc(2,1,16,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 170 "bibauthor.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 170 "bibauthor.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 170 "bibauthor.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 170 "bibauthor.sqC"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 170 "bibauthor.sqC"
  sqlaaloc(3,2,17,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 170 "bibauthor.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 50;
#line 170 "bibauthor.sqC"
      sql_setdlist[0].sqldata = (void*)publisher;
#line 170 "bibauthor.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 170 "bibauthor.sqC"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 170 "bibauthor.sqC"
      sql_setdlist[1].sqldata = (void*)&year;
#line 170 "bibauthor.sqC"
      sql_setdlist[1].sqlind = 0L;
#line 170 "bibauthor.sqC"
      sqlasetdata(3,0,2,sql_setdlist,0L,0L);
    }
#line 170 "bibauthor.sqC"
  sqlacall((unsigned short)24,8,2,3,0L);
#line 170 "bibauthor.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 170 "bibauthor.sqC"
  sqlastop(0L);
}

#line 170 "bibauthor.sqC"

            
            resultString = publisher;
            cout << "Publisher: " << resultString << endl;
            cout << "Year: " << year << endl;
        }
        
        else if (typeOfPublication == "proceedings"){
            
/*
EXEC SQL
                SELECT year into :year
                FROM proceedings
                WHERE pubid = :charPk;
*/

{
#line 181 "bibauthor.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 181 "bibauthor.sqC"
  sqlaaloc(2,1,18,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 181 "bibauthor.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 181 "bibauthor.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 181 "bibauthor.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 181 "bibauthor.sqC"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 181 "bibauthor.sqC"
  sqlaaloc(3,1,19,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 181 "bibauthor.sqC"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 181 "bibauthor.sqC"
      sql_setdlist[0].sqldata = (void*)&year;
#line 181 "bibauthor.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 181 "bibauthor.sqC"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 181 "bibauthor.sqC"
  sqlacall((unsigned short)24,9,2,3,0L);
#line 181 "bibauthor.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 181 "bibauthor.sqC"
  sqlastop(0L);
}

#line 181 "bibauthor.sqC"

            
            cout << "Year: " << year << endl;
        }
        
        else if (typeOfPublication == "journal"){
            
/*
EXEC SQL
                SELECT volume, number, year into :volume, :number, :year
                FROM journal
                WHERE pubid = :charPk;
*/

{
#line 190 "bibauthor.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 190 "bibauthor.sqC"
  sqlaaloc(2,1,20,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 190 "bibauthor.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 190 "bibauthor.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 190 "bibauthor.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 190 "bibauthor.sqC"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 190 "bibauthor.sqC"
  sqlaaloc(3,3,21,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 190 "bibauthor.sqC"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 190 "bibauthor.sqC"
      sql_setdlist[0].sqldata = (void*)&volume;
#line 190 "bibauthor.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 190 "bibauthor.sqC"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 190 "bibauthor.sqC"
      sql_setdlist[1].sqldata = (void*)&number;
#line 190 "bibauthor.sqC"
      sql_setdlist[1].sqlind = 0L;
#line 190 "bibauthor.sqC"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 190 "bibauthor.sqC"
      sql_setdlist[2].sqldata = (void*)&year;
#line 190 "bibauthor.sqC"
      sql_setdlist[2].sqlind = 0L;
#line 190 "bibauthor.sqC"
      sqlasetdata(3,0,3,sql_setdlist,0L,0L);
    }
#line 190 "bibauthor.sqC"
  sqlacall((unsigned short)24,10,2,3,0L);
#line 190 "bibauthor.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 190 "bibauthor.sqC"
  sqlastop(0L);
}

#line 190 "bibauthor.sqC"

            
            cout << "Volume: " << volume << endl;
            cout << "Number: " << number << endl;
            cout << "Year: " << year << endl;
        }
        
        else if (typeOfPublication == "article"){
            
/*
EXEC SQL
                SELECT appearsin, startpage, endpage into :appearsin, :startpage, :endpage
                FROM article
                WHERE pubid = :charPk;
*/

{
#line 201 "bibauthor.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 201 "bibauthor.sqC"
  sqlaaloc(2,1,22,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 201 "bibauthor.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 201 "bibauthor.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 201 "bibauthor.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 201 "bibauthor.sqC"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 201 "bibauthor.sqC"
  sqlaaloc(3,3,23,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 201 "bibauthor.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 201 "bibauthor.sqC"
      sql_setdlist[0].sqldata = (void*)appearsin;
#line 201 "bibauthor.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 201 "bibauthor.sqC"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 201 "bibauthor.sqC"
      sql_setdlist[1].sqldata = (void*)&startpage;
#line 201 "bibauthor.sqC"
      sql_setdlist[1].sqlind = 0L;
#line 201 "bibauthor.sqC"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 201 "bibauthor.sqC"
      sql_setdlist[2].sqldata = (void*)&endpage;
#line 201 "bibauthor.sqC"
      sql_setdlist[2].sqlind = 0L;
#line 201 "bibauthor.sqC"
      sqlasetdata(3,0,3,sql_setdlist,0L,0L);
    }
#line 201 "bibauthor.sqC"
  sqlacall((unsigned short)24,11,2,3,0L);
#line 201 "bibauthor.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 201 "bibauthor.sqC"
  sqlastop(0L);
}

#line 201 "bibauthor.sqC"

            
            string temp = appearsin;
            
            strcpy(charPk,temp.c_str());

            
            
            
/*
EXEC SQL
            SELECT title into :result
                FROM publication
                WHERE pubid = :charPk;
*/

{
#line 212 "bibauthor.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 212 "bibauthor.sqC"
  sqlaaloc(2,1,24,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 212 "bibauthor.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 212 "bibauthor.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 212 "bibauthor.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 212 "bibauthor.sqC"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 212 "bibauthor.sqC"
  sqlaaloc(3,1,25,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 212 "bibauthor.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 100;
#line 212 "bibauthor.sqC"
      sql_setdlist[0].sqldata = (void*)result;
#line 212 "bibauthor.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 212 "bibauthor.sqC"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 212 "bibauthor.sqC"
  sqlacall((unsigned short)24,12,2,3,0L);
#line 212 "bibauthor.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 212 "bibauthor.sqC"
  sqlastop(0L);
}

#line 212 "bibauthor.sqC"

            
            resultString = result;
            
            cout << "In: " << resultString << endl;
            cout << "Pages: " << startpage << " - " << endpage << endl;
        }
        
        cout << endl;
        
        
    }
    
	
	
/*
EXEC SQL COMMIT;
*/

{
#line 226 "bibauthor.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 226 "bibauthor.sqC"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 226 "bibauthor.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 226 "bibauthor.sqC"
  sqlastop(0L);
}

#line 226 "bibauthor.sqC"

	
/*
EXEC SQL CONNECT reset;
*/

{
#line 227 "bibauthor.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 227 "bibauthor.sqC"
  sqlacall((unsigned short)29,3,0,0,0L);
#line 227 "bibauthor.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 227 "bibauthor.sqC"
  sqlastop(0L);
}

#line 227 "bibauthor.sqC"

	
	exit(0);
	
error:
	check_error("Bad input",&sqlca);
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 233 "bibauthor.sqC"


	
/*
EXEC SQL ROLLBACK;
*/

{
#line 235 "bibauthor.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 235 "bibauthor.sqC"
  sqlacall((unsigned short)28,0,0,0,0L);
#line 235 "bibauthor.sqC"
  sqlastop(0L);
}

#line 235 "bibauthor.sqC"

	
/*
EXEC SQL CONNECT reset;
*/

{
#line 236 "bibauthor.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 236 "bibauthor.sqC"
  sqlacall((unsigned short)29,3,0,0,0L);
#line 236 "bibauthor.sqC"
  sqlastop(0L);
}

#line 236 "bibauthor.sqC"

	exit(1);
	
	
	
}
	



