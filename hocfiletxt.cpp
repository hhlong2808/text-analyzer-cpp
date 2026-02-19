#include <iostream>      
#include <fstream>       
#include <sstream>       
#include <string>        
#include <unordered_map> 
#include <unordered_set> 
#include <vector>        
#include <algorithm>     
#include <cctype>        
using namespace std;

int Word_count(string &word_list){
    int cnt=0;
    string word;
    stringstream ss(word_list);
    while(ss>>word) cnt++;
    return cnt;
}

void Word_freq(string &word_list, ofstream &fout){
    unordered_map <string, int> mp;
    string word;
    stringstream ss(word_list);
    while(ss>>word){
        mp[word]++;
    }
    for(auto it:mp){
        cout<<it.first<<": "<<it.second<<endl;
        fout<<it.first<<": "<<it.second<<endl;
    }
    fout<<endl;
}

void top_Word_freq(string &word_list, ofstream &fout){
    unordered_map <string, int> mp;
    string word;
    stringstream ss(word_list);
    while(ss>>word){
        mp[word]++;
    }
    vector<pair<string, int>> freq_vec(mp.begin(), mp.end());
    sort(freq_vec.begin(), freq_vec.end(),
         [](const pair<string, int> &a, const pair<string, int> &b) {
             if(a.second == b.second) 
                 return a.first < b.first;  
             return a.second > b.second;    
         });
    cout<<"Top 10 word frequency:\n";
    fout<<"Top 10 word frequency:"<<endl;
    int n=min(10, (int)freq_vec.size());
    for(int i=0; i<n; i++){
        cout<<freq_vec[i].first<<": "<<freq_vec[i].second<<endl;
        fout<<freq_vec[i].first<<": "<<freq_vec[i].second<<endl;
    }
}

void Longest_word(string &word_list, ofstream &fout){
    int max_len=0;
    string word;
    string long_word;
    stringstream ss(word_list);
    while(ss>>word){
        if(word.size()>max_len){
            max_len=word.size();
            long_word=word;
        }
    }
    fout<<endl;
    fout<<"The longest word: "<<long_word<<" with: "<<max_len<<" characters";
    cout<<"The longest word: "<<long_word<<" with: "<<max_len<<" characters";
}

void Longest_substring(string &word_list, ofstream &fout){
    string word;
    string res_longest_substr;
    int res_longest_len=0;
    string in_word;
    stringstream ss(word_list);
    while(ss>>word){
        if(word.empty()) {
            continue;
        }
        int l=0, r=0;
        unordered_set<char> st;
        int n=word.size();
        int max_len=0;
        string longest_substr;
        while(r<n){
            while(st.find(word[r])!=st.end()){
                st.erase(word[l]);
                l++;
            }
            st.insert(word[r]);
            if(r-l+1>max_len){
                max_len=r-l+1;
                longest_substr=word.substr(l, max_len);
            }
            r++;
        }
        if(max_len>res_longest_len){
            res_longest_len=max_len;
            res_longest_substr=longest_substr;
            in_word=word;
        }
    }
    cout<<endl;
    cout<<endl<<"Longest sub-string: "<<res_longest_substr<<": "<<res_longest_len<<" in "<<in_word<<endl;
    fout<<endl<<"Longest sub-string: "<<res_longest_substr<<": "<<res_longest_len<<" in "<<in_word<<endl;
}

int main(){
    ifstream fin("input.txt");
    if(!fin){
        cout << "Cannot open file\n";
        return 1;
    }
    string text;
    string word;
    while(getline(fin, word)){
        text+=word+ " ";
    }
    string word_list="";
    
    stringstream ss(text);
    while(ss>>word){
        string new_word="";
        if(!word.empty()){
            for (int i=0; i<word.size(); i++) {
                char c = tolower((unsigned char)word[i]);
                if(isalnum(c) ||((c=='-' || c=='\'') && (i!=0 && i!=word.size()-1))){
                    new_word += c;
                }
            }
        }
        word_list+=new_word+" ";
        
    }
        
    ofstream fout("output.txt");
    cout<<"Number of words: "<<Word_count(word_list)<<endl;
    cout<<"Word frequency: "<<endl;


    fout<<"Number of words: "<<Word_count(word_list)<<endl<<endl;
    fout<<"Word frequency: "<<endl;

    Word_freq(word_list, fout);
    cout<<endl;


    top_Word_freq(word_list, fout);
    cout<<endl;


    Longest_word(word_list, fout);


    Longest_substring(word_list, fout);
    
    fin.close();
    return 0;
}   