unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs,  StdCtrls, ControlCAN;

type
  TForm1 = class(TForm)
    ComboBox1: TComboBox;
    Button1: TButton;
    GroupBox1: TGroupBox;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Button5: TButton;
    GroupBox2: TGroupBox;
    Label8: TLabel;
    ComboBox6: TComboBox;
    ComboBox7: TComboBox;
    Edit1: TEdit;
    Edit4: TEdit;
    GroupBox6: TGroupBox;
    ListBox1: TListBox;
    GroupBox3: TGroupBox;
    Label1: TLabel;
    Edit2: TEdit;
    Label2: TLabel;
    Edit3: TEdit;
    procedure Button1Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);

    procedure FormClose(Sender: TObject; var Action: TCloseAction);

  private
    { Private declarations }
  public

  end;
  
PTListBox=^TListBox;
var
  Form1: TForm1;
var
    m_devtype : DWORD;
    m_devind : DWORD;
    m_cannum : DWORD;
    m_connect : DWORD;
    m_threadhandle : integer;



implementation

{$R *.dfm}
function ReceiveThread(param : Pointer): integer;
var
receivedata : array[0..49] of VCI_CAN_OBJ;
len : integer;
j : integer;
i : integer;
str : AnsiString;
tmpstr :AnsiString;
box : PTListBox;
errinfo : VCI_ERR_INFO;
begin
  box:=param;
   while TRUE do
    begin
      if m_connect=0 then
        break;
      Sleep(1);
      len:=VCI_Receive(m_devtype,m_devind,m_cannum,@receivedata[0],50,200);
      if len<=0 then
        begin
          //注意：如果没有读到数据则必须调用此函数来读取出当前的错误码，
    			//千万不能省略这一步（即使你可能不想知道错误码是什么）
		    	VCI_ReadErrInfo(m_devtype,m_devind,m_cannum,@errinfo);
          continue;
        end;
      for i:=0 to len-1 do
        begin
	    		str:='接收到数据帧:  ';
    			if receivedata[i].TimeFlag=0 then
		  		  tmpstr:='时间标识:无  '
    			else
    				tmpstr:='时间标识:0x'+IntToHex(receivedata[i].TimeStamp,8)+' ';
			    str:=str+tmpstr;
			    tmpstr:='帧ID:0x'+IntToHex(receivedata[i].ID,8)+' ';
			    str:=str+tmpstr;
			    str:=str+'帧格式:';
			    if receivedata[i].RemoteFlag=0 then
				    tmpstr:='数据帧 '
			    else
				    tmpstr:='远程帧 ';
    			str:=str+tmpstr;
		      str:=str+'帧类型:';
			    if receivedata[i].ExternFlag=0 then
    				tmpstr:='标准帧 '
    			else
		    		tmpstr:='扩展帧 ';
    			str:=str+tmpstr;
    			box.Items.Add(str);
	    		if receivedata[i].RemoteFlag=0 then
          begin
    				str:='数据:';
            if receivedata[i].DataLen>8 then
              receivedata[i].DataLen:=8;
    				for j:=0 to receivedata[i].DataLen-1 do
              begin
      					tmpstr:=IntToHex(receivedata[i].Data[j],2)+' ';
	      				str:=str+tmpstr;
              end;
   				box.Items.Add(str);
          end;
        end;
	  	box.ItemIndex:=box.Items.Count-1;
    end;

  EndThread(0);
  ReceiveThread:=0;
end;

procedure TForm1.Button1Click(Sender: TObject);
var
index: integer;
cannum: integer;
threadid: LongWord;
initconfig : VCI_INIT_CONFIG;
srcport: integer;
szcaneteip: array[0..19] of char;
caneteport: integer;
begin
index:=ComboBox1.ItemIndex;
cannum:=0;
srcport:=0;
caneteport:=StrToInt(Edit3.Text);
StrCopy(szcaneteip,PChar(Edit2.Text));

if m_connect=1 then
  begin
    m_connect:=0;
    Button1.Caption:='连接';
    VCI_CloseDevice(m_devtype,m_devind);
    Exit;
  end;
if (index>=0) then
  begin
    if VCI_OpenDevice(m_devtype,index,srcport)<>1 then
      ShowMessage('端口打开失败')
    else
      begin
        VCI_SetReference(m_devtype,index,0,0,@szcaneteip[0]);
        VCI_SetReference(m_devtype,index,0,1,@caneteport);
        if VCI_StartCAN(m_devtype,index,0)<>1 then
          begin
            ShowMessage('端口打开失败');
            Exit;
          end;

        m_devind:=index;
        m_cannum:=cannum;
        m_connect:=1;
        Button1.Caption:='断开';
        threadid:=111;
        m_threadhandle:=BeginThread(0,0,ReceiveThread,@ListBox1,0,threadid);
      end;
  end
else
  ShowMessage('选项不能为空');
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
  m_devtype := 17;//CANET-TCP 类型号
  m_devind := 0;
  m_cannum :=0;
  m_connect:= 0;
  ComboBox1.ItemIndex:=0;
  ComboBox6.ItemIndex:=0;
  ComboBox7.ItemIndex:=0;
end;

procedure TForm1.Button5Click(Sender: TObject);
var
frametype,frameformat : BYTE;
id : DWORD;
data : array[0..7] of BYTE;
str : AnsiString;
strdata : AnsiString;
senddata : VCI_CAN_OBJ;
i : integer;
begin
  if m_connect=0 then
    Exit;
  frametype:=ComboBox6.ItemIndex;
  frameformat:=ComboBox7.ItemIndex;
  id:=StrToInt('0x'+Edit1.Text);
  str:=Edit4.Text;
  for i:=0 to 7 do
    begin
      strdata:=Copy(str,3*i+1,2);
      strdata:=Trim(strdata);
      if Length(strdata)=0 then
        break;
      data[i]:=StrToInt('0x'+strdata);
    end;
  senddata.ExternFlag:=frametype;
  senddata.RemoteFlag:=frameformat;
  senddata.ID:=id;
  senddata.DataLen:=i;
  Move(data,senddata.Data,i);
  if VCI_Transmit(m_devtype,m_devind,m_cannum,@senddata,1)=1 then
    ListBox1.Items.Add('发送成功')
  else
    ListBox1.Items.Add('发送失败');
end;

procedure TForm1.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  if m_connect=1 then
  begin
    m_connect:=0;
    WaitForSingleObject(m_threadhandle,2000);
    m_threadhandle:=0;
    VCI_CloseDevice(m_devtype,m_devind);
  end
end;

end.
