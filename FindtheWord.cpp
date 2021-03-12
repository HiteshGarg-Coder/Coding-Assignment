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

int to_lower(string &word){
	int len = word.length();
	for(int i=0;i<len;i++)
    {
    	if(word[i]>='A' && word[i]<='Z'){
    		word[i] = word[i] - 'A' + 'a';
		}
	}
	return len;
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
    
    while(!fin.eof()){
    	
		to_lower(str);		
        obj.insert(str);
        getline(fin , str); 
    }
    
    cout<<"Enter the text to be searched: ";
    cin >> str;
	
	int len = to_lower(str);
    vector<string> words = obj.autoSuggest(str);
    int n = words.size();
    
    if(n == 0){
        cout<<"No\n";
    }
    
    else{
    	
        bool found = false;
        for(auto &x:words) {

        	if(x[len] == ','){

        		cout<<"YES, ";
        		int length = x.length();
        		
        		for(int i=len+1;i<length;i++){
        			cout<<x[i];
				}
				cout<<endl;
        		found = true;
			}        	
		}
		
		if(!found){
			cout<<"NO\n";
		}
    }
    
    fin.close();
    return 0;
}
