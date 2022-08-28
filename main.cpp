#include <iostream>
#include <string>
#include <deque>
#include <array>
#include <algorithm>

using namespace std;

array<string,50> KEYWORDS = {"NUM","DECIMAL","BIG-DECIMAL","CHAR","TEXT","LONG","SHORT","UNSIGNED","SOME-TYPE","FOR","WHILE","DO","IF","ELSE-IF","ELSE","REFER-FILE","NOTHING","RETURN","OUTPUT<=","INPUT=>","OUTPUT","INPUT","STOP","SKIP","STRUCTURE","UNION","BLUEPRINT","PRIVATE","PROTECTED","PUBLIC","STATIC","FRIEND","INLINE-FUN","TRY-DOING","IF-ERROR","THROW-ERROR","USING","NAMESPACE"};
array<string,50> CKEYWORDS = {"int","float","double","char","string","long","short","unsigned","auto","for","while","do","if","else if","else","#include","void","return","cout>>","cin<<","cout","cin","break","continue","struct","union","class","private","protected","public","static","friend","inline","try","catch","throw","using","namespace"};
array<string,50> ADDKEYWORDS = {"EVERY","WHENEVER-I-CALL","RETURN-OF-TYPE:"};

class Interpreter
{
    private:
    int Tokenlen = 0;
    string text,cppcode;

    deque<string> SplitText()
    {
        deque<string> arr;
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
            else if(i+1 == text.length())
            {
                wrd += text.at(i);
                arr.push_back(wrd);
                this->Tokenlen++;
                wrd = "";
                continue;
            }
            else if (text.at(i) == '"' || text.at(i) == '\'')
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
        return arr;
    }

    string Cppify(deque<string> txt)
    {
        string code = "";
        for (int i = 0;i <= Tokenlen-1;i++)
        {
            string wd = txt.at(i).erase(txt.at(i).find_last_not_of(" ")+1);

            array<string,50>::iterator KWitr = find(KEYWORDS.begin(),KEYWORDS.end(),wd);
            if(KWitr != KEYWORDS.end())
            {
                code += CKEYWORDS.at(std::distance<array<string,50>::iterator>(KEYWORDS.begin(),KWitr))+' ';
            }
            else
            {
                array<string,50>::iterator addKWitr = find(ADDKEYWORDS.begin(),ADDKEYWORDS.end(),wd);
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
    Interpret()
    {
        this->cppcode = Cppify(SplitText());
    }
    string GetCppCode()
    {
        return this->cppcode;
    }
};

int main()
{
    cout<<"\tENTER YOUR CODE\n"<<endl;
    string txt = "";
    int n = 1;
    while (true)
    {
        string l;
        cout<<n<<"   | ";
        getline(cin,l);
        if (l == "stop-program"){break;}
        txt += "\n "+l;
        n++;
    }
    Interpreter interpreter(txt);
    interpreter.Interpret();
    cout<<"\n\nC++ CODE: \n"<<interpreter.GetCppCode();

    return 0;
}
