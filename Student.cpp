#include "Student.h"
#include <cstring> //For strcpy

void Student :: setFName(char* newFName) { //Sets student's first name
  fname = new char[80];//Makes fname new pointer to char array of 80
  strcpy(fname, newFName); //copies the passed first name into fname
}

char* Student :: getFName() { //Returns student's first name
  return fname;
}

void Student :: setLName(char* newLName) { //Sets student's last name
  lname = new char[80];//Makes lname new pointer to char array of 80
  strcpy(lname, newLName); //copies the passed last name into fname
}

char* Student :: getLName() { //Returns student's last name
  return lname;
}

void Student :: setID(int newID) { //Sets the student's ID
  id = newID;//Sets id the same as the passed value
}

int Student :: getID() { //Returns the student's ID
  return id;
}

void Student :: setGPA(double newGPA) { //Sets the student's gpa
  gpa = newGPA;//Sets the gpa to equal the passed value
}

double Student :: getGPA() { //Returns gpas
  return gpa;
}
