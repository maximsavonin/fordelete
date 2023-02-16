#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool chek(string str)
{
    string a = "({[]})";
    int b[6];
    for (int i = 0; i < 6; i++) b[i] = 0;
    for (int i = 0; i < str.size(); i++) b[a.find(str[i])]++;
    return b[0] == b[5] and b[1] == b[4] and b[2] == b[3];
}

void stackPrint(vector<int> a)
{
    for (int i = a.size() - 1; i >= 0; i--)
        cout << a[i] << (i == 0 ? " ": "");
}

int main()
{
    string str;
    int n;
    vector<int> chi;
    for (;;)
    {
        /*cin >> str;
        cout << chek(str);*/
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            int a;
            cin >> a;
            chi.push_back(a);
        }
        stackPrint(chi);
    }
    return 0;
}