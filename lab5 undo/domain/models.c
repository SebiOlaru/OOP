#include <string.h>
#include "models.h"
#include <stdlib.h>

/*
 * Creates a new product
 * Preconditions: id: a positive integer
 *                type: a pointer to a char
 *                manufacturer: a pointer to a char
 *                model: a pointer to a char
 *                price: a positive float
 *                quantity: a positive integer
 * Post-conditions: a pointer to a new instance of the Product struct
 */
Product* createProduct(int id, char* type, char* manufacturer, char* model, long double price, int quantity) {
    // allocate the necessary space for a new product
    Product* newProduct = malloc(sizeof(Product));
    if(newProduct == NULL) {
		return NULL;
	}
    newProduct->type = malloc(sizeof(char) * (strlen(type) + 1));
    if(newProduct->type == NULL) {
        free(newProduct);
        return NULL;
    }
    newProduct->manufacturer = malloc(sizeof(char) * (strlen(manufacturer) + 1));
    if(newProduct->manufacturer == NULL) {
		free(newProduct->type);
		free(newProduct);
		return NULL;
	}
    newProduct->model = malloc(sizeof(char) * (strlen(model) + 1));
    if(newProduct->model == NULL) {
        free(newProduct->manufacturer);
        free(newProduct->type);
        free(newProduct);
        return NULL;
    }



    // assign the values
    newProduct->id = id;
    size_t typeSize = strlen(type) + 1;
    strcpy_s(newProduct->type, typeSize, type);
    size_t manufacturerSize = strlen(manufacturer) + 1;
    strcpy_s(newProduct->manufacturer, manufacturerSize, manufacturer);
    size_t modelSize = strlen(model) + 1;
    strcpy_s(newProduct->model, modelSize, model);
    newProduct->price = price;
    newProduct->quantity = quantity;

    // return the pointer to the newProduct
    return newProduct;
}

/*
 * Deallocates all the memory used by the received Product.
 * Preconditions: productToDestroy: a pointer to an instance of the Product class
 * Post-conditions: -
 */
void destroyProduct(Product* productToDestroy) {
    // deallocate the space used by the char fields
    free(productToDestroy->type);
    free(productToDestroy->manufacturer);
    free(productToDestroy->model);

    // deallocate the pointer to the product
    free(productToDestroy);
}

/*
 * Returns the id of the received product
 * Preconditions: product: a pointer to an instance of the Product class
 * Post-conditions: an integer
 */
int get_product_id(Product *product) {
	return product->id;

}

/*
 * Returns the type of the received product
 * Preconditions: product: a pointer to an instance of the Product class
 * Post-conditions: a pointer to a char
 */
char *get_product_type(Product *product) {
    return product->type;
}

/*
 * Returns the manufacturer of the received product
 * Preconditions: product: a pointer to an instance of the Product class
 * Post-conditions: a pointer to a char
 */

char *get_product_manufacturer(Product *product) {
	return product->manufacturer;
}

/*
 * Returns the model of the received product
 * Preconditions: product: a pointer to an instance of the Product class
 * Post-conditions: a pointer to a char
 */
char *get_product_model(Product *product) {
    return product->model;
}
    
/*
 * Returns the price of the received product
 * Preconditions: product: a pointer to an instance of the Product class
 * Post-conditions: a float
 */
long double get_product_price(Product *product) {
	return product->price;
}

/*
 * Returns the quantity of the received product
 * Preconditions: product: a pointer to an instance of the Product class
 * Post-conditions: an integer
 */
int get_product_quantity(Product *product) {
    return product->quantity;
}


