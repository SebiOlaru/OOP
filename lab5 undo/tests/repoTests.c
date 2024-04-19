#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "repoTests.h"
#include "assert.h"
#include "models.h"
#include "repos.h"
#include "controllers.h"

void testAddItemRepo() {
    // Arrange
    GenericRepo* repo = createRepo();
    Product* newProduct = createProduct(1, "Computer\0", "AAAA\0", "Aaaa\0", 12, 12);
    Product* newProduct1 = createProduct(2, "Computer\0", "gggg\0", "Aaaa\0", 12, 12);
    Product* newProduct2 = createProduct(3, "Computer\0", "AAAA\0", "Aaaa\0", 12, 12);

    //Act
    bool actual1 = addItemRepo(repo, newProduct, get_product_id);
    bool actual2 = addItemRepo(repo, newProduct, get_product_id);
    bool actual3 = addItemRepo(repo, newProduct2, get_product_id);
    bool actual4 = addItemRepo(repo, newProduct1, get_product_id);

    // Assert
    assert(get_product_id(repo->items[0]) == 1);

    assert(actual1 == true);
    assert(actual2 == false);
    assert(actual3 == true);
    assert(actual4 == true);

    assert(repo->numberOfItems == 3);

    // Cleanup
    destroyRepoProduct(repo);
}

void testUpdateItemRepo() {
    // Arrange
    GenericRepo* repo = createRepo();
    Product* newProduct = createProduct(1, "Computer", "AAAA", "Aaaa", 12, 12);
    Product* updatedProduct = createProduct(1, "Fridge", "Samsung", "FH2", 700, 300);
    addItemRepo(repo, newProduct, get_product_id);

    // Arrange
    bool actual1 = updateItemRepo(repo, updatedProduct, get_product_id);

    // Assert
    assert(actual1 == true);
    assert(get_product_id(repo->items[0]) == 1);
    assert(strcmp(get_product_type(repo->items[0]), "Fridge") == 0);
    assert(strcmp(get_product_manufacturer(repo->items[0]), "Samsung") == 0);
    assert(strcmp(get_product_model(repo->items[0]), "FH2") == 0);
    assert(get_product_price(repo->items[0]) == 700);
    assert(get_product_quantity(repo->items[0]) == 300);

    // Cleanup
    destroyRepoProduct(repo);
}

void testDeleteProductRepo() {
    // Arrange
    GenericRepo* repo = createRepo();
    Product* product1 = createProduct(1, "Computer", "Asus", "K2J", 2000, 220);
    addItemRepo(repo, product1, get_product_id);
    Product* product2 = createProduct(2, "Fridge", "Arctic", "HX2", 1200, 12);
    addItemRepo(repo, product2, get_product_id);

    // Act
    bool actual1 = deleteItemRepo(repo, 1, get_product_id, destroyProduct);
    bool actual2 = deleteItemRepo(repo, 1, get_product_id, destroyProduct);

    // Assert
    assert(actual1 == true);
    assert(actual2 == false);
    assert(get_product_id(repo->items[0]) == 2);
    assert(strcmp(get_product_manufacturer(repo->items[0]) , "Arctic") == 0);
    assert(strcmp(get_product_model(repo->items[0]) , "HX2") == 0);
    assert(get_product_price(repo->items[0]) == 1200);
    assert(get_product_quantity(repo->items[0]) == 12);

    assert(repo->numberOfItems == 1);


    // Cleanup
    destroyRepoProduct(repo);
}

void testCopieRepo() {
    // Arrange
	GenericRepo* repo = createRepo();
	Product* product1 = createProduct(1, "Computer", "Asus", "K2J", 2000, 220);
	addItemRepo(repo, product1, get_product_id);
	Product* product2 = createProduct(2, "Fridge", "Arctic", "HX2", 1200, 12);
	addItemRepo(repo, product2, get_product_id);

	// Act
	GenericRepo* repo2 = copie_repo(repo);

	// Assert
	assert(repo2->numberOfItems == 2);
	assert(get_product_id(repo2->items[0]) == 1);
	assert(get_product_id(repo2->items[1]) == 2);

	assert(strcmp(get_product_manufacturer(repo2->items[0]) , "Asus") == 0);
	assert(strcmp(get_product_manufacturer(repo2->items[1]) , "Arctic") == 0);

    assert(strcmp(get_product_model(repo2->items[0]) , "K2J") == 0);
    assert(strcmp(get_product_model(repo2->items[1]) , "HX2") == 0);

    assert(get_product_price(repo2->items[0]) == 2000);
    assert(get_product_price(repo2->items[1]) == 1200);

    assert(get_product_quantity(repo2->items[0]) == 220);
    assert(get_product_quantity(repo2->items[1]) == 12);

    // Cleanup
    destroyRepoProduct(repo);
    destroyRepoProduct(repo2);

}
void testCompareTwoRepos() {
    	// Arrange
	GenericRepo* repo1 = createRepo();
	Product* product1 = createProduct(1, "Computer", "Asus", "K2J", 2000, 220);
	addItemRepo(repo1, product1, get_product_id);
	Product* product2 = createProduct(2, "Fridge", "Arctic", "HX2", 1200, 12);
	addItemRepo(repo1, product2, get_product_id);

	GenericRepo* repo2 = createRepo();
	Product* product3 = createProduct(1, "Computer", "Asus", "K2J", 2000, 220);
	addItemRepo(repo2, product3, get_product_id);
	Product* product4 = createProduct(2, "Fridge", "Arctic", "HX2", 1201, 12);
	addItemRepo(repo2, product4, get_product_id);

	// Act
	bool actual1 = compare_two_repos(repo1, repo2);

	// Assert
	assert(actual1 == true);

	// Cleanup
	destroyRepoProduct(repo1);
	destroyRepoProduct(repo2);

}

void testDestroyContentOfProduct() {
    //Arrange
    GenericRepo* repo1 = createRepo();
    void* adr = repo1;

    Product* product1 = createProduct(1, "Computer", "Asus", "K2J", 2000, 220);
    addItemRepo(repo1, product1, get_product_id);
    Product* product2 = createProduct(2, "Fridge", "Arctic", "HX2", 1200, 12);
    addItemRepo(repo1, product2, get_product_id);

    // Act
    destroyContentRepoProduct(repo1);
    
    //Assert
    assert(adr == repo1);
    assert(repo1->numberOfItems == 0);
    assert(repo1->numberOfItemsAddedFromStart == 0);

    //Cleanup
    free(repo1);
}

void testDestroyProductRepo() {
    //Arrange
	GenericRepo* repo1 = createRepo();
	void* adr = repo1;

	Product* product1 = createProduct(1, "Computer", "Asus", "K2J", 2000, 220);
	addItemRepo(repo1, product1, get_product_id);
	Product* product2 = createProduct(2, "Fridge", "Arctic", "HX2", 1200, 12);
	addItemRepo(repo1, product2, get_product_id);

    // Act + Cleanup
    destroyRepoProduct(repo1);

    //Assert
    assert(adr == repo1);

}
//void testUndo() {
//    //Arrange
//    Controller* srv = createController();
//    addProductController(srv, 1, "Computer", "Asus", "K2J", "2000", "220");
//    //undo - add undo[0]
//    addProductController(srv, 2, "Fridge", "Arctic", "HX2", "1200", "12");
//    //undo - add undo[1]
//    addProductController(srv, 3, "Laptop", "Asus Rog", "J34", "6000", "40");
//    //undo - add undo[2]
//    // undo->nrOfItems = 3
//    // repo = undo[3-2] = undo[1]
//
//    //Act + assert
//    GenericRepo* topStack = srv->undoList->items[srv->undoList->numberOfItems - 1];
//    assert(topStack->numberOfItems == 3);
//    assert(get_product_id(topStack->items[0]) == 1);
//    assert(get_product_id(topStack->items[1]) == 2);
//    assert(get_product_id(topStack->items[2]) == 3);
//
//    doUndoRepo(srv->repo, srv->undoList, destroyContentRepoProduct);
//    assert(srv->repo->numberOfItems == 2);
//    assert(srv->undoList->numberOfItems == 1);
//    assert(srv->undoList->numberOfItemsAddedFromStart == 3);
//
//    assert(get_product_id(srv->repo->items[0]) == 1);
//    assert(strcmp(get_product_type(srv->repo->items[0]), "Computer") == 0);
//    assert(strcmp(get_product_manufacturer(srv->repo->items[0]), "Asus") == 0);
//    assert(strcmp(get_product_model(srv->repo->items[0]), "K2J") == 0);
//    assert(get_product_price(srv->repo->items[0]) == 2000);
//    assert(get_product_quantity(srv->repo->items[0]) == 220);
//
//    assert(get_product_id(srv->repo->items[1]) == 2);
//    assert(strcmp(get_product_type(srv->repo->items[1]), "Fridge") == 0);
//    assert(strcmp(get_product_manufacturer(srv->repo->items[1]), "Arctic") == 0);
//    assert(strcmp(get_product_model(srv->repo->items[1]), "HX2") == 0);
//    assert(get_product_price(srv->repo->items[1]) == 1200);
//    assert(get_product_quantity(srv->repo->items[1]) == 12);
//
//    doUndoRepo(srv->repo, srv->undoList, destroyContentRepoProduct);
//
//    assert(srv->repo->numberOfItems == 1);
//    assert(get_product_id(srv->repo->items[0]) == 1);
//    assert(strcmp(get_product_type(srv->repo->items[0]), "Computer") == 0);
//    assert(strcmp(get_product_manufacturer(srv->repo->items[0]), "Asus") == 0);
//    assert(strcmp(get_product_model(srv->repo->items[0]), "K2J") == 0);
//    assert(get_product_price(srv->repo->items[0]) == 2000);
//    assert(get_product_quantity(srv->repo->items[0]) == 220);
//
//    //Cleanup
//    destroyController(srv);
//}