/**
	@file datastore.c
	@author Michelle Van Enige <mave3@gatech.edu> 727-433-2927
	@brief This file facilitates data storage across multiple threads.
	@details This file uses linked lists in order to store data values of type node with an identifier
	@warning
	@note
	@todo finish get functions
	@todo test data storage
	@ingroup Common
	@addtogroup dataStore Data Store
	@brief Data storage, in a linked list.
	@{
*/
#include "datastore.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
	@var listHead Pointer to the first element in the linked list.
*/
static node* listHead;

/**
	@author Michelle Van Enige <mave3@gatech.edu> 727-433-2927
	@brief This function creates a node with a specified name and data.
	@param name character array holding the name of the new node
	@param data contains data to put in new node
	@return pointer to new node
	@retval NULL this functions returns NULL if the name is NULL
	@warning this function may return NULL
*/
node* createIntNode(char* name, int data){
	if (name == NULL){
		return NULL;
	}
	node* newNode;
	newNode = malloc(sizeof(node));
	newNode->dataInt = data;
	strcpy(newNode->name, name);
	return newNode;
	}
/**
	@override
*/
node* createStringNode(char* name, char* data){
	if (name == NULL){
		return NULL;
	}
	node* newNode;
	newNode = malloc(sizeof(node));
	strcpy (newNode->dataString, data);
	strcpy (newNode->name, name);
	return newNode;
	}
/**
	@override
*/
node* createFloatNode(char* name, float data){
	if (name==NULL){
		return NULL;
	}
	node* newNode;
	newNode = malloc(sizeof(node));
	newNode->dataFloat = data;
	strcpy (newNode->name, name);
	return newNode;
}
/**
	@override
*/
node* createDoubleNode(char* name, double data){
	if (name == NULL){
		return NULL;
	}
	node* newNode;
	newNode = malloc(sizeof(node));
	newNode->dataDouble = data;
	strcpy(newNode->name, name);
	return newNode;
}

/**
	@author Michelle Van Enige <mave3@gatech.edu> 727-433-2927
	@brief This function sets the values of the specified node.
	@details This function checks to see if a node with the specified name already exists. If not, it creates it.
	@param name character array holding the name of the new node
	@param data contains data to put in new node
	@return returns an int greater than 0 if the function is successful
	@retval 1 successful
*/
int setInt(char* name, int data){
	if(listHead == NULL){
		node* newNode = createIntNode(name, data);
		listHead = newNode;
	}else{
		node* newNode = listHead;
		while(!strcmp(name, newNode->name)){
			if(newNode->next != NULL){
				newNode = newNode->next;
			}
			else{
				newNode->next = createIntNode(name, data);
				return 1;
			}
		}
		newNode->dataInt = data;
	}
	return 1;
}
/**
	@override
*/
int setFloat(char* name, float data){
	if(listHead == NULL){
		node* newNode = createFloatNode(name, data);
		listHead = newNode;
	}else{
		node* newNode = listHead;
		while(!strcmp(name, newNode->name)){
			if(newNode->next != NULL){
				newNode = newNode->next;
			}
			else{
				newNode->next = createFloatNode(name, data);
				return 1;
			}
		}
		newNode->dataFloat = data;
	}
	return 1;
}
/**
	@override
*/
int setDouble(char* name, double data){
	if(listHead == NULL){
		node* newNode = createDoubleNode(name, data);
		listHead = newNode;
	}
	else{
		node* newNode = listHead;
		while(!strcmp(name, newNode->name)){
			if(newNode->next != NULL){
				newNode=newNode->next;
			}
			else{
				newNode->next = createDoubleNode(name, data);
				return 1;
			}
		}
		newNode->dataDouble = data;
	}
	return 1;
}
/**
	@override
*/
int setString(char* name, char* data){
	if(listHead == NULL){
		node* newNode = createStringNode(name, data);
		listHead = newNode;
	}
	else{
		node* newNode = listHead;
		while(!strcmp(name, newNode->name)){
			if(newNode->next != NULL){
				newNode = newNode->next;
			}
			else{
				newNode->next = createStringNode(name,data);
				return 1;
			}
		}
		strcpy(newNode->dataString, data);
	}
	return 1;
}
/**
	@author Reid Kersey	<reidkersey@gmail.com> 678-736-0899
	@brief This gets the data of a specified type, using the given name.
	@details This function checks to see if a node with the specified name already exists. If it does, then it returns the value, if not it returns -2000000000 (or NULL, or character arrays)
	@param name character array holding the name of requested node.
	@return returns the value of the requested data
	@warning This function returns -20000000000 if the data can not be found.
	@warning this function may return NULL
	@todo figure out better way than returning -2000000000 if the data can not be found. perror maybe?
	@retval -2000000000 The name does not exist.
	@retval NULL The name does not exist.
	
*/
int getInt(char* name){
	if(listHead == NULL){
		return -999;
	}
	else{
		node* newNode = listHead;
		while(!strcmp(name, newNode->name)){
			if(newNode->next != NULL){
				newNode = newNode->next;
			}
			else{
				return -999;
			}
		}
		return newNode->dataInt;
	}
}
/**
	@override
*/
float getFloat(char* name){
	if(listHead == NULL){
		return -2000000000;
	}
	else{
		node* newNode = listHead;
		while(!strcmp(name, newNode->name)){
			if(newNode->next != NULL){
				newNode = newNode->next;
			}
			else{
				return -2000000000;
			}
		}
		return newNode->dataFloat;
	}
}
/**
	@override
*/
double getDouble(char*name){
	if(listHead == NULL){
		return -2000000000;
	}
	else{
		node* newNode = listHead;
		while(!strcmp(name, newNode->name)){
			if(newNode->next != NULL){
				newNode = newNode->next;
			}
			else{
				return -2000000000;
			}
		}
		return newNode->dataDouble;
	}
}
/**
	@override
*/
char* getString(char* name){
	if(listHead == NULL){
		return NULL;
	}
	else{
		node* newNode = listHead;
		while(!strcmp(name, newNode->name)){
			if(newNode->next != NULL){
				newNode = newNode->next;
			}
			else{
				return NULL;
			}
		}
		return newNode->dataString;
	}
}
