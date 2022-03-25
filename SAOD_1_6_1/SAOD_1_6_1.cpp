#include <iostream>
#include <set>
#include <locale>
#include <ctime>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DBG_NEW new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define newDBG_NEW

using namespace std;

struct Node
{
    int key;
    int count;
    Node* left;
    Node* right;
};

Node *root, *pCur, *pTemp;

int CheckedInput(int begin, int end) // Ввод целочисленного значения с проверкой
{
    int choice;
    while (true)
    {
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Вводите данные корректно: ";
            continue;
        }
        cin.ignore(32767, '\n');
        if (choice < begin || choice > end)
        {
            cout << "Вводите данные корректно: ";
            continue;
        }
        break;
    }
    return choice;
}

int CheckedInput() // Ввод целочисленного значения с проверкой
{
    int choice;
    while (true)
    {
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Вводите данные корректно: ";
            continue;
        }
        cin.ignore(32767, '\n');
        break;
    }
    return choice;
}

void InitTree()
{
    root = nullptr;
}

bool isEmpty()
{
    if (root == nullptr)
    {
        return true;
    }
    return false;
}

void PrintNode(int info, int lvl) // вывод в консоль текущей вершины
{
    for (int i = 0; i < lvl * 5; i++)
    {
        cout << " ";
    }
    cout << info << "\n";
}

void PrintBack(Node* pCurr, int lvl) // обратно-симметрический проход
{
    if (pCurr != NULL)
    {
        PrintBack(pCurr->right, ++lvl); --lvl;
        PrintNode(pCurr->key, lvl);
        PrintBack(pCurr->left, ++lvl); --lvl;
    }
}

void PrintOrdered(Node* pCur)
{
    if (pCur != NULL)
    {
        PrintOrdered(pCur->left);
        cout << pCur->key << " (" << pCur->count << ")  ";
        PrintOrdered(pCur->right);
    }
}

Node* Search(int searchKey)
{
    pCur = root;
    bool stop = false;
    while (!stop)
    {
        if (pCur == nullptr) return nullptr;
            if (searchKey < pCur->key) pCur = pCur->left; else
                if (searchKey > pCur->key) pCur = pCur->right; else
                    return pCur;
    }
}

void AddRecur(Node*& pCur, int newKey)
{
    if (pCur == nullptr)
    {
        pCur = new Node();
        pCur->key = newKey;
        pCur->left = nullptr; pCur->right = nullptr;
        pCur->count = 1;
    }
    else
        if (newKey < pCur->key) AddRecur(pCur->left, newKey); else
            if (newKey > pCur->key) AddRecur(pCur->right, newKey); else
                pCur->count++;
}

void AddNonRecur(int newKey)
{
    if (root == nullptr)
    {
        root = new Node(); root->left = nullptr; root->right = nullptr;
        root->key = newKey; root->count = 1;
    }
    else
    {
        pCur = root;
        while (pCur != nullptr)
        {
            pTemp = pCur;
            if (newKey < pCur->key) pCur = pCur->left; 
            else
                if (newKey > pCur->key) pCur = pCur->right; 
                else
                {
                    pCur->count++;
                    pCur = nullptr;
                }       
        }
        
        if (newKey < pTemp->key)
        {
            pCur = new Node();
            pCur->key = newKey; pCur->count = 1; pCur->left = pCur->right = nullptr;
            pTemp->left = pCur;
        }
        else if (newKey > pTemp->key)
        {
            pCur = new Node();
            pCur->key = newKey; pCur->count = 1; pCur->left = pCur->right = nullptr;
            pTemp->right = pCur;
        }
    }
}

void Changer(Node*& p)
{
    if (p->right != nullptr) { Changer(p->right); }
    else
    {
        pTemp->key = p->key;
        pTemp = p;
        p = p->left;
    }
}

void DeleteNode(Node*& pCur, int newKey)
{
    if (pCur == nullptr)
    {
        cout << "Удаляемой вершины нет в дереве";
    }
    else
    {
        if (newKey < pCur->key) { DeleteNode(pCur->left, newKey); }
        else if (newKey > pCur->key) { DeleteNode(pCur->right, newKey); }
        else
        {
            pTemp = pCur;
            if (pTemp->right == nullptr) { pCur = pTemp->left; }
            else if (pTemp->left == nullptr) { pCur = pTemp->right; }
            else { Changer(pCur->left); }
            delete pTemp;
        }
    }
}

void DeleteAll(Node* pTemp) // рекурсивная функция освобождения памяти
{
    if (pTemp != NULL)
    {
        DeleteAll(pTemp->left);
        DeleteAll(pTemp->right);
        delete pTemp;
    }
}

void CallMenu()
{
    bool work = true;
    int choice;
    while (work)
    {
        cout << "Выбор действия:\n1 - Создание дерева с заданным числом вершин и со случайными ключами\n2 - Поиск вершины с заданным значением ключа\n3 - Добавление новой вершины с помощью рекурсивной функции\n";
        cout << "4 - Добавление новой вершины с помощью нерукерсивной программы\n5 - Вывод дерева в обратно-симметричном порядке\n6 - Вывод всех вершин в одну строку по порядку следования ключей (с счётчиками)\n";
        cout << "7 - Удаление вершины\n8 - Завершение работы\n";
        cout << "Действие: "; choice = CheckedInput(1, 8);
        switch (choice)
        {
            int serviceInt;
        case 1:
            if (!isEmpty())
            {
                cout << "Дерево уже создано.\n\n"; break;
            }
            cout << "Введите число новых вершин(до 20): "; serviceInt = CheckedInput(1, 20);
            for (int i = 0; i < serviceInt; i++)
            {
                int key = rand() % 100;
                AddRecur(root, key);
            }
            cout << "\n\n";
            break;
        case 2:
            cout << "Введите значение ключа: "; pTemp = Search(CheckedInput());
            if (pTemp == nullptr)
            {
                cout << "Заданного элемента не найдено.";
            }
            else
            {
                cout << "Заданный элемент найден. Счётчик: " << pTemp->count;
            }
            cout << "\n\n";
            break;
        case 3:
            cout << "Введите значение добавляемого ключа: "; serviceInt = CheckedInput();
            AddRecur(root,serviceInt);
            cout << "\n\n";
            break;
        case 4:
            cout << "Введите значение добавляемого ключа: "; serviceInt = CheckedInput();
            AddNonRecur(serviceInt);
            cout << "\n\n";
            break;
        case 5:
            if (isEmpty())
            {
                cout << "Дерево пустое.\n\n"; break;
            }
            cout << "Дерево: \n";
            PrintBack(root,0);
            cout << "\n\n";
            break;
        case 6:
            if (isEmpty())
            {
                cout << "Дерево пустое.\n\n"; break;
            }
            cout << "Упорядоченная строка вершин: ";
            PrintOrdered(root);
            cout << "\n\n";
            break;
        case 7:
            if (isEmpty())
            {
                cout << "Дерево пустое.Удалять нечего.\n\n"; break;
            }
            cout << "Введите ключ удаляемой вершины: "; serviceInt = CheckedInput();
            DeleteNode(root, serviceInt);
            cout << "\n\n";
            break;
        case 8:
            DeleteAll(root);
            work = false;
            break;
        default:
            break;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "RUS");
    srand(time(NULL));
    InitTree();
    CallMenu();
    _CrtDumpMemoryLeaks();
}