	#include "StudentList.h"

	// Define a constructor to initialize the list. The list starts with no Students
    StudentList::StudentList() {
		head = nullptr;
		tail = nullptr;
		numStudents = 0;
	}

	// return the number of students currently in the list
	int StudentList::listSize() {
		return numStudents;
	}

	//add a Node with a student to the front (head) of the list.
	void StudentList::addFront(Student s) {
		Node *newNode = new Node(s);
		
		if (head == nullptr) {
			// List is empty
			head = newNode;
			tail = newNode;
		} else {
			// List has at least one node
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
		}
		numStudents++;
	}

	//add a Node with a student to the back (tail) of the list.
	void StudentList::addBack(Student s) {
		Node *newNode = new Node(s);
		
		if (tail == nullptr) {
			// List is empty
			head = newNode;
			tail = newNode;
		} else {
			// List has at least one node
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
		numStudents++;
	}

	//Print out the names of each student in the list.
	void StudentList::printList() {
		if (head == nullptr) {
			cout << "List is empty" << endl;
			return;
		}
		
		Node *current = head;
		cout << "Student List: ";
		while (current != nullptr) {
			cout << current->data.name << " ";
			current = current->next;
		}
		cout << endl;
	}

	// Remove the Node with the student at the back (tail) of the list
	// should not fail if list is empty! Print an error message if this occurs
	// Don't forget that your head and tail pointers will be null pointers if the list is empty
	void StudentList::popBack() {
		if (tail == nullptr) {
			cout << "Error: Cannot remove from empty list" << endl;
			return;
		}
		
		if (head == tail) {
			// Only one node in the list
			delete tail;
			head = nullptr;
			tail = nullptr;
		} else {
			// Multiple nodes in the list
			Node *temp = tail;
			tail = tail->prev;
			tail->next = nullptr;
			delete temp;
		}
		numStudents--;
	}

	// Remove the Node with the student at the front (head) of the list
	// should not fail if list is empty! Print an error message if this occurs
	// Don't forget that your head and tail pointers will be null pointers if the list is empty
	void StudentList::popFront() {
		if (head == nullptr) {
			cout << "Error: Cannot remove from empty list" << endl;
			return;
		}
		
		if (head == tail) {
			// Only one node in the list
			delete head;
			head = nullptr;
			tail = nullptr;
		} else {
			// Multiple nodes in the list
			Node *temp = head;
			head = head->next;
			head->prev = nullptr;
			delete temp;
		}
		numStudents--;
	}

	//insert a student at the position "index".
	// for this list, count head as index 0
	// if index is outside of current list range, 
	// print a message and insert the student at the back of the list
	// the previous Node at your target index should be moved forward. "For exampe, Node with student at index i, becomes index i+1" 
	// Remember that you already have methods that can add students to the front or back of list if needed! Don't repeat this code.
	void StudentList::insertStudent(Student s, int index) {
		if (index < 0 || index > numStudents) {
			cout << "Index out of range, inserting at back" << endl;
			addBack(s);
			return;
		}
		
		if (index == 0) {
			addFront(s);
			return;
		}
		
		if (index == numStudents) {
			addBack(s);
			return;
		}
		
		// Find the node at the target index
		Node *current = head;
		for (int i = 0; i < index; i++) {
			current = current->next;
		}
		
		// Create new node and insert it before current
		Node *newNode = new Node(s);
		newNode->next = current;
		newNode->prev = current->prev;
		current->prev->next = newNode;
		current->prev = newNode;
		numStudents++;
	}

	//find the student with the given id number and return them
	// if no student matches, print a message 
	// and create and return a dummy student object
	Student StudentList::retrieveStudent(int idNum) {
		Node *current = head;
		while (current != nullptr) {
			if (current->data.id == idNum) {
				return current->data;
			}
			current = current->next;
		}
		
		cout << "Student with ID " << idNum << " not found" << endl;
		Student dummy;
		return dummy;
	}

	// Remove a Node with a student from the list with a given id number
	// If no student matches, print a message and do nothing
	void StudentList::removeStudentById(int idNum) {
		Node *current = head;
		while (current != nullptr) {
			if (current->data.id == idNum) {
				// Found the student, now remove the node
				if (current == head && current == tail) {
					// Only one node
					delete current;
					head = nullptr;
					tail = nullptr;
				} else if (current == head) {
					// Remove from front
					head = head->next;
					head->prev = nullptr;
					delete current;
				} else if (current == tail) {
					// Remove from back
					tail = tail->prev;
					tail->next = nullptr;
					delete current;
				} else {
					// Remove from middle
					current->prev->next = current->next;
					current->next->prev = current->prev;
					delete current;
				}
				numStudents--;
				return;
			}
			current = current->next;
		}
		
		cout << "Student with ID " << idNum << " not found" << endl;
	}

	//Change the gpa of the student with given id number to newGPA
	void StudentList::updateGPA(int idNum, float newGPA) {
		Node *current = head;
		while (current != nullptr) {
			if (current->data.id == idNum) {
				current->data.GPA = newGPA;
				return;
			}
			current = current->next;
		}
		
		cout << "Student with ID " << idNum << " not found" << endl;
	}

	//Add all students from otherList to this list.
	//otherlist should be empty after this operation.
	/*
	For example, if the list has 3 students:
	s1 <-> s2 <-> s3
	and otherList has 2 students
	s4 <-> s5
	then after mergeList the currently list should have all 5 students
	s1 <-> s2 <-> s3 <-> s4 <-> s5
	and otherList should be empty and have zero students.
	*/
	void StudentList::mergeList(StudentList &otherList) {
		if (otherList.head == nullptr) {
			// Other list is empty, nothing to merge
			return;
		}
		
		if (this->tail == nullptr) {
			// This list is empty, just adopt the other list
			this->head = otherList.head;
			this->tail = otherList.tail;
			this->numStudents = otherList.numStudents;
		} else {
			// Connect the tail of this list to the head of otherList
			this->tail->next = otherList.head;
			otherList.head->prev = this->tail;
			this->tail = otherList.tail;
			this->numStudents += otherList.numStudents;
		}
		
		// Clear otherList
		otherList.head = nullptr;
		otherList.tail = nullptr;
		otherList.numStudents = 0;
	}

	//create a StudentList of students whose gpa is at least minGPA.
	//Return this list.  The original (current) list should
	//not be modified (do not remove the students from the original list).
	StudentList StudentList::honorRoll(float minGPA) {
		StudentList honorList;
		Node *current = head;
		
		while (current != nullptr) {
			if (current->data.GPA >= minGPA) {
				honorList.addBack(current->data);
			}
			current = current->next;
		}
		
		return honorList;
	}

	//remove all students whose GPA is below a given threshold.
	// For example, if threshold = 3.0, all students with GPA less than 3.0
	// should be removed from the list. 
	// Be sure to correctly update both head and tail pointers when removing 
	// from the front or back, and adjust numStudents accordingly.
	// If the list is empty, print a message and do nothing.
	void StudentList::removeBelowGPA(float threshold) {
		if (head == nullptr) {
			cout << "Error: List is empty" << endl;
			return;
		}
		
		Node *current = head;
		while (current != nullptr) {
			if (current->data.GPA < threshold) {
				Node *toDelete = current;
				
				if (current == head && current == tail) {
					// Only one node
					head = nullptr;
					tail = nullptr;
					current = nullptr;
				} else if (current == head) {
					// Remove from front
					head = head->next;
					head->prev = nullptr;
					current = current->next;
				} else if (current == tail) {
					// Remove from back
					tail = tail->prev;
					tail->next = nullptr;
					current = nullptr;
				} else {
					// Remove from middle
					current->prev->next = current->next;
					current->next->prev = current->prev;
					current = current->next;
				}
				delete toDelete;
				numStudents--;
			} else {
				current = current->next;
			}
		}
	}
