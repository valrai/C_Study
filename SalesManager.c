#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define STOCK_MAX_NUMBER_OF_RECORDS  500
#define MAX_PRODUCT_NAME_SIZE  100

const float PROFIT_PERCENTAGE = 0.2;
typedef enum {  Ok = 200, BadRequest = 400, NotFound = 404, InsufficientStorage = 507} ResultStatus;

typedef struct Product
{
    int code;
    char* name;
    float costPrice;
    float sellingPrice;

}Product;

typedef struct
{
    int id;
    time_t date;
    int totalQuantityProducts;
    double totalCost;

}Sale;

typedef struct
{
    Product product;
    Sale sale;
    int productQuantity;
    float productUnitaryPrice;

}ProductSale;

typedef struct
{
    Product product;
    int quantity;

}ProductRecord;

typedef struct
{
    ProductRecord products[STOCK_MAX_NUMBER_OF_RECORDS]; 
    int totalQuantity;

}Stock; 


typedef struct
{
    char* message;
    ResultStatus status; 

}Result;

//=============================================================================================================

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

void SetSellingPrice(Product *product)
{
    float sellingPrice = product->costPrice + (product->costPrice*PROFIT_PERCENTAGE);
    product -> sellingPrice = sellingPrice;
}

Result ProductIsRegistered(Product *product, Stock *stock)
{
    Result result = {"The Product is already registered in the stock", Ok};

    for(int i=0; i < stock->totalQuantity; i++)    
        if (stock->products[i].product.code == product->code)
            return result;

    result.message = "The Product is NOT registered in the stock";
    result.status = NotFound;

    return result;    
}

Result AddProductToStock(Product *product, Stock *stock, ProductRecord *pr, int prodQuant)
{
    Result result;

    if (stock -> totalQuantity == STOCK_MAX_NUMBER_OF_RECORDS)
    {
        result.message = "Failed to add product, the stock is full";
        result.status = InsufficientStorage;
        return result;
    }

    result = ProductIsRegistered(product, stock);

    if (result.status == Ok)
    {
        result.status = BadRequest;
        return result;
    }
    pr -> product = *product;
    pr -> quantity = prodQuant;

    stock -> products[stock->totalQuantity] = *pr;
    stock -> totalQuantity++;

    result.message = "Product sucessfully added to stock.";
    result.status = Ok;

    return result;
}


Result RegisterProduct(Product *product, Stock *stock, ProductRecord *pr, char *name)
{
    int code, quantity;
    float cost;

    system("clear||cls");
    printf("\n================================================\n\n");
    printf("Inform the code of the product: ");
    scanf("%d", &code);
    printf("\nInform the name of the product: ");
    ClearBuffer();
    fgets(name, MAX_PRODUCT_NAME_SIZE, stdin);
    RemoveNewLine(name);
    printf("\nInform the quantity of products: ");
    scanf("%d", &quantity);
    printf("\nInform the purchase cost of the product: ");
    scanf("%f", &cost);
    printf("\n================================================\n");   

    product -> code = code;
    product -> name = name;
    product -> costPrice = cost;

    SetSellingPrice(product);

    return AddProductToStock(product, stock, pr, quantity);
}

void ShowProductsStored(Result result, Stock stock)
{
    system("clear||cls");
    for (int i = 0; i < stock.totalQuantity; i++)
    {
        printf("\n\n================================================"); 
        printf("\n\n %s\n\n", result.message);
        printf(" stored cost price: R$ %.2f\n", stock.products[i].product.costPrice);
        printf(" stored seeling Price: R$ %.2f\n", stock.products[i].product.sellingPrice);
        printf(" stored product name: %s\n", stock.products[i].product.name);
        printf(" stored product code: %d\n", stock.products[i].product.code);
        printf(" stored product quantity: %d\n", stock.products[i].quantity);
        printf("\n================================================\n"); 
    }    
}

int main ()
{
    int userOption;
    Stock stock;
    stock.totalQuantity = 0;

    do
    {
        Product product;
        ProductRecord pr;
        char name[MAX_PRODUCT_NAME_SIZE];

        Result result = RegisterProduct(&product, &stock, &pr, name);

        ShowProductsStored(result, stock);

        printf("Total quantity: %d\n", stock.totalQuantity);
        printf("Do you want continue? (0 for exit and 1 to continue)\n");
        scanf("%d", &userOption);

    } while (userOption != 0);
    

    return 0; 
}