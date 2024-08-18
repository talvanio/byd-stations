#include <bits/stdc++.h>
#include "../include/Set.hpp"
using namespace std;

StringSet::StringSet(int tamanho)
{
    tamanhoOriginal = tamanho;
    tamanhoTabela = tamanho;

    int tamanhoConjunto = 0;
    tabela = new ElementoTabela[tamanho];
    for (int i = 0; i < tamanho; i++)
    {
        tabela[i].retirada = 0;
        tabela[i].vazio = 1;
    }
};

StringSet::~StringSet()
{
    delete[] tabela;
}

void StringSet::Inserir(string s)
{
    if (Pertence(s))
        return;

    if (tamanhoConjunto >= tamanhoTabela)
    {
        int tamanhoConjuntoOriginal = tamanhoConjunto;
        Resize(tamanhoTabela * 2);
        tamanhoConjunto = tamanhoConjuntoOriginal;
    }

    int i = 0;
    int string_index = Hash(s);

    while (i < tamanhoTabela && !tabela[(string_index + i) % tamanhoTabela].vazio && !tabela[(string_index + i) % tamanhoTabela].retirada)
    {
        i++;
    }

    if (i < tamanhoTabela)
    {
        std::cout<<"HT posicao "<< (string_index + i) % tamanhoTabela <<" "<<s<<std::endl;
        tabela[(string_index + i) % tamanhoTabela].vazio = 0;
        tabela[(string_index + i) % tamanhoTabela].dado = s;
        tabela[(string_index + i) % tamanhoTabela].retirada = 0;
        tabela[(string_index + i) % tamanhoTabela].status = 'A';
        tamanhoConjunto++;
    }
}

void StringSet::Remover(string s)
{
    int string_index = Hash(s);
    int i = 0;

    while (i < tamanhoOriginal && !tabela[(string_index + i) % tamanhoOriginal].vazio &&
           tabela[(string_index + i) % tamanhoOriginal].dado != s)
    {
        i++;
    }

    if (tabela[(string_index + i) % tamanhoOriginal].dado == s && !tabela[(string_index + i) % tamanhoOriginal].retirada)
    {
        tabela[(string_index + i) % tamanhoOriginal].vazio = 1;
        tabela[(string_index + i) % tamanhoOriginal].retirada = 1;

        tamanhoConjunto--;
        i++;
        while (!tabela[(string_index + i) % tamanhoOriginal].vazio)
        {
            Rehash((string_index + i) % tamanhoOriginal);
            i++;
        }
    }
};

bool StringSet::Pertence(string s)
{
    int i = 0;
    int string_index = Hash(s);

    while (i < tamanhoTabela && !tabela[(string_index + i) % tamanhoOriginal].vazio &&
           tabela[(string_index + i) % tamanhoOriginal].dado != s)
    {
        i++;
    }

    if (tabela[(string_index + i) % tamanhoOriginal].dado == s && !tabela[(string_index + i) % tamanhoOriginal].retirada)
    {
        return 1;
    }
    return 0;
};

StringSet *StringSet::Intersecao(StringSet *S)
{
    StringSet *res = new StringSet(S->tamanhoTabela);

    for (int i = 0; i < tamanhoTabela; i++)
    {
        if (!tabela[i].vazio && !tabela[i].retirada)
        {
            if (S->Pertence(tabela[i].dado))
                res->Inserir(tabela[i].dado);
        }
    }
    return res;
};

StringSet *StringSet::Uniao(StringSet *S)
{
    StringSet *res = new StringSet(S->tamanhoTabela);

    for (int i = 0; i < tamanhoTabela; i++)
    {
        if (tabela[i].vazio || tabela[i].retirada)
        {
            continue;
        }

        res->Inserir(tabela[i].dado);
    }

    for (int i = 0; i < S->tamanhoTabela; i++)
    {
        if (S->tabela[i].vazio || S->tabela[i].retirada)
        {
            continue;
        }

        res->Inserir(S->tabela[i].dado);
    }
    return res;
};

StringSet *StringSet::DiferencaSimetrica(StringSet *S)
{
    StringSet *res = new StringSet(S->tamanhoTabela);

    for (int i = 0; i < tamanhoTabela; i++)
    {
        if (tabela[i].vazio || tabela[i].retirada)
        {
            continue;
        }
        if (!S->Pertence(tabela[i].dado))
        {
            res->Inserir(tabela[i].dado);
        }
    }

    for (int i = 0; i < S->tamanhoTabela; i++)
    {
        if (S->tabela[i].vazio || S->tabela[i].retirada)
        {
            continue;
        }
        if (!Pertence(S->tabela[i].dado))
        {
            res->Inserir(S->tabela[i].dado);
        }
    };
    return res;
};

int StringSet::Hash(string s)
{
    int str_total_value = 0;

    for (int i = 0; i < s.length(); i++)
    {
        str_total_value += s[i] * i;
    }
    return str_total_value % tamanhoTabela;
};

void StringSet::Rehash(int pos)
{
    if (tabela[pos].vazio)
        return;

    string s = tabela[pos].dado;
    tabela[pos].dado = "";
    tabela[pos].vazio = 1;
    tabela[pos].retirada = 0;
    tamanhoConjunto--;

    Inserir(s);
};

void StringSet::Resize(size_t tamanho)
{
    ElementoTabela *tabela_original = tabela;
    tabela = new ElementoTabela[tamanho];
    tamanhoTabela = tamanho;

    for (int i = 0; i < tamanhoTabela; i++)
    {
        tabela[i].vazio = 1;
        tabela[i].dado = "";
        tabela[i].retirada = 0;
    }

    for (int i = 0; i < tamanhoOriginal; i++)
    {
        if (!tabela_original[i].vazio && !tabela_original[i].retirada)
        {
            Inserir(tabela_original[i].dado);
        }
    }

    tamanhoOriginal = tamanhoTabela;
    delete[] tabela_original;
}

void StringSet::Imprimir()
{

    std::cout << " { ";
    for (int i = 0; i < tamanhoTabela; i++)
    {
        if (tabela[i].vazio == 1)
        {
            continue;
        }
        std::cout << tabela[i].dado;
        if (i != tamanhoTabela - 1)
        {
            std::cout << ",";
        }
    }
    std::cout << "}" << std::endl;
};

string StringSet::ativar(string _id)
{
    std::string res = "Ponto de recarga ";
    res.append(_id);
    bool encontrado = false;

    if (!Pertence(_id))
        std::cerr << "Item nao pertence a HashTable. " << std::endl;
    int string_index = Hash(_id);
    int i = 0;
    while (i < tamanhoTabela && !tabela[(string_index + i) % tamanhoOriginal].vazio &&
           tabela[(string_index + i) % tamanhoOriginal].dado != _id)
    {
        i++;
    }
    int pos = (string_index + i) % tamanhoOriginal;

    if (tabela[pos].dado == _id && !tabela[pos].retirada)
    {
        encontrado = true;
        if (tabela[pos].status == 'A')
        {
            res.append(" já estava ativo.");
        }
        else
        {
            tabela[pos].status = 'A';
            res.append(" ativado.");
        }
    }
    if(encontrado == true)
    {
        return res;
    }
    else std::cerr<<"Nao existe estacao com o ID "<<_id<<std::endl;
}

string StringSet::desativar(string _id)
{
    std::string res = "Ponto de recarga ";
    res.append(_id);
    bool encontrado = false;


    if (!Pertence(_id))
        std::cerr << "Item nao pertence a HashTable. " << std::endl;
    int string_index = Hash(_id);
    int i = 0;
    while (i < tamanhoTabela && !tabela[(string_index + i) % tamanhoOriginal].vazio &&
           tabela[(string_index + i) % tamanhoOriginal].dado != _id)
    {
        i++;
    }

    int pos = (string_index + i) % tamanhoOriginal;

    if (tabela[pos].dado == _id && !tabela[pos].retirada)
    {
        bool encontrado = true;
        if (tabela[pos].status == 'D')
        {
            res.append(" já estava desativado.");
        }
        else
        {
            tabela[pos].status = 'D';
            res.append(" desativado.");
        }
    }
    if(encontrado == true)
    {
        return res;
    }
    else std::cerr<<"Nao existe estacao com ID "<<_id<<std::endl;
}
