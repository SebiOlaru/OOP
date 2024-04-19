#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "repos.h"

/*
 * Returns a valid id for a new product.
 * Preconditions: repo: a pointer to an instance of the ProductsRepo struct
 * Post-conditions: an integer
 */
int getIdForNewProduct(GenericRepo* repo) {
    int maxId = 0;
    // find the max id in the list of products
    for (int i = 0; i < repo->numberOfItems; i++) {
        if (get_product_id(repo->items[i]) > maxId) {
            maxId = get_product_id(repo->items[i]);
        }
    }

    // return the id increased by one in order to be unique
    return maxId + 1;
}

/*
 * A function that compares two products in ascendant order by price and quantity.
 * Preconditions: product1: a pointer to an instance of the Product struct
 *                product2: a pointer to an instance of the Product struct
 * Post-conditions: a bool
 */
bool compareProductsInAscendantOrder(Product* product1, Product* product2) {
    // check the prices
    if (product1->price < product2->price) {
        return true;
    }
    else if (product1->price == product2->price) {
        // check the quantities if the prices are equal
        if (product1->quantity < product2->quantity) {
            return true;
        }
    }

    return false;
}

/*
 * A function that compares two products in descendant order by price and quantity.
 * Preconditions: product1: a pointer to an instance of the Product struct
 *                product2: a pointer to an instance of the Product struct
 * Post-conditions: a bool
 */
bool compareProductsInDescendantOrder(Product* product1, Product* product2) {
    // check the prices
    if (product1->price > product2->price) {
        return true;
    }
    else if (product1->price == product2->price) {
        // check the quantities if the prices are equal
        if (product1->quantity > product2->quantity) {
            return true;
        }
    }

    return false;
}

/*
 * A function that checks if a product has a certain manufacturer.
 * Preconditions: product: an instance of the Product struct
 *                manufacturer: a pointer to a char
 * Post-conditions: a bool
 */
bool compareManufacturers(Product* product, char* manufacturer) {
    if (strcmp(product->manufacturer, manufacturer) == 0) {
        return true;
    }
    return false;
}

/*
 * A function that checks if a product has a certain price.
 * Preconditions: product: an instance of the Product struct
 *                price: a pointer to a char
 * Post-conditions: a bool
 */
bool comparePrice(Product* product, char* price) {
    return product->price == atof(price);
}

/*
 * A function that checks if a product has a certain quantity.
 * Preconditions: product: an instance of the Product struct
 *                quantity: a pointer to a char
 * Post-conditions: a bool
 */
bool compareQuantity(Product* product, char* quantity) {
    return product->quantity == atoi(quantity);
}

bool compareLimit(Product* product, char* limit) {
	return product->quantity < atoi(limit);
}