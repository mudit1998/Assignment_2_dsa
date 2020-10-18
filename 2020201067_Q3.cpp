#include<bits/stdc++.h>
#define ll long long
using namespace std;
//int count=0;
template <typename T,typename U>
class ordered_map{
    public:
        class node
        {
            public:
                T key;
                U val;
                int height;
             
                node * left;
                node * right;
                node(T k,U v)
                {  
                    height = 1;
                    key=k;
                    val = v;
                    left = NULL;
                    right = NULL;
                }
        };
        int count=0;
        node * root=NULL;
        void insert(T x,U y)
        {
            root=insertUtil(root, x,y);
        }
        void remove(T x)
        {
            root=removeUtil(root, x);
        }
        string search(T x)
        {
            return searchUtil(root,x);
        }
        U & operator [] (T x){
        	return operUtil(root,x);
        }
        int size(){
        	return count; 
        }
        void clear(){
            clearUtil(root);
        }
        void display()
        {
        if(root==NULL)
            cout<<"Empty\n";
        else
            inorder(root);
         //cout<<n<<endl;
        }
 
        private:
        int height(node * head)
        {
            if(head==NULL)
                return 0;
            return head->height;
        }
        node * rightR(node * head)
        {
            node * newnode=head->left;
            head->left=newnode->right;
            newnode->right=head;
            head->height=1+max(height(head->left),height(head->right));
            newnode->height=1+max(height(newnode->left),height(newnode->right));
            return newnode;
        }
        node * leftR(node * head)
        {
            node * newnode=head->right;
            head->right=newnode->left;
            newnode->left=head;
            head->height=1+max(height(head->left),height(head->right));
            newnode->height=1+max(height(newnode->left),height(newnode->right));
            return newnode;
        }
        node * insertUtil(node * head,T x,U y){ 
            if(head==NULL)
            {
               // n+=1;
            	count++;
                node * temp=new node(x,y);
                return temp; 
            }
            if(x<head->key)head->left=insertUtil(head->left,x,y);
            else if(x>head->key) head->right=insertUtil(head->right,x,y);
            else { //count--;
            	head->val=y;
                
            }
            head->height=1+max(height(head->left),height(head->right));
            int bal=height(head->left)-height(head->right);
            if(bal>1){
                if(x<head->left->key){
                    return rightR(head);
                }
                else {
                    head->left=leftR(head->left);
                    return rightR(head);
                }
            }
            else{
                if(bal<-1){
                    if(x>head->right->key){
                        return leftR(head);
                    }
                    else{
                        head->right=rightR(head->right);
                        return leftR(head);
                    }
                }
                return head;
            }
            
              
        }
        node * removeUtil(node * head,T x){
             if(head==NULL) return NULL;
            if(x < head->key){
                head->left = removeUtil(head->left, x);
            }else if(x > head->key){
                head->right = removeUtil(head->right, x);
            }else{
                node * r = head->right;
                if(head->right==NULL){
                    node * l = head->left;
                    count--;
                    delete(head);
                    head = l;
                }else if(head->left==NULL){
                    count--;
                    delete(head);
                    head = r;
                }else{
                    while(r->left!=NULL) r = r->left;
                    head->key = r->key;
                    head->right = removeUtil(head->right, r->key);
                }
            }
            if(head==NULL) return head;
            head->height = 1 + max(height(head->left), height(head->right));
            int bal = height(head->left) - height(head->right);
            if(bal>1){
                if(height(head->left->left) - height(head->left->right)>=0){
                    return rightR(head);
                }else{
                    head->left = leftR(head->left);
                    return rightR(head);
                }
            }else if(bal < -1){
                if(height(head->right->left) - height(head->right->right)<=0){
                    return leftR(head);
                }else{
                    head->right = rightR(head->right);
                    return leftR(head);
                }
            }
            return head;
        }
        string searchUtil(node * head, T x){
            if(head == NULL) return "0";
            T k = head->key;
            if(k == x) return "true";
            if(k > x) return searchUtil(head->left, x);
            if(k < x) return searchUtil(head->right, x);
        }
        
        void clearUtil(node * head){
        	if(head){
        		clearUtil(head->left);
        		clearUtil(head->right);
        		delete(head);
        	}
        	count=0;
        }
        node *  find(node * head,T x){
        	//U var=0;
        	if(head==NULL)return NULL;
        	T k=head->key;
        	if(k==x)return head;
        	if(k>x)return find(head->left,x);
        	if(k<x)return find(head->right,x);
        }
        U & operUtil(node * head,T x){
            node * head1=head;
            auto var=find(head1,x);
            if(var!=NULL)return var->val;
            else{ U val;
            	insert(x,val);
            	auto ans= find(head,x);
            	return ans->val;
            }

        }
         void inorder(node * temp)
     {
        if(temp==NULL)
            return;
        inorder(temp->left);
        cout<<temp->key<<"  "<<temp->val<<endl;
        inorder(temp->right);
     }
};

int main(){
	ordered_map<float,int> m1;
    m1.insert(10.4,545);
    m1.insert(12.2,554);
    m1.insert(42.2,422);
    //m1.display();
    cout<<endl<<endl;
   // m1.remove(10.4);
   // m1.display();
    cout<<endl;
    m1.insert(10.4,546);
    m1.insert(10.3,456);
    //cout<<m1.search(10.4)<<endl;
    m1.display();
    m1[10.0]=123;
    cout<<"10.4     ----"<<m1[10.4]<<endl;
    //cout<<"15    ----"<<m1.find(15)<<endl;
    cout<<m1.size()<<endl;
    m1.clear();
    //m1.insert(10.2,1);
    cout<<m1.size();
    //m1.display();
}        