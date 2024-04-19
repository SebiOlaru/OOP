#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"
#include "validators.h"
#include "controllers.h"
#include "utils.h"
#include "repos.h"

void app() {
    printf("This is a electronics store shop.\n");

    bool running = true;
    Controller* controller = createController();
    // needed for fgets to pause the execution of the program
    char dummyInput[100];
    while (running) {
        printf(
            "Choose one of the following commands:\n"
            "  1. Add new product.\n"
            "  2. Update product.\n"
            "  3. Delete product.\n"
            "  4. Display available products.\n"
            "  5. Display products filtered by a certain criteria.\n"
            "  6. Undo.\n"
            "  7. Exit the application.\n "
        );
        char* option = getInput();
        if (validateOption(option)) {
            switch (atoi(option)) {
                // add new product feature
            case 1:
                // get type
                printf("Input the type of the product, the product can be a Laptop, a Computer or a Fridge.\n");
                char* type = getInput();

                // get id for new product
                int id = getIdForNewProduct(controller->repo);

                // get manufacturer
                printf("Input the manufacturer of the product.\n");
                char* manufacturer = getInput();

                // get model
                printf("Input the model of the product.\n");
                char* model = getInput();

                // get price
                printf("Input the price of the product.\n");
                char* price = getInput();

                // get quantity
                printf("Input the quantity of the product.\n");
                char* quantity = getInput();

                // check if the input data is valid
                if (
                    validateType(type) &&
                    validateManufacturer(manufacturer) &&
                    validateModel(model) &&
                    validatePrice(price) &&
                    validateQuantity(quantity)
                    ) {
                    // add the product if the data is valid
                    bool result = addProductController(controller, id, type, manufacturer, model, price, quantity);
                    if (result) 
                        printf("The product was added successfully.\n");   
                    else 
                        printf("The product was not added.\n");
                }
                else {
                    printf("The input data is invalid.\n");
                }
                free(type);
                free(manufacturer);
                free(model);
                free(price);
                free(quantity);
                break;
                // update product
            case 2:
                // check if there are any products to update
                if (controller->repo->numberOfItems == 0) {
                    printf("There are no products to update.\n");
                }
                else {
                    // display products and get the id
                    printf("Input the id of the product that will be updated.\n");
                    displayProducts(controller->repo);
                    char* newIdChar = getInput();

                    // get type
                    printf("Input the type of the product, the product can be a Laptop, a Computer or a Fridge.\n");
                    char* newType = getInput();

                    // get manufacturer
                    printf("Input the manufacturer of the product.\n");
                    char* newManufacturer = getInput();

                    // get model
                    printf("Input the model of the product.\n");
                    char* newModel = getInput();

                    // get price
                    printf("Input the price of the product.\n");
                    char* newPrice = getInput();

                    // get quantity
                    printf("Input the quantity of the product.\n");
                    char* newQuantity = getInput();

                    // check if the input is valid and if it is attempt the update
                    if (
                        validateType(newType) &&
                        validateManufacturer(newManufacturer) &&
                        validateModel(newModel) &&
                        validatePrice(newPrice) &&
                        validateQuantity(newQuantity)
                        ) {
                        bool result = updateProductController(controller, atoi(newIdChar), newType, newManufacturer, newModel, newPrice, newQuantity);
                        if (!result)
                            printf("The update was unsuccessful\n");
                        else
                            printf("The update was successful\n");
                    }
                    free(newIdChar);
                    free(newType);
                    free(newManufacturer);
                    free(newModel);
                    free(newPrice);
                    free(newQuantity);
                }
                break;
                // delete product
            case 3:
                // check if there are any products to display
                if (controller->repo->numberOfItems == 0) {
                    printf("There are no products to delete.\n");
                }
                else {
                    // display the products and obtain the id of the product that will be deleted
                    printf("Input the id of the product that will be deleted.\n");
                    displayProducts(controller->repo);
                    char* idChar = getInput();

                    // attempt to delete the product with the input id
                    if (validateId(idChar)) {
                        bool result = deleteProductController(controller, atoi(idChar));
                        if (result) 
                            printf("The selected product was deleted successfully.\n");
                        else 
                            printf("The deletion was unsuccessful.\n");
                    }
                    else {
                        printf("The input id was invalid.\n");
                    }
                    free(idChar);
                }
                break;
            case 4:
                // get the ordering of the list
                printf("Input the ordering of the available products: ascending / descending\n");
                char* ordering = getInput();

                // check if the input is valid
                if (strcmp(ordering, "ascending") == 0 || strcmp(ordering, "descending") == 0) {
                    GenericRepo* result;
                    if (strcmp(ordering, "ascending") == 0) {
                        result = getAvailableProducts(controller,
                            compareProductsInAscendantOrder);
                    }
                    else {
                        result = getAvailableProducts(controller,
                            compareProductsInDescendantOrder);
                    }
                    // display a table if there are any products available, otherwise show a message
                    if (result->numberOfItems > 0) {
                        displayProducts(result);
                    }
                    else {
                        printf("There are no products available.\n");
                    }
                    destroyRepoProduct(result);
                }
                else {
                    printf("The input ordering is invalid.\n");
                }
                free(ordering);
                break;
            case 5:
                // get the criteria
                printf("< limit > shows the products with a quantity less than the input quantity.\n");
                printf("Input the criteria by which the products will be filtered: manufacturer / price / quantity / limit \n");
                char* criteria = getInput();

                // check if the input is valid
                if (
                    strcmp(criteria, "manufacturer") == 0 ||
                    strcmp(criteria, "price") == 0 ||
                    strcmp(criteria, "quantity") == 0 ||
                    strcmp(criteria, "limit") == 0
                    ) {
                    // get the value by which the products should be filtered
                    char* valueToFilterBy;
                    GenericRepo* result = NULL;
                    if (strcmp(criteria, "manufacturer") == 0) {
                        printf("Input the manufacturer of the product.\n");
                        valueToFilterBy = getInput();

                        // check if the manufacturer is valid
                        if (validateManufacturer(valueToFilterBy)) {
                            // get the number of filtered products and the result
                            result = getProductsFiltered(controller, compareManufacturers, valueToFilterBy);
                        }
                        else {
                            printf("The input manufacturer is invalid.\n");
                        }
                        free(valueToFilterBy);
                    }
                    else if (strcmp(criteria, "price") == 0) {
                        printf("Input the price of the product.\n");
                        valueToFilterBy = getInput();

                        // check if the price is valid
                        if (validatePrice(valueToFilterBy)) {
                            // get the number of filtered products and the result
                            result = getProductsFiltered(controller, comparePrice, valueToFilterBy);
                        }
                        else {
                            printf("The input price is invalid.\n");
                        }
                        free(valueToFilterBy);
                    }
                    else if (strcmp(criteria, "quantity") == 0) {
                        printf("Input the quantity of the product.\n");
                        valueToFilterBy = getInput();

                        // check if the quantity is valid
                        if (validateQuantity(valueToFilterBy)) {
                            // get the number of filtered products and the result
                            result = getProductsFiltered(controller, compareQuantity, valueToFilterBy);
                        }
                        else {
                            printf("The input quantity is invalid.\n");
                        }
                        free(valueToFilterBy);
                    }
                    else if (strcmp(criteria, "limit") == 0) {
						printf("Input the quantity limit.\n");
						valueToFilterBy = getInput();

						// check if the limit is valid
						if (validateQuantity(valueToFilterBy)) {
							// get the number of filtered products and the result
							result = getProductsFiltered(controller, compareLimit, valueToFilterBy);
						}
						else {
							printf("The input limit is invalid.\n");
						}
						free(valueToFilterBy);
					}
                    // display a message if there are no products after the filtering and display the remaining ones otherwise
                    if (result != NULL) {
                        if (result->numberOfItems == 0) {
                            printf("There are no products after the filtering.\n");
                        }
                        else {
                            displayProducts(result);
                        }
                        destroyRepoProduct(result);
                    }
                }
                else {
                    printf("The input criteria is invalid.\n");
                }
                free(criteria);
                break;
            case 6:
                if (doUndo(controller) == false)
                    printf("There is no undo to do.\n");
                break;
            case 7:
                running = false;
                printf("Thank you for using this application.\n");
                break;
            }
            printf("Press ENTER to continue.\n");
            fgets(dummyInput, 100, stdin);

        }
        free(option);
    }
    destroyController(controller);
}

void displayProducts(GenericRepo* repo) {
    printf("+----------+--------------+------------------------+------------------------+---------------+---------------+\n");
    printf("|  %-6s  |  %-10s  |  %-20s  |  %-20s  |  %-11s  |  %-11s  |\n", "Id", "Type", "Manufacturer", "Model", "Price", "Quantity");
    printf("+----------+--------------+------------------------+------------------------+---------------+---------------+\n");
    for (int i = 0; i < repo->numberOfItems; i++) {
        int id = get_product_id(repo->items[i]);
        char* type = get_product_type(repo->items[i]);
        char* manufacturer = get_product_manufacturer(repo->items[i]);
        char* model = get_product_model(repo->items[i]);
        long double price = get_product_price(repo->items[i]);
        int quantity = get_product_quantity(repo->items[i]);
        printf(
			"|  %-6d  |  %-10s  |  %-20s  |  %-20s  |  %-11Lf  |  %-11d  |\n",
			id,
			type,
			manufacturer,
			model,
			price,
			quantity
		);
        printf("+----------+--------------+------------------------+------------------------+---------------+---------------+\n");
    }
    if (repo->numberOfItems == 0) {
        printf("|  %-6s  |  %-10s  |  %-20s  |  %-20s  |  %-11s  |  %-11s  |\n", " ", " ", " ", " ", " ", " ");
        printf("+----------+--------------+------------------------+------------------------+---------------+---------------+\n");

    }
}

/*
 * A function that removes the trailing new line from fgets.
 * Preconditions: string: a pointer to a char array
 * Post-conditions: -
 */
void removeTrailingNewLine(char* string) {
    if (strlen(string) > 0) {
        string[strlen(string) - 1] = '\0';
    }
}

char* getInput() {
    // get the input from the user
    char* input = malloc(sizeof(char) * 20);
    if(input == NULL) {
		return NULL;
	}
    fgets(input, 20, stdin);
    removeTrailingNewLine(input);

    // return a pointer to the input
    return input;
}

