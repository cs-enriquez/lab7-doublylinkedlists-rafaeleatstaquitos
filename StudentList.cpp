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
		if (numStudents == 0)
		{
			head = new Node(s);
			tail = head;
			numStudents++;
		}
		else
		{
			head->next = new Node(s);
			head->next->prev = head;
			head = head->next;
			numStudents++;
		}
	}

	//add a Node with a student to the back (tail) of the list.
	void StudentList::addBack(Student s) {
		if (numStudents == 0)
		{
			tail = new Node(s);
			head = tail;
			numStudents++;
		}
		else
		{
			tail->prev = new Node(s);
			tail->prev->next = tail;
			tail = tail->prev;
			numStudents++;
		}
	}

	//Print out the names of each student in the list.
	void StudentList::printList() {
		for(Node *curr = tail; curr != nullptr; curr = curr->next)
		{
			cout << curr->data.name << " ";
		}
		cout << endl;
	}

	// Remove the Node with the student at the back (tail) of the list
	// should not fail if list is empty! Print an error message if this occurs
	// Don't forget that your head and tail pointers will be null pointers if the list is empty
	void StudentList::popBack() {
		if(numStudents == 0)
		{
			cout << "Nothing to Pop!" << endl;
		}
		else if(numStudents == 1)
		{
			delete tail;
			tail = nullptr;
			head = nullptr;
			numStudents--;
		}
		else
		{
			tail = tail->next;
			delete tail->prev;
			numStudents--;
		}
	}

	// Remove the Node with the student at the front (head) of the list
	// should not fail if list is empty! Print an error message if this occurs
	// Don't forget that your head and tail pointers will be null pointers if the list is empty
	void StudentList::popFront() {
		if(numStudents == 0)
		{
			cout << "Nothing to Pop!" << endl;
		}
		else if(numStudents == 1)
		{
			delete head;
			head = nullptr;
			tail = nullptr;
			numStudents--;
		}
		else
		{
			head = head->prev;
			delete head->next;
			numStudents--;
		}
	}

	//insert a student at the position "index".
	// for this list, count head as index 0
	// if index is outside of current list range, 
	// print a message and insert the student at the back of the list
	// the previous Node at your target index should be moved forward. "For example, Node with student at index i, becomes index i+1" 
	// Remember that you already have methods that can add students to the front or back of list if needed! Don't repeat this code.
	void StudentList::insertStudent(Student s, int index) {
		Node *curr = head;
		if (index >= listSize())
		{
			cout << "Student out of range" << endl;
			addBack(s);
		}
		else
		{
			for(int i = 0; curr != nullptr ; i++)
			{
				if(i == index)
				{
					if(i == 0)
					{
						addFront(s);
					}
					else
					{
						curr->next->prev = new Node(s);
						curr->next->prev->next = curr->next;
						curr->next = curr->next->prev;
						curr->next->prev = curr;
						numStudents++;
					}
				}
				curr = curr->prev;
			}
		}
	}

	//find the student with the given id number and return them
	// if no student matches, print a message 
	// and create and return a dummy student object
	Student StudentList::retrieveStudent(int idNum) {
		for(Node *curr = head; curr != nullptr; curr = curr->prev)
		{
			if(curr->data.id == idNum)
			{
				return curr->data;
			}
		}
		Student dummy;
		return dummy;
	}

	// Remove a Node with a student from the list with a given id number
	// If no student matches, print a message and do nothing
	void StudentList::removeStudentById(int idNum) {
		
		for(Node *curr = head; curr != nullptr; curr = curr->prev)
		{
			if(curr->data.id == idNum)
			{
				if(curr == head)
				{
					head = head->prev;
					delete head->next;
				}
				else if (curr == tail)
				{
					tail = tail->next;
					delete tail->prev;
				}
				else
				{
					curr->prev->next = curr->next;
					curr->next->prev = curr->prev;
					delete curr;
				}
				numStudents--;
			}
		}
	}

	//Change the gpa of the student with given id number to newGPA
	void StudentList::updateGPA(int idNum, float newGPA) {
		for(Node *curr = head; curr != nullptr; curr = curr->prev)
		{
			if(curr->data.id == idNum)
			{
				curr->data.GPA = newGPA;
			}
		}
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
		while (otherList.numStudents != 0) 
		{
			addBack(otherList.head->data);
			otherList.popFront();
		}
	}

	//create a StudentList of students whose gpa is at least minGPA.
	//Return this list.  The original (current) list should
	//not be modified (do not remove the students from the original list).
	StudentList StudentList::honorRoll(float minGPA) {
		StudentList honorList;
		Node *temp = head;
		while (temp) 
		{
			if (temp->data.GPA >= minGPA) {
				honorList.addBack(temp->data);
			}
			temp = temp->prev;
		}
		return honorList;
	}
