#include "Registration.h"

//Overloaded constructor
Registration::Registration(string studentName, int cap) {
  cout << "Registration Constructor: Capacity=" << cap << endl;
  m_name = studentName;
  m_capacity = cap;
  m_used = 0;
  m_subjectArray = new string[cap];
}

//Implement Copy Constructor Here
Registration::Registration(const Registration& source):
  m_name(source.m_name) , m_capacity(source.m_capacity) , m_used(source.m_used){
  
  cout << "Copy Constructor: Capacity = " << m_capacity << endl;
  m_subjectArray = new string[m_capacity];

  for(int i = 0; i < m_capacity; i++){
    m_subjectArray[i] = source.m_subjectArray[i];
  }
}

//Implement Overloaded Assignment Operator Here
Registration& Registration::operator=(const Registration& source){
  // if registration is same
  if(this == &source)
    return *this;

  m_name = source.m_name;
  m_capacity = (source.m_capacity);
  m_used = (source.m_used);

  cout << "Overloaded Assignment: Capacity = " << m_capacity << endl;

  for(int i = 0; i < m_capacity; i++){
    m_subjectArray[i] = source.m_subjectArray[i];
  }

  return *this;
}

//Implement Destructor Here
Registration::~Registration(){
  cout << "Destructor called for " << m_name << " at this memory location: " << m_subjectArray << endl;
  delete[] m_subjectArray;
  m_subjectArray = NULL;
  
}

//Inserting a new subject into our subject array
void Registration::insert(const string& subjectName) {
  if(m_used == m_capacity) {
    cout<<"Subject array is full. Cannot add any additional subjects."<<endl;
  }
  else  {
    m_subjectArray[m_used] = subjectName;
    m_used++;
    cout << "Subject:" << subjectName << " added to registration." << endl;
  }
}

ostream& operator <<(ostream& os, const Registration& rg) {
  os << rg.m_name << " has selected the following subjects:" << endl << " | ";  
  for(int i=0;i<rg.m_used; i++) {
    os <<rg.m_subjectArray[i] + " | ";
  }
  return os << endl;
}
