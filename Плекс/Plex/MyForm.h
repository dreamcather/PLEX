#pragma once
#include "windows.h"
#include "MyPlex.h"


namespace Plex {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			left=Point(-1,-1);
			right=Point(-1,-1);
			iplex = gcnew Bitmap(200,200);
			changeplex=iplex;
			plex=new MyPlex;
			flag=false;
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// “ребуетс€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;
		Point left;
		MyPlex* plex;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
		Point right;
		Bitmap^ iplex;
		Bitmap^ changeplex;
		bool flag;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ќб€зательный метод дл€ поддержки конструктора - не измен€йте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(200, 200);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseClick);
			this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseDown);
			this->pictureBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseMove_1);
			this->pictureBox1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseUp);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
private: System::Void pictureBox1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
			 {
				 if(plex->IsEmpty())
				 {
				 int x=e->X;
				 int y=e->Y;
				 plex->AddPoint(x,y);
				 left=Point(x,y);
				 changeplex=iplex;
				 Graphics^ g=Graphics::FromImage(iplex);
				 plex->DrawPlex(g);
				 pictureBox1->Image=changeplex;
				 pictureBox1->Refresh();
				 iplex=changeplex;
				 }
				 else
				 {
					 int x=e->X;
					 int y=e->Y;
					 MyPoint* res = plex->FindPoint(x,y);
					 if(res!=NULL)
					 {
						 left.X=res->GetX();
						 left.Y=res->GetY();

					 }
				 }
			 }
private: System::Void pictureBox1_MouseMove_1(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			 if(flag)
				 {
						 right.X=e->X;
						 right.Y=e->Y;
						 pictureBox1->Image=iplex;
						 pictureBox1->Refresh();
						 Graphics^ g=pictureBox1->CreateGraphics();
						 g->DrawLine(Pens::Black,left.X,left.Y,right.X,right.Y);
				 }
		 }
private: System::Void pictureBox1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		 {
			 if(left.X!=-1)
				 {
						 right.X=e->X;
						 right.Y=e->Y;
						 pictureBox1->Image=iplex;
						 pictureBox1->Refresh();
						 Graphics^ g=pictureBox1->CreateGraphics();
						 g->DrawLine(Pens::Black,left.X,left.Y,right.X,right.Y);
						 flag=true;

				 }
		 }
private: System::Void pictureBox1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		 {
			 if(right.X!=-1)
			 {
				 int x=e->X;
				 int y=e->Y;
				 MyPoint* res = plex->FindPoint(left.X,left.Y);
				 plex->AddLine(res,x,y);
				 Graphics^ g=Graphics::FromImage(iplex);
				 plex->DrawPlex(g);
			 }
		 }
};
}