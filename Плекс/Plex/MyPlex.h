#pragma once
#include "Base.h"
#include "MyPoint.h"
#include "MyLine.h"
#include <stack>
class MyPlex
{
private:
	Base* start;
	int count;
public:

	MyPlex(Base* _start=NULL)
	{
		start=_start;
		count=0;
	}
	~MyPlex()
	{

	}
	Base* FindPoint(string name)
	{
		stack<MyLine*> lstack;
		stack<MyPoint*> pstack;
		lstack.push(NULL);
		Base *current=start;
		Base * res=NULL;
		while(current!=NULL)
		{
			if(current->GetFigures()=="TPoint")
			{
				if(current->GetName()==name)
					return res = current;
				else
				{
					current=(Base*)lstack.top();
					lstack.pop();
					((MyLine*)current)->ChangeRate();
				}
			}
			else
			{
				switch (current->GetRate())
				{
				case 1:
					{
						lstack.push((MyLine*)current);
						current=((MyLine*)current)->GetLeft();
						break;
					}
				case 2:
					{
						lstack.push((MyLine*)current);
						current=((MyLine*)current)->GetRight();
						break;
					}
				case 3:
					{
						current=(Base*)lstack.top();
						lstack.pop();
						break;
					}
				default:
					break;
				}
			}
		}
		return res;
	}
	Base* FindPointP(string name)
	{
		stack<MyLine*> lstack;
		stack<MyPoint*> pstack;
		lstack.push(NULL);
		Base *current=start;
		Base * res=start;
		while(current!=NULL)
		{
			if(current->GetFigures()=="TPoint")
			{
				if(current->GetName()==name)
				{
					res = lstack.top();
					return res;
				}
				else
				{
					current=(Base*)lstack.top();
					lstack.pop();
					((MyLine*)current)->ChangeRate();
				}
			}
			else
			{
				switch (current->GetRate())
				{
				case 1:
					{
						lstack.push((MyLine*)current);
						current=((MyLine*)current)->GetLeft();
						break;
					}
				case 2:
					{
						lstack.push((MyLine*)current);
						current=((MyLine*)current)->GetRight();
						break;
					}
				case 3:
					{
						current=(Base*)lstack.top();
						lstack.pop();
						break;
					}
				default:
					break;
				}
			}
		}
		return res;
	}
	MyPoint* FindPoint(int x,int y)
	{
		stack<MyLine*> lstack;
		stack<MyPoint*> pstack;
		lstack.push(NULL);
		Base *current=start;
		MyPoint * res=NULL;
		while(current!=NULL)
		{
			if(current->GetFigures()=="TPoint")
			{
				if(((MyPoint*)current)->Distance(x,y))
					return res = (MyPoint*)current;

				else
				{
					current=(Base*)lstack.top();
					lstack.pop();
					if(current!=NULL)
					((MyLine*)current)->ChangeRate();
				}
			}
			else
			{
				switch (current->GetRate())
				{
				case 1:
					{
						lstack.push((MyLine*)current);
						current=((MyLine*)current)->GetLeft();
						break;
					}
				case 2:
					{
						lstack.push((MyLine*)current);
						current=((MyLine*)current)->GetRight();
						break;
					}
				case 3:
					{
						current=(Base*)lstack.top();
						lstack.pop();
						break;
					}
				default:
					break;
				}
			}
		}
		return res;
	}
	string GenerateName()
	{
		int k=count/26;
		int l=count%26;
		string res="";
		for(int i=0;i<k;i++)
		{
			res=res+"A";
		}
		char let=(char)(65+l);
		res=res+let;
		count++;
		return res;
	}
	void AddLine(Base* point,int x,int y)
	{
		Base* left=FindPoint(point->GetName());
		if(left!=NULL)
		{
		MyPoint* right=new MyPoint(x,y,GenerateName());
		Base* res=(Base*)(new MyLine((Base*)left,(Base*)right));
		stack<MyLine*> lstack;
		stack<MyPoint*> pstack;
		lstack.push(NULL);
		Base *current=start;
		while(current!=NULL)
		{
			if(current->GetFigures()=="TPoint")
			{
				if(current->GetName()==(((MyLine*)res)->GetLeft()->GetName()))
				{
					current=res;
					current=lstack.top();
					if(current!=NULL)
					{
					if(current->GetRate()==1)
					{
						((MyLine*)current)->SetLeft(res);
					}
					else
					{
						((MyLine*)current)->SetRight(res);
					}
					lstack.pop();
					}
					else
					{
						start=res;
					}

				}
				else
				{
					current=(Base*)lstack.top();
					lstack.pop();
					if(current!=NULL)
					((MyLine*)current)->ChangeRate();
				}
			}
			else
			{
				switch (current->GetRate())
				{
				case 1:
					{
						lstack.push((MyLine*)current);
						current=((MyLine*)current)->GetLeft();
						break;
					}
				case 2:
					{
						lstack.push((MyLine*)current);
						current=((MyLine*)current)->GetRight();
						break;
					}
				case 3:
					{
						current=(Base*)lstack.top();
						lstack.pop();
						break;
					}
				default:
					break;
				}
			}
		}
		}
		}
	void AddPoint(int x,int y)
	{
		MyPoint* copy=new MyPoint(x,y,GenerateName());
		Base* res =(Base*)(copy);
		start=res;
	}
	bool IsEmpty()
	{
		if(start==NULL)
			return true;
		else
			return false;
	}
	void DrawLine(Graphics^ g,MyLine * line,MyPoint* left,MyPoint* right)
	{

		if(line->GetVisible()==true)
		{
		String^ colname=gcnew String(line->GetColor().c_str());
		Color clr=Color::FromName(colname);
		Pen^ mypen=gcnew Pen(clr);
		Point lf(left->GetX(),right->GetY());
		Point rh(left->GetX(),right->GetY());
		g->DrawLine(mypen,lf,rh);
		}
	}
	void DrawPlex(Graphics^ g)
	{
		stack<MyLine*> lstack;
		stack<MyPoint*> pstack;
		lstack.push(NULL);
		Base *current=start;
		Base * res;
		while(current!=NULL)
		{
			if(current->GetFigures()=="TPoint")
			{
				((MyPoint*)current)->Draw(g);
				pstack.push((MyPoint*)current);
					current=(Base*)lstack.top();
					lstack.pop();
					if(current!=NULL)
					{
					((MyLine*)current)->ChangeRate();
					}
			}
			else
			{
				switch (current->GetRate())
				{
				case 1:
					{
						lstack.push((MyLine*)current);
						string nmes=current->GetName();
						int k=nmes.length();
						MyLine* copys=(MyLine*)current;
					    nmes=copys->GetName();
						k=nmes.length();
						current=((MyLine*)current)->GetLeft();
						break;
					}
				case 2:
					{
						lstack.push((MyLine*)current);
						current=((MyLine*)current)->GetRight();
						break;
					}
				case 3:
					{
						MyPoint* lf=pstack.top();
						pstack.pop();
						MyPoint* rh=pstack.top();
						pstack.pop();
						DrawLine(g,(MyLine*)current,lf,rh);
						current=(Base*)lstack.top();
						lstack.pop();
						break;
					}
				default:
					break;
				}
			}
	}
	}
};

