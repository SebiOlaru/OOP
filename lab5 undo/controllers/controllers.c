#pragma once
#include <stdlib.h>
#include <string.h>
#include "controllers.h"
#include "validators.h"
#include "repos.h"


Controller *createController() {
    Controller* srv = malloc(sizeof(Controller));
	if (srv == NULL) {
        exit(EXIT_FAILURE);
	}
	srv->repo = createRepo();
    srv->undoList = createRepo();
    return srv;
}

void destroyController(Controller* srv) {
	destroyRepoProduct(srv->repo);
	destroyRepoGeneric(srv->undoList, destroyRepoProduct);
	free(srv);
}
/*
 * Attempts to add a new product in the list of products
 * Preconditions: products: a pointer to an instance of the ProductsRepo class
 *                id: a positive integer
 *                type: a pointer to a char
 *                manufacturer: a pointer to a char
 *                model: a pointer to a char
 *                price: a pointer to a char
 *                quantity: a pointer to a char
 * Post-conditions: a boolean
 */
bool addProductController(Controller* srv, int id, char* type, char* manufacturer, char* model,
    char* price, char* quantity) {
    // create the new product
    Product* newProduct = createProduct(id, type, manufacturer, model, atof(price), atoi(quantity));

    // add the new product
    addItemRepo(srv->undoList, copie_repo(srv->repo), NULL);
    bool result = addItemRepo(srv->repo, newProduct, get_product_id);
    // if the result is false free the memory allocated to the new product
    if (!result) {
        destroyProduct(newProduct);
    }
    return result;
}

/*
 * Attempts to update the product with the received id
 * Preconditions: repo: a pointer to an instance of the ProductsRepo class
 *                productToUpdateId: a positive integer
 *                newQuantity: a positive integer
 *                newPrice: a positive float
 * Post-conditions: a boolean
 */
bool updateProductController(Controller* srv, int id, char* type, char* manufacturer, char* model,
    char* price, char* quantity) {
    // create the new product
    Product* newProduct = createProduct(id, type, manufacturer, model, atof(price), atoi(quantity));

    // update the product
	addItemRepo(srv->undoList, copie_repo(srv->repo), NULL);
    bool result = updateItemRepo(srv->repo, newProduct, get_product_id);
    if (!result) {
		destroyProduct(newProduct);
	}
    return result;
}

/*
 * Attempts to delete the product with the received id
 * Preconditions: repo: a pointer to an instance of the ProductsRepo struct
 *                productToDeleteId: a positive integer
 * Post-conditions: a boolean
 */
bool deleteProductController(Controller* srv, int productToDeleteId) {
    // delete the product
    addItemRepo(srv->undoList, copie_repo(srv->repo), NULL);
	bool result = deleteItemRepo(srv->repo, productToDeleteId, get_product_id, destroyProduct);
	return result;
}

/*
 * Returns the available products sorted depending on the function received as a parameter
 * Preconditions: repo: a pointer to an instance of the ProductsRepo struct
 *                compareProducts: a function that returns a bool and takes two instances of the Product struct as parameters
 * Post-conditions: a pointer to an instance of the ProductsRepo struct
 */
GenericRepo* getAvailableProducts(Controller* srv, bool (*compareProducts)(Product*, Product*)) {
    // allocate memory for the result and initialize the number of products
    GenericRepo* result = createRepo();
    // go through all products and only copy those that are still available
    for (int i = 0; i < srv->repo->numberOfItems; i++) {
        if (get_product_quantity(srv->repo->items[i]) > 0) {
            Product *local_product = createProduct(get_product_id(srv->repo->items[i]), 
                get_product_type(srv->repo->items[i]), 
                get_product_manufacturer(srv->repo->items[i]),
                get_product_model(srv->repo->items[i]), 
                get_product_price(srv->repo->items[i]),
                get_product_quantity(srv->repo->items[i]));
            addItemRepo(result, local_product, get_product_id);
        }
    }
    // sort depending on the comparison function
    for (int i = 0; i < result->numberOfItems - 1; i++) {
        for (int j = i + 1; j < result->numberOfItems; j++) {
            if (!compareProducts(result->items[i], result->items[j])) {
                Product* aux = result->items[i];
                result->items[i] = result->items[j];
                result->items[j] = aux;
            }
        }
    }

    return result;
}

/*
 * Returns the products that meet a certain property depending on the value and function received as parameters
 * Preconditions: repo: a pointer to an instance of the ProductsRepo struct
 *                checkProductProperty: a function that returns a bool and takes as arguments a pointer to a Product and a pointer to a char
 *                valueToCompareWith: a pointer to a char
 * Post-conditions: a pointer to an instance of the ProductsRepo
 */
GenericRepo* getProductsFiltered(Controller* srv, bool (*checkProductProperty)(Product*, char*), char* valueToCompareWith) {
    // allocate memory to the result repo
    GenericRepo* result = createRepo();

    // filter by different criteria
    for (int i = 0; i < srv->repo->numberOfItems; i++) {
        if (checkProductProperty(srv->repo->items[i], valueToCompareWith)) {
            Product *local_product = createProduct(get_product_id(srv->repo->items[i]), 
				get_product_type(srv->repo->items[i]), 
				get_product_manufacturer(srv->repo->items[i]),
				get_product_model(srv->repo->items[i]), 
				get_product_price(srv->repo->items[i]),
				get_product_quantity(srv->repo->items[i]));
            addItemRepo(result, local_product, get_product_id);
        }
    }

    return result;
}

/*
 * Performs the undo operation
 * Preconditions: srv: a pointer to an instance of the Controller struct
 */
bool doUndo(Controller* srv) {
	if(srv->undoList->numberOfItems == 0)
		return false;
    destroyRepoProduct(srv->repo);
    GenericRepo *curent = srv->undoList->items[srv->undoList->numberOfItems - 1];
    srv->undoList->numberOfItems -= 1;
    srv->repo = copie_repo(curent);
    destroyRepoProduct(curent);
    return true;
    //return doUndoRepo(srv->repo, srv->undoList, destroyContentRepoProduct);
}

