#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <libpq-fe.h>

#define STOCK_MAX_NUMBER_OF_RECORDS  100
#define MAX_PRODUCT_NAME_LENGTH  100
#define MAX_CONNECTION_STRING_LENGTH  100

const float PROFIT_PERCENTAGE = 0.2;
typedef enum {  Ok = 200, BadRequest = 400, NotFound = 404, InsufficientStorage = 507} ResultStatus;
typedef enum { Purchase = 1, Sale = 2 } StockMovimentationType;

typedef struct
{
    int id;
    char* code;
    char* name;
    float costPrice;
    float sellingPrice;

}Product;

typedef struct
{
    int id;     
    int saleId;
    int purchaseId;
    time_t date;
    StockMovimentationType type;
    int previousQuant;
    int quant;
    double totalCost;

}StockMovimentation;

typedef struct StockMovimentation_Product
{
    int id;
    StockMovimentation stockMovimentation;
    Product product;
    int productQuantity;
    float productUnitaryPrice;

}SM_Product;

typedef struct 
{
    Product products[STOCK_MAX_NUMBER_OF_RECORDS];
    int lastIndex;

}ProductsList;

typedef struct
{
    char* message;
    ResultStatus status; 

}Result;

//================================================= Helpers ============================================================

void ClearBuffer()
{
	int c;
	while ( (c = getchar()) != '\n' && c != EOF ) { }
}

void RemoveNewLine(char *phase)
{
    int WordSize = strlen(phase);

    if (phase[WordSize - 1] == '\n') 
        phase[WordSize - 1] = '\0';
}

//=====================================================================================================================

void CloseDbConnection(PGconn *conn, PGresult *res) {
    
    char *errorMessage = PQerrorMessage(conn);

    PQclear(res);
    PQfinish(conn);    
    
    if (strlen(errorMessage) > 0)
    {
        fprintf(stderr, "%s\n", errorMessage);    
        exit(1);
    }
}

void SetConnectionString(char * connectionString)
{
    FILE *fp;
    char fileName[] = "DbConnectionString.txt";

    fp = fopen(fileName, "r");

    if (fp == NULL)
    {
      printf("Error while opening the file: %s.\n", fileName);
      exit(EXIT_FAILURE);
    }
    
    fgets(connectionString, MAX_CONNECTION_STRING_LENGTH, fp);
    fclose(fp);

}

PGresult* DbQuery(PGconn *conn, char* query)
{
    return PQexec(conn, query);
}

void PrintAllProducts(PGresult *res)
{
    int nRows = PQntuples(res);
    int nCols = PQnfields(res);
    
    for(int i = 0; i < nRows; i++)
    {
        for (int j = 0; j < nCols; j++)                 
            printf("%s  ", PQgetvalue(res, i, j));
        printf("\n");
    }
}

void PrintListProducts(ProductsList *productsList)
{
    for (int i = 0; i < productsList->lastIndex; i++)
    {
        printf("===================================================\n");
        printf("%d  %s  %s  %2.f  %2.f\n", productsList->products[i].id, productsList->products[i].code, productsList->products[i].name, productsList->products[i].costPrice, productsList->products[i].sellingPrice); 
        printf("===================================================\n\n");
    }
}

void GetAllProducts(PGresult *res, ProductsList *productsList)
{
    int nRows = PQntuples(res);

    Product product;
    
    for(int i = 0; i < nRows; i++)
    {
        product.code = PQgetvalue(res, i, 0);
        product.costPrice = strtof(PQgetvalue(res, i, 1), NULL);
        product.id = atoll(PQgetvalue(res, i, 2));
        product.name = PQgetvalue(res, i, 3);
        product.sellingPrice = strtof(PQgetvalue(res, i, 4), NULL);

        productsList->products[productsList->lastIndex] = product;
        productsList->lastIndex++;
    }
}

int main() 
{    
    char connectionString[MAX_CONNECTION_STRING_LENGTH];    
    SetConnectionString(connectionString);
    ProductsList products;
    products.lastIndex = 0;

    PGconn *conn = PQconnectdb(connectionString);

           
    if (PQstatus(conn) == CONNECTION_BAD) 
    {
        fprintf(stderr, "Connection to database failed: %s\n",
        PQerrorMessage(conn));

        PQfinish(conn);
        exit(1);
    }
   

    PGresult *res = DbQuery(conn, "SELECT * FROM \"Product\"");

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {

        printf("No data found\n");        
        CloseDbConnection(conn, res);
    } 

    GetAllProducts(res, &products);
    PrintListProducts(&products);

    CloseDbConnection(conn, res);

    return 0;
}