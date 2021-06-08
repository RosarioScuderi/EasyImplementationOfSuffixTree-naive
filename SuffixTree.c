/*****************************************************
    Progetto Algoritmi E Laboratorio 2020/2021
    Algoritmo naive di costruzione di un SuffixTree 
    Rosario Scuderi
    ATTENZIONE: IL CODICE POTREBBE CONTENERE BUG!!!
*****************************************************/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

static string LCP(string str1, string str2)   
{
    string result="";
    int n1 = str1.length(), n2 = str2.length();
 
    // Compare str1 and str2
    for (int i=0, j=0; i<=n1-1 && j<=n2-1; i++,j++)
    {
        if (str1[i] != str2[j])
            break;
        result.push_back(str1[i]);
    }
    
    return result;
}

class Nodo{
    public:
        vector<Nodo*> figli;
        string suffix;
        Nodo *parent;

        Nodo(){}

        Nodo(string suffix,Nodo *parent){
            this->suffix=suffix;
            this->parent=parent;
        }
};

class SuffixTree{
    private:

        Nodo *find(string suffix,Nodo* partenza){
            int max,dim;       max=dim=0;
            Nodo *daRitornare=partenza; string sdim;
            if(partenza->figli.size()>0){
                for(int i=0;i<partenza->figli.size();i++){
                    sdim=LCP(suffix,partenza->figli[i]->suffix);
                    dim=sdim.length();
                    if(dim>max){
                        max=dim;
                        daRitornare=partenza->figli[i];
                    }
                }
            }
            if(max==0){
                return daRitornare;
            }
            else{
                if(daRitornare->figli.size()>0){
                    return find(suffix.substr(dim),daRitornare);
                }
                else{
                    return daRitornare;
                }
            }
            return daRitornare;
        }

        int find_index(Nodo *a,Nodo *p){
            for(int i=0;i<p->figli.size();i++){
                if(p->figli[i]==a){
                    return i;
                }
            }
            return 0;
        }

        //continua da qui

        void split(string input,Nodo *current){
            
            string nev=" ";
            if(current->parent->suffix.length()==1){
                input=input.substr(1);
                current=find(input,current->parent);  
                //cout<<"Nodo attuale (current post reFind) == "<<current->suffix<<endl;
            }
            if(current->suffix.length()==1){
                string suff=input.substr(1);
                Nodo *nuovo=new Nodo(suff,current);
                current->figli.push_back(nuovo);
                return;
            }
            //cout<<"Nodo attuale (current) == "<<current->suffix<<endl;
            nev=LCP(input,current->suffix);
            int len=nev.length();
            Nodo * nuovo=new Nodo(nev,current->parent);
            int index=find_index(current,current->parent);
            current->parent->figli[index]=nuovo;
            nuovo->figli.push_back(current);
            current->parent=nuovo;
            string suffix1=current->suffix.substr(len);
            current->suffix=suffix1;
            string suffix2=input.substr(len);
            //cout<<"nev "<<nev<<" "<<"suffix1 "<<suffix1<<" "<<"suffix2 "<<suffix2<<endl;
            Nodo *right=new Nodo(suffix2,nuovo);
            nuovo->figli.push_back(right);
            return;
            
        }
        void build(string input){
            Nodo *first=new Nodo(input,root);
            root->figli.push_back(first);
            string tmp;
            for(int i=1;i<input.length();i++){
                tmp=input.substr(i);
                Nodo *nodo=find(tmp,root);
                if(nodo==root){
                    Nodo *nuovo=new Nodo (tmp,nodo);
                    root->figli.push_back(nuovo);
                }
                else{
                    split(tmp,nodo);
                }
            }
        }

    public:
        Nodo *root;
        SuffixTree(string input){
            root=new Nodo();
            build(input);
        }

        /*
        void print(){
            for(int i=0;i<root->figli.size();i++){
                cout<<root->figli[i]->suffix<<" [ "<<root->figli[i]->figli.size()<<" ] ";
                if(root->figli[i]->figli.size()>0){
                for(int j=0;j<root->figli[i]->figli.size();j++){
                        cout<<root->figli[i]->figli[j]->suffix<<" [ "<<root->figli[i]->figli[j]->figli.size()<<" ] ";
                        if(root->figli[i]->figli[j]->figli.size()>0){
                        cout<<" {";
                        for(int k=0;k<root->figli[i]->figli[j]->figli.size();k++){
                            cout<<root->figli[i]->figli[j]->figli[k]->suffix<<" [ "<<root->figli[i]->figli[j]->figli[k]->figli.size()<<" ] ";
                        }
                        cout<<"} ";
                        }
                    }
                    
                }
                cout<<endl;
            }
        }
*/

        void print(Nodo *x) {
            if(x->figli.size()==0){return;}
            for(int i=0;i<x->figli.size();i++){
                cout<<x->figli[i]->suffix<<"{ ";
                print(x->figli[i]);   
                cout<<"} ";   
            } 
        }
    

};

int main(){
    SuffixTree a("MISSISSIPPI$");
    a.print(a.root);
}
