#include <assert.h>
#include "validatorsTest.h"
#include "validators.h"

void testValidateId() {
    // Arrange
    char invalidId1[20] = "2a4";
    char invalidId2[20] = "";
    char validId[20] = "23";

    // Assert
    assert(validateId(invalidId1) == false);
    assert(validateId(invalidId2) == false);
    assert(validateId(validId) == true);
}

void testValidateType() {
    // Arrange
    char invalidType[20] = "Car";
    char validType[20] = "Computer";

    // Assert
    assert(validateType(invalidType) == false);
    assert(validateType(validType) == true);
}

void testValidateManufacturer() {
    // Arrange
    char invalidManufacturer1[20] = "ASD@#bf12";
    char invalidManufacturer2[20] = "";
    char validManufacturer[20] = "ASDFG12AS";

    // Assert
    assert(validateManufacturer(invalidManufacturer1) == false);
    assert(validateManufacturer(invalidManufacturer2) == false);
    assert(validateManufacturer(validManufacturer) == true);
}

void testValidateModel() {
    // Arrange
    char invalidModel1[20] = "12@#fG";
    char invalidModel2[20] = "";
    char validModel[20] = "12FG4GH";

    // Assert
    assert(validateModel(invalidModel1) == false);
    assert(validateModel(invalidModel2) == false);
    assert(validateModel(validModel) == true);
}

void testValidatePrice() {
    // Arrange
    char invalidPrice1[20] = "-23.4";
    char invalidPrice2[20] = "2.34.5.6";
    char invalidPrice3[20] = "";
    char validPrice[20] = "12.3455";

    // Assert
    assert(validatePrice(invalidPrice1) == false);
    assert(validatePrice(invalidPrice2) == false);
    assert(validatePrice(invalidPrice3) == false);
    assert(validatePrice(validPrice) == true);
}

void testValidateQuantity() {
    // Arrange
    char invalidQuantity1[20] = "2.3";
    char invalidQuantity2[20] = "";
    char validQuantity[20] = "2";

    // Assert
    assert(validateQuantity(invalidQuantity1) == false);
    assert(validateQuantity(invalidQuantity2) == false);
    assert(validateQuantity(validQuantity) == true);
}

void testValidateOption() {
    // Arrange
    char invalidOption1[20] = "20";
    char invalidOption2[20] = "";
    char invalidOption3[20] = "2a";
    char validOption[20] = "6";

    // Assert
    assert(validateOption(invalidOption1) == false);
    assert(validateOption(invalidOption2) == false);
    assert(validateOption(invalidOption3) == false);
    assert(validateOption(validOption) == true);
}