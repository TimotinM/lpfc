#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;


int p; // nr productii;
// e=epsilon,lambda,alfa;
struct cstr
{
    char c{};
    string s;

};

string neterm;
string term;
unordered_map <char, vector <string>> gramatica;
deque<char>nullables;
vector<cstr>nullfixneed;
vector<char> units;
vector<char> termrpl;
vector<string> added;
vector<cstr>::iterator nf;
unordered_map < char, vector<string>>::iterator iterz;
int istop, r_m, r_i, r_t;

int isNeterm(char X)
{
    for (char i : neterm)
    {
        if (i == X)
            return 1;

    }
    return 0;
}

int isTerm(char X)
{
    for (char i : term)
    {
        if (i == X)
            return 1;

    }
    return 0;
}

int isValidRhs(const string& rhs)
{
    int flag=0;
    for (char rh : rhs)
    {
        if (isNeterm(rh) || isTerm(rh))
            flag = 1;
        else
        {
            flag = 0;
            break;
        }

    }
    return flag;
}

void addrule(char X, const string& rhs)
{

    gramatica[X].push_back(rhs);
}
void read()
{
    char X;
    string rhs;
    cin >> p;
    cin >> term;
    cin >> neterm;
    for (int i = 0; i < p; i++)
    {
        cin >> X >> rhs;
        if (isTerm(X) && isValidRhs(rhs))
            addrule(X, rhs);

    }
}

void print()
{
    std::unordered_map <char, vector <string>>::iterator it;
    for (it = gramatica.begin(); it != gramatica.end(); ++it)
    {
        cout << it->first << ": ";
        for (auto & i : it->second)
            cout << i << "|";
        cout << endl;
    }
}
int IsInNullables(char X)
{
    for (char nullable : nullables)
        if (nullable == X) return 1;

    return 0;
}
int IsInNullfix(const cstr& arg)
{
    for (auto & i : nullfixneed)
        if (i.c == arg.c && i.s==arg.s) return 1;

    return 0;

}
int IsInUnits(char X)
{
    for (char unit : units)
        if (unit == X) return 1;

    return 0;

}
void isNullable()
{
    unordered_map <char, vector <string>>::iterator it;
    for (it = gramatica.begin(); it != gramatica.end(); ++it)
    {
        for (auto i = it->second.begin(); i != it->second.end(); ++i)
            if ((*i) == "e")
            {
                cout << "regula cu lambda: ";
                cout << it->first << "->" << *i << endl;
                nullables.push_back(it->first);
                break;

            }
    }

}

bool Isnullable(char c)
{
    if (IsInNullables(c)) return true;
    return false;
}

int IsinRule(char c, const string& s)
{
    unordered_map <char, vector <string>>::iterator tp;
    tp=gramatica.find(c);
    if (tp == gramatica.end()) return 0;
    for (auto & i : tp->second)
        if (i == s) return 1;
    return 0;

}

void spargestring(cstr param)
{
    string str1;

    str1 = param.s;
    for (unsigned int i = 0; param.s[i] != 0; ++i)
    {
        if (IsInNullables(param.s[i]))
        {

            param.s.erase(i, 1);
            if (param.s.empty())
                addrule(param.c, "e");
            else
            if (!(IsinRule(param.c,param.s)))
                addrule(param.c, param.s);
        }
        param.s=str1;
    }
    param.s.erase(remove_if(param.s.begin(), param.s.end(), &Isnullable), param.s.end());
    if ( !(param.s.size() == 1 && param.s[0] == (param.c)) )
        if (!param.s.empty())
            if ( !(IsinRule(param.c, param.s)) )
                addrule(param.c, param.s);
}

void erules()
{


    char c;
    isNullable();

    do
    {
        cout << endl;
        unordered_map <char, vector <string>>::iterator it;
        for (it = gramatica.begin(); it != gramatica.end(); ++it)
        {
            vector<char>::iterator();

            for (auto i = it->second.begin(); i != it->second.end(); ++i)
            {

                string::iterator s;
                for (s = (*i).begin(); s != (*i).end(); ++s)
                {
                    c = (*s);
                    cstr tmp;
                    tmp.c = it->first;
                    tmp.s = *i;

                    if (IsInNullables(c))
                    {
                        if (!IsInNullfix(tmp))
                        {
                            cstr cs;
                            cs.c = it->first;
                            cs.s = *i;
                            nullfixneed.push_back(cs);
                        }

                    }
                }

            }
        }

        for (nf = nullfixneed.begin(); nf != nullfixneed.end(); ++nf)
        {
            cstr tmp1;
            tmp1.c = nf->c;
            tmp1.s = nf->s;
            spargestring(tmp1);

        }

       unordered_map<char, vector<string>>::iterator de;
        for (char & nullable : nullables)
        {

            de = gramatica.find(nullable);
            for (auto it = de->second.begin(); it != de->second.end(); ++it)
            {
                if ((*it) == "e")
                {
                    de->second.erase(it);
                    break;
                }
            }

        }
        nullables.pop_front();
        isNullable();
        cout<<"sd";
    } while (!nullables.empty());

}

void unitrulez()
{
    string c;
    unordered_map <char, vector <string>>::iterator it, is;
    for (it=gramatica.begin(); it != gramatica.end(); ++it)
    {

        if (it->second.size() == 1 && it->second[0].size()==1 && isTerm((it->second[0])[0]))
        {
            units.push_back(it->first);
            c = it->second[0]; // ='C'

            iterz = gramatica.find(c[0]);
            for (vector<string>::size_type i = 0; i != iterz->second.size(); ++i)
                if (!iterz->second[i].empty())
                    addrule(it->first, iterz->second[i]);

        }
        else
        {

            for (vector<string>::size_type i = 0; i != it->second.size(); ++i)
            {
                if ((it->second)[i].size() == 1 && isTerm((it->second[i])[0]))
                {
                    if (!IsInUnits(it->first))
                        units.push_back(it->first);
                    c = (it->second[i]);

                    iterz = gramatica.find(c[0]);
                    istop = iterz->second.size();
                    for (vector<string>::size_type i = 0; i < iterz->second.size() && !IsinRule(it->first,iterz->second[i]); ++i)
                    {
                        if (iterz->second[i].size() > 1)
                            addrule(it->first, iterz->second[i]);
                        if (iterz->second[i].size() == 1 && !isTerm(iterz->second[i][0]))
                            addrule(it->first, iterz->second[i]);
                    }
                }

            }
        }

    }
    for (char & unit : units)
    {
        unordered_map<char, vector<string>>::iterator f;

        f=gramatica.find(unit);
        for (int i = 1; i <= 3; i++)
        {
            for (auto it = f->second.begin(); it != f->second.end(); ++it)
            {
                if ((*it).size() == 1 && isTerm((*it)[0]))
                {
                    f->second.erase(it);
                    break;
                }
            }
        }
    }

}

int isintermrpl(char X)
{
    for (vector<char>::size_type i = 0; i != termrpl.size();++i)
        if (termrpl[i] == X) return 1;
    return 0;
}

void replace()
{
    unordered_map <char, vector <string>>::iterator it, is;
    for (it = gramatica.begin(); it != gramatica.end(); ++it)
    {

        for (vector<string>::size_type i = 0; i != it->second.size(); ++i)
        {
            if (it->second[i].size() == 4)
            {
                string cm = "123456789";
                string rp, r;

                rp.push_back(cm[r_m]);

                r.append(it->second[i], 1, 3);
                added.push_back(r);
                it->second[i].replace(1, 3, rp);
                addrule(cm[r_m], r);
                r_m++;
            }
        }
    }

    for (it = gramatica.begin(); it != gramatica.end(); ++it)
    {
        for (vector<string>::size_type i = 0; i != it->second.size(); ++i)
        {
            if (it->second[i].size() == 3)
            {
                string a_to_z = "5!@#$%";
                string repl;
                string r;
                r.append(it->second[i], 1, 2);
                repl.push_back(a_to_z[r_i]);
                addrule(a_to_z[r_i], r);
                it->second[i].replace(1, 2, repl);
                r_i++;
            }
        }
        cout << endl;
    }
    for (it = gramatica.begin(); it != gramatica.end(); ++it)
    {
        for (vector<string>::size_type i = 0; i != it->second.size(); ++i)
        {
            for (string::size_type j = 0; j != it->second[i].size();++j)
            {

                if (isNeterm((it->second[i])[j]) && !it->second[i].empty() )
                {
                    if ( !isintermrpl((it->second[i])[j]) )
                        termrpl.push_back((it->second[i])[j]);
                }
            }
        }
    }


    for (vector<char>::size_type  r= 0; r != termrpl.size(); ++r)
    {
        string a_to_z = "6789^&*{}";
        string repl;
        r_t++;
        string t;
        t = termrpl[r];
        repl.push_back(a_to_z[r_t]);

        for (it = gramatica.begin(); it != gramatica.end(); ++it)
        {
            for (vector<string>::size_type i = 0; i != it->second.size(); ++i)
            {
                for (string::size_type j = 0; j != it->second[i].size(); ++j)
                {

                    if ((it->second[i])[j]==termrpl[r])
                    {
                        if ((it->second[i]).size()> 1)
                        {
                            string s;
                            s.push_back(termrpl[r]);
                            it->second[i].replace(it->second[i].find(s), it->second[i].find(s) + 1, repl);
                        }
                    }


                }
            }
        }
        addrule(repl[0], t);
    }


}


int main(int argc, char* argv[])
{
    read();
    erules();
    unitrulez();
    replace();
    print();
    return 0;
}
