#pragma once
#include "Base.h"
#include "MyLine.h"
class MyLine:public Base
{
private:
	Base* left;
	Base* right;
public:
	MyLine(Base* _left,Base* _right):Base("TLine")
	{
		left=_left;
		right=_right;
		name=_left->GetName()+" "+_right->GetName();
		radiusW=_left->GetWidht();
		radiusL=3*radiusW;
		visible=true;
		color=_left->GetColor();
	}
	MyLine(const MyLine &tmp):Base("Line",tmp.name)
	{
		left=tmp.left;
		right=tmp.right;
		name=tmp.name;
	}
	~MyLine()
	{
	}
	MyLine &operator =(const MyLine &tmp)
	{
		left=tmp.left;
		right=tmp.right;
		name=tmp.name;
		return *this;
	}
	string MyLineToString()
	{
		string str=name;
		String^ rad;
		string srad;
		String^ vis;
		string svis;
		MarshalString(rad,srad);
		MarshalString(vis,svis);
		str=str+"&&"+color+"&&"+srad+"&&"+svis+"&&";
		return str;
	}
	MyLine(string str,Base *_left,Base *_right):Base("TLine")
	{
		string w[4]= {"","","",""};
		string cstr=str;
		int k=cstr.find("&&");
		string valuecsr=str.substr(0,k);
		cstr.erase(0,k);
		w[0]=valuecsr;
		k=cstr.find("&&");
		valuecsr=str.substr(0,k);
		w[1]=valuecsr;
		k=cstr.find("&&");
		valuecsr=str.substr(0,k);
		w[2]=valuecsr;
		k=cstr.find("&&");
		valuecsr=str.substr(0,k);
		w[3]=valuecsr;
		k=cstr.find("&&");
		valuecsr=str.substr(0,k);
		name=w[0];
		color=w[1];
		radiusW=(atoi)(w[2].c_str());
		radiusL=3*radiusW;
		visible=(atoi)(w[3].c_str());
		left=_left;
		right=_right;
	}
	Base* GetLeft()
	{
		return left;
	}
	Base* GetRight()
	{
		return right;
	}
	void ChangeRate()
	{
		if(rate<=3)
		{
			rate++;
		}
		else
			rate=1;
	}
	void SetLeft(Base* tmp)
	{
		left=tmp;
	}
	void SetRight(Base* tmp)
	{
		right=tmp;
	}
};

