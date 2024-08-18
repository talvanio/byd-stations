#include "./../include/heap.hpp"


void swap(int posicao1, int posicao2,ptr_knn_t data)
{
    knn_t temp = data[posicao2];
    data[posicao2] = data[posicao1];
    data[posicao1] = temp;
}

Heap::Heap(int maxsize)
{
    this->tamanho = 0;
    this->data = new knn_t[maxsize];
}

Heap::~Heap()
{
    delete[] data;
}

int Heap::GetAncestral(int posicao)
{
    if ((posicao - 1) / 2 < 0)
    {
        return -1;
    }
    return (posicao - 1) / 2;
}

int Heap::GetSucessorEsq(int posicao)
{
    if (posicao * 2 + 1 >= this->tamanho) 
    {
        return -1;
    }
    return posicao * 2 + 1;
}

int Heap::GetSucessorDir(int posicao)
{
    if (posicao * 2 + 2 >= this->tamanho)
        return -1;
    return posicao * 2 + 2;
}

void Heap::Inserir(knn_t x)
{
    data[this->tamanho] = x;
    tamanho++;
    this->HeapifyPorBaixo(this->tamanho - 1);
}

knn_t Heap::Remover()
{
    if (Vazio())
    {
        std::cerr<<"Heap vazio.";
    }
    knn_t item = this->data[0];
    this->data[0] = this->data[this->tamanho - 1];
    this->tamanho--;
    this->HeapifyPorCima(0);
    return item;
};

bool Heap::Vazio()
{
    return (this->tamanho == 0);
}

void Heap::HeapifyPorBaixo(int posicao)
{
    while (posicao > 0 && data[posicao].dist < data[(posicao - 1) / 2].dist)
    {
        swap(posicao, (posicao - 1) / 2,this->data);
        posicao = (posicao-1) / 2;
    }
}

void Heap::HeapifyPorCima(int posicao)
{
    while (2 * posicao + 1 < tamanho)
    {
        // Encontrando o menor filho para garantir a comparação do item com os dois filhos.
        int IndexDoMenorFilho = posicao * 2 + 1;

        if (IndexDoMenorFilho + 1 < tamanho && GetSucessorDir(posicao) < GetSucessorEsq(posicao))
        {
            IndexDoMenorFilho = posicao * 2 + 2;
        }
        // Item é menor do que seus filhos (Está no local correto):
        if (data[posicao].dist < data[IndexDoMenorFilho].dist)
        {
            break;
        }
        // Item não está no local correto:
        else
        {
            swap(posicao, IndexDoMenorFilho,this->data);
        }
        posicao = IndexDoMenorFilho;
    }
};

