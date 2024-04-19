#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "repos.h"
#include "stdio.h"

/*
 * Instantiates a repository and returns a pointer to it.
 * Preconditions: -
 * Post-conditions: a pointer to an instance of ProductsRepo
 */
GenericRepo* createRepo() {
    // create the repo
    GenericRepo* repo = malloc(sizeof(GenericRepo));
    if(repo == NULL) {
        return NULL;
    }
    // initialize the numberOfProducts
    repo->numberOfItems = 0;
    repo->numberOfItemsAddedFromStart = 0;
    return repo;
}

/*
 * Deallocates the memory that is used by a given instance of the ProductsRepo class.
 * Preconditions: repoToDestroy: a pointer to a ProductsRepo struct
 * Post-conditions: -
 */
void destroyRepoProduct(GenericRepo* repoToDestroy) {
    // destroy the products in the repo
    for (int i = 0; i < repoToDestroy->numberOfItems; i++) {
        destroyProduct(repoToDestroy->items[i]);
    }

    // destroy the pointer to the repo
    if (repoToDestroy->numberOfItems != 0) {
        free(repoToDestroy->items);
    }
    free(repoToDestroy);
}

// Deallocates the memory that is used by a given instance of the GenericRepo struct which store items of Product type.
void destroyContentRepoProduct(GenericRepo* repoToDestroy) {
    // destroy the products in the repo
    for (int i = 0; i < repoToDestroy->numberOfItems; i++) {
        destroyProduct(repoToDestroy->items[i]);
    }
    // destroy the pointer to the repo
    if (repoToDestroy->numberOfItems != 0) {
        free(repoToDestroy->items);
    }
    repoToDestroy->numberOfItems = 0;
    repoToDestroy->numberOfItemsAddedFromStart = 0;
}

// Deallocates the memory that is used by a given instance of the GenericRepo struct which store items of any type using a destroy function.
void destroyRepoGeneric(GenericRepo* repoToDestroy, void(*destroy_function)(GenericRepo*)) {
    // destroy the products in the repo
    for (int i = 0; i < repoToDestroy->numberOfItemsAddedFromStart; i++) {
        destroy_function(repoToDestroy->items[i]);
    }

    // destroy the pointer to the repo
    if (repoToDestroy->numberOfItemsAddedFromStart != 0) {
        free(repoToDestroy->items);
    }
    free(repoToDestroy);
}


/*
 * Attempts to add the received Item in the repo
 * Preconditions: repo - a pointer to an instance of the GenericRepo
 *                      new_item - a pointer to an instance of any type
 *                      getProductId - a pointer to a function that returns the id of a product
 *                      getProductId == NULL if I want to add an Item different from a product
 * Post-conditions: a bool
 */
bool addItemRepo(GenericRepo* repo, void* new_item, int(*getProductId)(Product*)) {
    // check if the product is already in the repo
    if (getProductId != NULL) {
        for (int i = 0; i < repo->numberOfItems; i++) {
            if (getProductId(repo->items[i]) == getProductId(new_item)) {
                return false;
            }
        }
    }
    if (repo->numberOfItems == 0) {
        repo->items = malloc(sizeof(void*)); // void*  ->  void*
    }
    else {
        void** reallocatedProducts = realloc(repo->items, sizeof(void*) * (repo->numberOfItems + 1));
        if (reallocatedProducts == NULL) {
			return false;
		}
        repo->items = reallocatedProducts;
    }

    // add the new product and increase the number of products
    if(repo->items == NULL) {
		return false;
	}
    repo->items[repo->numberOfItems] = new_item;
    repo->numberOfItems += 1;
    repo->numberOfItemsAddedFromStart += 1;
    return true;
}

/*
 * Attempts to update the item
 * Preconditions: repo - a pointer to an instance of the GenericRepo
 *                new_item - a pointer to an instance of any type
 *                getProductId - a pointer to a function that returns the id of a product in case if is what I want to update
 *                getProductId == NULL if I want to update an Item defferent from a product
 * Post-conditions: a boolean
 */
bool updateItemRepo(GenericRepo* repo, void* new_item, int(*getProductId)(Product*)){
    // check if there is a product with the id of productToUpdateId
    int position = -1;
    if(getProductId != NULL) {
		for (int i = 0; i < repo->numberOfItems; i++) {
			if (getProductId(repo->items[i]) == getProductId(new_item)) {
				position = i;
			}
		}
	}

    // if the product is found, update it
    if (position != -1) {
        destroyProduct(repo->items[position]);
        repo -> items[position] = new_item;
        return true;
    }

    // return false a product with the id of productToUpdateId does not exist
    return false;
}

/*
 * Attempts to delete an Item.
 * Preconditions: repo - a pointer to an instance of the GenericRepo
 *                idItemToDelete - a positive integer
 * getProductId - a pointer to a function that returns the id of a product
 * getProductId == NULL if I want to delete an Item different from a product
 * destroyFunction - a pointer to a function that deallocates the memory of a product in case if is what I want to delete
 * Post-conditions: a bool
 */
bool deleteItemRepo(GenericRepo* repo, int idItemToDelete, int(*getProductId)(Product*), void(*destroyFunction)(void*)) {
    // check if there is a product with the id of productToDeleteId
    bool exists = false;
    int position = repo->numberOfItems - 1;
    if(getProductId != NULL)
        for (int i = 0; i < repo->numberOfItems; i++) {
            if (getProductId(repo->items[i]) == idItemToDelete) {
                exists = true;
                position = i;
            }
        }

    if(getProductId == NULL) {
		destroyFunction(repo->items[position]);
        repo->numberOfItems -= 1;
        return true;
	}

    // return false if the product does not exist
    if (!exists && getProductId != NULL) {
        return false;
    }


    // delete the product
    destroyFunction(repo->items[position]);
	for (int i = position; i < repo->numberOfItems - 1; i++) {
		repo->items[i] = repo->items[i + 1];
	}
	repo->numberOfItems -= 1;
	return true;

}

/*
 * Returns a copy of the repo
 * Preconditions: repo: a pointer to an instance of the GenericRepo
 * Post-conditions: a pointer to a copy of the repo
 */
GenericRepo* copie_repo(GenericRepo* repo_curent) {
    GenericRepo *repo_nou = createRepo();
    for (int i = 0; i < repo_curent->numberOfItems; i++) {
        Product* newProduct = malloc(sizeof(Product));
        if (newProduct == NULL)
            exit(EXIT_FAILURE);
        newProduct->id = get_product_id(repo_curent->items[i]);
        newProduct->quantity = get_product_quantity(repo_curent->items[i]);
        newProduct->price = get_product_price(repo_curent->items[i]);

        size_t lengh_type = strlen(get_product_type(repo_curent->items[i]));
        newProduct->type = (char*)malloc(lengh_type + 1);
        if (newProduct->type == NULL)
            exit(EXIT_FAILURE);
        strcpy_s(newProduct->type, lengh_type + 1, get_product_type(repo_curent->items[i]));

        size_t lengh_manufacturer = strlen(get_product_manufacturer(repo_curent->items[i]));
        newProduct->manufacturer = (char*)malloc(lengh_manufacturer + 1);
        if (newProduct->manufacturer == NULL)
            exit(EXIT_FAILURE);
        strcpy_s(newProduct->manufacturer, lengh_manufacturer + 1, get_product_manufacturer(repo_curent->items[i]));

        size_t lengh_model = strlen(get_product_model(repo_curent->items[i]));
        newProduct->model = (char*)malloc(lengh_model + 1);
        if (newProduct->model == NULL)
            exit(EXIT_FAILURE);
        strcpy_s(newProduct->model, lengh_model + 1, get_product_model(repo_curent->items[i]));

        addItemRepo(repo_nou, newProduct, get_product_id);
    }
    return repo_nou;
}

// Return true if the two repos are different
// Return false if the two repos are the same
bool compare_two_repos(GenericRepo* repo1, GenericRepo* repo2) {
	if (repo1->numberOfItems != repo2->numberOfItems) {
		return true;
	}
	for (int i = 0; i < repo1->numberOfItems; i++) {
		if(get_product_id(repo1->items[i]) != get_product_id(repo2->items[i])) {
			return true;
		}
        if (get_product_quantity(repo1->items[i]) != get_product_quantity(repo2->items[i])) {
			return true;
		}
        if (get_product_price(repo1->items[i]) != get_product_price(repo2->items[i])) {
			return true;
		}
		if (strcmp(get_product_type(repo1->items[i]), get_product_type(repo2->items[i])) != 0) {
			return true;
		}
		if (strcmp(get_product_manufacturer(repo1->items[i]), get_product_manufacturer(repo2->items[i])) != 0) {
			return true;
		}
		if (strcmp(get_product_model(repo1->items[i]), get_product_model(repo2->items[i])) != 0) {
			return true;
		}

	}
	return false;
}

//// Return true if the undo was successful
//// Return false if the undo was not successful
//bool doUndoRepo(GenericRepo* repo, GenericRepo* undoList, void(*destroyFunction)(void*)) {
//	if (undoList->numberOfItems == 0) {
//		return false;
//	}
//    GenericRepo* top_of_Stack = copie_repo(undoList->items[undoList->numberOfItems - 1]);
//    if (compare_two_repos(repo, top_of_Stack) == true || undoList->numberOfItems == 1) {
//        destroyFunction(repo);
//        for (int i = 0; i < top_of_Stack->numberOfItems; i++) {
//            addItemRepo(repo, top_of_Stack->items[i], get_product_id);
//        }
//        undoList->numberOfItems -= 1;
//    }
//    else if(compare_two_repos(repo, top_of_Stack) == false && undoList->numberOfItems >= 2) {
//        top_of_Stack = copie_repo(undoList->items[undoList->numberOfItems - 2]);
//        destroyFunction(repo);
//        for(int i = 0; i < top_of_Stack->numberOfItems; i++) {
//			addItemRepo(repo, top_of_Stack->items[i], get_product_id);
//		}
//        undoList->numberOfItems -= 2;
//    }
//    free(top_of_Stack->items);
//    free(top_of_Stack);
//	return true;
//}
