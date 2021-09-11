#include <iostream>
#include <fstream>
#include <math.h>
#include <queue>
using namespace std;

struct node
{
    int codigo;
    struct node *left, *right;
};

void lerNumeroN(int *n)
{
    cout << "\n Informe o valor : ";
    cin >> *n;
}

int menor(node *arvore)
{
    if (arvore == NULL)
    {
        cout << "\n Arvore vazia " << endl;
        return 0;
    }
    else if (arvore->left == NULL)
        cout << "\nMenor : " << arvore->codigo << endl;
    else
        return menor(arvore->left);
}

int maior(node *arvore)
{
    if (arvore == NULL)
    {
        cout << "\n Arvore vazia" << endl;
        return 0;
    }
    else if (arvore->right == NULL)
        cout << "\nMaior : " << arvore->codigo << endl;
    else
        return maior(arvore->right);
}

void posordem(node *arvore)
{
    if (arvore != NULL)
    {
        posordem(arvore->left);
        posordem(arvore->right);
        cout << " " << arvore->codigo;
    }
}

void emordem(node *arvore)
{
    if (arvore != NULL)
    {
        emordem(arvore->left);
        cout << " " << arvore->codigo;
        posordem(arvore->right);
    }
}

void preordem(node *arvore)
{
    if (arvore != NULL)
    {
        cout << " " << arvore->codigo;
        preordem(arvore->left);
        preordem(arvore->right);
    }
}

int qtdnode(node *arvore)
{
    if (arvore == NULL)
        return 0;
    return (1 + qtdnode(arvore->left) + qtdnode(arvore->right));
}

int sumnode(node *arvore)
{
    if (arvore == NULL)
        return 0;
    return (arvore->codigo + sumnode(arvore->left) + sumnode(arvore->right));
}

void crescente(node *arvore)
{
    if (arvore != NULL)
    {
        crescente(arvore->left);
        cout << " " << arvore->codigo;
        crescente(arvore->right);
    }
}

void decrescente(node *arvore)
{
    if (arvore != NULL)
    {
        decrescente(arvore->right);
        cout << " " << arvore->codigo;
        decrescente(arvore->left);
    }
}

float media(node *arvore)
{
    if (arvore == NULL)
        return 0;

    float sum = sumnode(arvore);
    float amount = qtdnode(arvore);
    float avg = (sum / amount);
    return avg;
}

int altura(node *arvore)
{

    if (arvore == NULL)
        return 0;

    int a_dir, a_esq;

    a_dir = altura(arvore->right);
    a_esq = altura(arvore->left);

    if (a_dir > a_esq)
        return a_dir + 1;

    return a_esq + 1;
}



bool consulta(int n, node *arvore)
{
    if (arvore == NULL)
        return false;
    else if (arvore->codigo == n)
        return true;
    else if (n < arvore->codigo)
        return consulta(n, arvore->left);
    else if (n > arvore->codigo)
        return consulta(n, arvore->right);
    return false;
}

int delete1(node **raiz)
{
    if ((*raiz)->right != NULL)
        return (delete1(&(*raiz)->right));
    else
    {
        int n = (*raiz)->codigo;
        node *lixo = (*raiz);
        free(lixo);
        (*raiz) = (*raiz)->left;
        return n;
    }
}

int remocao(node **arvore, int n)
{

    if ((*arvore) != NULL)
    {
        if ((*arvore)->codigo == n)
        {
            if ((*arvore)->left == NULL)
            {
                node *lixo = (*arvore);
                free(lixo);
                (*arvore) = (*arvore)->right;
            }
            else if ((*arvore)->right == NULL)
            {
                node *lixo = (*arvore);
                free(lixo);
                (*arvore) = (*arvore)->left;
            }
            else
                (*arvore)->codigo = delete1(&(*arvore)->left);
        }
        else if (n > (*arvore)->codigo)
            remocao(&(*arvore)->right, n);
        else if (n < (*arvore)->codigo)
            remocao(&(*arvore)->left, n);
    }
}



int valores(node *arvore)
{
    if (arvore == NULL)
        return 0;

    else if (arvore->codigo % 2 == 0)
        return 1 + valores(arvore->left) + valores(arvore->right);

    else
        return valores(arvore->left) + valores(arvore->right);
}

int multiplos(node *arvore, int k)
{
    if (arvore == NULL)
        return 0;

    else if (arvore->codigo % k == 0)
    {
        cout << "\n Multiplos de " << k << "-> " << arvore->codigo;
        return 1 + multiplos(arvore->left, k) + multiplos(arvore->right, k);
    }
    else
        return multiplos(arvore->left, k) + multiplos(arvore->right, k);
}

void insere(int n, node **arvore)
{
    if ((*arvore) == NULL)
    {
        (*arvore) = (node *)malloc(sizeof(node));
        if ((*arvore) == NULL)
            cout << "\n Heap Overflow" << endl;

        (*arvore)->codigo = n;
        (*arvore)->left = (*arvore)->right = NULL;
    }
    else if (n < (*arvore)->codigo)
        insere(n, &(*arvore)->left);
    else if (n > (*arvore)->codigo)
        insere(n, &(*arvore)->right);
    else
        cout << "\n Elemento ja existe ! " << endl;
}

int folhas(node *arvore)
{
    if (arvore == NULL)
        return 0;

    else if (arvore->left == NULL && arvore->right == NULL)
        return 1 + folhas(arvore->left) + folhas(arvore->right);
    else
        return folhas(arvore->left) + folhas(arvore->right);
}

int umfilho(node *arvore)
{
    if (arvore == NULL)
        return 0;

    if (arvore->left == NULL && arvore->right != NULL)
        return 1 + umfilho(arvore->left) + umfilho(arvore->right);

    if (arvore->left != NULL && arvore->right == NULL)
        return 1 + umfilho(arvore->left) + umfilho(arvore->right);
    else
        return umfilho(arvore->left) + umfilho(arvore->right);
}

int doisfilho(node *arvore)
{
    if (arvore == NULL)
        return 0;

    if (arvore->left != NULL && arvore->right != NULL)
        return 1 + doisfilho(arvore->left) + doisfilho(arvore->right);
    else
        return doisfilho(arvore->left) + doisfilho(arvore->right);
}

int desviopadrao(node *arvore, float media1, float qtd1)
{
    if (arvore == NULL)
        return 0;

    cout << " " << sqrt(pow((arvore->codigo - media1), 2)) / qtd1;
    return desviopadrao(arvore->left, media1, qtd1) + desviopadrao(arvore->right, media1, qtd1);
}

int largura(node *arvore)
{
    if (arvore == NULL)
        return 0;

    queue<node *> Q;
    Q.push(arvore);

    cout << "\n Percurso Largura:" << endl;

    while (!Q.empty())
    {
        node *dado = Q.front();
        cout << dado->codigo << " ";
        if (dado->left != NULL)
            Q.push(dado->left);
        if (dado->right != NULL)
            Q.push(dado->right);
        Q.pop();
    }
}

void esvaziar(node **arvore)
{
    if (*arvore != NULL)
    {
        esvaziar(&(*arvore)->left);
        esvaziar(&(*arvore)->right);
        free(*arvore);
        (*arvore) = NULL;
    }
}

void printarArvores(node *arvore2, node *arvore3)
{
    cout << "\n 1 Arvore gerada :" << endl;

    if (arvore2 != NULL)
    {
        crescente(arvore2->left);
        cout << " " << arvore2->codigo;
        crescente(arvore2->right);
    }

    cout << "\n\n 2 Arvore gerada :" << endl;

    if (arvore3 != NULL)
    {
        crescente(arvore3->left);
        cout << " " << arvore3->codigo;
        crescente(arvore3->right);
        cout << endl;
    }
}

bool comparaEstrutura(node *arvore2, node *arvore3)
{
    if (arvore2 == NULL && arvore3 == NULL)
        return true;
    if ((arvore2 == NULL) || (arvore3 == NULL))
        return false;

    return (comparaEstrutura(arvore2->left, arvore3->left)) && comparaEstrutura(arvore2->right, arvore3->right);
}

bool comparaValores(node *arvore2, node *arvore3)
{
    if (arvore2 == NULL && arvore3 == NULL)
        return true;

    if ((arvore2 == NULL) || (arvore3 == NULL))
        return false;

    if (arvore2->codigo != arvore3->codigo)
        return false;

    return (comparaValores(arvore2->left, arvore3->left)) && comparaValores(arvore2->right, arvore3->right);
}

node *arvore2 = NULL, *arvore3 = NULL;
int gerar()
{
    if (arvore2 != NULL)
    {
        cout << "\n Arvore 3 foi esvaziada com Sucesso!";
        esvaziar(&arvore2);
    }

    if (arvore3 != NULL)
    {
        cout << "\n Arvore 2 foi esvaziada  com Sucesso!";
        esvaziar(&arvore3);
    }

    int qtd_arvore2 = rand() % 11;
    int qtd_arvore3 = rand() % 11;

    for (int i = 0; i < qtd_arvore2; i++)
    {
        int x = rand() % 199;
        insere(x, &arvore2);
    }
    for (int i = 0; i < qtd_arvore3; i++)
    {
        int x = rand() % 199;
        insere(x, &arvore3);
    }
    cout << "\n Novas Arvores gerada com Sucesso!" << endl;
}

void pre_save1(node *arvore, FILE *arq)
{
    if (arvore != NULL)
    {
        fprintf(arq, "%d ", arvore->codigo);
        pre_save1(arvore->left, arq);
        pre_save1(arvore->right, arq);
    }
}

int verificaArvores()
{
    cout << "\n As duas arvores sao :" << endl;
    printarArvores(arvore2, arvore3);
    int backtree = comparaValores(arvore2, arvore3);
    int backtree2 = comparaEstrutura(arvore2, arvore3);

    if (backtree)
        cout << "\n (1)- Valores das arvores iguais" << endl;
    else
        cout << "\n (2)- Valores diferentes" << endl;
    if (backtree2)
        cout << "\n (3)- Estruturas iguais " << endl;
    else
        cout << "\n (4)- Estruturas diferentes" << endl;
    if (backtree && backtree2)
        cout << "\n (5)- Arvores completamente iguais " << endl;
    if (!backtree && !backtree2)
        cout << "\n (6)- Arvores completamente diferentes " << endl;
}


int main()
{
    int opcao, n, retorno = 0, select = 0, nulas = 0;
    ifstream arquivo("NodeArvore.txt");

    node *arvores[30];

    for (int i = 0; i < 30; i++)
        arvores[i] = NULL;

    do
    {
        cout << "\n (1) Insere \n (2) Consulta \n (3) Maior \n (4) Menor";
        cout << "\n (5) Preordem \n (6) Posordem \n (7) Em ordem \n (8) Total de nos";
        cout << "\n (9) Crescente \n (10) Decrescente \n (11) soma dos nos \n (12) Altura \n (13) Media";
        cout << "\n (14) Percurso Largura \n (15) Remocao \n (16) Pares e impares \n (17) Multiplos de K";
        cout << "\n (18) Desvio padrao \n (19) Quantidade folhas \n (20) nos 2 filhos \n (21) um filho";
        cout << "\n (22) Total subarvores null  \n (23) Salver arvore no arquivo  \n (24) Recuperar do arquivo";
        cout << "\n (25) Gerar novas 2 arvores aleatorias \n (26) Imprimir arvores geradas \n (27) Comparar arvores geradas";
        cout << "\n (28) Esvaziar arvore \n (29) Trocar arvores ";

        nulas = 0;

        for (int i = 0; i < 30; i++)
        {
            if (arvores[i] == NULL)
                nulas++;
        }

        cout << "\n\n\n INFORMACOES:";
        cout << "\n --  Arvores disponiveis : [0,29]";
        cout << "\n --  Arvore usada no momento : " << select;
        cout << "\n --  Arvores  nulas : " << nulas << endl;
        cout << " --  Arvores inicializadas " << 30 - nulas << endl;
        cout << "\n Informe sua opcao :";
        cin >> opcao;

        switch (opcao)
        {
        case 1:
            lerNumeroN(&n);
            insere(n, &arvores[select]);
            break;
        case 2:
            lerNumeroN(&n);
            retorno = consulta(n, arvores[select]);
            if (!retorno)
                cout << "\n Nada encontrado" << endl;
            else
                cout << "\n Elemento encontrado" << endl;
            break;
        case 3:
            maior(arvores[select]);
            break;
        case 4:
            menor(arvores[select]);
            break;
        case 5:
            preordem(arvores[select]);
            break;
        case 6:
            posordem(arvores[select]);
            break;
        case 7:
            emordem(arvores[select]);
            break;
        case 8:
            retorno = qtdnode(arvores[select]);
            cout << "\n O total de nos na arvore: " << retorno;
            break;
        case 9:
            crescente(arvores[select]);
            break;
        case 10:
            decrescente(arvores[select]);
            break;
        case 11:
            retorno = sumnode(arvores[select]);
            cout << "\n A soma dos nodes : " << retorno;
            break;
        case 12:
            retorno = altura(arvores[select]);
            cout << "\n A altura da arvore : " << retorno;
            break;
        case 13:
            retorno = media(arvores[select]);
            cout << "\n Media dos elementos na arvore : " << retorno;
            break;
        case 14:
            largura(arvores[select]);
            break;
        case 15:
            lerNumeroN(&n);
            remocao(&arvores[select], n);
            break;
        case 16:
            retorno = valores(arvores[select]);
            n = qtdnode(arvores[select]);
            cout << "\n O numero de pares : " << retorno;
            cout << "\n Quantidade de impares " << n - retorno;
            break;
        case 17:
            lerNumeroN(&n);
            retorno = multiplos(arvores[select], n);
            cout << "\n O numero de multiplos : " << retorno;
            break;
        case 18:
            float media1, qtd1;
            media1 = media(arvores[select]), qtd1 = qtdnode(arvores[select]);
            cout << "\n valores dos nos :" << endl;
            crescente(arvores[select]);
            cout << "\n Desvio padrao dos nos : " << endl;
            desviopadrao(arvores[select], media1, qtd1);
            break;
        case 19:
            retorno = folhas(arvores[select]);
            cout << "\n Quantidade de folhas : " << retorno;
            break;
        case 20:
            retorno = doisfilho(arvores[select]);
            cout << "\n Quantidade de nos com 2 filho :" << retorno;
            break;
        case 21:
            retorno = umfilho(arvores[select]);
            cout << "\n Quantidade de nos com um filho :" << retorno;
            break;
        case 22:
            int null;
            null = qtdnode(arvores[select]);
            cout << "\n Total de subarvores Null:  " << null + 1;
            break;
        case 23:
            FILE *arq;
            arq = fopen("NodeArvore.txt", "w+");
            pre_save1(arvores[select], arq);
            fclose(arq);
            cout << "\n Arquivo salvo..." << endl;
            break;
        case 24:
            if (arvores[select] != NULL)
            {
                cout << "\n Esvaziando arvore para inserir dados do arquivo" << endl;
                esvaziar(&arvores[select]);
            }
            int dado;
            if (arquivo)
            {
                while (arquivo >> dado)
                    insere(dado, &arvores[select]);
            }
            arquivo.close();
            cout << "\n Arquivos recuperados com Sucesso inseridos na arvore!" << endl;
            break;
        case 25:
            gerar();
            break;
        case 26:
            printarArvores(arvore2, arvore3);
            break;
        case 27:
            verificaArvores();
            break;
        case 28:
            esvaziar(&arvores[select]);
            cout << "\n Arvore esvaziada com Sucesso" << endl;
            break;
        case 29:
            do
            {
                cout << "\n Informe a arvore que vc quer trocar [0,29]:";
                cin >> select;
            } while (select < 0 || select > 29);
            arvores[select];
        }
    } while (opcao != 0);
}