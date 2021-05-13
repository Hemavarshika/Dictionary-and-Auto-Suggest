#include<iostream>
#include<string.h>
#include<fstream>
#include<vector>
#include<queue>
#include<windows.h>
#include<stdlib.h>
using namespace std;
struct node{
	        struct node *child[26];
	        bool endword;
	        string meaning;
}root;
bool isendword(struct node *root)
{
    return (root->endword != false);
}

node* getnode()
{
	struct node *root=new node;
	int i;
	for(i=0;i<26;i++)
	  root->child[i]=NULL;
	root->endword=false;
	return root;

}
void insert_node(struct node *root, string key,string meaning)
{
    int i,index;
    struct node *ptr = root;
    for (i = 0; i< key.length(); i++)
    {
        index = tolower(key[i])- 'a';
        if (ptr->child[index] == NULL)
            ptr->child[index] = getnode();
        ptr = ptr->child[index];

    }
    ptr->endword = true;
    ptr->meaning=meaning;
}
int search_return(struct node *root, string key)
{
    struct node *ptr= root;
    int i,index;
    for (i=0;i<key.length();i++)
    {
        index = key[i] - 'a';
        if (!ptr->child[index])
            return 0;

        ptr = ptr->child[index];
    }

     if(ptr!= NULL && ptr->endword)
        return 1;
}
//search function to search for a given word
void search( struct node *root,string key)
{
    struct node *ptr= root;
    int i,index;
    for (i=0;i<key.length();i++)
    {
        index = key[i] - 'a';
        if (!ptr->child[index])
            {
            	cout<<"Word not Found !"<<endl;
            	break;
			}

        ptr = ptr->child[index];
    }

     if(ptr!= NULL && ptr->endword)
      {
      	  cout<<"Word is Found !!"<<endl;
      	  cout<<key<<":"<<ptr->meaning<<endl;
	  }
}
//a recursive display function for the words with their meaning
void displaymeaning(struct node *root, char str[], int count)
{
    if (isendword(root))
    {
        str[count] = '\0';
        cout<<str<< " "<<" :";
        cout<<root->meaning<<endl;
    }

    int i;
    for (i = 0; i < 26; i++)
    {
        if (root->child[i]!=NULL)
        {
            str[count] = i + 'a';
            displaymeaning(root->child[i], str, count + 1);
        }
    }
}
//a recursive display function for the words
void displayword(struct node *root, char str[], int count)
{
    if (isendword(root))
    {
        str[count] = '\0';
        cout<<str<< endl;
    }

    int i;
    for (i = 0; i < 26; i++)
    {
        if (root->child[i]!=NULL)
        {
            str[count] = i + 'a';
            displayword(root->child[i], str, count + 1);
        }
    }
}
//it loads the words from the text file to the trie
void file(struct node *root)
{
    string key;
    string meaning;
    ifstream fp;
    int l=1;
    char str[200];
    fp.open("dictionary.txt",ios::in);
    while(!fp.eof())
    {
     getline(fp,key,':');
     getline(fp,meaning,'\n');
	 if(key!="end")
	 {
     insert_node(root,key,meaning);
	 }

    }
    fp.close();

}
void find_all_words( struct node *root,string key,vector<string>&all_words)
{
	if(root==NULL) return ;
	struct node *temp = root;
	int i;
    for(i=0;i<(int)key.size();i++)
     {
     	int index = int(key[i])-'a';

     	/* if child node at ind of current root is NULL this prefix do not exist in trie  */

     	if( temp->child[index] == NULL ) return ;
     	temp = temp->child[index];
     }

     
     queue<pair<node*,string> > q;
     q.push(make_pair(temp,key));
     string this_word;
     while(!q.empty())
     {
     	temp = q.front().first;
     	this_word = q.front().second;
     	if(temp->endword) all_words.push_back( this_word );
     	q.pop();
     	for(int i=0;i<26;i++)
     	{
     		if( temp->child[i] !=NULL )
     		{
     			q.push( make_pair( temp->child[i] , this_word+char(i+int('a')) ) );
     		}
     	}
     }

}

void auto_suggest(struct node *root, string key)
{
    /* this function takes two parametes
	   1.) root node of trie
	   2.) key for which suggestion need to be found.

	   this function prints all the words for which key is prefix.
	*/

	/* if key is empty , no need to print */
   if(key.size() == 0) return ;

   /* if key is not empty , then we will print all words in trie for which key is PREFIX. */

   vector<string> all_words;
   find_all_words(root,key,all_words);
   if( all_words.size() == 0  )
	{
		cout<<"There are no suggestions."<<'\n';
		return ;
	}

	cout<<"There are "<<all_words.size()<<" suggestions for this prefix "<<key<<'\n';
	for(int i=0;i<(int)all_words.size();i++){
		cout<<all_words[i]<<' '<<endl;
	}

	return ;
}
void  checkmeaningful(string st,struct node *root)
{
	if(search_return(root,st)==1)
	   cout<<"Word is meaningful and present in the Dictionary !"<<endl;
	else
	   cout<<"Word is meaningless!!"<<endl;
}

//to find all the possible combinations of a given word
void permute(string a, int l, int r,struct node *root)
{

	if (l == r)
	{
	   cout<<a<<endl;
        checkmeaningful(a,root);
	   //store(a,root);

    }
    else
    {
      for (int i = l; i <= r; i++)
        {
          swap(a[l], a[i]);
		  permute(a, l+1, r,root);
		  swap(a[l], a[i]);
        }
    }

}
int main()
{
	string key,word,meaning;
	char str[20];
	int a,n;
	string s,st;
    struct node *root = getnode();
    cout<<"Loading the contents to the dictionary !"<<endl;
    Sleep(2000);
    file(root);
     do{

            system("cls");
     	cout<<"Main Menu"<<endl;
     	cout<<"1.View the Dictionary words"<<endl;
     	cout<<"2.View the Dicionary meaning"<<endl;
     	cout<<"3.Search a word in a Dictionary"<<endl;
     	cout<<"4.Insert-New-Word"<<endl;
     	cout<<"5.Auto-complete"<<endl;
     	cout<<"6.random letters"<<endl;
     	cout<<"7.exit"<<endl;
     	cout<<"Enter the option"<<endl;
     	cin>>a;
     	switch(a)
     	{
     		case 1:cout<<"Viewing the Dictionary words !"<<endl;
     		       displayword(root, str, 0);
     		       Sleep(6000);
     		       break;
            case 2:cout<<"Viewing the Dictionary words with meaning !"<<endl;
     		       displaymeaning(root, str, 0);
     		       Sleep(6000);
				   break;
		    case 3:cout<<"Searching a word in the dictionary !"<<endl;
		           cout<<"Enter word to search for!"<<endl;
		           cin>>str;
		           search(root,str);
		           Sleep(6000);
				   break;
			case 4:cout<<"Inserting a new word in the dictionary !"<<endl;
			       cout<<"Enter the new word to be inserted : ";
				   cin>>word;
				   cout<<"Enter the meaning of the word : ";
				   cin>>meaning;
				   insert_node(root,word,meaning);
				   Sleep(6000);
				   break;
		   case 5: cout<<"Auto suggest !!"<<endl;
		           cout<<"Enter string"<<endl;
		           cin>>s;
			       auto_suggest(root,s);
			       Sleep(6000);
			       break;
		   case 6: cout<<"Word search !!"<<endl;
		           cout<<"Enter the set of random words"<<endl;
		           cin>>st;
		           n=st.size();
		           permute(st,0,n-1,root);
		           Sleep(10000);
		           break;

           case 7: exit(0);
                  


		}
	 }while(a>=1 && a<=7);



}