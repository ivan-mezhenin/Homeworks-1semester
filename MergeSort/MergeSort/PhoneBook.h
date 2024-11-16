#pragma once
#include <stdbool.h>

typedef struct PhoneBook PhoneBook;

typedef struct PhoneBookELement PhoneBookELement;

//return new list
PhoneBook* createPhoneBook(int* errorCode);

//checking empty list or not
bool isPhoneBookEmpty(PhoneBook* phoneBook, int* errorCode);

//return last element of list
PhoneBookElement* lastPhoneBookElement(PhoneBook* phonebook, int* errorCode);

//add new element in list
void addNewPhoneBookElement(PhoneBook* phoneBook, const char* name, const char* number, int* errorCode);

//print all elements of list
void printPhoneBook(PhoneBook* phoneBook);

//clear memory of list
void deletePhonebook(PhoneBook* phonebook);

//compare list elemens using parameter
int comparisonPhoneBookElements(PhoneBookElement* left, PhoneBookElement* right, const int parameter);

//merge two lists in one
void merge(PhoneBook* phoneBook, int leftBorderIndex, int middleIndex, int rightBorderIndex, const int parameter);

//sort elements in list
void mergeSort(PhoneBook* phoneBook, int leftIndex, int rightIndex, int parameter);