#include <vector> 
#include <string>
#include <iostream>
#include <queue>
#include <stack>
struct Node {
	int val;
	Node* left;
	Node* right;
};
//bool identical(Node* one, Node* two) {
//	//if they are both nullptr, return true
//	//then if one of them is nullptr, return false 
//	//then return (one->val == two->val && identical(one->left, two->left) && identical(one->right, two->right)
//	if (one == nullptr && two == nullptr)
//		return true;
//	else if (one == nullptr || two == nullptr)
//		return false;
//	return(one->val == two->val && identical(one->left, two->left) && identical(one->right, two->right));
//}
//bool isSubtree(Node* main, Node* potential) {
//	//check if potential is nullptr
//	//check if main is nullptr 
//	//check if they are identical
//	//return isSubtree(main->left, potential) || isSubtree(main->right, potential)
//	if (potential == nullptr)
//		return true;
//	else if (main == nullptr)
//		return false; 
//	else if (identical(main, potential))
//		return true; 
//	return isSubtree(main->left, potential) || isSubtree(main->right, potential); 	
//}

//void reverse(Node* root) {
//	//swap pointers root->left and root->right, recursively call that for root->left and root->right
//	//if root == nullptr, return
//	if (root == nullptr)
//		return; 
//	Node* temp = root->left;
//	//set the the left node to the right node 
//	root->left = root->right; 
//	root->right = temp; 
//	reverse(root->left); 
//	reverse(root->right); 
//}

//int getGreatestPath(Node* head) {
//	//if tree is empty, return -1 
//	//find the child node with the greatest value, and sum that
//	if (head == nullptr)
//		return 0; 
//	int left = getGreatestPath(head->left); 
//	int right = getGreatestPath(head->right); 
// 
//	if (left < right)
//		return right + head->val;
//	else
//		return left + head-> val;
//}

//std::vector<std::string> rootToLeaf(Node* head) {
//	// Fill in code
//	std::vector<std::string> x; 
//	std::string current; 
//	rootToLeaf(x, head, current); 
//	return x;
//}
//
//void rootToLeaf(std::vector<std::string> x, Node* root, std::string current) {
//	//if empty node, just return 
//	if (root->left == nullptr && root->right == nullptr)
//		x.push_back(current); 
//	else if (root->left == nullptr) {
//		current += std::to_string(root->right->val); 
//		rootToLeaf(x, root->right, current); 
//	}
//	else if (root->right == nullptr) {
//		current += std::to_string(root->left->val);
//		rootToLeaf(x, root->left, current);  
//	}
//}

int maxDepth(Node* root) {
	if (root == nullptr)
		return -1; 
	int left = maxDepth(root->left);
	int right = maxDepth(root->right); 

	if (left > right)
		return 1 + left;
	else
		return 1 + right; 
}

void levelOrder(Node* root) {
	//iterate through the levels of the tree and print 
	int height = maxDepth(root); 
	for (int i = 1; i <= height; i++)
		printLevel(root, i); 
	
}

void printLevel(Node* t, int level) {
	//only print if the level is one
	//recursively call (t->left, level -1) 
	if (t == nullptr)
		return; 
	if (level == 1)
		std::cout << t->val; 
	else if (level > 1) {
		printLevel(t->left, level - 1);
		printLevel(t->right, level - 1); 
	}
}

void printLevelOrder(Node* root) {
	if (root == nullptr)
		return; 
	std::queue <Node*> q;
	q.push(root); 
	while (!q.empty()) {
		int size = q.size(); 
		while (size > 0) {
			Node* copy = q.front();
			std::cout << copy->val; 
			q.pop();
			if (copy->left != nullptr)
				q.push(copy->left); 
			if (copy->right != nullptr)
				q.push(copy->right); 
			size--; 
		}
	}
}

void infixToPostfix(std::string infix, std::string& postfix) {
	postfix = " "; 
	std::stack<char> op; 
	for (int i = 0; i < infix.size(); i++) {
		char c = infix.at(i); 
		switch (c) {
			//case operand,
			//postfix += c; 
			//break; 

		}
	}
}
