#include <iostream>
using namespace std;

//计算表达式

class calc{
    enum Type{DATA,ADD,SUB,MULTI,DIV,OPAREN,CPAREN,EOL};  //运算数，加减乘除，开括号，闭括号，行结束

    struct node{
        Type type;
        int data;
        node *lchild,*rchild;
        node(Type t,int d = 0,node *lc=nullptr,node *rc=nullptr)
        {type = t;data = d,lchild = lc;rchild = rc;}
    };
    node *root;

    node *create(char *&s)       //从s创建一棵表达树
    {
        node *p,*root = nullptr;
        Type returnType;
        int value;

        while(*s){
            returnType = getToken(s,value);
            switch(returnType){
                case DATA:case OPAREN:
                    if(returnType == DATA) p = new node(DATA,value);
                    else p = create(s);
                    if(root != nullptr)
                        if(root->rchild == nullptr) root->rchild = p;
                        else root->rchild->rchild = p;
                    break;
                case CPAREN:
                case EOL:
                    return root;
                case ADD:
                case SUB:
                    if(root ==nullptr) root = new node(returnType,0,p);
                    else root = new node(returnType,0,root);
                    break;
                case MULTI:
                case DIV:
                    if(root == nullptr) root = new node(returnType,0,p);
                    else if(root->type == MULTI || root->type == DIV)
                        root = new node (returnType,0,root);
                    else root->rchild = new node(returnType,0,root->rchild);
            }
        }
        return root;
    }

    Type getToken(char *&s,int &data)  //从s中获取一个语法单位
    {
        char type;
        while(*s==' ') ++s;

        if(*s>='0' && *s<='9'){
            data = 0;
            while(*s>='0' && *s<='9'){
                data = 10*data + *s - '0';
                ++s;
            }
            return DATA;
        }
        if(*s=='\0') return EOL;

        type = *s;++s;
        switch(type){
            case '+':
                return ADD;
            case '-':
                return SUB;
            case '*':
                return MULTI;
            case '/':
                return DIV;
            case '(':
                return OPAREN;
            case ')':
                return CPAREN;
            default:
                return EOL;
        }
    }

    int result(node *t){
        int num1,num2;

        if(t->type==DATA) return t->data;
        num1 = result(t->lchild);
        num2 = result(t->rchild);
        switch (t->type){
            case ADD:t->data = num1 + num2;break;
            case SUB:t->data = num1 - num2;break;
            case MULTI:t->data = num1*num2;break;
            case DIV:t->data = num1/num2;
        }
        return t->data;
    }

public:
    calc(char *s){root = create(s);}
    int result(){
        if(root == nullptr) return 0;
        return result(root);
    }
};

int main() {
    char *s;    //表达式中不能有空格
    cin>>s;
    calc exp(s);
    cout<<exp.result();
    return 0;
}