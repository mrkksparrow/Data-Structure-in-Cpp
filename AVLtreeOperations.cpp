#include <bits/stdc++.h>
using namespace std;

class Node{
    public :
        int data;
        int height;
        Node* left;
        Node* right;

        Node* createNode (int);
        int Height (Node*);
        int getBalance (Node*);
        Node* insertNode (Node*, int);
        Node* deleteNode (Node*, int);
        Node* leftRotation (Node*);
        Node* rightRotation (Node*);
        Node* rightMinimum (Node*);
        void levelOrder (Node*);
        void zigZaglevelOrder (Node*);
        void Boundry (Node*);
        void leftView (Node*);
        void rightView (Node*);
        void topView (Node*);
        void bottomView (Node*);
        void printPathUtil (Node*, vector<string>&, string);
        void printPath (Node*);
        int Diameter (Node*, int&);
        Node* invertTree (Node*);
        int maxPathSumUtil (Node*, int&);
        void maxPathSum (Node*);
        int longestUniqueNodeUtil (Node*, int&);
        void longestUniqueNode (Node*);
};

Node* Node::createNode(int x){
    Node* temp = new Node();
    temp->data = x;
    temp->height = 1;
    temp->left = temp->right = NULL;

    return temp;
}

int Node::Height(Node* temp){
    if(temp==NULL){
        return 0;
    }
    return temp->height;
}

int Node::getBalance(Node* temp){
    if(temp==NULL){
        return 0;
    }
    return Height(temp->left) - Height(temp->right);
}

Node* Node::leftRotation(Node* temp){
    Node* a = temp->left;
    Node* subtree = a->right;

    a->right = temp;
    temp->left = subtree;

    temp->height = 1+max(Height(temp->left), Height(temp->right));
    a->height = 1+max(Height(a->left), Height(a->right));

    return a;
}

Node* Node::rightRotation(Node* temp){
    Node* a = temp->right;
    Node* subtree = a->left;

    a->left = temp;
    temp->right = subtree;

    temp->height = 1+max(Height(temp->left), Height(temp->right));
    a->height = 1+max(Height(a->left), Height(a->right));

    return a;    
}

Node* Node::rightMinimum(Node* temp){
    while(temp->left!=NULL){
        temp = temp->left;
    }
    return temp;
}

Node* Node::insertNode(Node* temp, int x){
    if(temp==NULL){
        return createNode(x);
    }

    if(temp->data > x){
        temp->left = insertNode(temp->left, x);
    }
    else if(temp->data < x){
        temp->right = insertNode(temp->right, x);
    }
    else{
        return temp;
    }
    temp->height = 1+max(Height(temp->left), Height(temp->right));

    int balance = getBalance(temp);

    if(balance > 1 && temp->left->data > x){
        return leftRotation(temp);
    }
    if(balance > 1 && temp->left->data < x){
        temp->left = rightRotation(temp->left);
        return leftRotation(temp);
    }
    if(balance < -1 && temp->right->data < x){
        return rightRotation(temp);
    }
    if(balance < -1 && temp->right->data > x){
        temp->right = leftRotation(temp->right);
        return rightRotation(temp);
    }
    return temp;
}

Node* Node::deleteNode(Node* temp, int x){
    if(temp==NULL){
        return temp;
    }

    if(temp->data > x){
        temp->left = deleteNode(temp->left, x);
    }
    else if(temp->data < x){
        temp->right = deleteNode(temp->right, x);
    }
    else {
        if(temp->left==NULL || temp->right==NULL){
            Node* curr = temp->left ? temp->left : temp->right;

            if(curr==NULL){
                curr = temp;
                temp = NULL;
            }
            else{
                *temp = *curr;
            }
            free(curr);
        }
        else{
            Node* successor = temp->rightMinimum(temp->right);
            temp->data = successor->data;
            temp->right = deleteNode(temp->right, successor->data);
        }
    }
    if(temp==NULL){
        return temp;
    }

    temp->height = 1+max(Height(temp->left), Height(temp->right));
    int balance = getBalance(temp);

    if(balance > 1 && getBalance(temp->left) >= 0){
        return leftRotation(temp);
    }
    if(balance > 1 && getBalance(temp->left) < 0){
        temp->left = rightRotation(temp->left);
        return leftRotation(temp);
    }
    if(balance < -1 && getBalance(temp->right) <= 0){
        return rightRotation(temp);
    }
    if(balance < -1 && getBalance(temp->right) > 0){
        temp->right = leftRotation(temp->right);
        return rightRotation(temp);
    }
    return temp;
}

void leftBoundry(Node* temp){
    if(temp==NULL){
        return ;
    }

    if(!(temp->left==NULL && temp->right==NULL)){
        cout<<temp->data<<" ";
    }

    leftBoundry(temp->left);
}

void leafBoundry(Node* temp){
    if(temp==NULL){
        return ;
    }

    leafBoundry(temp->left);
    leafBoundry(temp->right);

    if(temp->left==NULL && temp->right==NULL){
        cout<<temp->data<<" ";
    }
}

void rightBoundry(Node* temp){
    if(temp==NULL){
        return ;
    }

    rightBoundry(temp->right);

    if(!(temp->left==NULL && temp->right==NULL)){
        cout<<temp->data<<" ";
    }
}

void Node::Boundry(Node* temp){
    if(temp==NULL){
        return ;
    }

    cout<<temp->data<<" ";
    leftBoundry(temp->left);
    leafBoundry(temp);
    rightBoundry(temp->right);

}

void Node::levelOrder(Node* temp){
    if(temp==NULL){
        return ;
    }

    queue <Node*> que;
    que.push(temp);

    while(!que.empty()){
        int size = que.size();
        while(size--){
            Node* curr = que.front();
            que.pop();
            cout<<curr->data<<" ";
            if(curr->left) que.push(curr->left);
            if(curr->right) que.push(curr->right);
        }
        cout<<endl;
    }
}

void Node::zigZaglevelOrder(Node* temp){
    if(temp==NULL){
        return ;
    }

    int shift = 1;
    queue <Node*> que;
    que.push(temp);

    while(!que.empty()){
        int size = que.size();
        while(size--){
            Node* curr = que.front();
            cout<<curr->data<<" ";
            if(shift){
                if(curr->right) que.push(curr->right);
                if(curr->left) que.push(curr->left);
            }
            else{
                if(curr->left) que.push(curr->left);
                if(curr->right) que.push(curr->right);
            }
        }
        cout<<endl;
        if(shift) shift=0;
        else shift = 1;
    }
}

void Node::leftView(Node* temp){
    if(temp==NULL){
        return ;
    }

    queue <Node*> que;
    que.push(temp);

    while(!que.empty()){
        int size = que.size();
        cout<<que.front()->data<<" ";
        while(size--){
            Node* curr = que.front();
            que.pop();
            if(curr->left) que.push(curr->left);
            if(curr->right) que.push(curr->right);
        }
    }
}

void Node::rightView(Node* temp){
    if(temp==NULL){
        return ;
    }

    queue <Node*> que;
    que.push(temp);

    while(!que.empty()){
        int size = que.size();
        cout<<que.front()->data<<" ";
        while(size--){
            Node* curr = que.front();
            que.pop();
            if(curr->right) que.push(curr->right);
            if(curr->left) que.push(curr->right);
        }
    }
}

void markVerticaltopView(Node* temp, int order, int level, map <int, pair<int, int>>& verticalOrder){
    if(temp==NULL){
        return ;
    }
    
    if(verticalOrder.count(order)==0){
        verticalOrder[order] = make_pair(temp->data, level);
    }
    else{
        if(verticalOrder[order].second > level){
            verticalOrder[order] = make_pair(temp->data, level);
        }
    }

    markVerticaltopView(temp->left, order-1, level+1, verticalOrder);
    markVerticaltopView(temp->right, order+1, level+1, verticalOrder);
}

void Node::topView(Node* temp){
    if(temp==NULL){
        return ;
    }

    map <int, pair<int, int>> verticalOrder;
    markVerticaltopView(temp, 0, 0, verticalOrder);

    map <int, pair<int, int>>::iterator itr;
    for(itr=verticalOrder.begin(); itr!=verticalOrder.end(); itr++){
        cout<<itr->second.first<<" ";
    }
}

void markVerticalbottomView(Node* temp, int order, int level, map<int, pair<int, int>>& verticalorder){
    if(temp==NULL){
        return ;
    }

    if(verticalorder.count(order)==0){
        verticalorder[order] = make_pair(temp->data, level);
    }
    else{
        if(verticalorder[order].second < level){
            verticalorder[order] = make_pair(temp->data, level);
        }
    }

    markVerticalbottomView(temp->left, order-1, level+1, verticalorder);
    markVerticalbottomView(temp->right, order+1, level+1, verticalorder);
}

void Node::bottomView(Node* temp){
    if(temp==NULL){
        return ;
    }

    map<int,pair<int,int>> verticalorder;
    markVerticalbottomView(temp, 0, 0, verticalorder);

    map<int,pair<int, int>>::iterator itr;
    for(itr=verticalorder.begin(); itr!=verticalorder.end(); itr++){
        cout<<itr->second.first<<" ";
    }
}

int Node::Diameter(Node* temp, int& diameter){
    if(temp==NULL){
        return 0;
    }

    int left_height = Diameter(temp->left, diameter);
    int right_height = Diameter(temp->right, diameter);

    diameter = max(diameter, left_height+right_height+1);

    return max(left_height, right_height)+1;

    /*
    diameter = 1+max(left_height, right_height);

    return max(diameter, left_height+right_height+1);
    */
}

void Node::printPathUtil (Node* temp, vector<string>& path, string str){
    if(temp->left==NULL && temp->right==NULL){
        str += to_string(temp->data);
        path.push_back(str);
        return ;
    }
    else{
        str += to_string(temp->data)+"->";
    }
    if (temp->left!=NULL) printPathUtil (temp->left, path, str);
    if (temp->right!=NULL) printPathUtil (temp->right, path, str);
}

void Node::printPath (Node* temp){
    if(temp==NULL){
        return ;
    }
    vector <string> path;
    string str = "";
    printPathUtil(temp, path, str);

    for(auto &i : path){
        cout<<i<<endl;
    }
}

Node* Node::invertTree (Node* temp){
    if(temp==NULL){
        return temp;
    }
    Node* left = invertTree (temp->left);
    Node* right = invertTree (temp->right);

    temp->left = right;
    temp->right = left;

    return temp;
}

int Node::maxPathSumUtil (Node* temp, int& maxsum){
    if(temp==NULL){
        return INT_MIN;
    }

    int leftsum = maxPathSumUtil (temp->left, maxsum);
    int rightsum = maxPathSumUtil (temp->right, maxsum);

    if (leftsum<0) leftsum = 0;
    if (rightsum<0) rightsum = 0;

    int sum = leftsum + rightsum + temp->data;
    maxsum = max(maxsum, sum);

    return max(leftsum, rightsum)+temp->data;
}

void Node::maxPathSum (Node* temp){
    if (temp==NULL){
        return ;
    }
    int maxsum = INT_MIN;
    maxPathSumUtil (temp, maxsum);
    cout<<"Path with Maximum Sum Value : "<<maxsum;
}

int Node::longestUniqueNodeUtil (Node* temp, int& count){
    if(temp==NULL){
        return 0;
    }

    int leftlen = longestUniqueNodeUtil (temp->left, count);
    int rightlen = longestUniqueNodeUtil (temp->right, count);

    int leftcount=0, rightcount=0;
    if (temp->left && (temp->data==temp->left->data)) leftcount += leftlen + 1;
    if (temp->right && (temp->data==temp->right->data)) rightcount += rightlen + 1;

    count = max(count, leftcount+rightcount);

    return max(leftcount, rightcount);
}

void Node::longestUniqueNode (Node* temp){
    if(temp==NULL){
        return ;
    }
    int count = 0;
    longestUniqueNodeUtil (temp, count);
    cout<<"Lenght of Longest Unique Nodes : "<<count;
}

int main(){
    Node* root = NULL;
    int n = 7;
    cout<<"Enter 7 elements to be inserted into Self-balancing AVL tree"<<endl;
    while(n--){
        int x;
        cin>>x;
        root = root->insertNode(root, x);
    }
    cout<<"--------------------------"<<endl;
    root->levelOrder(root);
    cout<<"--------------------------"<<endl;

    int choice;
    do{
        cout<<"1. Insert New Element               11. Invert Tree                 "<<endl
            <<"2. Delete Element                   12. Maximum Path Sum            "<<endl
            <<"3. Level order Traversal            13. Longest Unique Node Length  "<<endl
            <<"4. Boundry Elements                 "<<endl
            <<"5. Left View                        "<<endl
            <<"6. Right View                       "<<endl
            <<"7. Top View                         "<<endl
            <<"8. Bottom View                      "<<endl
            <<"9. Diameter                         "<<endl
            <<"10. Path to root from leaf          "<<endl
            <<"0. Exit                             "<<endl;

        cin>>choice;
        cout<<"--------------------------"<<endl;
        switch(choice){
            case 1:
                cout<<"Enter a element"<<endl;
                int insert; cin>>insert;
                root = root->insertNode(root, insert);
                root->levelOrder(root);
                break ;

            case 2:
                cout<<"Enter a Element"<<endl;
                int remove; cin>>remove;
                root = root->deleteNode(root, remove);
                root->levelOrder(root);
                break ;

            case 3:
                cout<<"Level order Traversal"<<endl;
                root->levelOrder(root);
                break ;

            case 4: 
                cout<<"Boundry Elements"<<endl;
                root->Boundry(root);
                break ;

            case 5:
                cout<<"Left View "<<endl;
                root->leftView(root);
                break ;

            case 6:
                cout<<"Right View"<<endl;
                root->rightView(root);
                break ;

            case 7:
                cout<<"Top View"<<endl;
                root->topView(root);
                break ;

            case 8:
                cout<<"Bottom View"<<endl;
                root->bottomView(root);
                break ;

            case 9:{
                int diameter = 0;
                root->Diameter(root, diameter);
                cout<<"Diameter of tree : "<<diameter;
                break ;
            }

            case 10:{
                cout<<"Path to every leaf node from root : "<<endl;
                root->printPath(root);
                break ;
            }

            case 11:{
                cout<<"Original Tree : "<<endl;
                root->levelOrder (root);
                cout<<"Inverted Tree : "<<endl;
                root = root->invertTree (root);
                root->levelOrder(root);
                root = root->invertTree (root);                 // again i have done invert to reset tree to original form
            }

            case 12:{
                root->maxPathSum (root);
                break ;
            }

            case 13:{
                root->longestUniqueNode (root);
                break ;
            }

            case 0:
                cout<<"Thank You, Have a great day";
                break ;
        }
        cout<<endl<<"--------------------------"<<endl;
    }while(choice != 0);

    return 0;
}
/*
12
6
3
11
1
4
8
12
2
5
7
9
14
*/
