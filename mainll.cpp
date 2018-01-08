#include <iostream>
#include "Node.h"
#include <cstring>
#include <ctype.h>
#include <iomanip>

using namespace std;

//Linked List Student Version
//By Aidan Derocher
//This program takes the first and last name of a student, their id, and their gpa and stores it in the class student
//Each student is inside a node that contains the next node in a series known as a linked list.
//One can add students, print all students, or delete them by id


void add(Node*&);//passes node by reference to add (as it may change head)
void print(Node*); //takes by value node to help print
void deletenode(int, Node*&, Node*, Node*);//passes one node by reference(as head may change)
Node* sort(int, Node*); //passes in an id and node by value
void average(Node*); //passes in node head by value


int main() {

  Node* head = NULL; //head is beginning of linked list
  
  //Setup text
  cout << "Welcome to Student List: Linked List edition" << endl;
  bool run = true; //boolean to keep track whether the list should keep running
  while (run == true) {
    cout << "Please input a command (see commands with HELP)" << endl;
    char input [80];
    cin.getline(input, 80); //takes in user's input
    for (int i = 0; i < strlen(input); i++) {
      input[i] = toupper(input[i]); //Sets all commands to uppercase
    }

    if (strcmp(input, "HELP") == 0) { //if command is help, print all commands
      cout << "Commands:" << endl;
      cout << "ADD" << endl;
      cout << "PRINT" << endl;
      cout << "DELETE" << endl;
      cout << "HELP" << endl;
      cout << "QUIT" << endl;
      cout << "AVERAGE" << endl;
    }
    
    else if (strcmp(input, "ADD") == 0) { //if command is add run add function
      add(head);
    }

    else if (strcmp(input, "PRINT") == 0) { //if command is add run add function
      print(head);
    }
    
    else if (strcmp(input, "QUIT") == 0) { //if command is quit exits loop
      run = false;
    }
    else if (strcmp(input, "AVERAGE") == 0) { //if command is Average mean of gpa
      average(head);
    }
    
    else if (strcmp(input, "DELETE") == 0) { //if command is delete run delete function
      int delid;//holds id for student
      cout << "Please input the id of the student you wish to delete" << endl;
      cin >> delid; //puts input into integer
      cin.ignore(); //ignores the new line(for compatability with .getline
      deletenode(delid, head, head, head); //deletes the node at the id, starts with all 3 nodes being the head
    }

  }

  //Code that cleans up all nodes
  if(head != NULL) { //if their is a list
    bool todel = false; //says not all is deleted
    Node* prior = NULL; //one before current node
    while (todel == false) {//while not all deleted
      Node* temp = head;//the cureent starts as head
      while (temp -> getNext() != NULL) { //if another in list
	prior = temp;//makes prior equivalent to temp
	delete prior;//runs deconstructor and deletes prior
	temp = temp -> getNext();//goes to next in list
      }
      //at end
      delete temp;//deletes pointer 
    }
  }
}
//end
void add(Node*& start) {

  Node* tracker = start; //the node that will be made
  Student* stu = new Student(); //student that will be added to node

  cout << "Please input the first name" << endl;
  char* fname = new char[80]; //pointer for first name
  cin.getline(fname, 80); //makes the pointer point to input
  stu -> setFName(fname); //set student's first name

  cout << "Please input the last name" << endl;
  char* lname = new char[80];//pointer for last name
  cin.getline(lname, 80);// makes pointer point to input
  stu -> setLName(lname); //sets last name


  bool corid = false;//whether id is valid
  int id; //holds id
  while (corid == false) { //if not valid
    cout << "Please input the student id" << endl;
    cin >> id; //puts input into in
    cin.ignore(); //for compat with cin.getline
    if(id > 99999 && id < 1000000) {//if 6 digits
      stu -> setID(id); //sets id
      corid = true;//exits while
    }
    else{
      cout << "Make sure the student id is six digits" << endl;
    }
  }
  
  double gpa;//double to hold gpa
  bool corgpa = false; //if gpa is valid or not
  while (corgpa == false) { //while not valid
    cout << "Input the Gpa" << endl;
    cin >> gpa;//puts input into double
    cin.ignore();
    if (gpa < 6 && gpa > -.001) {//gpa is not - or greater than 6
      stu -> setGPA(gpa);//sets student gpa
      corgpa = true;//valid
    }
    else{
      cout << "Please input a gpa between 0 and 6" << endl;
    }
  }
  
  if (tracker == NULL) {//if no existing list
    start = new Node(); //start is a new node
    start -> setStudent(stu);//student is put into the node
    start -> setNext(NULL);//the next node does not exist
  }
  else {
    Node* infront = sort(id, start);// runs sort to determine which nodethe newe node is directly infront (by id)
    Node* newNode = new Node(); //creates new node
    newNode -> setStudent(stu);//puts student in new node
    if(infront -> getNext() == NULL) { //if the one in front is at end of list
      if(id < infront -> getStudent() -> getID()) {//if the id is less than one infront, infront is actually after
	newNode -> setNext(infront);//puts before infront
	if(infront == start) {//if infront is head
	  start = newNode;//new node becomes head
	}
      }
      else {
	newNode -> setNext(NULL); //otherwise if id is greater
	infront -> setNext(newNode);//put after the existing node
      }
    }
    else{
      if(infront == start && id < infront -> getStudent() -> getID()) {//if next is not null and id is less than infront
	start = newNode;//Newnode is head
	newNode -> setNext(infront);//put at start of list
      }
      else {//somewhere in the middle
	newNode -> setNext(infront -> getNext());//next is one after infront
	infront -> setNext(newNode);//new node is placed after infront
      }
    }
  }
  
}

Node* sort(int id, Node* check) {
  if(check -> getNext() != NULL){
    if(id < check -> getNext() -> getStudent() -> getID()) {
      return check; //will return the node to the last call or to add
    }
    else {
      check = sort(id, check -> getNext()); //runs sort again, when place is found, check is set equal
      return check;//returns check again either to prior sort or add
    }
  }
  else {
    return check;
  }
}

void print(Node* n) { //altered from student list part 1
  if(n != NULL) {//if the current node is not null
    cout << "First Name: " << n -> getStudent() -> getFName() << endl; //print out first name in it's student
    cout << "Last Name: " << n -> getStudent() -> getLName() << endl; //print out last name
    cout << "Id: " << n -> getStudent() -> getID() << endl; //prints id
    cout << "GPA: " << setprecision(3) << n -> getStudent() -> getGPA() << endl; //prints gpa
    cout << endl;
    print(n -> getNext()); //moves to next node in the line and runs print with that
  }
}

void deletenode(int delid, Node*& head, Node* prior, Node* del) {
  //originally has head for both prior and del
  bool found = false;
  if (del != NULL){ //if head is not null and is not end of line (as del will be null)
    if (found == false){ //if the node is not found 
      if (del -> getStudent() -> getID() == delid){//if the node's student's id is the one to be deleted
	found = true;//recognizes the node and prior node as correct
      }
      else{
	deletenode(delid, head, del, del -> getNext()); //recursion with next two in list
      }
    }
  
    if (found == true) {//will be false when returning to past runs in the recursion, so will run off end
      if (prior == del && del -> getNext() != NULL){//when first node has id and there is another node
	head = del -> getNext();//head changes the headin main since it is by reference
	delete del;//del still points to original head, so it is deleted without affecting current head
      }
      else if(prior == del) { //if first but next is null
      delete del;//deletes pointer to node
      head = NULL; //changes actual head
      }
      else {
	if(del -> getNext() == NULL){ //end of list
	  delete del;//deletes the pointer
	  prior -> setNext(NULL);//one before is head
      }
	else{
	  prior -> setNext(del -> getNext());//prior points to the one after the one that will be deleted
	  delete del;//deletes pointer 
	}
      }
    }
  }
  else{ //Either head didn't exist or the id was not in the list
    cout << "The specified Id does not exist" << endl; 
  }
}

void average(Node* start) {//will get average of all nodes
  if (start != NULL) { //if there are nodes
    int count = 0; //counts number of terms
    double gpa = 0; //holds sum of terms
    while(start != NULL) {//while there are still nodes
      gpa += start -> getStudent() -> getGPA();//adds gpa of current node to gpa
      count += 1;//adds one to count
      start = start -> getNext(); //moves to next node
    }
    gpa = gpa / count; //divides sum by number of terms
    cout << "The average GPA is " << setprecision(3) << gpa << endl;//prints gpa to two decimal points 
  }
  else {
    cout << "You need students in order to average their GPA" << endl;
  }
}
