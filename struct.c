#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_NAME_LENGTH 20
#define MAX_GROUP_LENGTH 20

typedef struct Product
{
	int code;
	char name[MAX_NAME_LENGTH];
	char group[MAX_GROUP_LENGTH];
	double price;
	int quantity;
} Product;

typedef struct ProductBase
{
	Product ** productData;
	int length; 
	int capacity;

} ProductBase;

void read_product_base_from_file(const char *filename, ProductBase *store);
void read_product_base_from_file(const char *filename, ProductBase *store)
{
	char c; int index = 0; Product* new_product; int tmp;
	FILE *file = fopen(filename, "r");
	if (file == NULL) 
	{
		printf("FileNotOpenError\n"); 
		return;
	}
	store->length = 0;
	store->capacity = 1;
	store->productData = (Product **)malloc(sizeof(Product *));
	while (fscanf(file, "%d", &tmp) == 1)
	{
		new_product = (Product *)malloc(sizeof(Product));
		new_product->code = tmp;

		index = 0;
		do c = fgetc(file); while (!isalpha(c));
		while (isalpha(c))
		{
			new_product->name[index] = c;
			index++;
			c = fgetc(file);		
		}
		new_product->name[index] = '\0';

		index = 0;
		do c = fgetc(file); while (!isalpha(c));
		while (isalpha(c))
		{
			new_product->group[index] = c;
			index++;
			c = fgetc(file);		
		}
		new_product->group[index] = '\0';

		fscanf(file, "%lf", &new_product->price);
		fscanf(file, "%d", &new_product->quantity);

		store->productData[store->length] = new_product;

		(store->length)++;
		if (store->length == store->capacity)
		{
			store->capacity *= 2;
			store->productData = (Product **)realloc(store->productData, (store->capacity)*sizeof(Product *));	
		}	
	}
	fclose(file);

}

void print_product_base(ProductBase store);
void print_product_base(ProductBase store)
{
	for (int index = 0; index < store.length; index++)
		printf("#%d: %s, group: %s, price: %.2lf, quantity: %d\n", store.productData[index]->code,
		store.productData[index]->name, store.productData[index]->group, store.productData[index]->price,
		store.productData[index]->quantity);

}

int main(void)
{
	ProductBase store;
	read_product_base_from_file("database.txt", &store);	
	print_product_base(store);
	return 0;
}

