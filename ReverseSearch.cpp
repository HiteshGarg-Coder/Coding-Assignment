#include<bits/stdc++.h>
using namespace std;

// Node Implementation
struct TrieNode{
        
		char data;
        unordered_map<char,TrieNode*> child;
        bool isEnd;
        
		TrieNode(char data){
            this->data = data;
            this->isEnd = false;
        }
};

// Trie Implementation
class Trie{

        TrieNode* root;
    
	public:
        
		Trie(){
            root = new TrieNode(' ');
        }
        
		void insert(string &);
        void dfs(TrieNode* , vector<string>& , string&);
        vector<string> autoSuggest(string &);   
};


// Dictionary Build-Up
void Trie :: insert(string &str){
	
    TrieNode* temp = root;
    for(auto &x:str){
        
		if(temp->child.find(x) == temp->child.end()){
            temp->child[x] = new TrieNode(x);
        }
        temp = temp->child[x];
    }
    temp->isEnd = true;
}

// Trie Tranversal
void Trie :: dfs(TrieNode* temp , vector<string>& words,string& curr){
	
    for(auto &p : temp->child){
    	
        curr.push_back(p.first);
        dfs(p.second , words , curr);
        curr.pop_back();
    }
    
    if(temp->isEnd){
        words.push_back(curr);
    }
}

// Suggestion
vector<string> Trie :: autoSuggest(string &str){
	
    TrieNode* temp = root;
    vector<string> words;
    
    for(auto &x:str){
    	
        if(temp->child.find(x) != temp->child.end()){
            temp = temp->child[x];
        }
        else return words;
    }
    
    string curr = str;
    dfs(temp , words , curr);
    
    return words;
}


int main(){
	
    string str;
    ifstream fin;
    string fileName;
    
    cout<<"Enter the name of file: ";
    cin>>fileName;
    
    fin.open(fileName , ios :: in);
    Trie obj;
    getline(fin , str);  
    
    int index=0;
    unordered_map<int,string> Book;
    
    while(!fin.eof()){
    	
    	Book[index] = str[0];
		str += ',' + to_string(index);
        obj.insert(str);
        
		getline(fin , str);  
        index++;
    }
    
    int val;
    cout<<"Enter the index (from 0 to "<<index<<") on which word to be searched: ";
    cin >> val;
    
    cout<<endl;
    while(val<0 || val > index){
    	cout<<"Sorry wrong input: "<<val<<"\nMax index is "<<index<<" starting from 0"<<endl<<endl;
    	cout<<"Please enter index again: ";
    	cin>> val;
	}
    
    
    
    string tobefound = to_string(val);
    vector<string> words = obj.autoSuggest(Book[val]);
    int n = words.size();
    
    if(n == 0){
        cout<<"No\n";
    }
    
    else{
    	
        bool found = false;
        string value,result,freq;
        int count,i,len;
        
        for(auto &x:words) {
        	
        	len = x.length();
        	count = 2;
        	freq=result=value="";
        
        	for(i=0;i<len && count>0;i++){
        		if(x[i]==',') count--;
        		else if(count==2) result += x[i];
        		else if(count==1) freq += x[i];
			}
						
			for(;i<len;i++){
        		value += x[i]; 
			}
		
			//word found
			if(value == tobefound){
				cout<<"Word is: "<<result<<endl;
				cout<<"Found at: "<<value<<endl;
				cout<<"Frequecy is: "<<freq<<endl;
				break;
			}      	
		}
    }
    
    fin.close();
    return 0;
}
