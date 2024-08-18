#ifndef SET_HPP
#define SET_HPP

#include <bits/stdc++.h>
using namespace std;

class ElementoTabela{
    public:
        ElementoTabela();
        string dado;
        char status;
        bool vazio;
        bool retirada;

};

class StringSet{

    public:
        StringSet(int tamanho);
        ~StringSet();

        string ativar(string s);
        string desativar(string s);

        ElementoTabela getElement(string s);

        void Inserir(string s);
        void Remover(string s);
        bool Pertence(string s);
        
        StringSet* Intersecao(StringSet* S);
        StringSet* Uniao(StringSet* S);
        StringSet* DiferencaSimetrica(StringSet* S);

        void Imprimir();

    private:
        int tamanhoTabela;
        int tamanhoConjunto;
        ElementoTabela* tabela;

        int Hash(string s);
        void Rehash(int pos);
        void Resize(size_t tamanho);
};


#endif