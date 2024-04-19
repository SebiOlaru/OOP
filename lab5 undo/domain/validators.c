#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "validators.h"

/*
 * Checks if the received id is valid.
 * Preconditions: id: a pointer to a char
 * Post-conditions: a boolean
 */
bool validateId(char* id) {
    // check if the string is not an empty string
    if (strlen(id) == 0) {
        return false;
    }
    // check if the array contains only numbers
    for (unsigned int i = 0; i < strlen(id); i++) {
        if (!('0' <= id[i] && id[i] <= '9')) {
            return false;
        }
    }

    return true;
}

/*
 * Checks if the received type is valid
 * Preconditions: type: a pointer to a char
 * Post-conditions: a boolean
 */
bool validateType(char* type) {
    // check if the type is one of the following: Fridge, Computer, Laptop
    if (!(strcmp(type, "Fridge") == 0 || strcmp(type, "Computer") == 0 || strcmp(type, "Laptop") == 0)) {
        return false;
    }

    return true;
}

/*
 * Checks if the received manufacturer is valid
 * Preconditions: manufacturer: a pointer to a char
 * Post-conditions: a boolean
 */
bool validateManufacturer(char* manufacturer) {
    // check if the manufacturer is not an empty string
    if (strlen(manufacturer) == 0) {
        return false;
    }

    // check if the manufacturer is made only of letters and numbers
    for (unsigned int i = 0; i < strlen(manufacturer); i++) {
        if (!(
            ('0' <= manufacturer[i] && manufacturer[i] <= '9') ||
            ('a' <= manufacturer[i] && manufacturer[i] <= 'z') ||
            ('A' <= manufacturer[i] && manufacturer[i] <= 'Z')
            )) {
            return false;
        }
    }

    return true;
}

/*
 * Checks if the received model is valid
 * Preconditions: a pointer to a char
 * Post-conditions: a boolean
 */
bool validateModel(char* model) {
    // check if the string is not an empty string
    if (strlen(model) == 0) {
        return false;
    }

    // check if the model is made only of numbers and letters
    for (unsigned int i = 0; i < strlen(model); i++) {
        if (!(
            ('0' <= model[i] && model[i] <= '9') ||
            ('a' <= model[i] && model[i] <= 'z') ||
            ('A' <= model[i] && model[i] <= 'Z')
            )) {
            return false;
        }
    }

    return true;
}

/*
 * Checks if the received price is valid
 * Preconditions: price: a pointer to a char
 * Post-conditions: a boolean
 */
bool validatePrice(char* price) {
    // check if the string is not an empty string
    if (strlen(price) == 0) {
        return false;
    }
    // check if the string is only made of numbers and no more than one '.'
    int dotCounter = 0;
    for (unsigned int i = 0; i < strlen(price); i++) {
        if (price[i] == '.') {
            dotCounter++;
        }
        else
            if (!('0' <= price[i] && price[i] <= '9')) {
                return false;
            }
    }
    if (dotCounter > 1) {
        return false;
    }

    return true;
}

/*
 * Checks if the received quantity is valid
 * Preconditions: quantity: a pointer to a char
 * Post-conditions: a boolean
 */
bool validateQuantity(char* quantity) {
    // check if the string is not an empty string
    if (strlen(quantity) == 0) {
        return false;
    }

    // check if the string is only made of numbers
    for (unsigned int i = 0; i < strlen(quantity); i++) {
        if (!('0' <= quantity[i] && quantity[i] <= '9')) {
            return false;
        }
    }

    return true;
}

/*
 * Checks if the received option is valid.
 * Preconditions: option: a pointer to a char
 * Post-conditions: a boolean
 */
bool validateOption(char* option) {
    // check if the string is an empty string
    if (strlen(option) == 0) {
        return false;
    }

    // check if the string is only made of numbers
    for (unsigned int i = 0; i < strlen(option); i++) {
        if (!('0' <= option[i] && option[i] <= '9')) {
            return false;
        }
    }

    // check if the option is between 1 and 6
    if (!(1 <= atoi(option) && atoi(option) <= 7)) {
        return false;
    }

    return true;
}