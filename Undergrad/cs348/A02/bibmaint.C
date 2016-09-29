static char sqla_program_id[292] = 
{
 172,0,65,69,65,78,65,73,86,65,81,70,79,97,71,99,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,8,0,66,75,82,65,86,67,
 72,69,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,8,0,66,73,66,77,65,73,78,84,0,0,0,0,0,0,0,0,
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


#line 1 "bibmaint.sqC"
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


#line 9 "bibmaint.sqC"
 



/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 12 "bibmaint.sqC"

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

#line 33 "bibmaint.sqC"





void print (string value){
    
    
        
    
    string typeOfPublication;
    
    strcpy(charPk,value.c_str());
    
    cout << "Pubid: " << value << endl;
    
    
    
/*
EXEC SQL
    SELECT pubid into :result
    FROM journal
    WHERE pubid = :charPk;
*/

{
#line 53 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 53 "bibmaint.sqC"
  sqlaaloc(2,1,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 53 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 53 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 53 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 53 "bibmaint.sqC"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 53 "bibmaint.sqC"
  sqlaaloc(3,1,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 53 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 100;
#line 53 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)result;
#line 53 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 53 "bibmaint.sqC"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 53 "bibmaint.sqC"
  sqlacall((unsigned short)24,1,2,3,0L);
#line 53 "bibmaint.sqC"
  sqlastop(0L);
}

#line 53 "bibmaint.sqC"

    
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
#line 62 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 62 "bibmaint.sqC"
  sqlaaloc(2,1,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 62 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 62 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 62 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 62 "bibmaint.sqC"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 62 "bibmaint.sqC"
  sqlaaloc(3,1,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 62 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 100;
#line 62 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)result;
#line 62 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 62 "bibmaint.sqC"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 62 "bibmaint.sqC"
  sqlacall((unsigned short)24,2,2,3,0L);
#line 62 "bibmaint.sqC"
  sqlastop(0L);
}

#line 62 "bibmaint.sqC"

    
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
#line 70 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 70 "bibmaint.sqC"
  sqlaaloc(2,1,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 70 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 70 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 70 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 70 "bibmaint.sqC"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 70 "bibmaint.sqC"
  sqlaaloc(3,1,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 70 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 100;
#line 70 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)result;
#line 70 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 70 "bibmaint.sqC"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 70 "bibmaint.sqC"
  sqlacall((unsigned short)24,3,2,3,0L);
#line 70 "bibmaint.sqC"
  sqlastop(0L);
}

#line 70 "bibmaint.sqC"

    
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
#line 78 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 78 "bibmaint.sqC"
  sqlaaloc(2,1,7,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 78 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 78 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 78 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 78 "bibmaint.sqC"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 78 "bibmaint.sqC"
  sqlaaloc(3,1,8,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 78 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 100;
#line 78 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)result;
#line 78 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 78 "bibmaint.sqC"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 78 "bibmaint.sqC"
  sqlacall((unsigned short)24,4,2,3,0L);
#line 78 "bibmaint.sqC"
  sqlastop(0L);
}

#line 78 "bibmaint.sqC"

    
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

#line 95 "bibmaint.sqC"

    
    
/*
EXEC SQL 
    OPEN C2;
*/

{
#line 98 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 98 "bibmaint.sqC"
  sqlaaloc(2,1,9,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 98 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 98 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 98 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 98 "bibmaint.sqC"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 98 "bibmaint.sqC"
  sqlacall((unsigned short)26,5,2,0,0L);
#line 98 "bibmaint.sqC"
  sqlastop(0L);
}

#line 98 "bibmaint.sqC"

    
    string resultString;
    int resultInt; 
    
    for( ;; ) {
        
        
/*
EXEC SQL
        FETCH C2 INTO :result;
*/

{
#line 106 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 106 "bibmaint.sqC"
  sqlaaloc(3,1,10,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 106 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 100;
#line 106 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)result;
#line 106 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 106 "bibmaint.sqC"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 106 "bibmaint.sqC"
  sqlacall((unsigned short)25,5,0,3,0L);
#line 106 "bibmaint.sqC"
  sqlastop(0L);
}

#line 106 "bibmaint.sqC"

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
#line 116 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 116 "bibmaint.sqC"
  sqlacall((unsigned short)20,5,0,0,0L);
#line 116 "bibmaint.sqC"
  sqlastop(0L);
}

#line 116 "bibmaint.sqC"

    
    
/*
EXEC SQL
    SELECT title into :result
    FROM publication
    WHERE pubid = :charPk;
*/

{
#line 121 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 121 "bibmaint.sqC"
  sqlaaloc(2,1,11,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 121 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 121 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 121 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 121 "bibmaint.sqC"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 121 "bibmaint.sqC"
  sqlaaloc(3,1,12,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 121 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 100;
#line 121 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)result;
#line 121 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 121 "bibmaint.sqC"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 121 "bibmaint.sqC"
  sqlacall((unsigned short)24,6,2,3,0L);
#line 121 "bibmaint.sqC"
  sqlastop(0L);
}

#line 121 "bibmaint.sqC"

    
    
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
#line 132 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 132 "bibmaint.sqC"
  sqlaaloc(2,1,13,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 132 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 132 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 132 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 132 "bibmaint.sqC"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 132 "bibmaint.sqC"
  sqlaaloc(3,2,14,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 132 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 50;
#line 132 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)publisher;
#line 132 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 132 "bibmaint.sqC"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 132 "bibmaint.sqC"
      sql_setdlist[1].sqldata = (void*)&year;
#line 132 "bibmaint.sqC"
      sql_setdlist[1].sqlind = 0L;
#line 132 "bibmaint.sqC"
      sqlasetdata(3,0,2,sql_setdlist,0L,0L);
    }
#line 132 "bibmaint.sqC"
  sqlacall((unsigned short)24,7,2,3,0L);
#line 132 "bibmaint.sqC"
  sqlastop(0L);
}

#line 132 "bibmaint.sqC"

        
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
#line 143 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 143 "bibmaint.sqC"
  sqlaaloc(2,1,15,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 143 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 143 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 143 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 143 "bibmaint.sqC"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 143 "bibmaint.sqC"
  sqlaaloc(3,1,16,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 143 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 143 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)&year;
#line 143 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 143 "bibmaint.sqC"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 143 "bibmaint.sqC"
  sqlacall((unsigned short)24,8,2,3,0L);
#line 143 "bibmaint.sqC"
  sqlastop(0L);
}

#line 143 "bibmaint.sqC"

        
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
#line 152 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 152 "bibmaint.sqC"
  sqlaaloc(2,1,17,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 152 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 152 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 152 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 152 "bibmaint.sqC"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 152 "bibmaint.sqC"
  sqlaaloc(3,3,18,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 152 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 152 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)&volume;
#line 152 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 152 "bibmaint.sqC"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 152 "bibmaint.sqC"
      sql_setdlist[1].sqldata = (void*)&number;
#line 152 "bibmaint.sqC"
      sql_setdlist[1].sqlind = 0L;
#line 152 "bibmaint.sqC"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 152 "bibmaint.sqC"
      sql_setdlist[2].sqldata = (void*)&year;
#line 152 "bibmaint.sqC"
      sql_setdlist[2].sqlind = 0L;
#line 152 "bibmaint.sqC"
      sqlasetdata(3,0,3,sql_setdlist,0L,0L);
    }
#line 152 "bibmaint.sqC"
  sqlacall((unsigned short)24,9,2,3,0L);
#line 152 "bibmaint.sqC"
  sqlastop(0L);
}

#line 152 "bibmaint.sqC"

        
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
#line 163 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 163 "bibmaint.sqC"
  sqlaaloc(2,1,19,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 163 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 163 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 163 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 163 "bibmaint.sqC"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 163 "bibmaint.sqC"
  sqlaaloc(3,3,20,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 163 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 163 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)appearsin;
#line 163 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 163 "bibmaint.sqC"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 163 "bibmaint.sqC"
      sql_setdlist[1].sqldata = (void*)&startpage;
#line 163 "bibmaint.sqC"
      sql_setdlist[1].sqlind = 0L;
#line 163 "bibmaint.sqC"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 163 "bibmaint.sqC"
      sql_setdlist[2].sqldata = (void*)&endpage;
#line 163 "bibmaint.sqC"
      sql_setdlist[2].sqlind = 0L;
#line 163 "bibmaint.sqC"
      sqlasetdata(3,0,3,sql_setdlist,0L,0L);
    }
#line 163 "bibmaint.sqC"
  sqlacall((unsigned short)24,10,2,3,0L);
#line 163 "bibmaint.sqC"
  sqlastop(0L);
}

#line 163 "bibmaint.sqC"

        
        string temp = appearsin;
        
        strcpy(charPk,temp.c_str());
        
        
        
        
/*
EXEC SQL
        SELECT title into :result
        FROM publication
        WHERE pubid = :charPk;
*/

{
#line 174 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 174 "bibmaint.sqC"
  sqlaaloc(2,1,21,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 174 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 174 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 174 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 174 "bibmaint.sqC"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 174 "bibmaint.sqC"
  sqlaaloc(3,1,22,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 174 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 100;
#line 174 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)result;
#line 174 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 174 "bibmaint.sqC"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 174 "bibmaint.sqC"
  sqlacall((unsigned short)24,11,2,3,0L);
#line 174 "bibmaint.sqC"
  sqlastop(0L);
}

#line 174 "bibmaint.sqC"

        
        resultString = result;
        
        cout << "In: " << resultString << endl;
        cout << "Pages: " << startpage << " - " << endpage << endl;
    }
    
    cout << endl;
    

    
    
    
    
}




int main(int argc, char *argv[]) {
	char * getpass();
	string myLine;


   
	
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 200 "bibmaint.sqC"

	
/*
EXEC SQL CONNECT TO :db;
*/

{
#line 201 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 201 "bibmaint.sqC"
  sqlaaloc(2,1,23,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 201 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 6;
#line 201 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)db;
#line 201 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 201 "bibmaint.sqC"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 201 "bibmaint.sqC"
  sqlacall((unsigned short)29,4,2,0,0L);
#line 201 "bibmaint.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 201 "bibmaint.sqC"
  sqlastop(0L);
}

#line 201 "bibmaint.sqC"
   
   
	while (getline(cin, myLine)){
   		
		vector <string> query;
	   
		string delims = "(;#)";
		size_t cur;
		size_t next = -1;
		
		do {
			cur = next + 1;
			next = myLine.find_first_of(delims, cur);
			query.push_back(myLine.substr(cur, next - cur));
		} while (next != string::npos);
        
	
		if(query[0] == "author"){
	
			pk = (sqlint32)atoi(query[1].c_str());
			strcpy(name,query[2].c_str());
				
			
/*
EXEC SQL
				SELECT name into :result
				FROM author
				WHERE aid = :pk;
*/

{
#line 226 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 226 "bibmaint.sqC"
  sqlaaloc(2,1,24,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 226 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 226 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)&pk;
#line 226 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 226 "bibmaint.sqC"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 226 "bibmaint.sqC"
  sqlaaloc(3,1,25,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 226 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 100;
#line 226 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)result;
#line 226 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 226 "bibmaint.sqC"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 226 "bibmaint.sqC"
  sqlacall((unsigned short)24,12,2,3,0L);
#line 226 "bibmaint.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 226 "bibmaint.sqC"
  sqlastop(0L);
}

#line 226 "bibmaint.sqC"

			
			if (SQLCODE == 100){
				
/*
EXEC SQL
					INSERT INTO author
					(aid,name)
					VALUES
					(:pk,:name);
*/

{
#line 233 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 233 "bibmaint.sqC"
  sqlaaloc(2,2,26,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 233 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 233 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)&pk;
#line 233 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 233 "bibmaint.sqC"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 22;
#line 233 "bibmaint.sqC"
      sql_setdlist[1].sqldata = (void*)name;
#line 233 "bibmaint.sqC"
      sql_setdlist[1].sqlind = 0L;
#line 233 "bibmaint.sqC"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 233 "bibmaint.sqC"
  sqlacall((unsigned short)24,13,2,0,0L);
#line 233 "bibmaint.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 233 "bibmaint.sqC"
  sqlastop(0L);
}

#line 233 "bibmaint.sqC"
	
			}
			
			else {
				
/*
EXEC SQL
					UPDATE author
					SET name = :name
					WHERE aid = :pk;
*/

{
#line 240 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 240 "bibmaint.sqC"
  sqlaaloc(2,2,27,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 240 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 22;
#line 240 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)name;
#line 240 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 240 "bibmaint.sqC"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 240 "bibmaint.sqC"
      sql_setdlist[1].sqldata = (void*)&pk;
#line 240 "bibmaint.sqC"
      sql_setdlist[1].sqlind = 0L;
#line 240 "bibmaint.sqC"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 240 "bibmaint.sqC"
  sqlacall((unsigned short)24,14,2,0,0L);
#line 240 "bibmaint.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 240 "bibmaint.sqC"
  sqlastop(0L);
}

#line 240 "bibmaint.sqC"
	
			}
            cout << "Author ID: " << query[1] << endl;
            cout << "Name: " << query[2] << endl;
            cout << endl;
			
		}
		
		if(query[0] == "authorurl"){
            
            pk = (sqlint32)atoi(query[1].c_str());
			strcpy(url,query[2].c_str());
				
			
/*
EXEC SQL
				UPDATE author
				SET url = :url
				WHERE aid = :pk;
*/

{
#line 256 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 256 "bibmaint.sqC"
  sqlaaloc(2,2,28,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 256 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 42;
#line 256 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)url;
#line 256 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 256 "bibmaint.sqC"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 256 "bibmaint.sqC"
      sql_setdlist[1].sqldata = (void*)&pk;
#line 256 "bibmaint.sqC"
      sql_setdlist[1].sqlind = 0L;
#line 256 "bibmaint.sqC"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 256 "bibmaint.sqC"
  sqlacall((unsigned short)24,15,2,0,0L);
#line 256 "bibmaint.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 256 "bibmaint.sqC"
  sqlastop(0L);
}

#line 256 "bibmaint.sqC"
	
            
            
/*
EXEC SQL
                SELECT name into :result
                FROM author
                where aid = :pk;
*/

{
#line 261 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 261 "bibmaint.sqC"
  sqlaaloc(2,1,29,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 261 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 261 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)&pk;
#line 261 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 261 "bibmaint.sqC"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 261 "bibmaint.sqC"
  sqlaaloc(3,1,30,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 261 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 100;
#line 261 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)result;
#line 261 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 261 "bibmaint.sqC"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 261 "bibmaint.sqC"
  sqlacall((unsigned short)24,16,2,3,0L);
#line 261 "bibmaint.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 261 "bibmaint.sqC"
  sqlastop(0L);
}

#line 261 "bibmaint.sqC"

            
            string temp = result;
            
            cout << "Author ID: " << query[1] << endl;
            cout << "Name: " << result << endl;
            cout << "URL: " << query[2] << endl;
            cout << endl;
            
		}
		
		
		if(query[0] == "book"){
	
			strcpy(charPk,query[1].c_str());
			strcpy(title,query[2].c_str());
			strcpy(publisher,query[query.size()-3].c_str());
            year = (sqlint32)atoi(query[query.size()-2].c_str());

	
			
/*
EXEC SQL
				SELECT title into :result
				FROM publication
				WHERE pubid = :charPk;
*/

{
#line 284 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 284 "bibmaint.sqC"
  sqlaaloc(2,1,31,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 284 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 284 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 284 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 284 "bibmaint.sqC"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 284 "bibmaint.sqC"
  sqlaaloc(3,1,32,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 284 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 100;
#line 284 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)result;
#line 284 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 284 "bibmaint.sqC"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 284 "bibmaint.sqC"
  sqlacall((unsigned short)24,17,2,3,0L);
#line 284 "bibmaint.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 284 "bibmaint.sqC"
  sqlastop(0L);
}

#line 284 "bibmaint.sqC"

			
			if (SQLCODE == 100){
				
/*
EXEC SQL
					INSERT INTO publication
					(pubid,title)
					VALUES
					(:charPk,:title);
*/

{
#line 291 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 291 "bibmaint.sqC"
  sqlaaloc(2,2,33,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 291 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 291 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 291 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 291 "bibmaint.sqC"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 70;
#line 291 "bibmaint.sqC"
      sql_setdlist[1].sqldata = (void*)title;
#line 291 "bibmaint.sqC"
      sql_setdlist[1].sqlind = 0L;
#line 291 "bibmaint.sqC"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 291 "bibmaint.sqC"
  sqlacall((unsigned short)24,18,2,0,0L);
#line 291 "bibmaint.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 291 "bibmaint.sqC"
  sqlastop(0L);
}

#line 291 "bibmaint.sqC"
	
				
/*
EXEC SQL	
					INSERT INTO book
					(pubid, publisher, year)
					VALUES
					(:charPk, :publisher, :year);
*/

{
#line 296 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 296 "bibmaint.sqC"
  sqlaaloc(2,3,34,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 296 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 296 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 296 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 296 "bibmaint.sqC"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 50;
#line 296 "bibmaint.sqC"
      sql_setdlist[1].sqldata = (void*)publisher;
#line 296 "bibmaint.sqC"
      sql_setdlist[1].sqlind = 0L;
#line 296 "bibmaint.sqC"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 296 "bibmaint.sqC"
      sql_setdlist[2].sqldata = (void*)&year;
#line 296 "bibmaint.sqC"
      sql_setdlist[2].sqlind = 0L;
#line 296 "bibmaint.sqC"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 296 "bibmaint.sqC"
  sqlacall((unsigned short)24,19,2,0,0L);
#line 296 "bibmaint.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 296 "bibmaint.sqC"
  sqlastop(0L);
}

#line 296 "bibmaint.sqC"

					
				for (int i = 3; i < query.size()-3; i++){
					author = (sqlint32)atoi(query[i].c_str());
					order = i-2;
					
					
/*
EXEC SQL	
						INSERT INTO wrote
						(aid, pubid, aorder)
						VALUES
						(:author, :charPk, :order);
*/

{
#line 306 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 306 "bibmaint.sqC"
  sqlaaloc(2,3,35,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 306 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 306 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)&author;
#line 306 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 306 "bibmaint.sqC"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 10;
#line 306 "bibmaint.sqC"
      sql_setdlist[1].sqldata = (void*)charPk;
#line 306 "bibmaint.sqC"
      sql_setdlist[1].sqlind = 0L;
#line 306 "bibmaint.sqC"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 306 "bibmaint.sqC"
      sql_setdlist[2].sqldata = (void*)&order;
#line 306 "bibmaint.sqC"
      sql_setdlist[2].sqlind = 0L;
#line 306 "bibmaint.sqC"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 306 "bibmaint.sqC"
  sqlacall((unsigned short)24,20,2,0,0L);
#line 306 "bibmaint.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 306 "bibmaint.sqC"
  sqlastop(0L);
}

#line 306 "bibmaint.sqC"

				}
					
			}
			
			else {
				
/*
EXEC SQL
					UPDATE publication
					SET title = :title
					WHERE pubid = :charPk;
*/

{
#line 315 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 315 "bibmaint.sqC"
  sqlaaloc(2,2,36,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 315 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 70;
#line 315 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)title;
#line 315 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 315 "bibmaint.sqC"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 10;
#line 315 "bibmaint.sqC"
      sql_setdlist[1].sqldata = (void*)charPk;
#line 315 "bibmaint.sqC"
      sql_setdlist[1].sqlind = 0L;
#line 315 "bibmaint.sqC"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 315 "bibmaint.sqC"
  sqlacall((unsigned short)24,21,2,0,0L);
#line 315 "bibmaint.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 315 "bibmaint.sqC"
  sqlastop(0L);
}

#line 315 "bibmaint.sqC"
	
				
/*
EXEC SQL	
					UPDATE book
					SET publisher = :publisher, year = :year
					WHERE pubid = :charPk;
*/

{
#line 319 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 319 "bibmaint.sqC"
  sqlaaloc(2,3,37,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 319 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 50;
#line 319 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)publisher;
#line 319 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 319 "bibmaint.sqC"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 319 "bibmaint.sqC"
      sql_setdlist[1].sqldata = (void*)&year;
#line 319 "bibmaint.sqC"
      sql_setdlist[1].sqlind = 0L;
#line 319 "bibmaint.sqC"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 10;
#line 319 "bibmaint.sqC"
      sql_setdlist[2].sqldata = (void*)charPk;
#line 319 "bibmaint.sqC"
      sql_setdlist[2].sqlind = 0L;
#line 319 "bibmaint.sqC"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 319 "bibmaint.sqC"
  sqlacall((unsigned short)24,22,2,0,0L);
#line 319 "bibmaint.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 319 "bibmaint.sqC"
  sqlastop(0L);
}

#line 319 "bibmaint.sqC"

				
/*
EXEC SQL	
					DELETE FROM wrote
					WHERE pubid = :charPk;
*/

{
#line 322 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 322 "bibmaint.sqC"
  sqlaaloc(2,1,38,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 322 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 322 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 322 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 322 "bibmaint.sqC"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 322 "bibmaint.sqC"
  sqlacall((unsigned short)24,23,2,0,0L);
#line 322 "bibmaint.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 322 "bibmaint.sqC"
  sqlastop(0L);
}

#line 322 "bibmaint.sqC"

				
				for (int i = 3; i < query.size()-3; i++){
					author = (sqlint32)atoi(query[i].c_str());
					order = i-2;
					
					
/*
EXEC SQL
						INSERT INTO wrote
						(aid, pubid, aorder)
						VALUES
						(:author, :charPk, :order);
*/

{
#line 332 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 332 "bibmaint.sqC"
  sqlaaloc(2,3,39,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 332 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 332 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)&author;
#line 332 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 332 "bibmaint.sqC"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 10;
#line 332 "bibmaint.sqC"
      sql_setdlist[1].sqldata = (void*)charPk;
#line 332 "bibmaint.sqC"
      sql_setdlist[1].sqlind = 0L;
#line 332 "bibmaint.sqC"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 332 "bibmaint.sqC"
      sql_setdlist[2].sqldata = (void*)&order;
#line 332 "bibmaint.sqC"
      sql_setdlist[2].sqlind = 0L;
#line 332 "bibmaint.sqC"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 332 "bibmaint.sqC"
  sqlacall((unsigned short)24,24,2,0,0L);
#line 332 "bibmaint.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 332 "bibmaint.sqC"
  sqlastop(0L);
}

#line 332 "bibmaint.sqC"

				}	
					
					
			}
            print(query[1].c_str());
			
		}
        
        if(query[0] == "journal"){
            
			strcpy(charPk,query[1].c_str());
			strcpy(title,query[2].c_str());
			volume = (sqlint32)atoi(query[3].c_str());
            number = (sqlint32)atoi(query[4].c_str());
            year = (sqlint32)atoi(query[5].c_str());
            
			
/*
EXEC SQL
            SELECT title into :result
            FROM publication
            WHERE pubid = :charPk;
*/

{
#line 352 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 352 "bibmaint.sqC"
  sqlaaloc(2,1,40,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 352 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 352 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 352 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 352 "bibmaint.sqC"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 352 "bibmaint.sqC"
  sqlaaloc(3,1,41,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 352 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 100;
#line 352 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)result;
#line 352 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 352 "bibmaint.sqC"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 352 "bibmaint.sqC"
  sqlacall((unsigned short)24,25,2,3,0L);
#line 352 "bibmaint.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 352 "bibmaint.sqC"
  sqlastop(0L);
}

#line 352 "bibmaint.sqC"

			
			if (SQLCODE == 100){
				
/*
EXEC SQL
                INSERT INTO publication
                (pubid,title)
                VALUES
                (:charPk,:title);
*/

{
#line 359 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 359 "bibmaint.sqC"
  sqlaaloc(2,2,42,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 359 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 359 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 359 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 359 "bibmaint.sqC"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 70;
#line 359 "bibmaint.sqC"
      sql_setdlist[1].sqldata = (void*)title;
#line 359 "bibmaint.sqC"
      sql_setdlist[1].sqlind = 0L;
#line 359 "bibmaint.sqC"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 359 "bibmaint.sqC"
  sqlacall((unsigned short)24,26,2,0,0L);
#line 359 "bibmaint.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 359 "bibmaint.sqC"
  sqlastop(0L);
}

#line 359 "bibmaint.sqC"
	
				
/*
EXEC SQL	
                INSERT INTO journal
                (pubid, volume, number, year)
                VALUES
                (:charPk, :volume, :number, :year);
*/

{
#line 364 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 364 "bibmaint.sqC"
  sqlaaloc(2,4,43,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 364 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 364 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 364 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 364 "bibmaint.sqC"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 364 "bibmaint.sqC"
      sql_setdlist[1].sqldata = (void*)&volume;
#line 364 "bibmaint.sqC"
      sql_setdlist[1].sqlind = 0L;
#line 364 "bibmaint.sqC"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 364 "bibmaint.sqC"
      sql_setdlist[2].sqldata = (void*)&number;
#line 364 "bibmaint.sqC"
      sql_setdlist[2].sqlind = 0L;
#line 364 "bibmaint.sqC"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 364 "bibmaint.sqC"
      sql_setdlist[3].sqldata = (void*)&year;
#line 364 "bibmaint.sqC"
      sql_setdlist[3].sqlind = 0L;
#line 364 "bibmaint.sqC"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 364 "bibmaint.sqC"
  sqlacall((unsigned short)24,27,2,0,0L);
#line 364 "bibmaint.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 364 "bibmaint.sqC"
  sqlastop(0L);
}

#line 364 "bibmaint.sqC"

			}
			
			else {
				
/*
EXEC SQL
                UPDATE publication
                SET title = :title
                WHERE pubid = :charPk;
*/

{
#line 371 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 371 "bibmaint.sqC"
  sqlaaloc(2,2,44,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 371 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 70;
#line 371 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)title;
#line 371 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 371 "bibmaint.sqC"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 10;
#line 371 "bibmaint.sqC"
      sql_setdlist[1].sqldata = (void*)charPk;
#line 371 "bibmaint.sqC"
      sql_setdlist[1].sqlind = 0L;
#line 371 "bibmaint.sqC"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 371 "bibmaint.sqC"
  sqlacall((unsigned short)24,28,2,0,0L);
#line 371 "bibmaint.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 371 "bibmaint.sqC"
  sqlastop(0L);
}

#line 371 "bibmaint.sqC"
	
				
/*
EXEC SQL	
                UPDATE journal
                SET volume = :volume, number = :number, year = :year
                WHERE pubid = :charPk;
*/

{
#line 375 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 375 "bibmaint.sqC"
  sqlaaloc(2,4,45,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 375 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 375 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)&volume;
#line 375 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 375 "bibmaint.sqC"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 375 "bibmaint.sqC"
      sql_setdlist[1].sqldata = (void*)&number;
#line 375 "bibmaint.sqC"
      sql_setdlist[1].sqlind = 0L;
#line 375 "bibmaint.sqC"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 375 "bibmaint.sqC"
      sql_setdlist[2].sqldata = (void*)&year;
#line 375 "bibmaint.sqC"
      sql_setdlist[2].sqlind = 0L;
#line 375 "bibmaint.sqC"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 10;
#line 375 "bibmaint.sqC"
      sql_setdlist[3].sqldata = (void*)charPk;
#line 375 "bibmaint.sqC"
      sql_setdlist[3].sqlind = 0L;
#line 375 "bibmaint.sqC"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 375 "bibmaint.sqC"
  sqlacall((unsigned short)24,29,2,0,0L);
#line 375 "bibmaint.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 375 "bibmaint.sqC"
  sqlastop(0L);
}

#line 375 "bibmaint.sqC"

			}
			 print(query[1].c_str());
		}
        
        
        if(query[0] == "proceedings"){
            
			strcpy(charPk,query[1].c_str());
			strcpy(title,query[2].c_str());
            year = (sqlint32)atoi(query[query.size()-2].c_str());
            
            
			
/*
EXEC SQL
            SELECT title into :result
            FROM publication
            WHERE pubid = :charPk;
*/

{
#line 391 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 391 "bibmaint.sqC"
  sqlaaloc(2,1,46,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 391 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 391 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 391 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 391 "bibmaint.sqC"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 391 "bibmaint.sqC"
  sqlaaloc(3,1,47,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 391 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 100;
#line 391 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)result;
#line 391 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 391 "bibmaint.sqC"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 391 "bibmaint.sqC"
  sqlacall((unsigned short)24,30,2,3,0L);
#line 391 "bibmaint.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 391 "bibmaint.sqC"
  sqlastop(0L);
}

#line 391 "bibmaint.sqC"

			
			if (SQLCODE == 100){
				
/*
EXEC SQL
                INSERT INTO publication
                (pubid,title)
                VALUES
                (:charPk,:title);
*/

{
#line 398 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 398 "bibmaint.sqC"
  sqlaaloc(2,2,48,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 398 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 398 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 398 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 398 "bibmaint.sqC"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 70;
#line 398 "bibmaint.sqC"
      sql_setdlist[1].sqldata = (void*)title;
#line 398 "bibmaint.sqC"
      sql_setdlist[1].sqlind = 0L;
#line 398 "bibmaint.sqC"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 398 "bibmaint.sqC"
  sqlacall((unsigned short)24,31,2,0,0L);
#line 398 "bibmaint.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 398 "bibmaint.sqC"
  sqlastop(0L);
}

#line 398 "bibmaint.sqC"
	
				
/*
EXEC SQL	
                INSERT INTO proceedings
                (pubid, year)
                VALUES
                (:charPk, :year);
*/

{
#line 403 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 403 "bibmaint.sqC"
  sqlaaloc(2,2,49,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 403 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 403 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 403 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 403 "bibmaint.sqC"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 403 "bibmaint.sqC"
      sql_setdlist[1].sqldata = (void*)&year;
#line 403 "bibmaint.sqC"
      sql_setdlist[1].sqlind = 0L;
#line 403 "bibmaint.sqC"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 403 "bibmaint.sqC"
  sqlacall((unsigned short)24,32,2,0,0L);
#line 403 "bibmaint.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 403 "bibmaint.sqC"
  sqlastop(0L);
}

#line 403 "bibmaint.sqC"

			}
			
			else {
				
/*
EXEC SQL
                UPDATE publication
                SET title = :title
                WHERE pubid = :charPk;
*/

{
#line 410 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 410 "bibmaint.sqC"
  sqlaaloc(2,2,50,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 410 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 70;
#line 410 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)title;
#line 410 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 410 "bibmaint.sqC"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 10;
#line 410 "bibmaint.sqC"
      sql_setdlist[1].sqldata = (void*)charPk;
#line 410 "bibmaint.sqC"
      sql_setdlist[1].sqlind = 0L;
#line 410 "bibmaint.sqC"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 410 "bibmaint.sqC"
  sqlacall((unsigned short)24,33,2,0,0L);
#line 410 "bibmaint.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 410 "bibmaint.sqC"
  sqlastop(0L);
}

#line 410 "bibmaint.sqC"
	
				
/*
EXEC SQL	
                UPDATE proceedings
                SET year = :year
                WHERE pubid = :charPk;
*/

{
#line 414 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 414 "bibmaint.sqC"
  sqlaaloc(2,2,51,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 414 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 414 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)&year;
#line 414 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 414 "bibmaint.sqC"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 10;
#line 414 "bibmaint.sqC"
      sql_setdlist[1].sqldata = (void*)charPk;
#line 414 "bibmaint.sqC"
      sql_setdlist[1].sqlind = 0L;
#line 414 "bibmaint.sqC"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 414 "bibmaint.sqC"
  sqlacall((unsigned short)24,34,2,0,0L);
#line 414 "bibmaint.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 414 "bibmaint.sqC"
  sqlastop(0L);
}

#line 414 "bibmaint.sqC"

			}
             print(query[1].c_str());
			
		}
        
        
        if(query[0] == "article"){
            
			strcpy(charPk,query[1].c_str());
			strcpy(title,query[2].c_str());
			strcpy(appearsin,query[query.size()-4].c_str());
            endpage = (sqlint32)atoi(query[query.size()-2].c_str());
            startpage = (sqlint32)atoi(query[query.size()-3].c_str());
            
			
/*
EXEC SQL
            SELECT title into :result
            FROM publication
            WHERE pubid = :charPk;
*/

{
#line 432 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 432 "bibmaint.sqC"
  sqlaaloc(2,1,52,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 432 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 432 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 432 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 432 "bibmaint.sqC"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 432 "bibmaint.sqC"
  sqlaaloc(3,1,53,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 432 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 100;
#line 432 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)result;
#line 432 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 432 "bibmaint.sqC"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 432 "bibmaint.sqC"
  sqlacall((unsigned short)24,35,2,3,0L);
#line 432 "bibmaint.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 432 "bibmaint.sqC"
  sqlastop(0L);
}

#line 432 "bibmaint.sqC"

			
			if (SQLCODE == 100){
				
/*
EXEC SQL
                INSERT INTO publication
                (pubid,title)
                VALUES
                (:charPk,:title);
*/

{
#line 439 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 439 "bibmaint.sqC"
  sqlaaloc(2,2,54,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 439 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 439 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 439 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 439 "bibmaint.sqC"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 70;
#line 439 "bibmaint.sqC"
      sql_setdlist[1].sqldata = (void*)title;
#line 439 "bibmaint.sqC"
      sql_setdlist[1].sqlind = 0L;
#line 439 "bibmaint.sqC"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 439 "bibmaint.sqC"
  sqlacall((unsigned short)24,36,2,0,0L);
#line 439 "bibmaint.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 439 "bibmaint.sqC"
  sqlastop(0L);
}

#line 439 "bibmaint.sqC"
	
				
/*
EXEC SQL	
                INSERT INTO article
                (pubid, appearsin, startpage, endpage)
                VALUES
                (:charPk, :appearsin, :startpage, :endpage);
*/

{
#line 444 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 444 "bibmaint.sqC"
  sqlaaloc(2,4,55,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 444 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 444 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 444 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 444 "bibmaint.sqC"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 10;
#line 444 "bibmaint.sqC"
      sql_setdlist[1].sqldata = (void*)appearsin;
#line 444 "bibmaint.sqC"
      sql_setdlist[1].sqlind = 0L;
#line 444 "bibmaint.sqC"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 444 "bibmaint.sqC"
      sql_setdlist[2].sqldata = (void*)&startpage;
#line 444 "bibmaint.sqC"
      sql_setdlist[2].sqlind = 0L;
#line 444 "bibmaint.sqC"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 444 "bibmaint.sqC"
      sql_setdlist[3].sqldata = (void*)&endpage;
#line 444 "bibmaint.sqC"
      sql_setdlist[3].sqlind = 0L;
#line 444 "bibmaint.sqC"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 444 "bibmaint.sqC"
  sqlacall((unsigned short)24,37,2,0,0L);
#line 444 "bibmaint.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 444 "bibmaint.sqC"
  sqlastop(0L);
}

#line 444 "bibmaint.sqC"

                
				for (int i = 3; i < query.size()-4; i++){
					author = (sqlint32)atoi(query[i].c_str());
					order = i-2;
					
					
/*
EXEC SQL	
                    INSERT INTO wrote
                    (aid, pubid, aorder)
                    VALUES
                    (:author, :charPk, :order);
*/

{
#line 454 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 454 "bibmaint.sqC"
  sqlaaloc(2,3,56,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 454 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 454 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)&author;
#line 454 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 454 "bibmaint.sqC"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 10;
#line 454 "bibmaint.sqC"
      sql_setdlist[1].sqldata = (void*)charPk;
#line 454 "bibmaint.sqC"
      sql_setdlist[1].sqlind = 0L;
#line 454 "bibmaint.sqC"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 454 "bibmaint.sqC"
      sql_setdlist[2].sqldata = (void*)&order;
#line 454 "bibmaint.sqC"
      sql_setdlist[2].sqlind = 0L;
#line 454 "bibmaint.sqC"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 454 "bibmaint.sqC"
  sqlacall((unsigned short)24,38,2,0,0L);
#line 454 "bibmaint.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 454 "bibmaint.sqC"
  sqlastop(0L);
}

#line 454 "bibmaint.sqC"

				}
                
			}
			
			else {
				
/*
EXEC SQL
                UPDATE publication
                SET title = :title
                WHERE pubid = :charPk;
*/

{
#line 463 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 463 "bibmaint.sqC"
  sqlaaloc(2,2,57,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 463 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 70;
#line 463 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)title;
#line 463 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 463 "bibmaint.sqC"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 10;
#line 463 "bibmaint.sqC"
      sql_setdlist[1].sqldata = (void*)charPk;
#line 463 "bibmaint.sqC"
      sql_setdlist[1].sqlind = 0L;
#line 463 "bibmaint.sqC"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 463 "bibmaint.sqC"
  sqlacall((unsigned short)24,39,2,0,0L);
#line 463 "bibmaint.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 463 "bibmaint.sqC"
  sqlastop(0L);
}

#line 463 "bibmaint.sqC"
	
				
/*
EXEC SQL	
                UPDATE article
                SET appearsin = :appearsin, startpage = :startpage, endpage = :endpage
                WHERE pubid = :charPk;
*/

{
#line 467 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 467 "bibmaint.sqC"
  sqlaaloc(2,4,58,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 467 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 467 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)appearsin;
#line 467 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 467 "bibmaint.sqC"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 467 "bibmaint.sqC"
      sql_setdlist[1].sqldata = (void*)&startpage;
#line 467 "bibmaint.sqC"
      sql_setdlist[1].sqlind = 0L;
#line 467 "bibmaint.sqC"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 467 "bibmaint.sqC"
      sql_setdlist[2].sqldata = (void*)&endpage;
#line 467 "bibmaint.sqC"
      sql_setdlist[2].sqlind = 0L;
#line 467 "bibmaint.sqC"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 10;
#line 467 "bibmaint.sqC"
      sql_setdlist[3].sqldata = (void*)charPk;
#line 467 "bibmaint.sqC"
      sql_setdlist[3].sqlind = 0L;
#line 467 "bibmaint.sqC"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 467 "bibmaint.sqC"
  sqlacall((unsigned short)24,40,2,0,0L);
#line 467 "bibmaint.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 467 "bibmaint.sqC"
  sqlastop(0L);
}

#line 467 "bibmaint.sqC"

				
/*
EXEC SQL	
                DELETE FROM wrote
                WHERE pubid = :charPk;
*/

{
#line 470 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 470 "bibmaint.sqC"
  sqlaaloc(2,1,59,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 470 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 470 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)charPk;
#line 470 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 470 "bibmaint.sqC"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 470 "bibmaint.sqC"
  sqlacall((unsigned short)24,41,2,0,0L);
#line 470 "bibmaint.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 470 "bibmaint.sqC"
  sqlastop(0L);
}

#line 470 "bibmaint.sqC"

				
				for (int i = 3; i < query.size()-4; i++){
					author = (sqlint32)atoi(query[i].c_str());
					order = i-2;
					
					
/*
EXEC SQL
                    INSERT INTO wrote
                    (aid, pubid, aorder)
                    VALUES
                    (:author, :charPk, :order);
*/

{
#line 480 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 480 "bibmaint.sqC"
  sqlaaloc(2,3,60,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 480 "bibmaint.sqC"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 480 "bibmaint.sqC"
      sql_setdlist[0].sqldata = (void*)&author;
#line 480 "bibmaint.sqC"
      sql_setdlist[0].sqlind = 0L;
#line 480 "bibmaint.sqC"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 10;
#line 480 "bibmaint.sqC"
      sql_setdlist[1].sqldata = (void*)charPk;
#line 480 "bibmaint.sqC"
      sql_setdlist[1].sqlind = 0L;
#line 480 "bibmaint.sqC"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 480 "bibmaint.sqC"
      sql_setdlist[2].sqldata = (void*)&order;
#line 480 "bibmaint.sqC"
      sql_setdlist[2].sqlind = 0L;
#line 480 "bibmaint.sqC"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 480 "bibmaint.sqC"
  sqlacall((unsigned short)24,42,2,0,0L);
#line 480 "bibmaint.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 480 "bibmaint.sqC"
  sqlastop(0L);
}

#line 480 "bibmaint.sqC"

				}	
                
                
			}
             print(query[1].c_str());
			
		}

        
        
        
        

	}
	
	
	
/*
EXEC SQL COMMIT;
*/

{
#line 497 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 497 "bibmaint.sqC"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 497 "bibmaint.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 497 "bibmaint.sqC"
  sqlastop(0L);
}

#line 497 "bibmaint.sqC"

	
/*
EXEC SQL CONNECT reset;
*/

{
#line 498 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 498 "bibmaint.sqC"
  sqlacall((unsigned short)29,3,0,0,0L);
#line 498 "bibmaint.sqC"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 498 "bibmaint.sqC"
  sqlastop(0L);
}

#line 498 "bibmaint.sqC"

	
	exit(0);
	
error:
	check_error("Bad input",&sqlca);
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 504 "bibmaint.sqC"


	
/*
EXEC SQL ROLLBACK;
*/

{
#line 506 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 506 "bibmaint.sqC"
  sqlacall((unsigned short)28,0,0,0,0L);
#line 506 "bibmaint.sqC"
  sqlastop(0L);
}

#line 506 "bibmaint.sqC"

	
/*
EXEC SQL CONNECT reset;
*/

{
#line 507 "bibmaint.sqC"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 507 "bibmaint.sqC"
  sqlacall((unsigned short)29,3,0,0,0L);
#line 507 "bibmaint.sqC"
  sqlastop(0L);
}

#line 507 "bibmaint.sqC"

	exit(1);
	
	
	
}
	



