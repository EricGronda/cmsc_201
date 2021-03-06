/**************************************************************
 * File:    Train.cpp
 * Author:  Eric Gronda
 * Project: CMSC 202 PROJ3, SP 18
 * Date:    4/10/18
 * E-mail:  eric.gronda@umbc.edu
 * Description:
 *   Contains all the function definitions for the Train class
 *************************************************************/
#include "Train.h"

const int START_LENGTH = 0;

const string BIO = "BIO";     // strings used in Train::display()
const string RAD = "RAD";
const string POI = "POI";
const string OXI = "OXI";
const string COM = "COM";
const string LOC = "ENGINE";
const string CAB = "CABOOSE";

// Name: Train (Default Constructor)
// PreCondition:  none
// PostCondition: instantiates a default-constructed Train object
Train::Train(){
  m_len    = START_LENGTH; // every trains starts with an engine
  m_number = NULL;
  m_head   = NULL; //***CAUSES SEG FAULT***
}

// Name: Train (Overloaded Constructor)
// PreCondition:  none
// PostCondition: instantiates a Train object with a given number
Train::Train(int number){
  m_len    = START_LENGTH;
  m_number = number;
  m_head   = NULL;
}

// Name: ~Train
// PreCondition:  none
// PostCondition: destroys train object
Train::~Train(){
  // delete all cars
  while(m_head != NULL){
    removeCar(m_len - 1);
  }
  
  delete m_head;
  m_head = NULL;
}

// Name: display
// PreCondition:  given ostream& is valid
// PostCondition: appends own train information to a given ostream&
void Train::display(ostream& output) const{
  Car* temp = m_head; // create a temporary pointer
  string cargoType;

  while(temp != NULL){ // loop until the pointer value is null

    //convert cargo to string
    if(temp->getCargo() == BIOLOGICAL)
      cargoType = BIO;
    else if(temp->getCargo() == RADIOACTIVE)
      cargoType = RAD;
    else if(temp->getCargo() == POISONOUS)
      cargoType = POI;
    else if(temp->getCargo() == OXIDIZER)
      cargoType = OXI;
    else if(temp->getCargo() == COMBUSTIBLE)
      cargoType = COM;
    else if(temp->getCargo() == LOCOMOTIVE)
      cargoType = LOC;
    else if(temp->getCargo() == CABOOSE)
      cargoType = CAB;

    // display last car
    if(temp->getNext() == NULL){
      output << cargoType;
      
      // check for valid train
      if( isValid() )
	output << " (valid)" << endl;      
      else
	output << " (invalid)" << endl;
    }

    // display other cars
    else
      output << cargoType << "->";

    temp = temp->getNext();
  }
  
}

// Name: isValid
// PreCondition:  none
// PostCondition: returns a boolean indicating whether the current
//                arrangement of the train is valid
bool Train::isValid() const{
  Car* temp = m_head;
  bool valid = true;

  // loop through train
  while(temp != NULL){
    
    // OXIDIZER not next to COMBUSTIBLE
    if(temp->getCargo() == OXIDIZER && 
       ( temp->getNext() )->getCargo() == COMBUSTIBLE){  
      valid = false;
    }
    
    else if(temp->getCargo() == COMBUSTIBLE &&
	    ( temp->getNext() )->getCargo() == OXIDIZER){
      valid = false;   
    }

    // 3 COMBUSTIBLE in a row
    if(temp->getCargo() == COMBUSTIBLE && 
       temp->getCargo() == ( temp->getNext() )->getCargo() &&
       temp->getCargo() == ( temp->getNext()->getNext() )->getCargo() ){
      valid = false;
    }

    // 5 BIOLOGICAL in a row
    if(temp->getCargo() == BIOLOGICAL && 
       temp->getCargo() == ( temp->getNext() )->getCargo() &&
       temp->getCargo() == ( temp->getNext()->getNext() )->getCargo() &&
       temp->getCargo() == ( temp->getNext()->getNext()->getNext() )
                               ->getCargo() &&
       temp->getCargo() == ( temp->getNext()->getNext()->getNext()
			     ->getNext() )->getCargo()            ){
      valid = false;
    }

    // RADIOACTIVE->BIOLOGICAL->RADIOACTIVE
    if(temp->getCargo() == RADIOACTIVE &&
       ( temp->getNext() )->getCargo() == BIOLOGICAL &&
       ( temp->getNext()->getNext() )->getCargo() == RADIOACTIVE ){
      valid = false;
    }

    temp = temp->getNext();
  }
  
  return valid;
}

// Name: addCar
// PreCondition:  given CARGO_TYPE is valid, given integer is a valid
//                index (where to insert in train)
// PostCondition: adds car to the train, at given index. zero-indexed
int Train::addCar(const CARGO_TYPE& cargo, int index){
  Car *newCar = new Car(cargo);
  Car *cur = m_head;
  Car *prev;

  // head case
  if(index == START_LENGTH){
    
    // list is empty
    if(m_head == NULL){
      m_head = newCar;
      m_head->setNext( NULL );
    }
    
    // list is not empty
    else{
      m_head = newCar;
      m_head->setNext(cur);
    }
    
  }
  
  // between head and end
  else if(index > START_LENGTH && index <= m_len){ 
    
    // loop to index
    for(int i = START_LENGTH; i < index; i++){
      prev = cur;
      cur = cur->getNext();
    }

    // assign car
    prev->setNext( newCar );
    newCar->setNext( cur );

  }

  // end
  else{
    cout << "Position out of range." << endl;
    return 0;
  }

  m_len++;
  return 0;
}

// Name: removeCar
// PreCondition:  given integer is a valid index
// PostCondition: removes Car from train at given index. zero-indexed
int Train::removeCar(int index){
  Car *cur = m_head;
  Car *prev;
  
  // empty list
  if(m_head == NULL){
    cout << "List is empty" << endl;
  }

  // remove at front
  else if(index == START_LENGTH){
    m_head = cur->getNext();    
  }

  // remove anywhere else
  else{
    
    // index within range
    if(index > START_LENGTH && index < m_len){
      
      // loop to index
      for(int i = START_LENGTH; i < index; i++){
	prev = cur;
	cur = cur->getNext();
      }

      // index at end
      if(index == m_len - 1) 
	prev->setNext( NULL );

      // index anywhere else
      else 
	prev->setNext( cur->getNext() );
  
    }

    // index out of range
    else{
      cout << "Position out of range." << endl;
      return 0;
    }

  }

  // postconditions
  m_len--;
  delete cur; // double deleting??
  prev = NULL;
  cur = NULL;
  return 0;
}

// Name: removeCar
// PreCondition:  given CARGO_TYPE is valid
// PostCondition: removes every car of given cargo_type from train.
int Train::removeCar(CARGO_TYPE cargo){
  Car *temp = m_head;
  int index = 0;
  
  while(temp != NULL){
    
    // cargo is at index
    if(temp->getCargo() == cargo)
      removeCar(index);

    // cargo is not at index; move on
    else
      index++;

    // update values
    temp = temp->getNext();
  }

  return 0;
}

// Name: getLength
// PreCondition:  none
// PostCondition: returns current length of the train
int Train::getLength() const{
  return m_len;
}

// Name: getNumber
// PreCondition:  none
// PostCondition: returns current number of the train (The number is the name of the train)
int Train::getNumber() const{
  return m_number;
}

// Name: setNumber
// PreCondition:  none
// PostCondition: sets a new number for the train
void Train::setNumber(int number){
  m_number = number;
}

// Name: operator<<
// PreCondition:  given arguments are valid
// PostCondition: appends train information to ostream&
// This function just calls the display function and allows us to cout << myTrain
std::ostream &operator<<(std::ostream& output, const Train& train){
  train.display(output);
  return output;
}
