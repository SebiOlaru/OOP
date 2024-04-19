#include <assert.h>
#include "utilsTests.h"
#include "models.h"
#include "utils.h"
//#include "../controllers/controllers.h"

void testGetIdForNewProduct() {
    // Arrange
    GenericRepo* repo = createRepo();
    Product* newProduct = createProduct(1, "Computer", "AAAA", "Aaaa", 12, 12);
    addItemRepo(repo, newProduct, get_product_id);

    // Act
    int actual1 = getIdForNewProduct(repo);

    // Assert
    assert(actual1 == 2);

    // Cleanup
    destroyRepoProduct(repo);
}

void testCompareProductsInAscendantOrder() {
    // Arrange
    Product* product1 = createProduct(1, "Computer", "AAAA", "Aaaa", 12, 12);
    Product* product2 = createProduct(2, "Computer", "AAAA", "Aaaa", 13, 12);
    Product* product3 = createProduct(3, "Computer", "AAAA", "Aaaa", 12, 11);
    Product* product4 = createProduct(4, "Computer", "AAAA", "Aaaa", 12, 13);


    // Act
    bool actual1 = compareProductsInAscendantOrder(product1, product2);
    bool actual2 = compareProductsInAscendantOrder(product1, product3);
    bool actual3 = compareProductsInAscendantOrder(product1, product4);

    // Assert
    assert(actual1 == true);
    assert(actual2 == false);
    assert(actual3 == true);

    // Cleanup
    destroyProduct(product1);
    destroyProduct(product2);
    destroyProduct(product3);
    destroyProduct(product4);
}

void testCompareProductsInDescendantOrder() {
    // Arrange
    Product* product1 = createProduct(1, "Computer", "AAAA", "Aaaa", 12, 12);
    Product* product2 = createProduct(2, "Computer", "AAAA", "Aaaa", 13, 12);
    Product* product3 = createProduct(3, "Computer", "AAAA", "Aaaa", 12, 11);


    // Act
    bool actual1 = compareProductsInDescendantOrder(product1, product2);
    bool actual2 = compareProductsInDescendantOrder(product1, product3);
    bool actual3 = compareProductsInDescendantOrder(product2, product1);

    // Assert
    assert(actual1 == false);
    assert(actual2 == true);
    assert(actual3 == true);

    // Cleanup
    destroyProduct(product1);
    destroyProduct(product2);
    destroyProduct(product3);
}

void testCompareManufacturers() {
    // Arrange
    Product* product1 = createProduct(1, "Computer", "ABC", "Aaaa", 12, 12);

    // Act
    bool actual1 = compareManufacturers(product1, "ABC");
    bool actual2 = compareManufacturers(product1, "ABCD");

    // Assert
    assert(actual1 == true);
    assert(actual2 == false);

    // Cleanup
    destroyProduct(product1);
}

void testComparePrice() {
    // Arrange
    Product* product1 = createProduct(1, "Computer", "ABC", "Aaaa", 12, 12);

    // Act
    bool actual1 = comparePrice(product1, "12");
    bool actual2 = comparePrice(product1, "13");

    // Assert
    assert(actual1 == true);
    assert(actual2 == false);

    // Cleanup
    destroyProduct(product1);
}

void testCompareQuantity() {
    // Arrange
    Product* product1 = createProduct(1, "Computer", "ABC", "Aaaa", 12, 12);

    // Act
    bool actual1 = compareQuantity(product1, "12");
    bool actual2 = compareQuantity(product1, "13");

    // Assert
    assert(actual1 == true);
    assert(actual2 == false);

    // Cleanup
    destroyProduct(product1);
}