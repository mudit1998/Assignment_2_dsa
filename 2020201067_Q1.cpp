#include<iostream>
using namespace std;

template <class T> struct Less {
	bool operator()(const T &lhs, const T &rhs) {
		// Datatype T must have operator< defined. Otherwise, this fails.
		return lhs < rhs;
	}
};

template <class T> struct Greater {
	bool operator()(const T &lhs, const T &rhs) {
		// Datatype T must have operator> defined. Otherwise, this fails.
		return lhs > rhs;
	}
};
template <class T, class Comparator = Less<T>>
//template <typename T>
class AVL {
public:

	class node
	{
	public:
		T val;
		int height;

		node * left;
		node * right;
		node(T k)
		{
			height = 1;
			val = k;
			left = NULL;
			right = NULL;
		}
	};
	node * root = NULL;
	int n;

	Comparator cmp;
	void insert(T x)
	{
		root = insertUtil(root, x);
	}
	void remove(T x)
	{
		root = removeUtil(root, x);
	}
	string search(T x)
	{
		return searchUtil(root, x);
	}
	void inorder()
	{
		inorderUtil(root);
		cout << endl;
	}
	int count(T x) {
		return countUtil(root, x);
	}
	T lower_bound(T x) {
		return  lower_bound_Util(root, x);
	}
	T upper_bound(T x) {
		return  upper_bound_Util(root, x);
	}
	void largest(int pos) {
		return largest_Util(root, pos);
	}
	int range(T a, T b) {
		return rangeUtil(root, a, b);
	}
	T closest(T x) {
		return closestUtil1(root, x);
	}
	/* <> string closest<string>(string x){
	    return closestUtil2(root,x);
	}*/

private:
	int height(node * head)
	{
		if (head == NULL)
			return 0;
		return head->height;
	}
	node * rightR(node * head)
	{
		node * newnode = head->left;
		head->left = newnode->right;
		newnode->right = head;
		head->height = 1 + max(height(head->left), height(head->right));
		newnode->height = 1 + max(height(newnode->left), height(newnode->right));
		return newnode;
	}
	node * leftR(node * head)
	{
		node * newnode = head->right;
		head->right = newnode->left;
		newnode->left = head;
		head->height = 1 + max(height(head->left), height(head->right));
		newnode->height = 1 + max(height(newnode->left), height(newnode->right));
		return newnode;
	}
	node * insertUtil(node * head, T x) {
		if (head == NULL)
		{
			n += 1;
			node * temp = new node(x);
			return temp;
		}
		if (cmp(x, head->val))head->left = insertUtil(head->left, x);
		else if (cmp(head->val, x)) head->right = insertUtil(head->right, x);
		else {
			head->right = insertUtil(head->right, x);
		}
		head->height = 1 + max(height(head->left), height(head->right));
		int bal = height(head->left) - height(head->right);
		if (bal > 1) {
			if (cmp(x, head->left->val)) {
				return rightR(head);
			}
			else {
				head->left = leftR(head->left);
				return rightR(head);
			}
		}
		else {
			if (bal < -1) {
				if (cmp(head->right->val, x)) {
					return leftR(head);
				}
				else {
					head->right = rightR(head->right);
					return leftR(head);
				}
			}
			return head;
		}


	}

	node * removeUtil(node * head, T x) {
		if (head == NULL) return NULL;
		if (cmp(x , head->val)) {
			head->left = removeUtil(head->left, x);
		} else if (cmp( head->val, x)) {
			head->right = removeUtil(head->right, x);
		} else {
			node * r = head->right;
			if (head->right == NULL) {
				node * l = head->left;

				delete(head);
				head = l;
			} else if (head->left == NULL) {

				delete(head);
				head = r;
			} else {
				while (r->left != NULL) r = r->left;
				head->val = r->val;
				head->right = removeUtil(head->right, r->val);
			}
		}
		if (head == NULL) return head;
		head->height = 1 + max(height(head->left), height(head->right));
		int bal = height(head->left) - height(head->right);
		if (bal > 1) {
			if (height(head->left->left) - height(head->left->right) >= 0) {
				return rightR(head);
			} else {
				head->left = leftR(head->left);
				return rightR(head);
			}
		} else if (bal < -1) {
			if (height(head->right->left) - height(head->right->right) <= 0) {
				return leftR(head);
			} else {
				head->right = rightR(head->right);
				return leftR(head);
			}
		}
		return head;
	}
	string searchUtil(node * head, T x) {
		if (head == NULL) return "false";
		T k = head->val;
		if (!cmp(k, x) && !cmp(x, k)) return "true";
		if (cmp(x, k)) return searchUtil(head->left, x);
		if (cmp(k, x)) return searchUtil(head->right, x);
		return "";
	}
	void inorderUtil(node * head) {
		if (head == NULL) return ;
		inorderUtil(head->left);
		cout << head->val << " ";
		inorderUtil(head->right);
	}

	int countUtil(node * head, T x) {
		if (head == NULL)return 0;
		T k = head->val;
		if (!cmp(k, x) && !cmp(x, k)) {
			return (1 + countUtil(head->left, x) + countUtil(head->right, x));

		}
		if (cmp(x, k))return countUtil(head->left, x);
		if (cmp(k, x)) return countUtil(head->right, x);
		return 0;
	}
	T lower_bound_Util(node * head, T x) {
		if (search(x) == "true")return x;
		else {
			T ans;
			while (head != NULL) {
				T k = head->val;
				if (cmp(x, k)) {
					ans = k;
					head = head->left;
				}
				else {
					head = head->right;
				}
			} return ans;
		}
	}
	T upper_bound_Util(node * head, T x) {

		T ans;
		while (head != NULL) {
			T k = head->val;
			if (cmp(x, k)) {
				ans = k;
				head = head->left;
			}
			else {
				head = head->right;
			}
		} return ans;
	}

	void largest_Util(node * head, int pos) {
		if (head) {
			static int z = pos;
			largest_Util(head->right, pos);
			z--;
			if (z == 0){cout<< head->val<<endl;return;}
			largest_Util(head->left, pos);
		}
		//return head->val;
	}
	int rangeUtil(node * head, T a, T b) {
		if (head) {
			if (cmp(b, head->val))return rangeUtil(head->left, a, b);
			else if (cmp(head->val, a))return rangeUtil(head->right, a, b);
			return (1 + rangeUtil(head->left, a, b) + rangeUtil(head->right, a, b));
		}
		return 0;
	}
	T closestUtil1(node * head, T x) {
		if (search(x) == "true")return x;
		else {
			T ans1, ans2, z, y;
			node * head1 = head;
			while (head1 != NULL) {
				T k = head1->val;
				if (cmp(x, k)) {ans1 = k; head1 = head1->left;}
				else {head1 = head1->right;}
			}
			while (head != NULL) {
				T k = head->val;
				if (cmp(k, x)) {ans2 = k; head = head->right;}
				else {head = head->left;}
			}
			z = abs(ans1 - x);
			y = abs(ans2 - x);
			if (cmp(z, y))return ans1;
			else return ans2;
		}
	}
	/*string closestUtil2(node * head,string x){
	     if(search(x))return x;
	     else{ int f=0;
	       string ans;
	       node * head1=head;
	       while(head1!=NULL){
	           string k=head1->val;
	           if(k<x){ans=k; head1=head1->right;f=1;}
	           else{head1=head1->left;}
	       }
	       if(f==1)return ans;
	       else{
	          while(head!=NULL){
	           string k=head->val;
	           if(k>x){ans=k;head=head->left;}
	           else{head=head->right;}
	          }
	          return ans;
	       }
	     }
	}*/
};
class stud {
public:
	int mar;
	string name;
};

struct cmpare {
	bool operator()(stud a, stud b) {
		return a.name < b.name;
	}
};
int main() {

     AVL<int>t;
     t.insert(1);
     t.insert(1);
    t.insert(2);
     t.insert(3);
     t.inorder();
     t.largest(1);
     cout<<t.count(2)<<endl;
     cout<<t.lower_bound(1);
     cout<<t.closest(2);

	/*AVL<stud, cmpare> a;

	stud s1, s2, s3, s4;

	s1.name = "abc";
	s1.mar = 12;
	s2.name = "bcd";
	s2.mar = 23;
	s3.name = "aas";
	s3.mar = 13;
	s4.name = "zzz";
	s4.mar = 13;

	a.insert(s1);
	a.insert(s2);
	a.insert(s3);
	a.insert(s4);
	a.remove(s4);
	cout << a.count(s1) << endl;
	cout << a.count(s4) << endl;
	cout << a.lower_bound(s1).name << endl;
	cout << a.upper_bound(s1).name << endl;
	a.largest(2);
	cout << a.range(s1, s3) << endl;
	cout << a.search(s1) << endl;
	a.inorder();*/
}