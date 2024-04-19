#include <stdbool.h>
#include "models.h"
#include "repos.h"

#ifndef LAB2_4_CONTROLLERS_H
#define LAB2_4_CONTROLLERS_H
typedef struct {
	GenericRepo* repo;
	GenericRepo* undoList;
} Controller;

Controller* createController();

void destroyController(Controller* srv);

bool addProductController(Controller* srv, int id, char* type, char* manufacturer, char* model,
    char* price, char* quantity);

bool updateProductController(Controller* srv, int id, char* type, char* manufacturer, char* model,
	char* price, char* quantity);

bool deleteProductController(Controller* srv, int productToDeleteId);

GenericRepo* getAvailableProducts(Controller* srv, bool (*compareProducts)(Product*, Product*));

GenericRepo* getProductsFiltered(Controller* srv, bool (*checkProductProperty)(Product*, char*), char* valueToCompareWith);

bool doUndo(Controller* srv);

void testUndo();

#endif //LAB2_4_CONTROLLERS_H

