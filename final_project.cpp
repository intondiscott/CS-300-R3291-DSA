/******************************************
 *   Author: Scotty M Intondi             *
 *   Date: Feb 18, 2024                   *
 *	 Course: CS-300: DSA                  *
 *   Assigment: Project 2                 *
 ******************************************/

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;
struct Course
{
	string courseId;
	string courseName;
	string preReq;	
};

struct Node 
{
	Course course;
	Node* left;
	Node* right;

	// default constructor
	Node() {
		left = nullptr;
		right = nullptr;
	}

	// initialize with a course
	Node(Course aCourse) :
		Node() {
		course = aCourse;
	}
};

class BinarySearchTree
{
private:
	Node* root;
	void inOrder(Node* node);
	void addNode(Node* node, Course course);
	void destroyTree(Node* node);

public:
	BinarySearchTree();
	virtual ~BinarySearchTree();
	void InOrder();
	void Insert(Course course);
	Course Search(string courseId);
};
BinarySearchTree::BinarySearchTree() 
{
	root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
	destroyTree(root);
}

void BinarySearchTree::destroyTree(Node* node) {
	if (node != nullptr) {
		destroyTree(node->left);
		node->left = nullptr;
		destroyTree(node->right);
		node->right = nullptr;
		delete node;
	}
}

void BinarySearchTree::Insert(Course course) {
	if (root == nullptr) root = new Node(course);
	else this->addNode(root, course);
}

Course BinarySearchTree::Search(string courseId) {
	Node* cur = root;

	while (cur != nullptr)
	{
		//if cur node match
		if (cur->course.courseId.compare(courseId) == 0) return cur->course;

		//if course is smaller than current then traverse left
		if (courseId.compare(cur->course.courseId) < 0) cur = cur->left;

		else cur = cur->right;
	}

	Course course;
	return course;
}
void BinarySearchTree::InOrder() {
	this->inOrder(root);
}
void BinarySearchTree::inOrder(Node* node) {
	if (node == nullptr)return;
	inOrder(node->left);

	//print nodes
	cout << node->course.courseId << ", " << node->course.courseName << endl;

	inOrder(node->right);
}
void BinarySearchTree::addNode(Node* node, Course course) {
	// if node is larger then add to left subtree
	if (node->course.courseId.compare(course.courseId) > 0)
		if (node->left == nullptr) node->left = new Node(course);

		else this->addNode(node->left, course);
	// add to right subtree
	else
		if (node->right == nullptr) node->right = new Node(course);

		else this->addNode(node->right, course);

}

void displayMenuOptions()
{
	cout << " -------------------------\n"
			"| 1.) Load courses        |\n"
			"| 2.) Print courses       |\n" 
			"| 3.) Search for a course |\n" 
			"| 9.) Exit program        |\n"
			" -------------------------\n";
}
void loadCourses(string file, BinarySearchTree* bst)
{
	ifstream myFile(file);
	if (!myFile.is_open()) cout << "\"" << file << "\" failed to open..." << endl;
	if (myFile.is_open())
	{
		cout << "Courses Loaded..." << endl;
		string line;
			
		while (getline(myFile, line))
		{
			int col = 0;
			stringstream ss(line);
			string courseId, courseName, preReq, preReqText;
			
			while (col < 2)
			{
				if (col == 0) getline(ss, courseId, ',');
				if (col == 1) getline(ss, courseName, ',');
				col++;
			}
			while (getline(ss, preReq, ','))
			{
				if (preReq == "") preReqText = "None";
				else preReqText += preReq + ", ";
			}
				
			Course course;
			course.courseId = courseId;
			course.courseName = courseName;
			course.preReq = preReqText;
			
			bst->Insert(course);	
		}
	}	
}
void printCourses(Course course)
{
	cout << endl;
	cout << string(100, '~') << endl;

	cout << "Course Id: " << course.courseId << " | " <<
			"Course Name: " << course.courseName << " | " <<
			"Prerequisites: " << course.preReq << endl;

	cout << string(100, '~') << endl;
}

int main()
{
	// Define a binary search tree to hold all courses
	BinarySearchTree* bst = new BinarySearchTree();
	string file, courseKey, courseKeyUpper;
	Course course;
	char cmd = '0';
	while (cmd != '9')
	{
		displayMenuOptions();
		cin >> cmd;
		switch (cmd)
		{
		case '1':
			cout << "Enter file to look up (or press ENTER for default file): ";
			cin.ignore();
			getline(cin, file);
			
			if (file.size() < 1) file = "ABCU_Advising_Program_Input.csv";
			loadCourses(file, bst);
			break;
		case '2':
			bst->InOrder();
			break;
		case '3':
			cout << "Enter the courseId...";
			
			cin >> courseKey;
			
			for (int i = 0; i < courseKey.size(); i++)
				courseKeyUpper += putchar(toupper(courseKey[i]));
			
			course = bst->Search(courseKeyUpper);
			courseKeyUpper = "";
			if (!course.courseId.empty()) {
				printCourses(course);
			}
			else {
				cout << "Course Id \"" << courseKeyUpper << "\" not found." << endl;
			}
			break;
		case '9':
			cout << "Good Bye..." << endl;
			break;
		default:
			cout << cmd << " is not a valid option, please try again..." << endl;
			break;
		}	
	}
	return 0;
}