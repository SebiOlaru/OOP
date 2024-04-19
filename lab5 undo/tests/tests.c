#include "tests.h"
#include "repoTests.h"
#include "validatorsTest.h"
#include "controllerTests.h"
#include "utilsTests.h"

void runAllTests() {
    // repo tests
    testAddItemRepo();
    testUpdateItemRepo();
    testDeleteProductRepo();
    testCopieRepo();
    testCompareTwoRepos();
    testDestroyContentOfProduct();
    testDestroyProductRepo();
    //testUndo();

    // validators tests
    testValidateId();
    testValidateManufacturer();
    testValidateModel();
    testValidateOption();
    testValidatePrice();
    testValidateQuantity();
    testValidateType();

    // controller tests
    testAddProductController();
    testUpdateProductController();
    testDeleteProductController();
    testGetAvailableProducts();
    testGetProductsFiltered();
    testDestroyController();
    testUndo();

    // utils tests
    testGetIdForNewProduct();
    testCompareProductsInAscendantOrder();
    testCompareProductsInDescendantOrder();
    testCompareManufacturers();
    testComparePrice();
    testCompareQuantity();
}