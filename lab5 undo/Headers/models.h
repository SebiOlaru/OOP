#ifndef LAB2_4_MODELS_H
#define LAB2_4_MODELS_H

typedef struct {
    int id;
    char* type;
    char* manufacturer;
    char* model;
    long double price;
    int quantity;
}Product;

Product* createProduct(int id, char* type, char* manufacturer, char* model, long double price, int quantity);

int get_product_id(Product *product);
char *get_product_type(Product *product);
char *get_product_manufacturer(Product *product);
char *get_product_model(Product *product);
long double get_product_price(Product *product);
int get_product_quantity(Product *product);


void destroyProduct(Product* productToDestroy);

#endif //LAB2_4_MODELS_H
