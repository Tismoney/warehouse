#include "Math.h"
#include "Tree.h"

Math::Math()
{
    str = string();
}

void Math::PutStr(string st)
{
    str = st;
    S = str.begin();
}

string Math::GetEquation()
{
    ifstream File;
    File.open ("exp.txt");
    if (File.is_open()) printf("File is open\n");
    getline(File, str);
    cout << str << endl;
    File.close();
    return str;
}

string Math::PrepareEquation()
{
    string tmp;
    int count = 0;
    try
    {
        for(S = str.begin(); S != str.end(); S++) 
        {
            if ((*S == ' ') || (*S == 10))
            {}
            else if(((*S >= '0') && (*S <= '9')) || (*S == '+') || (*S == '-') || (*S == '*') || (*S == '/'))
            {
                tmp += *S;
            }
            else if ((*S == '(') || (*S == ')'))
            {
                tmp += *S;
                if (*S == '(') 
                {
                    count += 1;
                }
                if (*S == ')')
                { 
                    count -= 1;
                }
                if (count < 0) 
                {
                    break;
                }
            }
            else if(*S == '\0')
            {
                break;
            }
            else
            {
                throw string("Incorrect expression. Please correct it\n") ;
            }
        }
        if(count != 0)
        {
            throw string("Incorrect expression. Check '(' and ')'. Please correct it\n") ;
        }
    }
    catch(string ex)
    {
        cout << ex << endl;
        exit(-1);
    }
    return tmp;
}


CNode* Math::GetNum()
{
    double val = 0.0;
    string::iterator debug = S;
    while('0' <= *S && *S <= '9')
    {
        val = val*10 + *S - '0';
        S++;
    }
    try
    {
        if(debug == S)
            throw string("Expected number. Please correct expression\n");
    }
    catch(string ex)
    {
        cout << ex << endl;
        exit(1);
    }
    
    CNode* tmp = new CNode(val);
    return tmp;
} 

CNode* Math::GetExp()
{
    CNode* tmp = GetMulDiv();
    while(*S == '-' || *S =='+')
    {
        if (*S == '+') 
        {
            S++;
            CNode* tmp1 = new CNode(Sign, '+', tmp, GetMulDiv());
            tmp = tmp1;
        }
        else if (*S == '-')
        {
            S++;
            CNode* tmp1 = new CNode(Sign, '-', tmp, GetMulDiv());
            tmp = tmp1;
        }
    }
    return tmp;
}

CNode* Math::GetMulDiv()
{
    CNode* tmp= GetPas();
    while(*S == '*' || *S == '/')
    {
        if (*S == '*') 
        {
            S++;
            CNode* tmp1 = new CNode(Sign, '*', tmp, GetPas());
            tmp = tmp1;
        }
        else if (*S == '/')
        {
            S++;
            CNode* tmp1 = new CNode(Sign, '/', tmp, GetPas());
            tmp = tmp1;
        }
    }
    return tmp;
}

CNode*  Math::GetPas()
{
    CNode* tmp;
    if (*S == '(')
    {
        S++;
        tmp = GetExp();
        try
        {
            if (*S != ')')
                throw string ("Expected ')'. Please correct expression\n");
        }
        catch(string ex)
        {
            cout << ex << endl;
            exit(1);
        }
        S++;
    }
    else 
    tmp = GetNum();
    return tmp;
}
