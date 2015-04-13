#include<iostream>
#include<string>
#include<cstring>
#include<sstream>


using namespace std;

class GenListNode 
{ 
	public: 
	int tag; 
	string s; 
	GenListNode *down, *next; 
	};

int count=1;

GenListNode *makeList()
{
GenListNode* g=NULL;
GenListNode* head=NULL;

label:if (count!=0)
{string t;
cin >> t;

if (t=="(")
{count+=1;
GenListNode* l=new GenListNode;
l->next=NULL;
if (head==NULL)
{g=l;head=l;
}
else
{
g->next=l;
g=l;
}
l->tag=1;
g->down=makeList();
}

else if (t==")")
{count-=1;
return head;
}

else 
{GenListNode *l=new GenListNode;
l->tag=0;
l->s=t;
l->down=NULL;
l->next=NULL;
if (head==NULL)
{head=l;
g=l;}

else
{
g->next=l;
g=l;}
}

goto label;}}



//Evaluator


class Value
{public:
    int tag;
    float val;
    GenListNode *link;
    Value()
    {
        link=NULL;
    }
};

class Env
{public:
    Value *table[26];
    Env *parent;
    Env()
    {
        for (int i=0;i<26;i++)
            table[i]=NULL;
        	parent=NULL;
    }
};

void add(char x,Value new_val,Env &e)
{
    Value *p=new Value();
    p->tag=new_val.tag;
    p->val=new_val.val;
    p->link=new_val.link;
    e.table[x-'a']=p;
}

Value find(char x,Env &e)
{
    if (e.table[x-'a']!=NULL)
        return *(e.table[x-'a']);
    else
        if (e.parent==NULL)
           cout<<"Element is not found";
        else
            {
                //cout<<"Element is being searched...";
                return find(x,*(e.parent));
            }
}

Value evalList(GenListNode *p, Env& e);


Value evalNode(GenListNode *p, Env& e)
{
	char c;
	float n;
	stringstream ccon(p->s);
	stringstream fcon(p->s);
	fcon >> n;
	ccon >> c;
if (p->s.size()==1 && p->s>="a" && p->s<="z")
return find(c,e);
else if (p->tag==1)
{
	return evalList(p->down,e);
}
else
{
	Value val;
	val.val=n;
	return val;
}


	
};


Value evalList(GenListNode *p, Env& e)
{
		if (p->s == "begin") 
		{
			p=p->next;
			while(p->next != NULL) 
			{
				evalNode(p, e);
				p = p->next;
			}
			return evalNode(p, e);
		}
		
		else if (p->s == "lambda") 
		{
			Value new_val;
			new_val.tag=1;
			new_val.link=p;
			return new_val;
		}
		
		else if (p->s == "define")
		{
			Value v=evalNode(p->next->next,e);
			stringstream ccon(p->next->s);
			char c;
			ccon>>c;
			add(c,v,e);
			return evalNode(p->next,e);
		}
		
		else if (p->s=="if")
		{
			Value val=evalNode(p->next,e);
			if (val.val==1) return evalNode(p->next->next,e);
			else return evalNode(p->next->next->next,e);
			
		}
		
		
	
		else if (p->s=="while")
		{
			Value v2;			
			int i=0;
			while (evalNode(p->next,e).val==1) { v2=evalNode (p->next->next,e); i++;}
			if (i>0) return v2;
		
		}




		
		else if (p->s=="set")
		{
			add(p->next->s[0],evalNode(p->next->next,e),e);
			return evalNode(p->next,e);
		}
		
		else if (p->s=="+")
		{
			Value val1=evalNode(p->next,e);
			Value val2=evalNode(p->next->next,e);
			Value new_val;
			new_val.tag=0;
			new_val.val=val1.val+val2.val;
			return new_val;
		}
		
		else if (p->s=="-")
		{
			Value val1=evalNode(p->next,e);
			Value val2=evalNode(p->next->next,e);
			Value new_val;
			new_val.tag=0;
			new_val.val=val1.val-val2.val;
			return new_val;
		}
		
		else if (p->s=="*")
		{
			Value val1=evalNode(p->next,e);
			Value val2=evalNode(p->next->next,e);
			Value new_val;
			new_val.tag=0;
			new_val.val=val1.val*val2.val;
			return new_val;
		}
		
		else if (p->s=="/")
		{
			Value val1=evalNode(p->next,e);
			Value val2=evalNode(p->next->next,e);
			Value new_val;
			new_val.tag=0;
			new_val.val=val1.val/val2.val;
			return new_val;
		}
		
		else if (p->s=="%")
		{
			Value val1=evalNode(p->next,e);
			Value val2=evalNode(p->next->next,e);
			Value new_val;
			new_val.tag=0;
			new_val.val=(int)val1.val%(int)val2.val;
			return new_val;
		}
		
		else if (p->s=="<")
		{
			Value val1=evalNode(p->next,e);
			Value val2=evalNode(p->next->next,e);
			Value new_val;
			new_val.tag=0;
			if (val1.val<val2.val)
			{
				new_val.val=1;
			}
			else new_val.val=0;
			return new_val;
		}
		
		else if (p->s=="<=")
		{
			Value val1=evalNode(p->next,e);
			Value val2=evalNode(p->next->next,e);
			Value new_val;
			new_val.tag=0;
			if (val1.val<=val2.val)
			{
				new_val.val=1;
			}
			else new_val.val=0;
			return new_val;
		}
		
		else if (p->s=="==")
		{
			Value val1=evalNode(p->next,e);
			Value val2=evalNode(p->next->next,e);
			Value new_val;
			new_val.tag=0;
			if (val1.val==val2.val)
			{
				new_val.val=1;
			}
			else new_val.val=0;
			return new_val;
		}



 	else if((p->s[0]>='a')&&(p->s[0]<='z'))
    {
    char ch=p->s[0];
    Value v=find(ch,e);
    if(v.tag==0)
    return v;
    else if(v.tag==1)
	{
		Env e1;
		e1.parent=&e;
		v=evalNode(p,e);
		char ch;

		GenListNode *arglist=new GenListNode;
		GenListNode *body=new GenListNode;
		GenListNode *counter=new GenListNode;
	
		arglist=v.link->next->down;
		body=v.link->next->next;
		counter=p->next;
		

	while(arglist!=NULL)
	{
		add(arglist->s[0],evalNode(counter,e),e1);
		arglist=arglist->next;
		counter=counter->next;
	}
	
	return evalNode(body,e1);


 	}
}

	else if(p->tag==1)
	{
	GenListNode *q=new GenListNode;
	q=p->down;
	Env e1;
	e1.parent=&e;
	
	

	GenListNode *arglist=new GenListNode;
	GenListNode *body=new GenListNode;
	GenListNode *counter=new GenListNode;
	
	arglist=q->next->down;
	body=q->next->next;
	counter=p->next;
		

	while(arglist!=NULL)
	{
	add(arglist->s[0],evalNode(counter,e),e1);
	arglist=arglist->next;
	counter=counter->next;
	}
	
	return evalNode(body,e1);

	}



}

main()
{
	Env e;
	string t;
	cin >> t;
	GenListNode *ptr;
	ptr=makeList();
	Value g=evalList(ptr,e);
	cout << g.val <<endl;
	
	return 0;
}




