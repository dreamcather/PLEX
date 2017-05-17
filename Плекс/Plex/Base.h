#pragma once
#include <string>
using namespace std;
using namespace System;
class Base
{
	protected:
	string figures;
	string name;
	string color;
	int radiusW;
	bool visible;
	int rate;
	int radiusL;
public:
	Base(string _figures,string _name="",string _color ="",int _radius=0,bool _visible=true)
	{
		figures=_figures;
		name=_name;
		if (_color=="")
			color="Black";
		else
			color=_color;
		if(_radius==0)
			radiusW=5;
		else
			radiusW=_radius;
		radiusL=3*radiusW;
		rate=1;
		visible=_visible;
	}
	Base(const Base &tmp)
	{
		figures=tmp.figures;
		color=tmp.color;
		radiusL=tmp.radiusL;
		radiusW=tmp.radiusW;
		visible=tmp.visible;
		rate=tmp.rate;

	}
	Base(const Base &tmp,string _name)
	{
		name=_name;
		color=tmp.color;
		radiusL=tmp.radiusL;
		radiusW=tmp.radiusW;
		visible=tmp.visible;
		rate=tmp.rate;
	}
	~Base()
	{
	}
	string GetFigures()
	{
		return figures;
	}
	string GetName()
	{
		return name;
	}
	string GetColor()
	{
		return color;
	}
	void SetColor(string _color)
	{
		color=_color;
	}
	int GetWidht()
	{
		return radiusW;
	}
	void SetWidht(int _widht)
	{
		radiusW=_widht;
		radiusL=3*radiusW;
	}
	void SetVisible(bool _visible)
	{
		visible=_visible;
	}
	bool GetVisible()
	{
		return visible;
	}
	int GetRate()
	{
		return rate;
	}
	void MarshalString ( String ^ s, string& os ) {  
   using namespace Runtime::InteropServices;  
   const char* chars =   
      (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();  
   os = chars;  
   Marshal::FreeHGlobal(IntPtr((void*)chars));  
}  
};

