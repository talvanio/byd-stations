#include <bits/stdc++.h>
#include <stdexcept>
#include "../include/Set.hpp"
using namespace std;

ElementoTabela::ElementoTabela()
    : dado(""), status('A'), vazio(1), retirada(0) {};

StringSet::StringSet(int tamanho)
    : tamanhoTabela(tamanho), tamanhoConjunto(0), tabela(new ElementoTabela[tamanho])
{
    for (int i = 0; i < tamanho; i++)
    {
        tabela[i] = ElementoTabela();
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
        std::cerr << "Tabela hash cheia.";
        return;
    }

    int i = 0;
    int string_index = Hash(s);

    while (i < tamanhoTabela && !tabela[(string_index + i) % tamanhoTabela].vazio && !tabela[(string_index + i) % tamanhoTabela].retirada)
    {
        i++;
    }

    if (i < tamanhoTabela)
    {
        tabela[(string_index + i) % tamanhoTabela].vazio = 0;
        tabela[(string_index + i) % tamanhoTabela].dado = s;
        tabela[(string_index + i) % tamanhoTabela].retirada = 0;
        tamanhoConjunto++;
    }
}

void StringSet::Remover(string s)
{
    int string_index = Hash(s);
    int i = 0;

    while (i < tamanhoTabela && !tabela[(string_index + i) % tamanhoTabela].vazio &&
           tabela[(string_index + i) % tamanhoTabela].dado != s)
    {
        i++;
    }

    if (tabela[(string_index + i) % tamanhoTabela].dado == s && !tabela[(string_index + i) % tamanhoTabela].retirada)
    {
        tabela[(string_index + i) % tamanhoTabela].vazio = 1;
        tabela[(string_index + i) % tamanhoTabela].retirada = 1;

        tamanhoConjunto--;

        // Rehash dos itens seguintes para manter a integridade da tabela
        i++;
        while (!tabela[(string_index + i) % tamanhoTabela].vazio)
        {
            Rehash((string_index + i) % tamanhoTabela);
            i++;
        }
    }
};

bool StringSet::Pertence(string s)
{
    int i = 0;
    int string_index = Hash(s);

    while (i < tamanhoTabela && !tabela[(string_index + i) % tamanhoTabela].vazio &&
           tabela[(string_index + i) % tamanhoTabela].dado != s)
    {
        i++;
    }

    if (tabela[(string_index + i) % tamanhoTabela].dado == s && !tabela[(string_index + i) % tamanhoTabela].retirada)
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

    for (size_t i = 0; i < s.length(); i++)
    {
        str_total_value += s[i] * i;
    }
    return str_total_value % tamanhoTabela;
};

void StringSet::Rehash(int pos)
{
    char status = tabela[pos].status;
    if (tabela[pos].vazio)
        return;

    string s = tabela[pos].dado;
    tabela[pos].dado = "";
    tabela[pos].vazio = 1;
    tabela[pos].retirada = 0;
    tamanhoConjunto--;

    Inserir(s);
    if (status == 'D')
    {
        desativar(s);
    }
};

ElementoTabela StringSet::getElement(string id)
{
    try
    {
        if (!Pertence(id))
        {
            throw std::runtime_error("Esse elemento nao está na tabela.");
        }
        else
        {
            int i=0;

            int string_index = Hash(id);
            while (i < tamanhoTabela && !tabela[(string_index + i) % tamanhoTabela].vazio &&
                   tabela[(string_index + i) % tamanhoTabela].dado != id)
            {
                i++;
            }
            int pos = (string_index + i) % tamanhoTabela;

            if (tabela[pos].dado == id && !tabela[pos].retirada)
            {
                return tabela[pos];
            }
            else
            {
                throw std::runtime_error("Erro de logica: a tabela nao encontrou o elemento.");
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
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

    if (!Pertence(_id))
        return "Item nao pertence a HashTable. \n";
    int string_index = Hash(_id);
    int i = 0;
    while (i < tamanhoTabela && !tabela[(string_index + i) % tamanhoTabela].vazio &&
           tabela[(string_index + i) % tamanhoTabela].dado != _id)
    {
        i++;
    }
    int pos = (string_index + i) % tamanhoTabela;

    if (tabela[pos].dado == _id && !tabela[pos].retirada)
    {
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
    return res;
}

string StringSet::desativar(string _id)
{
    std::string res = "Ponto de recarga ";
    res.append(_id);

    if (!Pertence(_id))
        return "Item nao pertence a HashTable.\n ";
    int string_index = Hash(_id);
    int i = 0;
    while (i < tamanhoTabela && !tabela[(string_index + i) % tamanhoTabela].vazio &&
           tabela[(string_index + i) % tamanhoTabela].dado != _id)
    {
        i++;
    }

    int pos = (string_index + i) % tamanhoTabela;
    if (tabela[pos].dado == _id && !tabela[pos].retirada)
    {
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
    return res;
}