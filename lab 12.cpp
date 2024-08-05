#include <iostream>

using namespace std;

class Student 
{

private:
	double cgpa;
	int rollno;

public:

	Student()
	{
		this->cgpa = 0.0;
		this->rollno = 0;
	}

	Student(double cgpa, int rollno)
	{
		this->cgpa = cgpa;
		this->rollno = rollno;
	}

	friend class StudentmaxHeap;

};

class StudentmaxHeap 
{
private:
	Student* arr;
	int currSize;
	int maxSize;


	int parent(int i)
	{
		return (i - 1) / 2;
	}

	int left(int i) 
	{
		return (i * 2 + 1);
	}

	int right(int i) 
	{
		return (i * 2 + 2);
	}

	void maxHeapify(int index)
	{
		int largest = index;
		int l = left(index);
		int r = right(index);

		if (l < currSize && (arr[l].cgpa > arr[largest].cgpa || (arr[l].cgpa == arr[largest].cgpa && arr[l].rollno < arr[largest].rollno))) {
			largest = l;
		}

		if (r < currSize && (arr[r].cgpa > arr[largest].cgpa || (arr[r].cgpa == arr[largest].cgpa && arr[r].rollno < arr[largest].rollno))) {
			largest = r;
		}

		if (largest != index) 
		{
			swap(arr[largest], arr[index]);
			maxHeapify(largest);
		}

	}

	void buildMaxHeap()
	{
		for (int i = (currSize / 2) - 1; i >= 0; i--)
		{
			maxHeapify(i);
		}
	}


public:
	StudentmaxHeap(int size) 
	{
		currSize = 0;
		maxSize = size;
		arr = new Student[maxSize];
	}

	~StudentmaxHeap()
	{
		delete[] arr;
	}

	bool isEmpty()
	{
		return (currSize == 0);
	}

	bool isFull() 
	{
		return (currSize == maxSize);
	}

	bool insert(double cgpa, int rollno) 
	{
		if (isFull()) 
		{
			return false;
		}

		//insert new student
		arr[currSize] = Student(cgpa, rollno);

		//mainatining heap
		int newPosition = currSize;

		while ((newPosition != 0) && (arr[newPosition].cgpa > arr[parent(newPosition)].cgpa || (arr[newPosition].cgpa == arr[parent(newPosition)].cgpa && arr[newPosition].rollno < arr[parent(newPosition)].rollno))) {
			swap(arr[newPosition], arr[parent(newPosition)]);
			newPosition = parent(newPosition);
		}
		currSize++;
		return true;
	}

	bool remove(double& cgpa, int& rollno) 
	{
		if (isEmpty())
		{
			return false;
		}

		//root ki info store karen
		rollno = arr[0].rollno;
		cgpa = arr[0].cgpa;

		//root ko last element se replace kar den
		arr[0] = arr[--currSize];

		//heap ko maintain karen
		maxHeapify(0);

		return true;
	}

	void displayStudentList()
	{
		for (int i = 0; i < currSize; i++) 
		{
			cout << "ROLLNO: " << arr[i].rollno << endl;
			cout << "CGPA: " << arr[i].cgpa << endl;
		}
		cout << endl << endl;
	}

	void levelOrder() 
	{
		for (int i = 0; i < currSize; ++i) 
		{
			cout << "ROLLNO: " << arr[i].rollno << ", CGPA: " << arr[i].cgpa << " ";
		}
		cout << endl;
	}

};

int main() 
{
	int maxSize;
	cout << "ENTER MAX STUDENTS: ";
	cin >> maxSize;

	StudentmaxHeap maxHeap(maxSize);

	int choice;
	do 
	{
		cout << "\n1. Insert a new student\n"
			<< "2. Remove (and display) the student with the Max CGPA\n"
			<< "3. Display the list of students (Descending order of CGPA)\n"
			<< "4. Display the list of students (Level-order traversal)\n"
			<< "5. Exit\n"
			<< "Enter your choice: ";
		cin >> choice;

		if (choice == 1)
		{
			int rollNo;
			double cgpa;
			cout << "ENTER ROLLNO AND CGPA: ";
			cin >> rollNo >> cgpa;
			if (maxHeap.insert(rollNo, cgpa))
			{
				cout << "STUDENT INSERTED." << endl;
			}
			else 
			{
				cout << "STUDENT NOT INSERTED" << endl;
			}
		}
		else if (choice == 2) 
		{
			int rollno;
			double cgpa;
			if (maxHeap.remove(cgpa, rollno))
			{
				cout << "REMOVED ROLLNO:  " << rollno << ", CGPA: " << cgpa << endl;
			}
			else 
			{
				cout << "STUDENT NOT REMOVED" << endl;
			}
		}
		else if (choice == 3)
		{
			cout << "LIST (DESC CGPA) : " << endl;
			maxHeap.displayStudentList();
		}
		else if (choice == 4) 
		{
			cout << "LIST (LEVEL ORDER TRAVERSAL CGPA) :";
			maxHeap.levelOrder();
		}
		else if (choice == 5)
		{
			cout << "PROGRAM EXITED" << endl;
		}
		else 
		{
			cout << "ERROR!!! TRY AGAIN..." << endl;
		}
	} while (choice != 5);

	return 0;
}