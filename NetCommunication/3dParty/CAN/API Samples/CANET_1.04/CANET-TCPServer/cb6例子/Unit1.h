//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <process.h>
#include <ExtCtrls.hpp>

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TComboBox *ComboBox1;
        TButton *Button1;
        TGroupBox *GroupBox1;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TGroupBox *GroupBox2;
        TLabel *Label8;
        TComboBox *ComboBox6;
        TComboBox *ComboBox7;
        TEdit *Edit1;
        TEdit *Edit4;
        TGroupBox *GroupBox6;
        TListBox *ListBox1;
        TButton *Button4;
        TLabel *Label2;
        TEdit *Edit3;
        TGroupBox *GroupBox3;
        TListBox *ListBox2;
        TButton *Button2;
        TTimer *Timer1;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Button1Click(TObject *Sender);

       void __fastcall FormCreate(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);


private:	// User declarations
public:
        HANDLE m_readhandle;		// User declarations
        __fastcall TForm1(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
