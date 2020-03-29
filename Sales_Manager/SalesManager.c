#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <libpq-fe.h>

#define STOCK_MAX_NUMBER_OF_RECORDS  100
#define MAX_PRODUCT_NAME_LENGTH  200
#define MAX_PRODUCT_CODE_LENGTH  100
#define MAX_CONNECTION_STRING_LENGTH  100

const float PROFIT_PERCENTAGE = 0.2;
const char* BORDER = "\n================================================\n";
typedef enum {  Ok = 200, BadRequest = 400, NotFound = 404, ServerError = 500, InsufficientStorage = 507} ResultStatus;
typedef enum { Purchase = 1, Sale = 2 } StockMovimentationType;

typedef struct
{
    int id;
    char name[MAX_PRODUCT_NAME_LENGTH];
    char code[MAX_PRODUCT_CODE_LENGTH];
    float costPrice, sellingPrice;
    int quantity;

}Product;   

typedef struct
{
    int id;     
    time_t date;
    int quant;
    double totalPrice;
    Product *soldProducts;

}Sale;

typedef struct
{
    int id;     
    time_t date;
    int quant;
    double totalCost;
    Product *boughtProducts;

}Purchase;

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

typedef struct ProductQueryResult
{
    Result result;
    ProductsList productsList;
    
}PResult;

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

//=====================================================================================================================

void PrintResults(PGresult *res)
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

void PrintProductsList(ProductsList *productsList)
{
    for (int i = 0; i < productsList->lastIndex; i++)
    {
        printf(BORDER);
        printf("%s  %s  %2.f  %2.f  %d", productsList->products[i].code, productsList->products[i].name, productsList->products[i].costPrice, productsList->products[i].sellingPrice, productsList->products[i].quantity); 
        printf(BORDER);
    }
}

void SetSellingPrice(Product *product)
{
    float sellingPrice = product->costPrice + (product->costPrice*PROFIT_PERCENTAGE);
    product -> sellingPrice = sellingPrice;
}


Product SetProduct(Product *product)
{
    system("clear||cls");
    printf(BORDER);
    printf("\nInform the code of the product: ");
    fgets(product->code, MAX_PRODUCT_CODE_LENGTH, stdin);
    RemoveNewLine(product->code);
    printf("\nInform the name of the product: ");
    fgets(product->name, MAX_PRODUCT_NAME_LENGTH, stdin);
    RemoveNewLine(product->name);
    printf("\nInform the quantity of products: ");
    scanf("%d", &product->quantity);
    printf("\nInform the purchase cost of the product: ");
    scanf("%f", &product->costPrice);
    printf(BORDER);

    SetSellingPrice(product);
}

Result RegisterProduct(Product product, PGconn *conn)
{
    Result result;
    char query[600];

    snprintf(query, 600,
        "INSERT INTO \"Product\"(code, \"costPrice\", name, \"sellingPrice\", quantity) VALUES (\'%s\' , %.2f, \'%s\', %.2f, %d);",
        product.code, product.costPrice, product.name, product.sellingPrice, product.quantity);

    PGresult* res = DbQuery(conn, query);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) 
    {
        result.message = PQerrorMessage(conn);
        result.status = ServerError;        
    }
    else{
        result.message = "Product insert sucessfully !";
        result.status = Ok;
    }
    return result;
}

void MountProducts(PGresult *res, ProductsList *productsList)
{
    int nRows = PQntuples(res);
    Product product;
    
    for(int i = 0; i < nRows; i++)
    {
        strcpy(product.code, PQgetvalue(res, i, 0));
        product.costPrice = strtof(PQgetvalue(res, i, 1), NULL);
        product.id = atoll(PQgetvalue(res, i, 2));
        strcpy(product.name, PQgetvalue(res, i, 3));
        product.sellingPrice = strtof(PQgetvalue(res, i, 4), NULL);
        product.quantity = atoll(PQgetvalue(res, i, 5));

        productsList->products[productsList->lastIndex] = product;
        productsList->lastIndex++;
    }
}

ProductsList SelectProducts(PGconn *conn, char* query, PGresult* res)
{
    ProductsList products;
    res = DbQuery(conn, query);
    ExecStatusType status = PQresultStatus(res);

    if (status == PGRES_TUPLES_OK || status == PGRES_SINGLE_TUPLE) 
        MountProducts(res, &products);   

    return products;
}

PResult GetProducts(PGconn *conn, char *query)
{
    PResult pResult;
    PGresult* res; 

    pResult.productsList = SelectProducts(conn, query, res);
    char *errorMessage = PQerrorMessage(conn);

    if (strlen(errorMessage) > 0)
    {
        strcpy(pResult.result.message, errorMessage);
        pResult.result.status = BadRequest;
    }
    else
    {
        char buffer[50];
        sprintf(buffer, "The search return %d results.", pResult.productsList.lastIndex);
        pResult.result.message = buffer;
        pResult.result.status = Ok;
    }

    return pResult;
}

Result RemoveProduct(PGconn *conn, int id)
{
    Result result;
    char query[50];
    sprintf(query, "DELETE FROM \"Product\" WHERE id = %d", id);

    PGresult* res = DbQuery(conn, query);
    ExecStatusType status = PQresultStatus(res);

    if (status == PGRES_COMMAND_OK){
        result.status = Ok;
        result.message = "product was sucessfully removed!";
    }
    else{
        result.status = BadRequest;
        result.message = PQerrorMessage(conn);
    }

    return result;
}

Result EditProduct(PGconn *conn, Product product, int  id)
{
    char query[200];
    Result result;

    if (id <= 0){
        result.status = BadRequest;
        result.message = "You must inform a valid identifier.";

        return result;
    }

    sprintf(query, "UPDATE \"Product\" SET code='%s', \"costPrice\"=%.2f, name='%s', \"sellingPrice\"=%.2f, quantity=%d WHERE id = %d;", product.code, product.costPrice, product.name, product.sellingPrice, product.quantity, id);

    PGresult* res = DbQuery(conn, query);
    ExecStatusType status = PQresultStatus(res);

    if (status == PGRES_COMMAND_OK){
    result.status = Ok;
    result.message = "product was sucessfully updated!";
    }
    else{
        result.status = BadRequest;
        result.message = PQerrorMessage(conn);
    }

    return result;
}

int main() 
{    
    char connectionString[MAX_CONNECTION_STRING_LENGTH];    
    SetConnectionString(connectionString);
    ProductsList products;
    Product product;

    products.lastIndex = 0;
    PGconn *conn = PQconnectdb(connectionString);
           
    if (PQstatus(conn) == CONNECTION_BAD) 
    {
        fprintf(stderr, "Connection to database failed: %s\n",
        PQerrorMessage(conn));

        PQfinish(conn);
        exit(1);
    }

    SetProduct(&product);
    Result result = EditProduct(conn, product, 8);

    // PResult pResult = GetProducts(conn, "SELECT * FROM \"Product\";");
    // system("clear||cls");

    // if (pResult.result.status == Ok)
    //     PrintProductsList(&pResult.productsList);

    // printf(BORDER);
    // printf("%s", pResult.result.message);
    // printf(BORDER);

    // SetProduct(&product);
    // Result result = RegisterProduct(product, conn);

    system("clear||cls");
    printf(BORDER);
    printf("%s", result.message);
    printf(BORDER);

    PQfinish(conn);

    return 0;
}