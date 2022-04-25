#include<iostream>
using namespace std;

class Student
{
    public:
        string name, address;
        int rollno;
        void getInput();
};

void Student :: getInput()
{
    cout<<"Enter the Students Name        : ";
    cin>>name;

    cout<<"Enter the Students Roll Number : ";
    cin>>rollno;

    cout<<"Enter the Students Address     : ";
    cin>>address;
}

class Node
{
	public:
	Student *key;
	Node *left;
	Node *right;
	int height;
};

int maxHeight(int a, int b);

int maxHeight(int a, int b)
{
	return (a > b)? a : b;
}

Node* newNode(Student *key)
{
	Node* node = new Node();
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->height = 1; // new node is initially
					// added at leaf
	return(node);
}

Node *rightRotate(Node *y)
{
	Node *x = y->left;
	Node *T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = maxHeight((y->left)->height,(y->right)->height) + 1;
	x->height = maxHeight((x->left)->height,(x->right)->height) + 1;

	return x;
}

Node *leftRotate(Node *x)
{
	Node *y = x->right;
	Node *T2 = y->left;

	y->left = x;
	x->right = T2;

	x->height = maxHeight((x->left)->height,(x->right)->height) + 1;
	y->height = maxHeight((y->left)->height,(y->right)->height) + 1;

	return y;
}

int getBalance(Node *N)
{
	if (N == NULL)
		return 0;
	return ((N->left)->height) - ((N->right)->height);
}

Node* insertElement(Node* node, Student *key)
{
	if (node == NULL)
		return(newNode(key));

	if (key->rollno < (node->key)->rollno)
		node->left = insertElement(node->left, key);
	else if (key->rollno > (node->key)->rollno)
		node->right = insertElement(node->right, key);
	else
		return node;

	node->height = 1 + maxHeight((node->left)->height,(node->right)->height);


	int balance = getBalance(node);

	if (balance > 1 && key < node->left->key)
		return rightRotate(node);


	if (balance < -1 && key > node->right->key)
		return leftRotate(node);


	if (balance > 1 && key > node->left->key)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}


	if (balance < -1 && key < node->right->key)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}


	return node;
}

Node * minValueNode(Node* node)
{
    Node* current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}

// Recursive function to delete a node
// with given key from subtree with
// given root. It returns root of the
// modified subtree.
Node* deleteElement(Node *root, int key)
{
    if (root == NULL)
        return root;

    if ( key < (root->key)->rollno)
        root->left = deleteElement(root->left, key);
    else if( key > (root->key)->rollno)
        root->right = deleteElement(root->right, key);
    else
    {
        if((root->left == NULL) || (root->right == NULL))
        {
            Node *temp = root->left ? root->left : root->right;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;

            free(temp);
        }
        else
        {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;

            root->right = deleteElement(root->right, (temp->key)->rollno);
        }
    }

    if (root == NULL)
    return root;

    root->height = maxHeight((root->left)->height, (root->right)->height) + 1;

    int balance = getBalance(root);


    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void getTree(Node **root)
{
    char ch;
    Student *s;

    do
    {
        s = new Student;

        s->getInput();
        *root = insertElement(*root,s);

        cout<<"Do You Want to Enter Another Students Record (Y / N) : ";
        cin>>ch;

        cout<<"\n";
    }while((ch == 'Y') || (ch == 'y'));
}

void preOrder(Node *root)
{
	if(root != NULL)
	{
		cout <<"("<<(root->key)->name<<", "<<(root->key)->rollno<<", "<<(root->key)->address<<")   ";
		preOrder(root->left);
		preOrder(root->right);
	}
}

int main()
{
    char c;
    int ch, r;

	Node *root = NULL;
    Student *s;

	getTree(&root);
	do
    {
        system("cls");

        cout<<"----------------------------"<<endl;
        cout<<"What do you want to do?"<<endl;
        cout<<"----------------------------"<<endl;
        cout<<"1. Insert a New Record"<<endl;
        cout<<"2. Delete a Record "<<endl;
        cout<<"3. Search for an Record"<<endl;
        cout<<"4. Display All the Records"<<endl;
        cout<<"----------------------------"<<endl;

        cout<<"\nEnter your choice : ";
        cin>>ch;

        cout<<"\n";
        switch(ch)
        {
            case 1:
                s = new Student;

                s->getInput();
                root = insertElement(root,s);
                break;
            case 2:
                cout<<"Enter the Roll Number of the student to be Deleted : ";
                cin>>r;

                root = deleteElement(root,r);
                break;
            case 3:
                break;
            case 4:
                preOrder(root);
                break;
            default:
                cout<<"INVALID CHOICE"<<endl;
        }

        cout<<"\nDo You Want to Perform Any other Operation (Y / N) : ";
        cin>>c;
    }while((c == 'Y') || (c == 'y'));

    return 0;
}

