#include<bits/stdc++.h>
#define ll long long
#define blocks 100
#define prime 31

using namespace std;

template <typename T, typename U>
class Unordered_map{
    public:
    class node{
        public:
        T key_val;
        U value;
        node* next;
    }; 
    node* arr[blocks];
    Unordered_map(){

        for(ll i=0;i<blocks;i++){
            arr[i]=NULL;
        }
    }
    ll hash(T keys){

        ostringstream os;
        os << keys;
        string key=os.str();

        ll result = key[0];
        for (ll i=1;i<key.size();i++){ 
            result = ((result*prime)%blocks+key[i])%blocks; 
        }
        return result%blocks;
    }

  
    void insert(T key, U value){
        ll idx=hash(key);
        if(arr[idx]!=NULL){
            node* temp=arr[idx];
            while(temp){
                if(temp->key_val!=key){
                    temp=temp->next;
                }
                else{
                    return;
                }
            }
        }
        node* newnode = new node();
        newnode->key_val=key;
        newnode->value=value;
        node* p=arr[idx];
        newnode->next=p;
        arr[idx]=newnode;
        return;
    }

     bool find(T key){
        ll idx=hash(key);
        node* temp=arr[idx];
        while(temp){
            if(temp->key_val!=key){
                temp=temp->next;
            }
            else break;
        }
        if(temp==NULL)  return false;
        return true;
    }

    void erase(T key){
        ll idx=hash(key);

        node* temp=arr[idx];
        node* prev=NULL;

        if(temp!=NULL && temp->key_val==key){
            arr[idx]=temp->next;
            free(temp);
            return;
        }

        while(temp!=NULL && temp->key_val!=key){
            prev=temp;
            temp=temp->next;
        }

        if(temp==NULL)  return;

        prev->next=temp->next;
        free(temp);
        return;
    }
     
    U operator[] (T key){
        ll idx=hash(key);
        node* temp=arr[idx];
        while(temp){
            if(temp->key_val!=key){
                temp=temp->next;
            }
            else break;
        }
        if(temp==NULL)  return NULL;
        return temp->value;
    }
    void display()
    {
        for(int i=0;i<blocks;i++)
        {
            if(arr[i]!=NULL)
            {
                int cnt=0;
                node * temp=arr[i];
                cout<<i<<"    ";
                while(temp)
                {
                    cout<<"("<<temp->key_val<<","<<temp->value<<") ";
                    temp=temp->next;
                }
                cout<<endl;
            }
        }
    }
};
int main(){
Unordered_map<float,int> m1;
    m1.insert(10.4,545);
    m1.insert(12.2,554);
    m1.insert(42.2,422);
    m1.display();
    m1.insert(10.4,546);
    m1.insert(10.3,456);
    m1.display();
    cout<<m1[10.3];
}