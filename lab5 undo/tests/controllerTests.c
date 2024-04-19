#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "controllerTests.h"
#include "controllers.h"
#include "utils.h"

void testAddProductController() {
    // Arrange
    Controller* srv = createController();

    //Act
    bool actual1 = addProductController(srv, 1, "Computer", "Lenovo", "Hx31", "12",
        "44");
    bool actual2 = addProductController(srv, 1, "Computer", "AAAA", "Aaaa", "12",
        "12");

    // Assert
    assert(actual1 == true);
    assert(srv->repo->numberOfItems == 1);
    
    assert(get_product_id(srv->repo->items[0]) == 1);
    assert(strcmp(get_product_type(srv->repo->items[0]), "Computer") == 0);
    assert(get_product_quantity(srv->repo->items[0]) == 44);
    assert(strcmp(get_product_manufacturer(srv->repo->items[0]), "Lenovo") == 0);
    assert(strcmp(get_product_model(srv->repo->items[0]), "Hx31") == 0);
    assert(get_product_price(srv->repo->items[0]) == 12);

    assert(actual2 == false);

    // Cleanup
    destroyController(srv);
}

void testUpdateProductController() {
    // Arrange
    Controller* srv = createController();
    addProductController(srv, 1, "Computer", "AAAA", "Aaaa", "12", "12");

    // Act
    bool actual1 = updateProductController(srv, 1, "Fridge", "Arctic", "H2X", "123", "13");
    bool actual2 = updateProductController(srv, 2, "Laptop", "Lenovo", "H2XT", "3333", "133");

    // Assert
    assert(actual1 == true);
    assert(get_product_id(srv->repo->items[0]) == 1);
    assert(strcmp(get_product_type(srv->repo->items[0]), "Fridge") == 0);
    assert(strcmp(get_product_manufacturer(srv->repo->items[0]), "Arctic") == 0);
    assert(strcmp(get_product_model(srv->repo->items[0]), "H2X") == 0);
    assert(get_product_price(srv->repo->items[0]) == 123);
    assert(get_product_quantity(srv->repo->items[0]) == 13);

    assert(actual2 == false);
    // Cleanup
    destroyController(srv);
}

void testDeleteProductController() {
    // Arrange
    Controller *srv = createController();
    addProductController(srv, 1, "Computer", "AAAA", "Aaaa", "12", "12");
    addProductController(srv, 2, "Laptop", "Lenovo", "H2XT", "3333", "133");

    // Act
    bool actual1 = deleteProductController(srv, 1);
    bool actual2 = deleteProductController(srv, 3);

    // Assert
    assert(actual1 == true);
    assert(get_product_id(srv->repo->items[0]) == 2);
    assert(srv->repo->numberOfItems == 1);
    
    assert(strcmp(get_product_type(srv->repo->items[0]), "Laptop") == 0);
    assert(strcmp(get_product_manufacturer(srv->repo->items[0]), "Lenovo") == 0);
    assert(strcmp(get_product_model(srv->repo->items[0]), "H2XT") == 0);
    assert(get_product_price(srv->repo->items[0]) == 3333);
    assert(get_product_quantity(srv->repo->items[0]) == 133);

    assert(actual2 == false);

    // Cleanup
    destroyController(srv);
}

void testGetAvailableProducts() {
    // Arrange
    Controller *srv = createController();
    addProductController(srv, 1, "Computer", "AAAA", "Aaaa", "12", "12");
    addProductController(srv, 2, "Laptop", "Lenovo", "H2XT", "3333", "133");
    addProductController(srv, 3, "Laptop", "Asus", "H2", "200", "13");

    // Act
    GenericRepo* actual1 = getAvailableProducts(srv, compareProductsInAscendantOrder);

    // Assert
    assert(get_product_id(actual1->items[0]) == 1);
    assert(get_product_id(actual1->items[1]) == 3);
    assert(get_product_id(actual1->items[2]) == 2);

    // Cleanup
    destroyController(srv);
    destroyRepoProduct(actual1);
}

void testGetProductsFiltered() {
    // Arrange
    Controller* srv = createController();
    addProductController(srv, 1, "Computer", "AAAA", "Aaaa", "12", "12");
    addProductController(srv, 2, "Computer", "AAAA", "aa", "11", "102");
    addProductController(srv, 3, "Computer", "AAAA", "Aaa", "12", "3");

    // Act
    GenericRepo* actual1 = getProductsFiltered(srv, comparePrice, "12");
    GenericRepo* actual2 = getProductsFiltered(srv, compareLimit, "100"); // new filter

    // Assert
    assert(get_product_id(actual1->items[0]) == 1);
    assert(get_product_id(actual1->items[1]) == 3);

    assert(get_product_id(actual2->items[0]) == 1);
    assert(get_product_id(actual2->items[1]) == 3);


    // Cleanup
    destroyController(srv);
    destroyRepoProduct(actual1);
    destroyRepoProduct(actual2);
}

void testDestroyController() {
	// Arrange
	Controller* srv = createController();
    addProductController(srv, 1, "Computer", "AAAA", "Aaaa", "12", "12");
    addProductController(srv, 2, "Laptop", "Lenovo", "H2XT", "3333", "133");
    addProductController(srv, 3, "Laptop", "Asus", "H2", "200", "13");

    destroyController(srv);
}

void testUndo() {
    	// Arrange
	Controller* srv = createController();
	addProductController(srv, 1, "Computer", "Asus", "K2J", "2000", "220");
	addProductController(srv, 2, "Fridge", "Arctic", "HX2", "1200", "12");
	addProductController(srv, 3, "Laptop", "Asus Rog", "J34", "6000", "40");

	// Act
	doUndo(srv);

	// Assert
	assert(srv->repo->numberOfItems == 2);
	assert(get_product_id(srv->repo->items[0]) == 1);
	assert(get_product_id(srv->repo->items[1]) == 2);

	// Cleanup
	destroyController(srv);
}