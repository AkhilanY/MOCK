#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <fstream>
#include <stdlib.h>

using namespace std;

array<string,40> KEYWORDS = {"NUM","DECIMAL","BIG-DECIMAL","CHAR","TEXT","LONG","SHORT","UNSIGNED","SOME-TYPE","FOR","WHILE","DO","IF","ELSE-IF","ELSE","REFER-FILE","NOTHING","RETURN","OUTPUT","INPUT","<=","=>","STOP","SKIP","STRUCTURE","UNION","BLUEPRINT","PRIVATE","PROTECTED","PUBLIC","STATIC","FRIEND","INLINE-FUN","TRY-DOING","IF-ERROR","THROW-ERROR","USING","NAMESPACE"};
array<string,40> CKEYWORDS = {"int","float","double","char","string","long","short","unsigned","auto","for","while","do","if","else if","else","#include","void","return","cout","cin","<<",">>","break","continue","struct","union","class","private","protected","public","static","friend","inline","try","catch","throw","using","namespace"};
array<string,40> ADDKEYWORDS = {"EVERY","WHENEVER-I-CALL","RETURN-OF-TYPE:"};

class Interpreter
{
    private:
    int Tokenlen = 0;
    string text,cppcode;

    vector<string> SplitText()
    {
        vector<string> arr;
        string wrd;
        bool strorchr = false;
        for (int i=0;i <= text.length()-1;i++)
        {
            if (text.at(i) == ' ' && !strorchr) // if there is space and it is not in str
            {
                arr.push_back(wrd);
                this->Tokenlen++;
                wrd = "";
                continue;
            }
            else if (text.at(i) == '\n' && !strorchr) // if there is space and it is not in str
            {
                arr.push_back(wrd);
                arr.push_back("\n");
                this->Tokenlen+=2;
                wrd = "";
                continue;
            }
            else if(i+1 == text.length()) // if last word
            {
                wrd += text.at(i);
                arr.push_back(wrd);
                this->Tokenlen++;
                wrd = "";
                continue;
            }
            else if (text.at(i) == '"' || text.at(i) == '\'') // if " or ' present
            {
                if (!strorchr) // if not char or string
                {strorchr = true;wrd+='"';}
                else
                {
                    strorchr=false;
                    wrd+='"';
                }
                continue;
            }
            wrd.push_back(text.at(i));
        }
        //for (string x:arr){cout<<"ARRAY: "<<x<<endl;}
        return arr;
    }

    string Cppify(vector<string> txt)
    {
        string code = "";
        for (int i = 0;i <= Tokenlen-1;i++)
        {
            string wd = txt.at(i).erase(txt.at(i).find_last_not_of(" ")+1);

            array<string,40>::iterator KWitr = find(KEYWORDS.begin(),KEYWORDS.end(),wd);
            if(KWitr != KEYWORDS.end())
            {
                code += CKEYWORDS.at(std::distance<array<string,40>::iterator>(KEYWORDS.begin(),KWitr))+' ';
            }
            else
            {
                array<string,40>::iterator addKWitr = find(ADDKEYWORDS.begin(),ADDKEYWORDS.end(),wd);
                if (addKWitr == ADDKEYWORDS.end())
                {
                    code += wd + ' ';
                }
            }
        }
        return code;
    }
    public:
    Interpreter(string text):text(text){};
    void Interpret()
    {
        this->cppcode = Cppify(SplitText());
        this->text.clear();
    }
    string GetCppCode()
    {
        return this->cppcode;
    }
};

int main()
{
    string line;
    string code;
    ifstream mockfile("mockcode.txt");
    while (getline(mockfile,line))
    {
        code += line + "\n";
    }
    mockfile.close();
    Interpreter *interpreter = new Interpreter(code);
    interpreter->Interpret();

    ofstream cppfile("./Executer/main.cpp",ios::trunc);
    cppfile<<(interpreter->GetCppCode());
    cppfile.flush();
    cppfile.close();
    cout<<"Written to file..."<<endl;
    cout<<"calling compiler..."<<endl;
    cout<<"\n\nOUTPUT:\n"<<endl;

    delete interpreter; // clear stack
    /*system("g++.exe -Wall -fexceptions -g  -c D:\\MOCK\\Executer\\main.cpp -o obj\\Debug\\main.o");
    system("g++.exe  -o bin\\Debug\\Executer.exe obj\\Debug\\main.o");
    system("Executer\\bin\\Debug\\Executer.exe");*/
    system("execfile.bat");
    cout<<"\n\n\nFinshed Execution"<<endl;

    return 0;
}
/*g++.exe -Wall -fexceptions -g  -c D:\MOCK\main.cpp -o obj\Debug\main.o
g++.exe  -o bin\Debug\MOCK.exe obj\Debug\main.o
*/
