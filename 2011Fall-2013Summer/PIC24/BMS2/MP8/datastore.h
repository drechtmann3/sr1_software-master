#ifndef DATASTORE_H
#define DATASTORE_H

typedef struct node_t{
int dataInt;
double dataDouble;
float dataFloat;
char dataString[1000];
char name[50];
struct node_t *next;
}node;



node* createIntNode(char* name, int data);
node* createStringNode(char* name, char* data);
node* createFloatNode(char* name, float data);
node* createDoubleNode(char* name, double data);


int setInt(char* name, int data);
int setFloat(char* name, float data);
int setDouble(char* name, double data);
int setString(char* name, char* data);
int getInt(char* name);
float getFloat(char* name);
double getDouble(char*name);
char* getString(char* name);


#endif