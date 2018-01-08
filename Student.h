class Student {

 public:
  void setFName(char*); //Sets the student's first name
  char* getFName(); //Returns the student's first name

  void setLName(char*); //Sets the student's last name
  char* getLName(); //Returns the student's last name

  void setID(int); //Sets the student's 6 digit ID number
  int getID(); //Returns the student's 6 digit ID number

  void setGPA(double); //Sets the student's gpa to two decimal places
  double getGPA(); //Returns the student's gpa  to two decimal places

 private:
  char* fname; //Stores the student's first name
  char* lname; //Stores the student's last name
  int id; //Stores the student's 6 digit id number
  double gpa; //Stores the student's gpa

};
