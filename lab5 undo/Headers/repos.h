#include "models.h"
#include <stdbool.h>

#ifndef LAB2_4_REPOS_H
#define LAB2_4_REPOS_H

typedef struct {
    void** items;
    int numberOfItems;
    int numberOfItemsAddedFromStart;
} GenericRepo;

GenericRepo* createRepo();

void destroyRepoProduct(GenericRepo* repoToDestroy);

void destroyRepoGeneric(GenericRepo* repoToDestroy, void(*destroy_function)(GenericRepo*));

void destroyContentRepoProduct(GenericRepo* repoToDestroy);

bool addItemRepo(GenericRepo* repo, void* new_item, int(*getProductId)(Product*));

bool updateItemRepo(GenericRepo* repo, void* new_item, int(*getProductId)(Product*));

bool deleteItemRepo(GenericRepo* repo, int idItemToDelete, int(*getProductId)(Product*), void(*destroyFunction)(void*));

GenericRepo* copie_repo(GenericRepo* repo_curent);

bool compare_two_repos(GenericRepo* repo1, GenericRepo* repo2);

//bool doUndoRepo(GenericRepo* repo, GenericRepo* undoList, void(*destroyFunction)(void*));

#endif //LAB2_4_REPOS_H
