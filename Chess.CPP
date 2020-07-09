#include <graphics.h>
#include <iostream.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <time.h>
#include <PIECES.h>
#include <FONTS.H>
#include <fstream.h>
#include <alloc.h>
#include <string.h>
//#include <Pieces.h>

class Pawn;
class Knight;
class Rook;
class Bishop;
class Queen;
class King;
class Chessboard;
class Box;
class MessageBox;
class AlertBox;
class Time;

const int WHITEPAWN  =1;
const int WHITEKNIGHT=2;
const int WHITEBISHOP=3;
const int WHITEROOK  =4;
const int WHITEQUEEN =5;
const int WHITEKING  =6;

const int EMPTY =0;

const int BLACKPAWN  =-1;
const int BLACKKNIGHT=-2;
const int BLACKBISHOP=-3;
const int BLACKROOK  =-4;
const int BLACKQUEEN =-5;
const int BLACKKING  =-6;

const short DISABLE=0;
const short ENABLE=1;

const short DARK=0;
const short LIGHT=1;

const int TRUE=1;
const int FALSE=0;
const int UNKNOWN=2;

const int Up=1;
const int Down=0;

const int White=1;
const int Black=0;

const int Next=1;
const int Current=0;

const int WHITEPLAY=1;
const int BLACKPLAY=0;

int PLAY;
int HedDehNuudel=0;
int FileHedDehNuudel=0;
int DEPTH=3;
int RunEnable=TRUE;

int ComputerPlayer=Black;
int HumanPlayer=White;

int HOUR=0;
int MINUT=5;
int SECOND=0;

void main (void);

typedef struct HISTORY
{

};

//#######################################################################################################
//
//			Evaluate Piece
//
//#######################################################################################################

int WhitePawn_Value[8][8]={{0, 0, 0,  0,  0, 0, 0,0},
			   {5,10,15, 20, 20,15,10,5},
			   {4, 8,12, 16, 16,12, 8,4},
			   {3, 6, 9, 12, 12, 9, 6,3},
			   {2, 4, 6,  8,  8, 6, 4,2},
			   {1, 2, 3,  4,  4, 3, 2,1},
			   {0, 0, 0,-20,-20, 0, 0,0},
			   {0, 0, 0,  0,  0, 0, 0,0}};

int BlackPawn_Value[8][8]={{ 0,  0,  0,  0,  0,  0,  0, 0},
			   { 0,  0,  0, 20, 20,  0,  0, 0},
			   {-1, -2, -3,  4, -4, -3, -2,-1},
			   {-2, -4, -6, -8, -8, -6, -4,-2},
			   {-3, -6, -9,-12,-12, -9, -6,-3},
			   {-4, -8,-12,-16,-16,-12, -8,-4},
			   {-5,-10,-15,-20,-20,-15,-10,-5},
			   { 0,  0,  0,  0,  0,  0,  0, 0}};

int WhiteBod_Value[8][8]={{-10,-10,-10,-10,-10,-10,-10,-10},
			  {-10,  0,  0,  0,  0,  0,  0,-10},
			  {-10,  0,  5,  5,  5,  5,  0,-10},
			  {-10,  0,  5, 10, 10,  5,  0,-10},
			  {-10,  0,  5, 10, 10,  5,  0,-10},
			  {-10,  0,  5,  5,  5,  5,  0,-10},
			  {-10,  0,  0,  0,  0,  0,  0,-10},
			  {-10,-10,-10,-10,-10,-10,-10,-10}};

int BlackBod_Value[8][8]={{10,10,10, 10, 10,10,10,10},
			  {10, 0, 0,  0,  0, 0, 0,10},
			  {10, 0,-5, -5, -5,-5, 0,10},
			  {10, 0,-5,-10,-10,-5, 0,10},
			  {10, 0,-5,-10,-10,-5, 0,10},
			  {10, 0,-5, -5, -5,-5, 0,10},
			  {10, 0, 0,  0,  0, 0, 0,10},
			  {10,10,10, 10, 10,10,10,10}};

int WhiteKing_Value[8][8]={{-40, -40, -40, -40, -40, -40, -40, -40},
			   {-40, -40, -40, -40, -40, -40, -40, -40},
			   {-40, -40, -40, -40, -40, -40, -40, -40},
			   {-40, -40, -40, -40, -40, -40, -40, -40},
			   {-40, -40, -40, -40, -40, -40, -40, -40},
			   {-40, -40, -40, -40, -40, -40, -40, -40},
			   {-20, -20, -20, -20, -20, -20, -20, -20},
			   {-10,   0,  10, -20,   0, -20,  10,   0}};

int BlackKing_Value[8][8]={{-10,   0, -10,  20,   0,  20, -10,   0},
			   { 20,  20,  20,  20,  20,  20,  20,  20},
			   { 40,  40,  40,  40,  40,  40,  40,  40},
			   { 40,  40,  40,  40,  40,  40,  40,  40},
			   { 40,  40,  40,  40,  40,  40,  40,  40},
			   { 40,  40,  40,  40,  40,  40,  40,  40},
			   { 40,  40,  40,  40,  40,  40,  40,  40},
			   { 40,  40,  40,  40,  40,  40,  40,  40}};

int WhiteKingSide_pawn[8][8]={{ 0, 0, 0, 0, 0, 0, 0, 0},
			      { 0, 0, 0, 0, 0, 0, 0, 0},
			      { 0, 0, 0, 0, 0, 0, 0, 0},
			      { 0, 0, 0, 0, 0, 0, 0, 0},
			      { 0, 0, 0, 0, 0, 5, 5, 5},
			      { 0, 0, 0, 0, 0,10,10,10},
			      { 0, 0, 0, 0, 0,20,20,20},
			      { 0, 0, 0, 0, 0, 0, 0, 0}};


int WhiteQueenSide_Pawn[8][8]={{ 0, 0, 0, 0, 0, 0, 0, 0},
			       { 0, 0, 0, 0, 0, 0, 0, 0},
			       { 0, 0, 0, 0, 0, 0, 0, 0},
			       { 0, 0, 0, 0, 0, 0, 0, 0},
			       { 5, 5, 5, 0, 0, 0, 0, 0},
			       {10,10,10, 0, 0, 0, 0, 0},
			       {20,20,20, 0, 0, 0, 0, 0},
			       { 0, 0, 0, 0, 0, 0, 0, 0}};

int BlackKingSide_pawn[8][8]={{ 0, 0, 0, 0, 0,  0,  0,  0 },
			      { 0, 0, 0, 0, 0,-20,-20,-20 },
			      { 0, 0, 0, 0, 0,-10,-10,-10 },
			      { 0, 0, 0, 0, 0, -5, -5, -5 },
			      { 0, 0, 0, 0, 0,  0,  0,  0 },
			      { 0, 0, 0, 0, 0,  0,  0,  0 },
			      { 0, 0, 0, 0, 0,  0,  0,  0 },
			      { 0, 0, 0, 0, 0,  0,  0,  0 }};


int BlackQueenSide_Pawn[8][8]={{  0,  0,  0, 0, 0, 0, 0, 0 },
			       {-20,-20,-20, 0, 0, 0, 0, 0 },
			       {-10,-10,-10, 0, 0, 0, 0, 0 },
			       { -5, -5, -5, 0, 0, 0, 0, 0 },
			       {  0,  0,  0, 0, 0, 0, 0, 0 },
			       {  0,  0,  0, 0, 0, 0, 0, 0 },
			       {  0,  0,  0, 0, 0, 0, 0, 0 },
			       {  0,  0,  0, 0, 0, 0, 0, 0}};

int BoardCenterRow[8]={75,125,175,225,275,325,375,425};
int BoardCenterColumn[8]={75,125,175,225,275,325,375,425};

int pieceboard[8][8]={{BLACKBISHOP,BLACKKNIGHT,BLACKROOK,BLACKQUEEN,BLACKKING,BLACKROOK,BLACKKNIGHT,BLACKBISHOP},
		      {BLACKPAWN,BLACKPAWN,BLACKPAWN,BLACKPAWN,BLACKPAWN,BLACKPAWN,BLACKPAWN,BLACKPAWN},                                                    		      {0,0,0,0,0,0,0,0},
		      {0,0,0,0,0,0,0,0},
		      {0,0,0,0,0,0,0,0},
		      {0,0,0,0,0,0,0,0},
		      {1,1,1,1,1,1,1,1},
		      {3,2,4,5,6,4,2,3}
		     };
int boardcolor[8][8]={{1,0,1,0,1,0,1,0},
		      {0,1,0,1,0,1,0,1},
		      {1,0,1,0,1,0,1,0},
		      {0,1,0,1,0,1,0,1},
		      {1,0,1,0,1,0,1,0},
		      {0,1,0,1,0,1,0,1},
		      {1,0,1,0,1,0,1,0},
		      {0,1,0,1,0,1,0,1}};

int BoardColor[8][8]={{7,8,7,8,7,8,7,8},
		      {8,7,8,7,8,7,8,7},
		      {7,8,7,8,7,8,7,8},
		      {8,7,8,7,8,7,8,7},
		      {7,8,7,8,7,8,7,8},
		      {8,7,8,7,8,7,8,7},
		      {7,8,7,8,7,8,7,8},
		      {8,7,8,7,8,7,8,7}};

				   //Nudnii unguud {0-har,1-tsagaan}
//##########################################################################
//
//                    MOUSE class
//
//###########################################################################

//******************************Mouse Presentation [BEGIN]********************
void Graphic_mode(void);
int mouse_init(void);
void mouse_show(void);
void mouse_hide(void);
void mouse_info(void);
void mouse_put(int,int);
void button_on(int x1,int y1,int x2,int y2,int color);
void button_off(int x1,int y1,int x2,int y2,int color);

unsigned int Column,Row,MouseButton,column1,row1;

void mouse_put(int column,int row)
{
 asm {  mov ax,04h;
	mov dx,row
	mov cx,column
	int 33h;
     }
}
/*void mouse_delay()
 { int TempRow,TempColumn;
   TempRow=Row;
   TempColumn=Column;
   delay(30);
   mouse_hide();
   mouse_put(TempRow,TempColumn);
   mouse_show();
 }
*/
void Display_Mouse_Position(void)
{
  char xpos[3], ypos[3];
  setcolor(BLUE);
  mouse_hide();
  sprintf(xpos,"%i",Column);
  sprintf(ypos,"%i",Row);
  mouse_show();
}

int mouse_init(void)
{
 int result;
 asm {
     mov ax,00h;
     int 33h;
     mov result,ax;
     }
 return(result);
}

void mouse_show(void)
{
 asm {
	mov ax,01h;
	int 33h;
     }
}

void mouse_hide(void)
{
 asm {
	mov ax,02h;
	int 33h;
 }
}

void mouse_info(void)
{
asm {
  mov ax,03h;
  int 33h;
  mov MouseButton,bx;
  mov Row,dx;
  mov Column,cx;
 }
}
void mouse_limited(int column_up,int row_right,int column_down,int row_left)
 {
 asm{
      mov ax,07h
      mov cx,row_right
      mov dx,row_left
      int 33h
      mov ax,08h
      mov cx,column_up
      mov dx,column_down
      int 33h
     };
 }
void Start_Chess(void)
{
if (mouse_init() == 0) {
 printf("Mouse driver not installed, please install it and run the program again");
 exit(0);
 }
 Graphic_mode();
}
/*
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          ////////////////////////////////////////////////////
//          //               * * CLASS Time * *  BEGIN        //
//          ////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//******************************Mouse Presentation [END]************************
//
//                  SHALGAH HESEG BUH BOLOMJ       <TUGSGUL>
//
//**************************************************************************/


void EXIT(void);
void far *SIZE;
unsigned size;
//###########################################################################
//             Panel class ni
//
//
//###########################################################################
void DRAW_SUM(char CHAR,int x,int y,int color)
{
  switch(CHAR)
  { case '>':FontDraw(SUM_,x+5,y,color);break;
    case '<':FontDraw(_SUM,x+5,y,color);break;
    case ']':FontDraw(sum_,x+5,y,color);break;
    case '[':FontDraw(_sum,x+5,y,color);break;
    case '5':FontDraw(N,x,y,color);break;
    default:break;
  }
}
void DRAW_FONT1(char CHAR,int x,int y,int color)
{
  switch(CHAR)
  {
    case 'D':FontDraw(D,x,y,color);break;
    case 'C':FontDraw(C,x,y,color);break;
    case 'c':FontDraw(c,x,y,color);break;
    case 'J':FontDraw(J,x,y,color);break;
    case 'H':FontDraw(H,x,y,color);break;
    case 'O':FontDraw(O,x,y,color);break;
    case 'N':FontDraw(N,x,y,color);break;
    case 'U':FontDraw(U,x,y,color);break;   //Ugui
    case 'u':FontDraw(u,x,y,color);break;   //uragsh
    case 'S':FontDraw(S,x,y,color);break;   //TS
    case 's':FontDraw(s,x,y,color);break;   //SH
    case 'I':FontDraw(I,x,y,color);break;   //hagas i
    case 'i':FontDraw(i,x,y,color);break;   //
    case 'M':FontDraw(M,x,y,color);break;
    default :DRAW_SUM(CHAR,x,y,color);break;

  }
}


void DRAW_FONT(char CHAR,int x,int y,int color)
{
  switch(CHAR)
  {
    case 'A':FontDraw(A,x,y,color);break;
    case 'b':FontDraw(b,x,y,color);break;   //b
    case 'B':FontDraw(B,x,y,color);break;
    case 'G':FontDraw(G,x,y,color);break;
    case 'E':FontDraw(E,x,y,color);break;
    case 'H':FontDraw(H,x,y,color);break;
    case 'L':FontDraw(L,x,y,color);break;
    case 'R':FontDraw(R,x,y,color);break;
    case 'T':FontDraw(T,x,y,color);break;
    default :DRAW_FONT1(CHAR,x,y,color);break;
 }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          ////////////////////////////////////////////////////
//          //               * * CLASS Time * *  BEGIN        //
//          ////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

class Time
{ int Hour;  int Minut; int Second;
  clock_t Start,End;
  int clockevent;
  int X,Y;
  public:
  Time(){Start=0;End=0;Hour=0;Minut=5;Second=0;clockevent=FALSE; }
  void SetTime(int hour,int minut,int second,int x,int y);
  void Set(int hour,int minut){Hour=hour;Minut=minut;Second=0;};
  int TestClock(void);
  void Draw_Clock(void);
  void RunTime(void);
  int ReturnHour()
   {  return Hour;
   };
  int ReturnMinut()
  {  return Minut;
  }
  int ReturnSecond()
  {  return Second;
  }
};
  void Time::SetTime(int hour,int minut,int second,int x,int y)
    { Hour=hour;Minut=minut;Second=second;X=x;Y=y;}

  int Time::TestClock(void)
   {
    if(Hour<=0 && Minut<=0 && Second<=0)
     {
       return TRUE;
     }
    else return FALSE;
   }

  void Time::Draw_Clock(void)
  { char STR[8];  int M;
    STR[0]=char(Hour+48);
    M=Minut;    STR[1]=':';
    if(M>=10) { STR[2]=char(M/10+48); STR[3]=char(M%10+48); }
    else      { STR[2]='0';           STR[3]=char(M+48);    }
    M=Second;   STR[4]=':';
    if(M>=10) { STR[5]=char(M/10+48); STR[6]=char(M%10+48); }
    else      { STR[5]='0';           STR[6]=char(M+48);    }
    STR[7]=' ';
    mouse_hide();

	  button_on(X-15,Y-10,X+125,Y+30,11);
	  settextstyle(0, HORIZ_DIR, 2);
	  outtextxy(X,Y,STR);
    mouse_show();
  }


void Time::RunTime(void)
   {   if(Second>0){
		     if(clockevent==FALSE)
			{ Start=clock(); clockevent=TRUE;}
		     else
			{ End=clock();
			  if((End -Start)/ CLK_TCK >1)
			    { Second--;
			      clockevent=FALSE;
			      Draw_Clock();
			    }
			}
		   }
       else
	   if(Minut>0){ Second=59; Minut--; }
	   else
	       if(Hour>0){ Hour--;Minut=59; }
   }
Time BlackTimer,WhiteTimer;


//#########################################################################

/////////////////////////////////////////////////////////////////////////////
//
//                 ** ChessBoard CLASS **    BEGIN
//
/////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
class Chessboard
 {
   int PieceBoard[8][8];             //Nuden deerh bodnuudiin bairlal {Hoen-5,bers-4,...}
   int BoardColor[8][8];             //Nudnii unguud {0-har,1-tsagaan}
   public :
   int BlackEvaluation;
   int WhiteEvaluation;

   int WhiteKingCheck;
   int BlackKingCheck;
   int TULUB;
   int WhiteKing;                    // Noen hodolBol False bolno;
   int WhiteKingBishop;
   int WhiteQueenBishop;
   int BlackKing;                    // Noen hodolBol False bolno;
   int BlackKingBishop;              // Tereg hodolbol
   int BlackQueenBishop;

   int LastCurrentColumn;
   int LastCurrentRow;
   int LastNextColumn;
   int LastNextRow;
   int LastCurrentPiece;
   int LastNextPiece;

   int ReturnKingRow(int color);
   int ReturnKingColumn(int color);
   void PutLastPosition(int LastCol,int LastRow,int emp)
     {
       PieceBoard[LastCol][LastRow]=emp;
     };
   void BackPieceBoard(int CP,int NP,int CC,int CR,int NC,int NR);
   int ReturnPieceBoard(int column,int row);
   int ReturnBoardColor(int column,int row);
   void PutPieceBoard(int piece,int Ccolumn,int Crow,int Ncolumn,int Nrow);
   //Baiguulagch punkts
   Chessboard();

};

//#####################################################################
   void Chessboard::BackPieceBoard(int CP,int NP,int CC,int CR,int NC,int NR)
    {
      PieceBoard[CC][CR]=CP;
      PieceBoard[NC][NR]=NP;
    };

   int Chessboard::ReturnPieceBoard(int column,int row)
     { return(PieceBoard[column][row]);}

   int Chessboard::ReturnBoardColor(int column,int row)
     {
       return(BoardColor[column][row]);
     };

   int Chessboard::ReturnKingRow(int color)
   {
     for(int row1=0;row1<8;row1++)
      for(int col1=0;col1<8;col1++)
       {
	if(color==White)
	   { if(WHITEKING==PieceBoard[col1][row1])
		return(row1);
	   }
	else
	   {
	     if(BLACKKING==PieceBoard[col1][row1])
		return(row1);
	   }
       }
       return 0;
   };

   void Chessboard::PutPieceBoard(int piece,int Ccolumn,int Crow,int Ncolumn,int Nrow)
     {
       switch(PieceBoard[Ncolumn][Nrow])
	    {
	      case 1: WhiteEvaluation=WhiteEvaluation-100;break;
	      case 2:case 4: WhiteEvaluation=WhiteEvaluation-300;break;
	      case 3: WhiteEvaluation=WhiteEvaluation-500;break;
	      case 5: WhiteEvaluation=WhiteEvaluation-900;break;
	      case 6: WhiteEvaluation=WhiteEvaluation-1000;break;
	      case -1: BlackEvaluation=BlackEvaluation+100;break;
	      case -2:case -4: BlackEvaluation=BlackEvaluation+300;break;
	      case -3: BlackEvaluation=BlackEvaluation+500;break;
	      case -5: BlackEvaluation=BlackEvaluation+900;break;
	      case -6: BlackEvaluation=BlackEvaluation+1000;break;
	      default :break;
	    }
       PieceBoard[Ccolumn][Crow]=EMPTY;
       PieceBoard[Ncolumn][Nrow]=piece;

//       LastCurrentPiece=piece;
//       LastCurrentColumn=Ccolumn;
//       LastCurrentRow=Crow;
//       LastNextColumn=Ncolumn;
//       LastNextRow=Nrow;
     }

  Chessboard::Chessboard()
     {int row1,col1;
      WhiteKing=TRUE;                    // Noen hodolBol False bolno;
      WhiteKingBishop=TRUE;
      WhiteQueenBishop=TRUE;
      BlackKing=TRUE;                    // Noen hodolBol False bolno;
      BlackKingBishop=TRUE;              // Tereg hodolbol
      BlackQueenBishop=TRUE;
      TULUB=FALSE;
      WhiteKingCheck=FALSE;
      BlackKingCheck=FALSE;
      WhiteEvaluation=0;
      BlackEvaluation=0;
      for(row1=0;row1<8;row1++)
	  for(col1=0;col1<8;col1++)
		{
		   BoardColor[col1][row1]=boardcolor[row1][col1];         //board nii nudnii ungu
		   PieceBoard[col1][row1]=pieceboard[row1][col1];
		   switch(PieceBoard[col1][row1])
		    {
		      case 1: WhiteEvaluation=WhiteEvaluation+100;break;
		      case 2:case 4: WhiteEvaluation=WhiteEvaluation+300;break;
		      case 3: WhiteEvaluation=WhiteEvaluation+500;break;
		      case 5: WhiteEvaluation=WhiteEvaluation+900;break;
		      case 6: WhiteEvaluation=WhiteEvaluation+1000;break;
		      case -1: BlackEvaluation=BlackEvaluation-100;break;
		      case -2:case -4: BlackEvaluation=BlackEvaluation-300;break;
		      case -3: BlackEvaluation=BlackEvaluation-500;break;
		      case -5: BlackEvaluation=BlackEvaluation-900;break;
		      case -6: BlackEvaluation=BlackEvaluation-1000;break;

		      default :break;
		    }
		}
     };

int Chessboard::ReturnKingColumn(int color)
   {
     for(int row1=0;row1<8;row1++)
      for(int col1=0;col1<8;col1++)
       {
	 if(color==White)
	    {if(WHITEKING==PieceBoard[col1][row1])
		return(col1);
	    }
	 else
	    {if(BLACKKING==PieceBoard[col1][row1])
		return(col1);
	    }
       }
       return 0;
   };



/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
//                 ** ChessBoard CLASS **    END
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
//                 ** ChessBoard History **    BEGIN
//
/////////////////////////////////////////////////////////////////////////////
/*
typedef struct History
{
 Chessboard Position;
 int CurrentCol;
 int CurrentRow;
 int NextCol;
 int NextRow;
 int CurrentPiece;
 int NextPiece;
 struct History *Prev;
 int index;
};
History *BlackTop=NULL;
History *WhiteTop=NULL;

int BlackPush(Chessboard Pos,int CR,int CC,int NR,int NC,int CP,int NP)
{
  History *P;
  P=(History *)malloc(sizeof(History));
  if(BlackTop==NULL){BlackTop->index=0;}
  else {P->index=BlackTop->index+1;}

  P->CurrentRow=CR;   P->CurrentCol=CC; P->CurrentPiece=CP;
  P->NextRow=NR;      P->NextCol=NC;    P->NextPiece=NP;     P->Position=Pos;
  P->Prev=BlackTop;   BlackTop=P;
}

int WhitePush(Chessboard Pos,int CR,int CC,int NR,int NC,int CP,int NP)
{
  History *P;
  P=(History *)malloc(sizeof(History));
  if(WhiteTop==NULL){WhiteTop->index=0;}
  else {P->index=WhiteTop->index+1;}
  P->CurrentRow=CR;   P->CurrentCol=CC; P->CurrentPiece=CP;
  P->NextRow=NR;      P->NextCol=NC;    P->NextPiece=NP;     P->Position=Pos;

  P->Prev=WhiteTop;WhiteTop=P;
}

void HistoryShow(void)
{ int i=0;
  History *WP,*BP;
  WP=WhiteTop; BP=BlackTop;

  mouse_hide();
  button_on(485,125,625,350,9);

  while(WP!=NULL && i<=5)
    {
       gotoxy(65,15-i);cout<<WP->index<<". ";
		       cout<<char(WP->CurrentCol+65)<<WP->CurrentRow+1<<"-";
		       cout<<char(WP->NextCol+65)<<WP->NextRow+1<<" ";
		       cout<<char(BP->CurrentCol+65)<<BP->CurrentRow+1<<"-";
		       cout<<char(BP->NextCol+65)<<BP->NextRow+1;
       i++;
       WP=WP->Prev;
       BP=BP->Prev;
   }
  mouse_show();

}
 */

//##########################################################################
//
//
//
//##########################################################################

class Panel
{ int TopRow;       int ButtonRow;
  int RightColumn;  int LeftColumn;
  int OnColor;      int OffColor;
  int MouseOn;
  char Text[8];
  public:
  int Visable;
  Panel() { MouseOn=FALSE; Visable=TRUE; };
  void Panel_Set(int rcol,int trow,int lcol,int brow,int onclr,int offclr,char text[8]);
  void Draw_Text(void);
  void DrawPanel_On(int Over);
  void DrawPanel_Off(int Over);
  void Hide_Panel(void);
  int OnMouseUp(void);
};
//********************************Inline Function ***************************
  void Panel::Panel_Set(int rcol,int trow,int lcol,int brow,int onclr,int offclr,char text[8])
  { TopRow=trow; ButtonRow=brow; OnColor=onclr;
    RightColumn=rcol;LeftColumn=lcol;OffColor=offclr;
    for(int i=0;i<8;i++)
      Text[i]=text[i];
  };
  void Panel::Draw_Text(void)
  {
   for(int i=0;i<8;i++)
    {
     DRAW_FONT(Text[i],((RightColumn+LeftColumn)/2-40)+10*i,TopRow+5,2);
    }
  }
   void Panel::DrawPanel_On(int Over)
   { mouse_hide();
     Visable=FALSE;
     if(Over==Up)
      {	Menubutton_on(RightColumn,TopRow,LeftColumn,ButtonRow,OnColor);
	Draw_Text();
      }
     else
      {	Menubutton_on(RightColumn,TopRow,LeftColumn,ButtonRow,OffColor);
	Draw_Text();
      }
     mouse_show();
   };

   void Panel::DrawPanel_Off(int Over)
   { mouse_hide();
     Visable=FALSE;
     if(Over==Up)
       { Menubutton_off(RightColumn,TopRow,LeftColumn,ButtonRow,OnColor);
	 Draw_Text();
       }
     else
       { Menubutton_off(RightColumn,TopRow,LeftColumn,ButtonRow,OffColor);
	 Draw_Text();
       }
     mouse_show();
   };


  int Panel::OnMouseUp(void)
  {
   mouse_info();
   if(Visable==FALSE)
   {
     if(Row>TopRow && Row<ButtonRow && Column>RightColumn && Column<LeftColumn)
      {
	if(MouseButton == Up)
	    {
	      if(MouseOn!=Up)
	       {  DrawPanel_Off(Down);  }
	      MouseOn=Up;

	    }
	else{
	      if(MouseOn != Down)
		  DrawPanel_On(Down);
	      MouseOn=Down;
	    }
      }
     else
      {
       if(MouseOn!=UNKNOWN) { DrawPanel_On(Up);}
       MouseOn=UNKNOWN;
      }
  }
  else MouseOn=UNKNOWN;
  return MouseOn;
  };
  void Panel::Hide_Panel(void)
  {
    Visable=TRUE;
  }
//##########################################################################
//
//
//
//##########################################################################

class CheckBox
{
  int Radius;
  int row;
  int column;
  char Text[20];
  int OnMouse;
  int Checked;
  public:
  int Visable;
  CheckBox(){ Checked=FALSE; Radius=4;Visable=TRUE;}
  void Draw_CheckBox(void);
  void CheckBox_Set(int col,int r,int R,char text[20]);
  void Draw_Text(void);
  void Hide_CheckBox(void){Visable=TRUE;};
  void CheckedToBox(int Bool)
  {
    Checked=Bool;
    Draw_CheckBox();
  }
  int OnMouseUp(void);
};

  int CheckBox::OnMouseUp(void)
  {
   mouse_info();
   if(Visable==FALSE)
   {
     if(Row>row-5 && Row < row+5 && Column>column-5 && Column<column+5)
      {

	if(MouseButton == Up)
	    {
	       OnMouse=Up;
	    }
	else OnMouse=Down;
      }
     else OnMouse=UNKNOWN;
   }
   else OnMouse=UNKNOWN;
   return OnMouse;
  };

  void CheckBox::Draw_Text(void)
   {
     for(int i=0;i<20;i++)
      {
	DRAW_FONT(Text[i],column+i*10,row,2);
      }
   }

  void CheckBox::CheckBox_Set(int col,int r,int R,char text[20])
  { row=r;  column=col; Radius=R;
    for(int i=0;i<20;i++)
      Text[i]=text[i];
  };

 void CheckBox::Draw_CheckBox(void)
  {  mouse_hide();
     int Temp=getcolor();
     if(Checked==TRUE)
	{
	  button_on(column-5,row-5,column+5,row+5,4);
	}
     else
	{
	  button_on(column-5,row-5,column+5,row+5,5);
	}

     setcolor(Temp);
     Visable=FALSE;
     Draw_Text();
     mouse_show();
  }

//##########################################################################
//
//
//
//##########################################################################

class Box
{ protected:
  int TopRow;     int ButtonRow;
  int RightColumn;int LeftColumn;
  int BackGround;
  int MouseOn;
  int Color;      char Text[20];
  public:
  int Visable;
  Box(){Color=BLUE;}

  void Draw_Text(void)
  {
   for(int i=0;i<30;i++)
    {
     DRAW_FONT(Text[i],((RightColumn+LeftColumn)/2-100)+10*i,TopRow+15,0);
    }
  }

  void Draw_Box(void)
  {
     mouse_hide();
     button_on(RightColumn+10,ButtonRow,LeftColumn+10,ButtonRow+10,Black);
     button_on(LeftColumn,TopRow+10,LeftColumn+10,ButtonRow+10,Black);
     button_on(RightColumn,TopRow,LeftColumn,ButtonRow,6);
     setcolor(WHITE);
     rectangle(RightColumn+2,TopRow+2,LeftColumn-2,ButtonRow-2);
     rectangle(RightColumn+3,TopRow+3,LeftColumn-3,ButtonRow-3);
     Draw_Text();  Visable=FALSE;
     mouse_show();
  }

  void Box_Set(int rcol,int trow,int lcol,int brow,char text[20])
  { TopRow=trow;      ButtonRow=brow;
    RightColumn=rcol; LeftColumn=lcol;
    for(int i=0;i<20;i++) Text[i]=text[i];
  };
};
//##########################################################################
//
//
//
//##########################################################################
class AlertBox: public Box
{
  public:
  Panel Ok_Panel;
  AlertBox(){ Visable=TRUE; MouseOn=FALSE;}
  void AlertBox_Set(int rcol,int trow,int lcol,int brow,char text[20]);
  void Draw_AlertBox(void);
  void Hide_AlertBox(void);
  int OnMouseUp(void);
};

 void AlertBox::AlertBox_Set(int rcol,int trow,int lcol,int brow,char text[20])
  { Box_Set(rcol,trow,lcol,brow,text);
    Ok_Panel.Panel_Set((RightColumn+LeftColumn)/2-30,ButtonRow-40,(RightColumn+LeftColumn)/2+30,ButtonRow-23,8,7,"11TiIM11");
  };


  void AlertBox::Draw_AlertBox(void)
   {
     mouse_hide();
     Draw_Box();
     Ok_Panel.DrawPanel_On(TRUE);
     Visable=FALSE;
     mouse_show();
   }

   void AlertBox::Hide_AlertBox(void)
    {
      Visable=TRUE;
    }

 int AlertBox::OnMouseUp(void)
  {
   if(Visable==FALSE)
    {
	 if(Ok_Panel.OnMouseUp()==Up)
	  {
	   return TRUE;
	  }
	 else return UNKNOWN;
   }
   else return UNKNOWN;
 };


//##########################################################################
//
//
//
//##########################################################################

class MessageBox: public Box
{
  public:
  Panel Ok_Panel;
  Panel Cancel_Panel;
  MessageBox(){ Visable=TRUE;MouseOn=FALSE;Color=6;}
  void MessageBox_Set(int rcol,int trow,int lcol,int brow,char text[20]);
  void Draw_MessageBox(void);
  void Hide_MessageBox(void);
  int OnMouseUp(void);
};

 void MessageBox::MessageBox_Set(int rcol,int trow,int lcol,int brow,char text[20])
  { TopRow=trow;      ButtonRow=brow;
    RightColumn=rcol; LeftColumn=lcol;
    Box_Set(rcol,trow,lcol,brow,text);
    Ok_Panel.Panel_Set((RightColumn+LeftColumn)/2-70,ButtonRow-30,(RightColumn+LeftColumn)/2-20,ButtonRow-13,8,7,"11TiIM11");
    Cancel_Panel.Panel_Set((RightColumn+LeftColumn)/2+20,ButtonRow-30,(RightColumn+LeftColumn)/2+70,ButtonRow-13,8,7,"11UGUI11");
  };

  void MessageBox::Draw_MessageBox(void)
   {
     mouse_hide();
     Draw_Box();
     Ok_Panel.DrawPanel_On(TRUE);     Cancel_Panel.DrawPanel_On(TRUE);
     Visable=FALSE;
     mouse_show();

   }

   void MessageBox::Hide_MessageBox(void)
    {   Visable=TRUE;    }

 int MessageBox::OnMouseUp(void)
  {
   if(Visable==FALSE)
    {
      if(Cancel_Panel.OnMouseUp()==Up)
	{ return FALSE;}
      else
	{
	 if(Ok_Panel.OnMouseUp()==Up)
	  {
	   return TRUE;
	  }
	}
    }
   else return UNKNOWN;

    return UNKNOWN;
 };



//###########################################################################
//
//
//
//###########################################################################
class CHESSBOARD
{
  int PieceBlackColor;
  int PieceWhiteColor;
  public:
  int Visable;
  Panel EhlehButton;
  Panel GunButton;
  Panel TohirgooButton;
  Panel GarahButton;
  Panel BackClock;
  Panel NextClock;

//#########################################################################

  CHESSBOARD()
  {
   Visable=FALSE;
   PieceBlackColor=8;
   PieceWhiteColor=7;
   EhlehButton.Panel_Set(25,3,125,20,8,7,"11EHLEH1");
   GunButton.Panel_Set(135,3,235,20,8,7,"1TUBsiN1");
   TohirgooButton.Panel_Set(245,3,345,20,8,7,"111SAG11");
   GarahButton.Panel_Set(355,3,455,20,8,7,"11GARAH1");
   BackClock.Panel_Set(500,105,530,120,8,7,"111<1111");
   NextClock.Panel_Set(560,105,590,120,8,7,"111>1111");
  };

  void MessageBoxErs(Chessboard position)
  {
       mouse_hide();
       for(int r=1;r<=5;r++)
	 {
	  for(int c=1;c<=7;c++)
	   {
	     DrawOn(c*50+75,r*50+75,BoardColor[c][r]);
	     DrawPiece(position.ReturnPieceBoard(c,r),c*50+75,r*50+75);
	    }
	 }
       mouse_show();
  }

   Mouse_Over(Chessboard position)
  {
      int Bol;
//Ehleh Box >
      Bol=EhlehButton.OnMouseUp();
      if(Bol==Up)
       {
	 MessageBox *EhlehMessageBox;
	 EhlehMessageBox= (MessageBox *) malloc(sizeof(MessageBox));
	 EhlehMessageBox->MessageBox_Set(100,100,400,200,"111EHLEH1UU1UTGAA111");
	 EhlehMessageBox->Draw_MessageBox();
	 int Bol1=UNKNOWN;
	 while(Bol1==UNKNOWN)
	   {
	     Bol1=EhlehMessageBox->OnMouseUp();
	   }

	  if(Bol1==Up){ main(); }
	  else
	     {
	       MessageBoxErs(position);
	     }
	  free(EhlehMessageBox);
	  delay(100);
       }
//Ehleh Box <

//Gun Box >
      Bol=GunButton.OnMouseUp();
      if(Bol==Up)
       {
	 MessageBox *GunMessageBox;
	 GunMessageBox= (MessageBox *) malloc(sizeof(MessageBox));
	 GunMessageBox->MessageBox_Set(100,100,400,300,"1111111TUBsiN1111111");
	 GunMessageBox->Draw_MessageBox();

	 CheckBox *Gun_1;
	 Gun_1 = (CheckBox *) malloc(sizeof(CheckBox));
	 Gun_1->CheckBox_Set(140,170,4,"11111Muu1TOGLOGc1111");
	 if(DEPTH==1)Gun_1->CheckedToBox(TRUE);
	 Gun_1->Draw_CheckBox();
	 CheckBox *Gun_3;
	 Gun_3 = (CheckBox *) malloc(sizeof(CheckBox));
	 Gun_3->CheckBox_Set(140,190,4,"1111DuND1TOGLOGc1111");
	 if(DEPTH==3)Gun_3->CheckedToBox(TRUE);
	 Gun_3->Draw_CheckBox();
	 CheckBox *Gun_5;
	 Gun_5 = (CheckBox *) malloc(sizeof(CheckBox));
	 Gun_5->CheckBox_Set(140,210,4,"1111CAiN1TOGLOGc1111");
	 if(DEPTH==4)Gun_5->CheckedToBox(TRUE);
	 Gun_5->Draw_CheckBox();

	 int Depth=DEPTH;
	 int Bol1=UNKNOWN;
	 while(Bol1==UNKNOWN)
	   {
	     if(Gun_1->OnMouseUp()==Up)
	      { Depth=1;
		Gun_1->CheckedToBox(TRUE);
		Gun_3->CheckedToBox(FALSE);
		Gun_5->CheckedToBox(FALSE);
	      }

	     if(Gun_3->OnMouseUp()==Up)
	      { Depth=3;
		Gun_1->CheckedToBox(FALSE);
		Gun_3->CheckedToBox(TRUE);
		Gun_5->CheckedToBox(FALSE);
	      }

	     if(Gun_5->OnMouseUp()==Up)
	      { Depth=4;
		Gun_1->CheckedToBox(FALSE);
		Gun_3->CheckedToBox(FALSE);
		Gun_5->CheckedToBox(TRUE);
	      }

	     Bol1=GunMessageBox->OnMouseUp();
	   }

	  if(Bol1==Up){ DEPTH=Depth;}

	  MessageBoxErs(position);
	  free(Gun_1);
	  free(Gun_3);
	  free(Gun_5);
	  free(GunMessageBox);
	  delay(100);
       }

//Tohirgoo Box >
      Bol=TohirgooButton.OnMouseUp();
      if(Bol==Up)
       {
	 int minut=MINUT+HOUR*60;

	 MessageBox *TohirgooMessageBox;
	 TohirgooMessageBox= (MessageBox *) malloc(sizeof(MessageBox));
	 TohirgooMessageBox->MessageBox_Set(100,100,400,300,"1111111SAG1111111111");
	 TohirgooMessageBox->Draw_MessageBox();

	 Panel *ToUper;
	 ToUper = (Panel *) malloc(sizeof(Panel));

	 ToUper->Panel_Set(150,150,170,165,8,7,"111[1111");
	 ToUper->DrawPanel_On(Up);

	 mouse_hide();
	 textbackground(WHITE);
	 button_on(150,175,170,195,WHITE);
	 char Text[5]="MiNuT";
	 for(int i=0;i<5;i++)
	 {
	  DRAW_FONT(Text[i],200+i*10,180,2);
	 }

	 gotoxy(20,12);cout<<minut;
	 mouse_show();

	 Panel *ToDown;

	 ToDown= (Panel *) malloc(sizeof(Panel));
	 ToDown->Panel_Set(150,200,170,215,8,7,"111]1111");
	 ToDown->DrawPanel_On(Up);

	 int BackBoolToUper=0;
	 int BackBoolToDown=0;
	 int Bol1=UNKNOWN;

	 while(Bol1==UNKNOWN)
	   {
	     int BoolToUper=ToUper->OnMouseUp();

	     if(BoolToUper==Up)
	       {
		 BackBoolToUper=BoolToUper;
	       }
	     else
	       {
		if(BackBoolToUper==Up)
		 {
		  if(90>minut)
		  {  minut++;
		     mouse_hide();
		     textbackground(WHITE);
		     button_on(150,175,170,195,WHITE);
		     gotoxy(20,12);cout<<minut;
		     mouse_show();
		  }
		 }
		BackBoolToUper=BoolToUper;
	       }

	     int BoolToDown=ToDown->OnMouseUp();
	     if(BoolToDown==Up)
	       {
		  BackBoolToDown=BoolToDown;
	       }
	     else
	       {
		 if(BackBoolToDown==Up)
		  {
		    if(1<minut)
		     { minut--;
		       mouse_hide();
		       textbackground(WHITE);
		       button_on(150,175,170,195,WHITE);
		       gotoxy(20,12);cout<<minut;
		       mouse_show();
		     }
		  }
		 BackBoolToDown=BoolToDown;
	       }
	     Bol1=TohirgooMessageBox->OnMouseUp();
	   }

	  if(Bol1==Up)
	       {
		   MINUT=minut%60;
		   HOUR=minut/60;
		   WhiteTimer.Set(HOUR,MINUT);
		   BlackTimer.Set(HOUR,MINUT);
		   WhiteTimer.Draw_Clock();
		   BlackTimer.Draw_Clock();

	       }
	  MessageBoxErs(position);
	  free(TohirgooMessageBox);
	  free(ToUper);
	  free(ToDown);
	  delay(100);
       }
//Tohirgoo Box <
//Garah Box >
      Bol=GarahButton.OnMouseUp();
      if(Bol==Up)
       {
	 MessageBox *GarahMessageBox;
	 GarahMessageBox= (MessageBox *) malloc(sizeof(MessageBox));
	 GarahMessageBox->MessageBox_Set(100,100,400,200,"11TOGLOOMOOC1GARAH11");
	 GarahMessageBox->Draw_MessageBox();
	  int Bol1=UNKNOWN;
	  while(Bol1==UNKNOWN)
	   {
	     Bol1=GarahMessageBox->OnMouseUp();
	   }

	  if(Bol1==Up){ exit(0); }
	  else
	     {
	       MessageBoxErs(position);
	     }
	  free(GarahMessageBox);
	  delay(100);
       }
//Garah Box <

      Bol=BackClock.OnMouseUp();
      Bol=NextClock.OnMouseUp();
      Bol=FALSE;
  return 1;
  }

 //##################### tses baiguulah #################################
     void Menu(void)
     {
	 EhlehButton.DrawPanel_On(Up);
	 GunButton.DrawPanel_On(Up);
	 TohirgooButton.DrawPanel_On(Up);
	 GarahButton.DrawPanel_On(Up);
	 BackClock.DrawPanel_On(Up);
	 NextClock.DrawPanel_On(Up);
     }


  //##################### 		 #################################

  void Time(void)
  {
    button_on(485,50,625,70,11);
    settextstyle(0, HORIZ_DIR, 2);

    outtextxy(500,60,"0:05:00");
    button_on(485,125,625,350,9);

    button_on(485,375,625,415,11);
    outtextxy(500,385,"0:05:00");
  }

  void DrawOn(int col,int row,int color) // Nudee zurna
   {  mouse_hide();
      button_on(col-25,row-25,col+25,row+25,color);
      mouse_show();
   }

  int ReturnPieceColor(int color)
  {    if(color==0 || color==15)
	  return TRUE;
       else return FALSE;
  }
  void DrawPiece(int piece,int col,int row)
  { mouse_hide();
    switch(piece)
    {
     case -1: dursdraw(Pawnpixel,col-18,row-18,BLACK,1);break;
     case -2: dursdraw(Knightpixel,col-18,row-18,BLACK,2);break;
     case -3: dursdraw(Bishoppixel,col-18,row-18,BLACK,3);break;
     case -4: dursdraw(Rookpixel,col-18,row-18,BLACK,4);break;
     case -5: dursdraw(Queenpixel,col-18,row-18,BLACK,5);break;
     case -6: dursdraw(Kingpixel,col-18,row-18,BLACK,6);break;
     case  1: dursdraw(Pawnpixel,col-18,row-18,WHITE,1);break;
     case  2: dursdraw(Knightpixel,col-18,row-18,WHITE,2);break;
     case  3: dursdraw(Bishoppixel,col-18,row-18,WHITE,3);break;
     case  4: dursdraw(Rookpixel,col-18,row-18,WHITE,4);break;
     case  5: dursdraw(Queenpixel,col-18,row-18,WHITE,5);break;
     case  6: dursdraw(Kingpixel,col-18,row-18,WHITE,6);break;
     default :break;
    }
    mouse_show();
  }

  void DrawBoard()
   {  int row,col;
      int size=50;  int X=50,Y=50,color=PieceWhiteColor; int bool=1;

      setfillstyle(BLUE,LIGHTBLUE);
      bar(0,0,getmaxx(),getmaxy());

      button_off(X-20,Y-20,X+420,Y+420,7);

      for(col=0;col<8;col++)
       {   Y=50;
	   for(row=0;row<8;row++)
		    {  button_on(X,Y,X+50,Y+50,color); Y=Y+50;
		       if(bool==1) { bool=0; color=PieceBlackColor;}
		       else 	   { bool=1; color=PieceWhiteColor;}
		    }
	    X=X+50;
	    if(color==PieceWhiteColor){color=PieceBlackColor;bool=0;}
	    else {color=PieceWhiteColor;bool=1;}
       }
//      setcolor(0);
      settextstyle(1, 0, 2);
      outtextxy(75,447,"A");     outtextxy(35,60,"8");
      outtextxy(125,447,"B");     outtextxy(35,110,"7");
      outtextxy(175,447,"C");     outtextxy(35,160,"6");
      outtextxy(225,447,"D");     outtextxy(35,210,"5");
      outtextxy(275,447,"E");     outtextxy(35,260,"4");
      outtextxy(325,447,"F");     outtextxy(35,310,"3");
      outtextxy(375,447,"G");     outtextxy(35,360,"2");
      outtextxy(425,447,"H");     outtextxy(35,410,"1");
      //durs zurah
      for(row=0;row<8;row++)
       for(col=0;col<8;col++)
	{
	 DrawPiece(pieceboard[col][row],BoardCenterRow[row],BoardCenterColumn[col]);
	}
     Menu();
     Time();
    };
 };

/////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// OK
// 				** Class Rook ** BEGIN
//
///////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

class Rook  //-3
{ public:
  int TestRook(Chessboard,int,int,int,int,int,int);
}rook;
//****************************** inline function ROOK**********************

int Rook::TestRook(Chessboard Position,int piece,int Npiece,int Ccol,int Crow,int Ncol,int Nrow)
{  int row1,col1,result=FALSE;

    if(piece>0 &&(Ccol+Crow==Nrow+Ncol||Ccol+Nrow==Crow+Ncol)&&Npiece<=0||
       piece<0 &&(Ccol+Crow==Nrow+Ncol||Ccol+Nrow==Crow+Ncol)&&Npiece>=0)
	  {
	      if((Nrow > Crow) && (Ccol+Crow==Nrow+Ncol))
		 {
		    if(abs(Nrow-Crow)==1 && abs(Ncol-Ccol)==1)
			 result=TRUE;
		    else
		      {  col1=Ccol-1;
			 for(row1=Crow+1;row1 < Nrow;row1=row1+1)
			  {
			   if(Position.ReturnPieceBoard(col1,row1)!=EMPTY)
				 return(FALSE);
			   col1=col1-1;
			  }
			 result=TRUE;
		      }
		};
	     if((Nrow < Crow) && (Ccol+Crow==Nrow+Ncol))
		{
		   if(abs(Nrow-Crow)==1 && abs(Ncol-Ccol)==1)
			  result=TRUE;
		   else
		      {
			 row1=Crow-1;
			 for(col1=Ccol+1;col1< Ncol;col1=col1+1)
			      {
				if(Position.ReturnPieceBoard(col1,row1)!=EMPTY)
				     return(FALSE);
				row1=row1-1;
			      }
			 result=TRUE;
		      }
		};
	    if((Ccol>Ncol)&&(Ccol+Nrow==Crow+Ncol))
		 {
		   if(abs(Nrow-Crow)==1 && abs(Ncol-Ccol)==1)
			    result=TRUE;
		   else
		      {   row1=Nrow+1;
			  for(col1=Ncol+1;col1<Ccol;col1=col1+1)
			       {
				if(Position.ReturnPieceBoard(col1,row1)!=EMPTY)
					return(FALSE);
				row1=row1+1;
			       }
			  result=TRUE;
		      }
		 };
	    if((Ccol<Ncol)&&(Ccol+Nrow==Crow+Ncol))
		 {
		   if(abs(Nrow-Crow)==1 && abs(Ncol-Ccol)==1)
			  result=TRUE;
		   else
		      {   row1=Crow+1;
			  for(col1=Ccol+1; col1 < Ncol;col1=col1+1)
			       {
				if(Position.ReturnPieceBoard(col1,row1)!=EMPTY)
					return(FALSE);
				row1=row1+1;
			       }
			   result=TRUE;
		      }
		  }
      }
   return(result);
  };
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//   OK
// 				** Class Rook ** END
//
///////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// OK
//			Class Bishop      BEGIN;
//
//
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

class Bishop
{ public:
//  int TestBishop(Chessboard,int,int,int,int,int);
int TestBishop(Chessboard Position,int piece,int Npiece,int Ccol,int Crow,int Ncol,int Nrow)
{ int row1,col1,result=FALSE;
   if(Ccol==Ncol|| Crow==Nrow)
    { if((Npiece<=EMPTY && piece > EMPTY) || (Npiece>=EMPTY && piece<EMPTY))
      {
	     if(Ccol==Ncol)
	       {
		  if(Crow > Nrow)
		      {
			if(abs(Crow-Nrow)==1)
			   { result=TRUE;}
			else
			   {
			     for(row1=Nrow+1;row1<Crow;row1=row1+1)
			       {
				if(Position.ReturnPieceBoard(Ncol,row1)!=EMPTY)
				    return(FALSE);
			       }
			     result=TRUE;
			   }
		      }
		  else
		     {
		      if(abs(Crow-Nrow)==1)
			{ result=TRUE;}
		      else
			{
			  for(row1=Crow+1; row1 < Nrow;row1=row1+1)
			    {
			      if(Position.ReturnPieceBoard(Ccol,row1)!=EMPTY)
				    return(FALSE);
			     }
			  result=TRUE;
			}
		     }
	       }
	      else
	       {
		if(Ccol > Ncol)
		   {
		     if(abs(Ccol-Ncol)==1)
			{ result=TRUE;}
		     else
			{
			  for(col1=Ncol+1; col1 < Ccol; col1=col1+1)
			    {
			      if(Position.ReturnPieceBoard(col1,Nrow)!=EMPTY)
				    return(FALSE);
			     }
			  result=TRUE;
			}
		   }
		else
		   {
		     if(abs(Ccol-Ncol)==1)
			{result=TRUE;}
		     else
			{
			  for(col1=Ccol+1; col1 < Ncol;col1=col1+1)
			    {
			       if(Position.ReturnPieceBoard(col1,Crow)!=EMPTY)
				  return(FALSE);
			    }
			  result=TRUE;
			}
		   }
	      }
       }
    }//if ========
    return(result);
   };//test end
}bishop;

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//
//			Class Bishop      END;
//
//
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// OK
//                      CLass Knight BEGIN:
//
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

class Knight
 {
   public:
   int TestKnight(Chessboard,int piece,int Npiece,int Ccol,int Crow,int Ncol,int Nrow);
 }knight;

int Knight::TestKnight(Chessboard Position,int piece,int Npiece,int Ccol,int Crow,int Ncol,int Nrow)
{ int result=FALSE;
      if((piece<0 && Npiece>=0)||(piece>0 && Npiece<=0))
      {
	if((abs(Ccol-Ncol)==2 && abs(Crow-Nrow)==1)||(abs(Crow-Nrow)==2 && abs(Ccol-Ncol)==1))
	   {  result=TRUE; }
      }
   return result;
}
/////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//
//                      CLass Knight END:
//
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// OK
//                      CLass PAWN  BEGIN:
//
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

class Pawn
{ public:
  int TestPawn(Chessboard Position,int piece,int Npiece,int Ccol,int Crow,int Ncol,int Nrow);
}pawn;

int Pawn::TestPawn(Chessboard Position,int piece,int Npiece,int Ccol,int Crow,int Ncol,int Nrow)
   { int result=FALSE;
      if(piece>0)
       {

	 if(Crow==6)
	     {
		if(Npiece==EMPTY && Crow-Nrow==2 && Ccol==Ncol && Position.ReturnPieceBoard(Ccol,Crow-1)==EMPTY)
		       result=TRUE;
		else
		  {
		    if(Npiece==EMPTY && Crow-Nrow==1 && Ccol==Ncol)
			 result=TRUE;
		    else
			if(Npiece<EMPTY && Crow-Nrow==1 && abs(Ccol-Ncol)==1)
			      result=TRUE;
		  }
	     }
	  else
	     {
	       if(Crow==3)
		 {
		    if(Crow-Nrow==1 && abs(Ccol-Ncol)==1 && Npiece==EMPTY && Position.LastCurrentPiece==BLACKPAWN && Position.LastNextRow==Crow
		       && abs(Position.LastNextColumn-Ccol)==1)
		       {
			 result=TRUE;
		       }
		    else
		       {
			  if(Crow-Nrow==1 && Ccol==Ncol && Npiece==EMPTY)
			     result=TRUE;
			  else
			      if(Crow-Nrow==1 && abs(Ccol-Ncol)==1 && Npiece<EMPTY)
				 result=TRUE;
		       }
		 }
		else
		 {
		   if(Crow-Nrow==1 && Ccol==Ncol && Npiece==EMPTY)
		       result=TRUE;
		   else
		     {
		      if(Crow-Nrow==1 && abs(Ccol-Ncol)==1 && Npiece<EMPTY)
			 result=TRUE;
		     }
		 }
	   }
	}
      else
       {
	  if(Crow==1)
	     {
		if(Npiece==EMPTY && Nrow-Crow==2 && Ccol==Ncol && Position.ReturnPieceBoard(Ccol,Nrow-1)==EMPTY)
		       result=TRUE;
		else
		  {
		    if(Npiece==EMPTY && Nrow-Crow==1 && Ccol==Ncol)
			 result=TRUE;
		    else
			if(Npiece>EMPTY && Nrow-Crow==1 && abs(Ccol-Ncol)==1)
			      result=TRUE;
		  }
	     }
	  else
	     {
	       if(Crow==3)
		 {
		    if(Nrow-Crow==1 && abs(Ccol-Ncol)==1 && Npiece==EMPTY && Position.LastCurrentPiece==WHITEPAWN && Position.LastNextRow==Crow && abs(Position.LastNextColumn-Ccol)==1)
		       {
			 result=TRUE;
		       }
		    else
		       {
			 if(Nrow-Crow==1 && Ccol==Ncol && Npiece==EMPTY)
			     result=TRUE;
			 else
			    if(Nrow-Crow==1 && abs(Ccol-Ncol)==1 && Npiece>EMPTY)
			       result=TRUE;
		       }
		 }
		else
		 {
		   if(Nrow-Crow==1 && Ccol==Ncol && Npiece==EMPTY)
		       result=TRUE;
		   else
		     {
		      if(Nrow-Crow==1 && abs(Ccol-Ncol)==1 && Npiece>EMPTY)
			 result=TRUE;
		     }
		 }
	   }

       }
    return result;
   };

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//
//                      CLass PAWN  END:
//
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// OK
//                      CLass Queen  BEGIN:
//
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

class Queen
{ public:
   int TestQueen(Chessboard Position,int piece,int Npiece,int Ccol,int Crow,int Ncol,int Nrow)
    { int result=FALSE;
      int Tbishop=bishop.TestBishop(Position,piece,Npiece,Ccol,Crow,Ncol,Nrow);
      int Trook  =rook.TestRook(Position,piece,Npiece,Ccol,Crow,Ncol,Nrow);
       if(Tbishop!=Trook)
	 {
	  if(Tbishop==TRUE || Trook==TRUE)
	     {
	       return(TRUE);
	     }
	 }
      return(result);
     };

}queen;

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//
//                      CLass Queen  END:
//
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

long Evaluate(Chessboard Position);
struct DataList
{int CurrentRow;
 int CurrentColumn;
 int NextRow;
 int NextColumn;
 int CurrentPiece;
 int NextPiece;
}Data[6];

int AlphaBeta(Chessboard Position,int depth, int alpha, int beta,int color);
/*********************************************************************/
/*
/*          List   BEGIN
/*
/**********************************************************************/
/*******************************************************/
class LIST
{ public:
  struct List
  {
   int CurrentRow;
   int CurrentColumn;
   int NextRow;
   int NextColumn;
   int CurrentPiece;
   int NextPiece;
  }Lister[64];
  int Index;
  int i;
  LIST(){Index=0;}
  void ListPush(int Cpiece,int Npiece,int Ccol,int Crow,int Ncol,int Nrow);
}LISTER[6];

void LIST::ListPush(int Cpiece,int Npiece,int Ccol,int Crow,int Ncol,int Nrow)
{    Lister[Index].CurrentPiece=Cpiece;
     Lister[Index].NextPiece=Npiece;
     Lister[Index].CurrentColumn=Ccol;
     Lister[Index].CurrentRow=Crow;
     Lister[Index].NextColumn=Ncol;
     Lister[Index].NextRow=Nrow;
     Index++;
}
long P=0;
void ListAdd(Chessboard Position,int color,int depth);
/*********************************************************************/
/*
/*          List   END;
/*
/**********************************************************************/
Chessboard Temp[6];

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
//                              Class King BEGIN;
//
/////////////////////////////////////////////////////////////////////////////
int test(Chessboard position,int piece,int Npiece,int ccol,int crow,int ncol,int nrow);
int KingTestPiece(Chessboard Position,int piece,int Npiece,int Ccol,int Crow,int Ncol,int Nrow);

/////////////////////////////////////////////////////////////////////////////
 class King
  { public:
    int TestKing(Chessboard,int,int,int,int,int,int);
    int TestKingCheck(Chessboard,int color);
    int TestKingSelgee(Chessboard,int,int,int,int,int,int);
   } king;


int TestKingMate(Chessboard Position,int color)
{       int depth=0;
	Chessboard Temp=Position;
	ListAdd(Position,color,depth);
	for(LISTER[depth].i=0;LISTER[depth].i < LISTER[depth].Index;LISTER[depth].i++)
	 {
	   Position.PutPieceBoard(LISTER[depth].Lister[LISTER[depth].i].CurrentPiece,LISTER[depth].Lister[LISTER[depth].i].CurrentColumn,LISTER[depth].Lister[LISTER[depth].i].CurrentRow,LISTER[depth].Lister[LISTER[depth].i].NextColumn,LISTER[depth].Lister[LISTER[depth].i].NextRow);
	   if(king.TestKingCheck(Position,color)==TRUE)
		  return TRUE;
	   Position=Temp;
	}
 return FALSE;
}
/*
*/

int King::TestKingCheck(Chessboard Position,int color)
 { int row1,col1,result=TRUE;
   int Krow,Kcol;
   for(row1=0;row1<8;row1++)
     for(col1=0;col1<8;col1++)
      {
	if(color==White)
	    {
	     if(Position.ReturnPieceBoard(col1,row1)==WHITEKING)
	       {Kcol=col1; Krow=row1; goto A1;}
	    }
	else{
	     if(Position.ReturnPieceBoard(col1,row1)==BLACKKING)
	       {Kcol=col1; Krow=row1; goto A1;}
	    }
      }
   A1:
//  Kcol=Position.ReturnKingColumn(color);
//  Krow=Position.ReturnKingRow(color);
   if(color==White)
    {
       for(row1=0;row1<=7;row1=row1+1)
	  for(col1=0;col1<=7;col1=col1+1)
	     {
	       int TempPiece=Position.ReturnPieceBoard(col1,row1);
	       if(TempPiece < EMPTY)
		 {
		  if(test(Position,TempPiece,WHITEPAWN,col1,row1,Kcol,Krow)==TRUE)
		    {
			return(FALSE);
		    }
		 }
	      }
    }
   else
    {
      for(row1=0;row1<=7;row1=row1+1)
	  for(col1=0;col1<=7;col1=col1+1)
	     { int TempPiece=Position.ReturnPieceBoard(col1,row1);
	       if(TempPiece >EMPTY)
		 {
		   if(test(Position,TempPiece,BLACKPAWN,col1,row1,Kcol,Krow)==TRUE)
		    {
		      return(FALSE);
		    }
		 }
	      }
    }
 return(result);
}

int King::TestKingSelgee(Chessboard Position,int piece,int Npiece,int Ccol,int Crow,int Ncol,int Nrow)
 {      Chessboard TempPosition;int result=FALSE;
	 if(piece>0)
	  {
	     // 0-0 selgeeg shalgah
		 if((Ncol-Ccol)==2 && Nrow==Crow && Nrow==7 && Position.WhiteKing==TRUE && Position.WhiteKingBishop==TRUE)
		    {
		     if(Position.ReturnPieceBoard(5,7)==EMPTY && Position.ReturnPieceBoard(6,7)==EMPTY)
		       {
			  TempPosition=Position;
			  TempPosition.PutPieceBoard(WHITEKING,4,7,5,7);
			  if(king.TestKingCheck(TempPosition,White)==TRUE)
			     {
			       result=TRUE;
			     };
		      }
		    }
		   if((Ccol-Ncol)==2 && Nrow==Crow && Nrow==7 && Position.WhiteKing==TRUE && Position.WhiteQueenBishop==TRUE)
		    {
		     if(Position.ReturnPieceBoard(1,7)==EMPTY && Position.ReturnPieceBoard(2,7)==EMPTY&& Position.ReturnPieceBoard(3,7)==EMPTY)
		       {
			  TempPosition=Position;
			  TempPosition.PutPieceBoard(WHITEKING,4,7,3,7);
			  if(king.TestKingCheck(TempPosition,White)==TRUE)
			     {
			       result=TRUE;
			     };
		       }
		    }
	  }
	  else
		{ // 0-0 selgeeg shalgah
		  if((Ncol-Ccol)==2 && Nrow==Crow && Nrow==0 && Position.BlackKing==TRUE && Position.BlackKingBishop==TRUE)
		    {
		     if(Position.ReturnPieceBoard(5,0)==EMPTY && Position.ReturnPieceBoard(6,0)==EMPTY)
		       {
			  TempPosition=Position;
			  TempPosition.PutPieceBoard(BLACKKING,4,0,5,0);
			  if(king.TestKingCheck(TempPosition,Black)==TRUE)
			     {
			       result=TRUE;
			     };
		      }
		    }
		   if((Ccol-Ncol)==2 && Nrow==Crow && Nrow==0 && Position.BlackKing==TRUE && Position.BlackQueenBishop==TRUE)
		    {
		     if(Position.ReturnPieceBoard(1,0)==EMPTY && Position.ReturnPieceBoard(2,0)==EMPTY&& Position.ReturnPieceBoard(3,0)==EMPTY)
		       {
			  TempPosition=Position;
			  TempPosition.PutPieceBoard(BLACKKING,4,0,3,0);
			  if(king.TestKingCheck(TempPosition,Black)==TRUE)
			     {
			       result=TRUE;
			     };
		       }
		    }
		}

      return result;
 }

int King::TestKing(Chessboard Position,int piece,int Npiece,int Ccol,int Crow,int Ncol,int Nrow)
 {   int result=FALSE,col1,row1;
     if(piece==6)
      {
       if(Npiece<=0)
	   {
	    if(abs(Ccol-Ncol)==1&&abs(Crow-Nrow)==1||abs(Ccol-Ncol)==1&&Crow==Nrow || abs(Crow-Nrow)==1&&Ccol==Ncol)
		  {
		    result=TRUE;
		  }
	   }
      }
     else
       {
	 if(Npiece>=0)
	    {
	      if( abs(Ccol-Ncol)==1&&Crow==Nrow||abs(Crow-Nrow)==1&&Ccol==Ncol||abs(Ccol-Ncol)==1&&abs(Crow-Nrow)==1)
		{
		  result=TRUE;
		}
	    }
       }
 return(result);
};

int test(Chessboard position,int piece,int Npiece,int ccol,int crow,int ncol,int nrow)
{ int result;
  switch(piece)
   {
   case 1:case -1:result=pawn.TestPawn(position,piece,Npiece,ccol,crow,ncol,nrow);break;
   case 2:case -2:result=knight.TestKnight(position,piece,Npiece,ccol,crow,ncol,nrow);break;
   case 3:case -3:result=bishop.TestBishop(position,piece,Npiece,ccol,crow,ncol,nrow);break;
   case 4:case -4:result=rook.TestRook(position,piece,Npiece,ccol,crow,ncol,nrow);break;
   case 5:case -5:result=queen.TestQueen(position,piece,Npiece,ccol,crow,ncol,nrow);break;
   case 6:case -6:result=king.TestKing(position,piece,Npiece,ccol,crow,ncol,nrow);break;
   }
  return(result);
}

int TestPiece(Chessboard Position,int piece,int Npiece,int ccol,int crow,int ncol,int nrow)
{
  int result=FALSE;
  Chessboard NextBoard;

  NextBoard=Position;
  NextBoard.PutPieceBoard(piece,ccol,crow,ncol,nrow);

  if(piece > EMPTY)
     {
	    if(piece==WHITEKING && abs(ncol-ccol)==2 && nrow==crow && nrow==7)
	      {
		 if(king.TestKingSelgee(Position,piece,Npiece,ccol,crow,ncol,nrow)==TRUE)
		     { result=TRUE;};
	      }
	    else
	      {
		 if(test(Position,piece,Npiece,ccol,crow,ncol,nrow)==TRUE)
		     {
		       if(king.TestKingCheck(NextBoard,White)==TRUE)
			     result=TRUE;////////////////////
		     };
	      }
     }
  else
     {
	    if(piece==BLACKKING && abs(ncol-ccol)==2 && nrow==crow && nrow==0)
	      {
		 if(king.TestKingSelgee(Position,piece,Npiece,ccol,crow,ncol,nrow)==TRUE)
		     {
			result=TRUE;
		     };
	      }
	    else
	      {
		if(test(Position,piece,Npiece,ccol,crow,ncol,nrow)==TRUE)
		     {
		       if(king.TestKingCheck(NextBoard,Black)==TRUE)
			     result=TRUE;
		     }

	      }

     }
  NextBoard=Position;
  return result;
}

Chessboard TestPiece1(Chessboard Position,int piece,int Npiece,int ccol,int crow,int ncol,int nrow)
{
  Chessboard NextBoard;
  Position.TULUB=FALSE;
  NextBoard=Position;
  NextBoard.PutPieceBoard(piece,ccol,crow,ncol,nrow);
  if(piece > EMPTY)
     {
       if(piece==WHITEKING && abs(ncol-ccol)==2 && nrow==crow && nrow==7)
	      {
		 if(king.TestKingSelgee(Position,piece,Npiece,ccol,crow,ncol,nrow)==TRUE)
		     {
		      if(ncol-ccol==2)
		       { Position.PutPieceBoard(piece,ccol,crow,ncol,nrow);
			 Position.PutPieceBoard(WHITEBISHOP,7,7,5,7);
			 Position.TULUB=TRUE;
			 Position.WhiteKing=FALSE;
			 Position.WhiteKing=FALSE;
		       }
		      else
		       { Position.PutPieceBoard(piece,ccol,crow,ncol,nrow);
			 Position.PutPieceBoard(WHITEBISHOP,0,7,3,7);
			 Position.TULUB=TRUE;
			 Position.WhiteKing=FALSE;
			 Position.WhiteQueenBishop=FALSE;
		       }
		     };
	      }
	    else
	      {
		if(WHITEPAWN==piece && Npiece==EMPTY && crow==3 && crow-nrow==1 && abs(ccol-ncol)==1)
		  {
		  if(test(Position,piece,Npiece,ccol,crow,ncol,nrow)==TRUE)
		      {
			Position.TULUB=TRUE;
			Position.PutPieceBoard(piece,ccol,crow,ncol,nrow);
			Position.PutPieceBoard(EMPTY,Position.LastNextColumn,Position.LastNextRow,Position.LastNextColumn,Position.LastNextRow);
			if(king.TestKingCheck(Position,Black)==FALSE)
				{
				   Position.BlackKingCheck=TRUE;
				}
		      }
		  }
		else
		  {
		    if(crow==1 && WHITEPAWN==piece && Npiece==EMPTY && ccol==ncol && crow-nrow==1 || crow==1 &&WHITEPAWN==piece && Npiece<EMPTY && abs(ccol-ncol)==1 && crow-nrow==1 )
		     {
		       // DISPLAY duudna
			Position.PutPieceBoard(WHITEQUEEN,ccol,crow,ncol,nrow);
			Position.TULUB=TRUE;

			if(king.TestKingCheck(Position,Black)==TRUE)
				{
				   Position.BlackKingCheck=TRUE;
				}
		     }
		     else
		      {
		       if(test(Position,piece,Npiece,ccol,crow,ncol,nrow)==TRUE)
			 {
			   if(king.TestKingCheck(NextBoard,White)==TRUE)
			    {
			       Position.PutPieceBoard(piece,ccol,crow,ncol,nrow);
			       Position.TULUB=TRUE;
			      if(piece==WHITEBISHOP && ccol==0 && crow==7)
				{ Position.WhiteQueenBishop=FALSE; }
			      if(piece==WHITEBISHOP && ccol==7 && crow==7)
				{ Position.WhiteKingBishop=FALSE;}
			      if(piece==WHITEKING)
				{ Position.WhiteKing=FALSE;}

			      if(king.TestKingCheck(Position,Black)==FALSE)
				{
				   Position.BlackKingCheck=TRUE;
				}
			    }
			 };
		      }
		 }
	      }
     }
  else
     {
	    if(piece==BLACKKING && abs(ncol-ccol)==2 && nrow==crow && nrow==0)
	      {
		 if(king.TestKingSelgee(Position,piece,Npiece,ccol,crow,ncol,nrow)==TRUE)
		     {
		      if(ncol-ccol==2)
			{ Position.PutPieceBoard(piece,ccol,crow,ncol,nrow);
			  Position.PutPieceBoard(BLACKBISHOP,7,0,5,0);
			  Position.TULUB=TRUE;
			  Position.BlackKing=FALSE;
			  Position.BlackKingBishop=FALSE;
			}
		      else
			{ Position.PutPieceBoard(piece,ccol,crow,ncol,nrow);
			  Position.PutPieceBoard(BLACKBISHOP,0,0,3,0);
			  Position.TULUB=TRUE;
			  Position.BlackKing=FALSE;
			  Position.BlackQueenBishop=FALSE;
			}
		     };
	      }
	    else
	      {

	       if(BLACKPAWN==piece && Npiece==EMPTY && crow==5 && nrow-crow==1 && abs(ccol-ncol)==1)
		  {
		     if(test(Position,piece,Npiece,ccol,crow,ncol,nrow)==TRUE)
		      {
			Position.TULUB=TRUE;
			Position.PutPieceBoard(piece,ccol,crow,ncol,nrow);
			Position.PutPieceBoard(EMPTY,Position.LastNextColumn,Position.LastNextRow,Position.LastNextColumn,Position.LastNextRow);
			if(king.TestKingCheck(Position,White)==TRUE)
				{
				   Position.WhiteKingCheck=TRUE;
				}
		      }
		   }
	       else
		  {
		    if(crow==6 && BLACKPAWN==piece && Npiece==EMPTY && ccol==ncol && nrow-crow==1 || crow==6 &&BLACKPAWN==piece && Npiece>EMPTY && abs(ccol-ncol)==1 && nrow-crow==1 )
		       {
			// DISPLAY duudna
			Position.PutPieceBoard(BLACKQUEEN,ccol,crow,ncol,nrow);
			if(king.TestKingCheck(Position,White)==TRUE)
				{
				   Position.WhiteKingCheck=TRUE;
				}
		       }
		    else
		      {
			if(test(Position,piece,Npiece,ccol,crow,ncol,nrow)==TRUE)
			   {
			     if(king.TestKingCheck(NextBoard,Black)==TRUE)
				{
				 Position.PutPieceBoard(piece,ccol,crow,ncol,nrow);
				 Position.TULUB=TRUE;
				 if(piece==BLACKBISHOP && ccol==0 && crow==0)
				    Position.BlackQueenBishop=FALSE;
				 if(piece==BLACKBISHOP && ccol==7 && crow==0)
				    Position.BlackKingBishop=FALSE;
				 if(piece==BLACKKING)
				    Position.BlackKing=FALSE;
				 if(king.TestKingCheck(Position,White)==FALSE)
				   {
				    Position.WhiteKingCheck=TRUE;
				   }
				}
			   }
		      }
		  }
	    }
     }

  NextBoard=Position;
  return Position;
}
IsTentsee(void)
{
       AlertBox *T;
       delay(2000);
       T= (AlertBox *) malloc(sizeof(AlertBox));
       T->AlertBox_Set(100,100,400,200,"1111111TENSEE1111111");
       T->Draw_AlertBox();
       int Bol=UNKNOWN;
       while(Bol==UNKNOWN)
       { Bol=T->OnMouseUp();}
       free(T);
       delay(200);
       main();
}

int IsGameOver(Chessboard Position,int color)
{
 MessageBox *GameOver;
 if(TestKingMate(Position,color)==FALSE)
    {
       delay(2000);
       GameOver=(MessageBox *) malloc(sizeof(MessageBox));
       if(color==White)
	    {
	      if(Position.WhiteEvaluation<=1300)
	      {
	       IsTentsee();
	      }
	      else
	      {
	      GameOver->MessageBox_Set(100,100,400,200,"11111HAR1HOJLOO11111");
	      }
	     }
       else {
	      if(Position.BlackEvaluation>=-1300)
	      {
	       IsTentsee();
	      }
	      else
	      {
		GameOver->MessageBox_Set(100,100,400,200,"11sAGAAN1HOJLOO11111");
	      }
	    }
       GameOver->Draw_MessageBox();
       int Bol=UNKNOWN;
       while(Bol==UNKNOWN)
       { Bol=GameOver->OnMouseUp();}
       free(GameOver);
       delay(200);
       return TRUE;
  }
 else return FALSE;
}

Chessboard Run(Chessboard CurrentBoard,CHESSBOARD ChessBoard)
{
   unsigned int MousePositionColor;
   int TestPositionResult;
   int CurrentColumn50,CurrentRow50,CurrentColumn8,CurrentRow8,column1,row1;
   int NextColumn50,NextRow50,NextColumn8,NextRow8;
   int piece,color,Npiece;
   CurrentBoard.TULUB=0;
   mouse_info();

   column1=Column;row1=Row;
   switch(MouseButton)
      {
	 case 1:{
		  if(Column>50&&Column<450&&Row>50&&Row<450)
		     {
		       CurrentRow8=int(Row/50)-1;         CurrentRow50=CurrentRow8*50+75;
		       CurrentColumn8=int(Column/50)-1;   CurrentColumn50=CurrentColumn8*50+75;

		       piece=CurrentBoard.ReturnPieceBoard(CurrentColumn8,CurrentRow8);

		       if(piece!=0)
			 {
			    mouse_limited(75,75,425,425);
			    mouse_put(CurrentColumn50,CurrentRow50);

			    while(MouseButton==1)
			     {
			       mouse_info();
			       if((Column!=column1)||(Row!=row1))
				{ //mouse_delay();
				    ChessBoard.DrawOn(((column1-18)/50-1)*50+75,((row1-18)/50-1)*50+75,BoardColor[((column1-18)/50-1)][((row1-18)/50-1)]);
				    if(!((CurrentColumn8==(column1-18)/50-1)&&(CurrentRow8==(row1-18)/50-1)))
				      {
				       ChessBoard.DrawPiece(CurrentBoard.ReturnPieceBoard(((column1-18)/50-1),((row1-18)/50-1)),((column1-18)/50-1)*50+75,((row1-18)/50-1)*50+75);
				      }
				    ChessBoard.DrawOn(((column1+18)/50-1)*50+75,((row1+18)/50-1)*50+75,BoardColor[((column1+18)/50-1)][((row1+18)/50-1)]);
				     if(!((CurrentColumn8==(column1+18)/50-1)&&(CurrentRow8==(row1+18)/50-1)))
				      {
					ChessBoard.DrawPiece(CurrentBoard.ReturnPieceBoard(((column1+18)/50-1),((row1+18)/50-1)),((column1+18)/50-1)*50+75,((row1+18)/50-1)*50+75);
				      }

				      ChessBoard.DrawOn(((column1+18)/50-1)*50+75,((row1-18)/50-1)*50+75,BoardColor[((column1+18)/50-1)][((row1-18)/50-1)]);
				      if(!((CurrentColumn8==(column1+18)/50-1)&&(CurrentRow8==(row1-18)/50-1)))
				      {
					ChessBoard.DrawPiece(CurrentBoard.ReturnPieceBoard(((column1+18)/50-1),((row1-18)/50-1)),((column1+18)/50-1)*50+75,((row1-18)/50-1)*50+75);
				      }

				      ChessBoard.DrawOn(((column1-18)/50-1)*50+75,((row1+18)/50-1)*50+75,BoardColor[((column1-18)/50-1)][((row1+18)/50-1)]);
				      if(!((CurrentColumn8==(column1-18)/50-1)&&(CurrentRow8==(row1+18)/50-1)))
				      {
					ChessBoard.DrawPiece(CurrentBoard.ReturnPieceBoard(((column1-18)/50-1),((row1+18)/50-1)),((column1-18)/50-1)*50+75,((row1+18)/50-1)*50+75);
				      }

				      ChessBoard.DrawPiece(piece,Column,Row);
				   }
			       column1=Column; row1=Row;
			      }


			     NextRow8=int(Row/50)-1;         NextRow50=NextRow8*50+75;
			     NextColumn8=int(Column/50)-1;   NextColumn50=NextColumn8*50+75;
			     Npiece=CurrentBoard.ReturnPieceBoard(NextColumn8,NextRow8);


			     if(NextRow8!=CurrentRow8 || CurrentColumn8!=NextColumn8)
			      {
				if(HumanPlayer==White && piece>EMPTY || HumanPlayer==Black && piece<EMPTY)
				     {CurrentBoard=TestPiece1(CurrentBoard,piece,Npiece,CurrentColumn8,CurrentRow8,NextColumn8,NextRow8);}
				else {
				       AlertBox *Alert;
				       Alert= (AlertBox *) malloc(sizeof(AlertBox));
				       Alert->AlertBox_Set(100,120,400,220,"1TANiI1NUUH1EELJ1bis");
				       Alert->Draw_AlertBox();
				       int Bol=UNKNOWN;
				       while(Bol==UNKNOWN)
					    {
					     Bol=Alert->OnMouseUp();
					    }
					  free(Alert);
				       ChessBoard.DrawOn(NextColumn50,NextRow50,BoardColor[NextColumn8][NextRow8]);
				       ChessBoard.DrawOn(CurrentColumn50,CurrentRow50,BoardColor[CurrentColumn8][CurrentRow8]);
				       ChessBoard.DrawPiece(piece,CurrentColumn50,CurrentRow50);
				       ChessBoard.DrawPiece(Npiece,NextColumn50,NextRow50);
				       ChessBoard.MessageBoxErs(CurrentBoard);
					  delay(100);
				       ////////////////////////////////////////////////
				     }
			      }


			     if(CurrentBoard.TULUB==TRUE)
			       {
				    ChessBoard.DrawOn(((Column-20)/50-1)*50+75,((Row-20)/50-1)*50+75,BoardColor[((Column-20)/50-1)][((Row-20)/50-1)]);
				    if(!((CurrentColumn8==(Column-20)/50-1)&&(CurrentRow8==(Row-20)/50-1)))
				       { ChessBoard.DrawPiece(CurrentBoard.ReturnPieceBoard(((Column-20)/50-1),((Row-20)/50-1)),((Column-20)/50-1)*50+75,((Row-20)/50-1)*50+75);}
				    ChessBoard.DrawOn(((Column+20)/50-1)*50+75,((Row+20)/50-1)*50+75,BoardColor[((Column+20)/50-1)][((Row+20)/50-1)]);
				    if(!((CurrentColumn8==(Column+20)/50-1)&&(CurrentRow8==(Row+20)/50-1)))
				       { ChessBoard.DrawPiece(CurrentBoard.ReturnPieceBoard(((Column+20)/50-1),((Row+20)/50-1)),((Column+20)/50-1)*50+75,((Row+20)/50-1)*50+75);}
				    ChessBoard.DrawOn(((Column+20)/50-1)*50+75,((Row-20)/50-1)*50+75,BoardColor[((Column+20)/50-1)][((Row-20)/50-1)]);
				    if(!((CurrentColumn8==(Column+20)/50-1)&&(CurrentRow8==(Row-20)/50-1)))
				       { ChessBoard.DrawPiece(CurrentBoard.ReturnPieceBoard(((Column+20)/50-1),((Row-20)/50-1)),((Column+20)/50-1)*50+75,((Row-20)/50-1)*50+75);}
				    ChessBoard.DrawOn(((Column-20)/50-1)*50+75,((Row+20)/50-1)*50+75,BoardColor[((Column-20)/50-1)][((Row+20)/50-1)]);
				    if(!((CurrentColumn8==(Column-20)/50-1)&&(CurrentRow8==(Row+20)/50-1)))
				       { ChessBoard.DrawPiece(CurrentBoard.ReturnPieceBoard(((Column-20)/50-1),((Row+20)/50-1)),((Column-20)/50-1)*50+75,((Row+20)/50-1)*50+75);}

				    ChessBoard.DrawOn(NextColumn50,NextRow50,BoardColor[NextColumn8][NextRow8]);
				    ChessBoard.DrawOn(CurrentColumn50,CurrentRow50,BoardColor[CurrentColumn8][CurrentRow8]);

				    if(piece>0)
				     { PLAY=BLACKPLAY;
				       switch(piece)
					 {    case WHITEKING:
						       if(piece==WHITEKING && NextColumn8-CurrentColumn8==2 && NextRow8==CurrentRow8 && NextRow8==7)
							     {
								 ChessBoard.DrawOn(425,425,BoardColor[7][7]);
								 ChessBoard.DrawPiece(WHITEBISHOP,NextColumn50-50,NextRow50);
								 ChessBoard.DrawPiece(piece,NextColumn50,NextRow50);

							     }
						       else  {
								 if(piece==WHITEKING && CurrentColumn8-NextColumn8==2 && NextRow8==CurrentRow8 && NextRow8==7)
								   {
								     ChessBoard.DrawOn(75,425,BoardColor[0][7]);
								     ChessBoard.DrawPiece(WHITEBISHOP,CurrentColumn50-50,NextRow50);
								     ChessBoard.DrawPiece(piece,NextColumn50,NextRow50);
								   }
								 else ChessBoard.DrawPiece(piece,NextColumn50,NextRow50);

							     }
					      break;
					      case WHITEPAWN:
							if(Npiece==EMPTY && CurrentRow8==3 && CurrentRow8-NextRow8==1 && abs(CurrentColumn8-NextColumn8)==1)
							     {
								   ChessBoard.DrawOn(NextColumn50,NextRow50+50,BoardColor[NextColumn8][NextRow8-1]);
								   ChessBoard.DrawPiece(piece,NextColumn50,NextRow50);

							     }
							else
							     {
							      if(Npiece==EMPTY && CurrentRow8==1 && NextRow8==0 && CurrentColumn8==NextColumn8 ||
								 Npiece<EMPTY && CurrentRow8==1 && NextRow8==0 && abs(CurrentRow8-NextRow8)==1)
								  {
								     Box *SelectPiece;
								     Panel *QueenPanel,*BishopPanel,*RookPanel,*KnightPanel;

								     SelectPiece=(Box *)malloc(sizeof(Box));
								     SelectPiece->Box_Set(100,100,370,200,"11111111111111111111");
								     SelectPiece->Draw_Box();
								     QueenPanel=(Panel *)malloc(sizeof(Panel));
								     QueenPanel->Panel_Set(120,120,170,170,8,7,"11111111");
								     BishopPanel=(Panel *)malloc(sizeof(Panel));
								     BishopPanel->Panel_Set(180,120,230,170,8,7,"11111111");
								     RookPanel=(Panel *)malloc(sizeof(Panel));
								     RookPanel->Panel_Set(240,120,290,170,8,7,"11111111");
								     KnightPanel=(Panel *)malloc(sizeof(Panel));
								     KnightPanel->Panel_Set(300,120,350,170,8,7,"11111111");

								     QueenPanel->DrawPanel_On(Up);
								     ChessBoard.DrawPiece(WHITEQUEEN,145,145);
								     BishopPanel->DrawPanel_On(Up);
								     ChessBoard.DrawPiece(WHITEBISHOP,205,145);
								     RookPanel->DrawPanel_On(Up);
								     ChessBoard.DrawPiece(WHITEROOK,265,145);
								     KnightPanel->DrawPanel_On(Up);
								     ChessBoard.DrawPiece(WHITEKNIGHT,325,145);
								     int PIECE=WHITEQUEEN;
								 //    ChessBoard.DrawPiece(WHITEQUEEN,100,100);
								     int Bol=UNKNOWN;
								     while(Bol==UNKNOWN)
									   {
									      if(QueenPanel->OnMouseUp()==Up){PIECE=WHITEQUEEN;Bol=1;}
									      else {ChessBoard.DrawPiece(WHITEQUEEN,145,145);}
									      if(BishopPanel->OnMouseUp()==Up){PIECE=WHITEBISHOP;Bol=1;}
									      else {ChessBoard.DrawPiece(WHITEBISHOP,205,145);}
									      if(RookPanel->OnMouseUp()==Up){PIECE=WHITEROOK;Bol=1;}
									      else {ChessBoard.DrawPiece(WHITEROOK,265,145);}
									      if(KnightPanel->OnMouseUp()==Up){PIECE=WHITEKNIGHT;Bol=1;}
									      else {ChessBoard.DrawPiece(WHITEKNIGHT,325,145);}

									   }
								     free(SelectPiece);
								     free(QueenPanel);
								     free(RookPanel);
								     free(BishopPanel);
								     free(KnightPanel);
								     ChessBoard.MessageBoxErs(CurrentBoard);
								     delay(100);

								     ChessBoard.DrawOn(CurrentColumn50,CurrentRow50,BoardColor[CurrentColumn8][CurrentRow8]);
								     ChessBoard.DrawPiece(PIECE,CurrentColumn50,NextRow50);
								     CurrentBoard.PutPieceBoard(PIECE,CurrentColumn8,CurrentRow8,NextColumn8,NextRow8);


								  }
							      else ChessBoard.DrawPiece(piece,NextColumn50,NextRow50);
							     }
					      break;
					      default:
						    HedDehNuudel++;
						    ChessBoard.DrawPiece(piece,NextColumn50,NextRow50);

 //    WhitePush(CurrentBoard,CurrentRow8,CurrentColumn8,NextRow8,NextColumn8,piece,Npiece);
					      break;
					   }
				      }
				    else
				      {
					PLAY=WHITEPLAY;

					if(piece==BLACKKING && NextColumn8-CurrentColumn8==2 && NextRow8==CurrentRow8 && NextRow8==0)
					  {
					    ChessBoard.DrawOn(425,75,BoardColor[7][0]);
					    ChessBoard.DrawPiece(BLACKBISHOP,NextColumn50-50,NextRow50);
					   }
					 else
					   {
					     if(piece==BLACKKING && CurrentColumn8-NextColumn8==2 && NextRow8==CurrentRow8 && NextRow8==0)
					      {
						ChessBoard.DrawOn(75,75,BoardColor[0][0]);
						ChessBoard.DrawPiece(BLACKBISHOP,CurrentColumn50-50,NextRow50);
						CurrentBoard.PutPieceBoard(BLACKQUEEN,CurrentColumn8,CurrentRow8,NextColumn8,NextRow8);
					      }
					    }
				      }
				}
			      else
			       {    mouse_hide();
				    ChessBoard.DrawOn(((Column-20)/50-1)*50+75,((Row-20)/50-1)*50+75,BoardColor[((Column-20)/50-1)][((Row-20)/50-1)]);
				    ChessBoard.DrawPiece(CurrentBoard.ReturnPieceBoard(((Column-20)/50-1),((Row-20)/50-1)),((Column-20)/50-1)*50+75,((Row-20)/50-1)*50+75);

				    ChessBoard.DrawOn(((Column+20)/50-1)*50+75,((Row+20)/50-1)*50+75,BoardColor[((Column+20)/50-1)][((Row+20)/50-1)]);
				    ChessBoard.DrawPiece(CurrentBoard.ReturnPieceBoard(((Column+20)/50-1),((Row+20)/50-1)),((Column+20)/50-1)*50+75,((Row+20)/50-1)*50+75);

				    ChessBoard.DrawOn(((Column+20)/50-1)*50+75,((Row-20)/50-1)*50+75,BoardColor[((Column+20)/50-1)][((Row-20)/50-1)]);
				    ChessBoard.DrawPiece(CurrentBoard.ReturnPieceBoard(((Column+20)/50-1),((Row-20)/50-1)),((Column+20)/50-1)*50+75,((Row-20)/50-1)*50+75);

				    ChessBoard.DrawOn(((Column-20)/50-1)*50+75,((Row+20)/50-1)*50+75,BoardColor[((Column-20)/50-1)][((Row+20)/50-1)]);
				    ChessBoard.DrawPiece(CurrentBoard.ReturnPieceBoard(((Column-20)/50-1),((Row+20)/50-1)),((Column-20)/50-1)*50+75,((Row+20)/50-1)*50+75);

				    ChessBoard.DrawPiece(piece,CurrentColumn50,CurrentRow50);
				    mouse_show();
			       }

			   }
		     }
		      //	Exit();
		 mouse_limited(1,1,500,700);
		 }break;
      }
 //Switech end;

 if(piece>EMPTY)
  {
      if(king.TestKingCheck(CurrentBoard,Black)==FALSE)
	{
	  if(IsGameOver(CurrentBoard,Black)==FALSE)
	   {
	    CurrentBoard.BlackKingCheck=FALSE;
	   }
	  else {main();}
	}
 }
 else
  {
      if(king.TestKingCheck(CurrentBoard,Black)==FALSE)
	{
	  if(IsGameOver(CurrentBoard,White)==FALSE)
	    {
	      CurrentBoard.WhiteKingCheck=FALSE;
	    }
	 else {main();}
	}
   }
 mouse_show();
 return CurrentBoard;
};
//***********************************************************
//           BOOK
//
// ***********************************************************
struct ST
{int R;  int B;
 int E;  int CC;
 int CR; int NC;
 int NR; int S;
};
void OpenFile()
{ ST *W,*B;
  ifstream infw("w1.txt"); infw.read((char *) &W,sizeof(W));
  ifstream infb("b1.txt"); infb.read((char *) &B,sizeof(B));
  for(int i=W[1].B;i<=W[1].E;i++)
    {  cout<<"\n CC="<<B[i].CC<<" CR="<<B[i].CR<<" NR="<<B[i].NR<<" NC="<<B[i].NC;
    }
  getch();
}

//*************************************************************
//          BOOK
//*************************************************************
long MinMax(Chessboard,int,int,CHESSBOARD);
unsigned long AllPosition=0;

long ABSearch(Chessboard Position,int depth,long alpha,long beta,int color,CHESSBOARD);


Chessboard ComputerRun(Chessboard CurrentBoard,CHESSBOARD ChessBoard,int color,int depth)
{ Chessboard TempBoard;
  TempBoard=CurrentBoard;
  AllPosition=0;
  long i=MinMax(CurrentBoard,depth,color,ChessBoard);
//  long i=ABSearch(CurrentBoard,depth,-20000,20000,color,ChessBoard);
  AllPosition=abs(AllPosition);
  mouse_hide();
  char Eval[10], Pos[10],W[10],B[10];

  mouse_show();
  if(i==20000 || i==-20000)
   {

     LISTER[depth].Index=0;
     ListAdd(CurrentBoard,color,depth);
     if(LISTER[depth].Index==0)
       {    IsTentsee();
       }
     else
       {
	CurrentBoard.PutPieceBoard(LISTER[depth].Lister[0].CurrentPiece,LISTER[depth].Lister[0].CurrentColumn,LISTER[depth].Lister[0].CurrentRow,LISTER[depth].Lister[0].NextColumn,LISTER[depth].Lister[0].NextRow);
	Data[depth].CurrentPiece=LISTER[depth].Lister[0].CurrentPiece;
	Data[depth].CurrentColumn=LISTER[depth].Lister[0].CurrentColumn;
	Data[depth].CurrentRow=LISTER[depth].Lister[0].CurrentRow;
	Data[depth].NextPiece=LISTER[depth].Lister[0].NextPiece;
	Data[depth].NextColumn=LISTER[depth].Lister[0].NextColumn;
	Data[depth].NextRow=LISTER[depth].Lister[0].NextRow;
       }
   }
  else
   {
  CurrentBoard=TempBoard;
  CurrentBoard.PutPieceBoard(Data[depth].CurrentPiece,Data[depth].CurrentColumn,Data[depth].CurrentRow,Data[depth].NextColumn,Data[depth].NextRow);
  CurrentBoard.LastCurrentPiece=Data[depth].CurrentPiece;
  CurrentBoard.LastCurrentColumn=Data[depth].CurrentColumn;
  CurrentBoard.LastCurrentRow=Data[depth].CurrentRow;
  CurrentBoard.LastNextColumn=Data[depth].NextColumn;
  CurrentBoard.LastNextRow=Data[depth].NextRow;

   }
//////////////  BlackPush(CurrentBoard,Data[depth].CurrentRow,Data[depth].CurrentColumn,Data[depth].NextRow,Data[depth].NextColumn,Data[depth].CurrentPiece,Data[depth].NextPiece);
/////  HistoryShow();

  ChessBoard.DrawOn(Data[depth].NextColumn*50+75,Data[depth].NextRow*50+75,BoardColor[Data[depth].NextColumn][Data[depth].NextRow]);
  ChessBoard.DrawPiece(Data[depth].CurrentPiece,Data[depth].NextColumn*50+75,Data[depth].NextRow*50+75);
  ChessBoard.DrawOn(Data[depth].CurrentColumn*50+75,Data[depth].CurrentRow*50+75,BoardColor[Data[depth].CurrentColumn][Data[depth].CurrentRow]);

 if(Data[depth].CurrentPiece>EMPTY)
  {
      if(king.TestKingCheck(CurrentBoard,Black)==FALSE)
	{
 //	  cout<<"----------------";
	  if(IsGameOver(CurrentBoard,Black)==FALSE)
	   {
	    CurrentBoard.BlackKingCheck=FALSE;
	   }
	  else {main();}
	}
 }
 else
  {
      if(king.TestKingCheck(CurrentBoard,White)==FALSE)
	{
  //	  cout<<"----------------";
	  if(IsGameOver(CurrentBoard,White)==FALSE)
	    {
	      CurrentBoard.WhiteKingCheck=FALSE;
	    }
	 else {main();}
	}
   }
  PLAY=WHITEPLAY;

   setcolor(9);
  sprintf(Eval,"%i",i);
  sprintf(Pos,"%i",AllPosition);
  sprintf(W,"%i",CurrentBoard.WhiteEvaluation);
  sprintf(B,"%i",CurrentBoard.BlackEvaluation);

  setfillstyle(SOLID_FILL,LIGHTGRAY);
  bar(480,420,620,465);
  settextstyle(0, HORIZ_DIR, 1);
  outtextxy(490,425,"Evalution:"); outtextxy(570,425,Eval);
  outtextxy(490,435,"Positions:"); outtextxy(570,435,Pos);
  outtextxy(490,445,"White Eva:"); outtextxy(570,445,W);
  outtextxy(490,455,"Black Eva:"); outtextxy(570,455,B);

  return CurrentBoard;
}


//****************************** Main Function BEGIN ********************************
void EXIT(void)
{
  closegraph();
  exit(0);
}
void KEY(void)
{
   switch(getch())
     {
      case 27: EXIT();break;
      case 14: main();   break;
      default: break;
     }

}
short STARTPROGRAM=FALSE;

PlayTimer(Chessboard Position,int Color)
{
  AlertBox *GameOver;
  if(Color==White)
   {
     WhiteTimer.RunTime();
     if(WhiteTimer.TestClock()==TRUE)
       {
	 if(Position.WhiteEvaluation<=1300)
	   {
	       IsTentsee();
	   }
	 else
	   {
		  GameOver= (AlertBox *) malloc(sizeof(AlertBox));
		  GameOver->AlertBox_Set(100,100,400,200,"11111HAR1HOJiLOO1111");
		  GameOver->Draw_AlertBox();
		  int Bol=UNKNOWN;
		  while(Bol==UNKNOWN)
		    {
		     Bol=GameOver->OnMouseUp();
		    }
	  free(GameOver);
	  delay(100);
	  main();
	  }
       }
   }
  else
   {
     BlackTimer.RunTime();
     if(BlackTimer.TestClock()==TRUE)
	{
	 if(Position.WhiteEvaluation<=1300)
	      {
	       IsTentsee();
	      }
	      else
	      {
		  GameOver= (AlertBox *) malloc(sizeof(AlertBox));
		  GameOver->AlertBox_Set(100,120,400,220,"111SAGAAN1HOJiLOO111");
		  GameOver->Draw_AlertBox();
		  int Bol=UNKNOWN;
		  while(Bol==UNKNOWN)
		   { Bol=GameOver->OnMouseUp();
		   }
		  free(GameOver);
		  delay(100);
		  main();
	       }
	}
   }
 return 1;
}

void main (void)
{

   if(STARTPROGRAM==FALSE){Start_Chess(); STARTPROGRAM=TRUE;}
   mouse_put(1,1);
   mouse_show();
   mouse_limited(1,1,499,699);
   Chessboard CurrentBoard;
   CHESSBOARD ChessBoard;
   ChessBoard.DrawBoard();    PLAY=WHITEPLAY;
   setcolor(WHITE);
   WhiteTimer.SetTime(HOUR,MINUT,10,500,60);
   BlackTimer.SetTime(HOUR,MINUT,SECOND,500,385);

   for(;;)
   {
     if(ChessBoard.Visable==FALSE)
      {
       mouse_info();
       ChessBoard.Mouse_Over(CurrentBoard);
      }

    if(RunEnable==TRUE)
     {
       if(PLAY==WHITEPLAY)
	{
	   CurrentBoard=Run(CurrentBoard,ChessBoard);
	   PlayTimer(CurrentBoard,HumanPlayer);
	}
       else
	{
	   CurrentBoard=ComputerRun(CurrentBoard,ChessBoard,BLACK,DEPTH);
	}
     }

     if(kbhit())
       { KEY(); };
   }
}
//****************************** Main Function END ******************************
void Graphic_mode(void)
{
int gdriver = DETECT, gmode, errorcode;
initgraph(&gdriver, &gmode, "");
errorcode = graphresult();
   if (errorcode != grOk)
   {
	  printf("Graphics error: %s\n", grapherrormsg(errorcode));
	  printf("Press any key to halt:");
	  getch();
	  exit(1);    /* terminate with an error code */
   }
}
    /*  Here you can define your function than are mentioned above */

/*------------------------------------------------*/

void ListAdd1(Chessboard,int,int,int,int);
void ListAdd(Chessboard Position,int color,int depth)
{LISTER[depth].Index=0;
for(int col1=0;col1<8;col1++)
  for(int row1=0;row1<8;row1++)
    {
     int Cpiece=Position.ReturnPieceBoard(col1,row1);

     if(color==White)
       {
	 if(Cpiece>0)
	   { ListAdd1(Position,Cpiece,col1,row1,depth); }
       }
     else
       {
	 if(Cpiece<0)
	   {
	     ListAdd1(Position,Cpiece,col1,row1,depth);
	   }
       }
    }
}

void ListAddBishop(Chessboard Position,int Cpiece,int col1,int row1,int depth)
{  int row2,col2,Npiece;
   for(col2=0;col2<8;col2++)
	 { Npiece=Position.ReturnPieceBoard(col2,row1);
	   if(TestPiece(Position,Cpiece,Npiece,col1,row1,col2,row1)==TRUE)
	       {
		    if(!(row1==row2 && col1==col2))
		      {
			LISTER[depth].ListPush(Cpiece,Npiece,col1,row1,col2,row1);
		      }
	       }
	 }
   for(row2=0;row2<8;row2++)
	 {   Npiece=Position.ReturnPieceBoard(col1,row2);
	    if(TestPiece(Position,Cpiece,Npiece,col1,row1,col1,row2)==TRUE)
		{
		     if(!(row1==row2 && col1==col2))
		      {
			LISTER[depth].ListPush(Cpiece,Npiece,col1,row1,col1,row2);
		      }
		}
	 }
}
void ListAddRook(Chessboard Position,int Cpiece,int col1,int row1,int depth)
{  int col2,row2,Npiece;

   if(col1 < row1)
	  {  col2=0;
	       // zuv dashuu
	       for(row2=(row1-col1);row2<=7;row2=row2+1)
		{  Npiece=Position.ReturnPieceBoard(col2,row2);
		  if(TRUE==TestPiece(Position,Cpiece,Npiece,col1,row1,col2,row2))
		     {  if(col1!=col2 || row1!=row2)
			   {
			    LISTER[depth].ListPush(Cpiece,Npiece,col1,row1,col2,row2);
			   }
		      }
		   col2=col2+1;
		 }
	       //
		  if(col1+row1 >7)
		     { row2=7;
		       for(col2=(col1+row1)-7;col2<=7;col2=col2+1)
			 { Npiece=Position.ReturnPieceBoard(col2,row2);
			   if(TRUE==TestPiece(Position,Cpiece,Npiece,col1,row1,col2,row2))
			     {
			       if(col1!=col2 || row1!=row2)
				   {
				     LISTER[depth].ListPush(Cpiece,Npiece,col1,row1,col2,row2);
				    }
			     }
			      row2=row2-1;
			  }
		      }
		   else
		      { col2=col1+row1;
			for(row2=0;row2<=row1+col1;row2=row2+1)
			 { Npiece=Position.ReturnPieceBoard(col2,row2);
			  if(TRUE==TestPiece(Position,Cpiece,Npiece,col1,row1,col2,row2))
			    {
			      if(col1!=col2 && row1!=row2)
				 {
				  LISTER[depth].ListPush(Cpiece,Npiece,col1,row1,col2,row2);
				 }
			    }
			   col2=col2-1;
			  }
		      }
	     }
      else
	   {   row2=0;
	       for(col2=col1-row1;col2<=7;col2=col2+1)
		  { Npiece=Position.ReturnPieceBoard(col2,row2);

		    if(TRUE==TestPiece(Position,Cpiece,Npiece,col1,row1,col2,row2))
			 {
			    if(col1!=col2 && row1!=row2)
			     {
				LISTER[depth].ListPush(Cpiece,Npiece,col1,row1,col2,row2);
			     }
			 }
		     row2=row2+1;
		  }

		if(row1+col1>7)
		   {  row2=7;
		      for(col2=(row1+col1)-7;col2<=7;col2=col2+1)
			 { Npiece=Position.ReturnPieceBoard(col2,row2);

			  if(TRUE==TestPiece(Position,Cpiece,Npiece,col1,row1,col2,row2))
				 {
				    if(col1!=col2 && row1!=row2)
				      {	LISTER[depth].ListPush(Cpiece,Npiece,col1,row1,col2,row2);
				      }
				 }
				 row2=row2-1;
			 }
		   }
		else
		   { row2=col1+row1;
		     for(col2=0;col2<=col1+row1;col2=col2+1)
		      {Npiece=Position.ReturnPieceBoard(col2,row2);

		       if(TRUE==TestPiece(Position,Cpiece,Npiece,col1,row1,col2,row2))
			 {
			    if(col1!=col2 && row1!=row2)
			     {
			      LISTER[depth].ListPush(Cpiece,Npiece,col1,row1,col2,row2);
			      }
			}
		       row2=row2-1;
		     }
		  }
	 }
}
void ListAdd1(Chessboard Position,int Cpiece,int col1,int row1,int depth)
{ int row2,col2,Npiece;
	if(Cpiece==1)
		 {
		      if(row1-1>=0)
		       { Npiece=Position.ReturnPieceBoard(col1,row1-1);

			if(TestPiece(Position,Cpiece,Npiece,col1,row1,col1,row1-1)==TRUE)
			  {
			    LISTER[depth].ListPush(Cpiece,Npiece,col1,row1,col1,row1-1);
			  }
		       }
		      if(row1-2>=0)
		       {  Npiece=Position.ReturnPieceBoard(col1,row1-2);

			if(TestPiece(Position,Cpiece,Npiece,col1,row1,col1,row1-2)==TRUE)
			  { LISTER[depth].ListPush(Cpiece,Npiece,col1,row1,col1,row1-2);
			  }
		       }
		      if(row1-1>=0 && col1-1>=0)
		       { Npiece=Position.ReturnPieceBoard(col1-1,row1-1);

			if(TestPiece(Position,Cpiece,Npiece,col1,row1,col1-1,row1-1)==TRUE)
			  { LISTER[depth].ListPush(Cpiece,Npiece,col1,row1,col1-1,row1-1);
			  }
		       }
		      if(row1-1>=0 && col1+1<8)
		       { Npiece=Position.ReturnPieceBoard(col1+1,row1-1);

			if(TestPiece(Position,Cpiece,Npiece,col1,row1,col1+1,row1-1)==TRUE)
			   {
			    LISTER[depth].ListPush(Cpiece,Npiece,col1,row1,col1+1,row1-1);
			   }
		       }
		   }
	       if(Cpiece==-1)
		   {
		      if(row1+1< 8)
		       {Npiece=Position.ReturnPieceBoard(col1,row1+1);

			if(TestPiece(Position,Cpiece,Npiece,col1,row1,col1,row1+1)==TRUE)
			   {
			   LISTER[depth].ListPush(Cpiece,Npiece,col1,row1,col1,row1+1);
			    }
			}
		      if(row1+2>=0)
		       { Npiece=Position.ReturnPieceBoard(col1,row1+2);

			if(TestPiece(Position,Cpiece,Npiece,col1,row1,col1,row1+2)==TRUE)
			  {
			   LISTER[depth].ListPush(Cpiece,Npiece,col1,row1,col1,row1+2);
			  }
		       }
		      if(row1+1<8 && col1+1<8)
		       {  Npiece=Position.ReturnPieceBoard(col1+1,row1+1);

			if(TestPiece(Position,Cpiece,Npiece,col1,row1,col1+1,row1+1)==TRUE)
			   { LISTER[depth].ListPush(Cpiece,Npiece,col1,row1,col1+1,row1+1);
			   }
		       }
		      if(row1+1>=0 && col1-1<8)
		       {  Npiece=Position.ReturnPieceBoard(col1-1,row1+1);

			 if(TestPiece(Position,Cpiece,Npiece,col1,row1,col1-1,row1+1)==TRUE)
			   {
			    LISTER[depth].ListPush(Cpiece,Npiece,col1,row1,col1-1,row1+1);
			   }
		       }
		  }
	       if(Cpiece==-2 || Cpiece==2)
		      {  Npiece=Position.ReturnPieceBoard(col1+2,row1+1);

			if(row1+1< 8 && col1+2<8)
			  {  if(TestPiece(Position,Cpiece,Npiece,col1,row1,col1+2,row1+1)==TRUE)
			      {
				LISTER[depth].ListPush(Cpiece,Npiece,col1,row1,col1+2,row1+1);
			      }
			  }
			if(row1+2<8&&col1+1<8)
			  {  Npiece=Position.ReturnPieceBoard(col1+1,row1+2);
			     if(TestPiece(Position,Cpiece,Npiece,col1,row1,col1+1,row1+2)==TRUE)
			      {
				LISTER[depth].ListPush(Cpiece,Npiece,col1,row1,col1+1,row1+2);
			      }
			  }
			if(row1-1>=0&& col1-2>=0)
			  { Npiece=Position.ReturnPieceBoard(col1-2,row1-1);
			    if(TestPiece(Position,Cpiece,Npiece,col1,row1,col1-2,row1-1)==TRUE)
			      {
			       LISTER[depth].ListPush(Cpiece,Npiece,col1,row1,col1-2,row1-1);
			      }
			  }
			if(row1-2>=0&&col1-1>=0)
			  { Npiece=Position.ReturnPieceBoard(col1-1,row1-2);
			    if(TestPiece(Position,Cpiece,Npiece,col1,row1,col1-1,row1-2)==TRUE)
			      {
			      LISTER[depth].ListPush(Cpiece,Npiece,col1,row1,col1-1,row1-2);
			      }
			  }
			if(row1+1<8&&col1-2>=0)
			  { Npiece=Position.ReturnPieceBoard(col1-2,row1+1);
			    if(TestPiece(Position,Cpiece,Npiece,col1,row1,col1-2,row1+1)==TRUE)
			      {
			      LISTER[depth].ListPush(Cpiece,Npiece,col1,row1,col1-2,row1+1);
			      }
			  }
			if(row1+2<8&&col1-1>=0)
			  { Npiece=Position.ReturnPieceBoard(col1-1,row1+2);

			    if(TestPiece(Position,Cpiece,Npiece,col1,row1,col1-1,row1+2)==TRUE)
			      {LISTER[depth].ListPush(Cpiece,Npiece,col1,row1,col1-1,row1+2);
			      }
			  }
			if(row1-1>=0&&col1+2<8)
			  { Npiece=Position.ReturnPieceBoard(col1+2,row1-1);

			    if(TestPiece(Position,Cpiece,Npiece,col1,row1,col1+2,row1-1)==TRUE)
			      {LISTER[depth].ListPush(Cpiece,Npiece,col1,row1,col1+2,row1-1);
			      }
			  }
			if(row1-2>=0&&col1+1<8)
			  {Npiece=Position.ReturnPieceBoard(col1+1,row1-2);

			    if(TestPiece(Position,Cpiece,Npiece,col1,row1,col1+1,row1-2)==TRUE)
			      {LISTER[depth].ListPush(Cpiece,Npiece,col1,row1,col1+1,row1-2);
			      }
			  }
		       }
	      if(Cpiece==3 || Cpiece==-3)
		      {  ListAddBishop(Position,Cpiece,col1,row1,depth);}
	      if(Cpiece==4 || Cpiece==-4)
		     {
		       ListAddRook(Position,Cpiece,col1,row1,depth);
		     }
	      if(Cpiece==5 || Cpiece==-5)
		     { ListAddBishop(Position,Cpiece,col1,row1,depth);
		       ListAddRook(Position,Cpiece,col1,row1,depth);
		     };
// *************** HOEH ************************
	      if(Cpiece==6||Cpiece==-6)
		   { if(row1+1<8 && col1+1<8)
			 { Npiece=Position.ReturnPieceBoard(col1+1,row1+1);

			  if(TestPiece(Position,Cpiece,Npiece,col1,row1,col1+1,row1+1)==TRUE)
			      {LISTER[depth].ListPush(Cpiece,Npiece,col1,row1,col1+1,row1+1);}
			 }
			if(row1-1>=0 && col1-1>=0)
			 {Npiece=Position.ReturnPieceBoard(col1-1,row1-1);

			  if(TestPiece(Position,Cpiece,Npiece,col1,row1,col1-1,row1-1)==TRUE)
			      {LISTER[depth].ListPush(Cpiece,Npiece,col1,row1,col1-1,row1-1);}
			 }
			if(row1+1<8 && col1-1>=0)
			 {Npiece=Position.ReturnPieceBoard(col1-1,row1+1);

			  if(TestPiece(Position,Cpiece,Npiece,col1,row1,col1-1,row1+1)==TRUE)
			      {LISTER[depth].ListPush(Cpiece,Npiece,col1,row1,col1-1,row1+1);}
			 }
			if(row1-1>=0 && col1+1<8)
			 { Npiece=Position.ReturnPieceBoard(col1+1,row1-1);

			  if(TestPiece(Position,Cpiece,Npiece,col1,row1,col1+1,row1-1)==TRUE)
			      {LISTER[depth].ListPush(Cpiece,Npiece,col1,row1,col1+1,row1-1);}
			 }
			if(col1+1<8)
			 {Npiece=Position.ReturnPieceBoard(col1+1,row1);

			  if(TestPiece(Position,Cpiece,Npiece,col1,row1,col1+1,row1)==TRUE)
			      {LISTER[depth].ListPush(Cpiece,Npiece,col1,row1,col1+1,row1);}
			}
			if(col1-1>=0)
			 { Npiece=Position.ReturnPieceBoard(col1-1,row1);

			  if(TestPiece(Position,Cpiece,Npiece,col1,row1,col1-1,row1)==TRUE)
			      {LISTER[depth].ListPush(Cpiece,Npiece,col1,row1,col1-1,row1);}
			 }
			if(row1+1<8)
			  { Npiece=Position.ReturnPieceBoard(col1,row1+1);

			   if(TestPiece(Position,Cpiece,Npiece,col1,row1,col1,row1+1)==TRUE)
			      {LISTER[depth].ListPush(Cpiece,Npiece,col1,row1,col1,row1+1);}
			  }
			if(row1-1>=0)
			 { Npiece=Position.ReturnPieceBoard(col1,row1-1);

			   if(TestPiece(Position,Cpiece,Npiece,col1,row1,col1,row1-1)==TRUE)
			      {LISTER[depth].ListPush(Cpiece,Npiece,col1,row1,col1,row1-1);}
			 }
		      /*
			if(Cpiece==WHITEKING)
			 {
			  if(row1==7 && col1==4)
			   {
			     if(TestPiece(Position,Cpiece,Npiece,col1,row1,col1+2,row1)==TRUE)
			       {
				LISTER[depth].ListPush(WHITEKING,WHITEBISHOP,7,7,7,7);
			       }
			     if(TestPiece(Position,Cpiece,Npiece,col1,row1,col1-2,row1)==TRUE)
			       {
				LISTER[depth].ListPush(WHITEKING,WHITEBISHOP,0,0,0,0);
			       }
			   }
			 }

			if(Cpiece==BLACKKING)
			 {
			   if(row1==0 && col1==4)
			   {
			     if(TestPiece(Position,Cpiece,Npiece,col1,row1,col1+2,row1)==TRUE)
			       {
				LISTER[depth].ListPush(BLACKKING,BLACKBISHOP,7,7,7,7);
			       }
			     if(TestPiece(Position,Cpiece,Npiece,col1,row1,col1-2,row1)==TRUE)
			       {
				LISTER[depth].ListPush(BLACKKING,BLACKBISHOP,0,0,0,0);
			       }
			    }
			 }
		       */
		     }
}
/*********************************************************************/

/*********************************************************************/
/*
/*          List   END
/*
/**********************************************************************/
//WhitePawn_Value[8][8]               =
//BlackPawn_Value[8][8]                =
//WhiteBod_Value[8][8]                  =
//BlackBod_Value[8][8]                   =
//WhiteKing_Value[8][8]
//WhiteKing_Value[8][8]
//WhiteKingSide_pawn[8][8]
//WhiteQueenSide_Pawn[8][8]
//BlackKingSide_pawn[8][8]
//BlackQueenSide_Pawn[8][8]

long Evaluate(Chessboard Position)
 { long score=0;
   for(int row1=0;row1<8;row1++)
    for(int col1=0;col1<8;col1++)
     { int piece=Position.ReturnPieceBoard(col1,row1);
	  switch(piece)
	     {	case  1:
			  if(Position.BlackEvaluation<-2000 && Position.WhiteEvaluation>2000)
			    {
			     score=score+100+WhitePawn_Value[row1][col1]+WhiteKingSide_pawn[row1][col1]+WhiteQueenSide_Pawn[row1][col1];
			    }
			  else
			    {
			      score=score+100+WhitePawn_Value[row1][col1];
			    }
			  break;
		case -1:  if(Position.BlackEvaluation<-2000 && Position.WhiteEvaluation>2000)
			    {
			     score=score-100+BlackPawn_Value[row1][col1]+BlackKingSide_pawn[row1][col1]+BlackQueenSide_Pawn[row1][col1];
			    }
			  else
			    {
			      score=score-100+BlackPawn_Value[row1][col1];
			    }
			  break;
		case  2:  score=score+300+WhiteBod_Value[row1][col1];
			  break;
		case -2:  score=score-300+BlackBod_Value[row1][col1];
			  break;

		case  3:  score=score+500+WhiteBod_Value[row1][col1];
			  break;
		case -3:  score=score-500+BlackBod_Value[row1][col1];
			  break;

		case  4:  score=score+300+WhiteBod_Value[row1][col1];
			  break;
		case -4:  score=score-300+BlackBod_Value[row1][col1];
			  break;

		case  5:  score=score+900+WhiteBod_Value[row1][col1];
			  break;
		case -5:  score=score-900+BlackBod_Value[row1][col1];
			  break;

		case  6:
			  if(Position.BlackEvaluation<-3000 && Position.WhiteEvaluation>3000)
			    { score=score+1000+WhiteKing_Value[row1][col1];
			    }
			  else
			    {
			      if(Position.BlackEvaluation<-2000 && Position.WhiteEvaluation>2000)
				  score=score+1000+WhiteBod_Value[row1][col1];
			      else
				  score=score+1000;
			    }
			  break;

		case -6:  if(Position.BlackEvaluation<-3000 && Position.WhiteEvaluation>3000)
			    { score=score-1000+BlackKing_Value[row1][col1];
			    }
			  else
			    {
			      if(Position.BlackEvaluation<-2000 && Position.WhiteEvaluation>2000)
				 score=score-1000+BlackBod_Value[row1][col1];
			      else
				 score=score-1000;
			    }

			  break;

		default :break;
	   }

     }
   P++;
   return(score);
 }

/*

long Evaluate(Chessboard Position)
 {long score=0;
  for(int row1=0;row1<8;row1++)
    for(int col1=0;col1<8;col1++)
     { int piece=Position.ReturnPieceBoard(col1,row1);
	  switch(piece)
	     {	case  1:  score=score+100+WhitePawn_Value[row1][col1]+WhiteKingSide_pawn[row1][col1]+WhiteQueenSide_Pawn[row1][col1];
			  break;
		case -1:  score=score-100+BlackPawn_Value[row1][col1]+BlackKingSide_pawn[row1][col1]+BlackQueenSide_Pawn[row1][col1];
			  break;

		case  2:  score=score+300+WhiteBod_Value[row1][col1];
			  break;
		case -2:  score=score-300+BlackBod_Value[row1][col1];
			  break;

		case  3:  score=score+500+WhiteBod_Value[row1][col1];
			  break;
		case -3:  score=score-500+BlackBod_Value[row1][col1];
			  break;

		case  4:  score=score+300+WhiteBod_Value[row1][col1];
			  break;
		case -4:  score=score-300+BlackBod_Value[row1][col1];
			  break;

		case  5:  score=score+900+WhiteBod_Value[row1][col1];
			  break;
		case -5:  score=score-900+BlackBod_Value[row1][col1];
			  break;

		case  6:  score=score+1000+WhiteKing_Value[row1][col1];
			  break;
		case -6:  score=score-1000+BlackKing_Value[row1][col1];
			  break;

		default :break;
	   }

     }
   P++;
   return(score);
 }
 */

long val;
long ABSearch(Chessboard Position,int depth,long alpha,long beta,int color,CHESSBOARD Board)
{ // Pieces back;

  PlayTimer(Position,ComputerPlayer);

  Board.Mouse_Over(Position);

  if(depth==0) return Evaluate(Position);
  if(color==1) color=0;
  else color=1;

  ListAdd(Position,color,depth);
  for(LISTER[depth].i=0;LISTER[depth].i < LISTER[depth].Index;LISTER[depth].i++)
 {   Temp[depth]=Position;

     if(LISTER[depth].Lister[LISTER[depth].i].CurrentPiece==WHITEKING && LISTER[depth].Lister[LISTER[depth].i].NextPiece==WHITEBISHOP)
       {
	  if(LISTER[depth].Lister[LISTER[depth].i].CurrentColumn==7)
	    {  Position.PutPieceBoard(WHITEKING,4,7,6,7);
	       Position.PutPieceBoard(WHITEBISHOP,7,7,5,7);}
	  else
	    {  Position.PutPieceBoard(WHITEKING,4,7,2,7);
	       Position.PutPieceBoard(WHITEBISHOP,0,7,3,7);}
       }
     else
       {
	  if(LISTER[depth].Lister[LISTER[depth].i].CurrentPiece==BLACKKING && LISTER[depth].Lister[LISTER[depth].i].NextPiece==BLACKBISHOP)
	    {
	     if(LISTER[depth].Lister[LISTER[depth].i].CurrentColumn==7)
	       {  Position.PutPieceBoard(BLACKKING,4,0,6,0);
		  Position.PutPieceBoard(BLACKBISHOP,7,0,5,0);}
	     else
	       {  Position.PutPieceBoard(BLACKKING,4,0,2,0);
		  Position.PutPieceBoard(BLACKBISHOP,0,0,3,0);
	       }
	    }
	  else
	    {
	      Position.PutPieceBoard(LISTER[depth].Lister[LISTER[depth].i].CurrentPiece,LISTER[depth].Lister[LISTER[depth].i].CurrentColumn,LISTER[depth].Lister[LISTER[depth].i].CurrentRow,LISTER[depth].Lister[LISTER[depth].i].NextColumn,LISTER[depth].Lister[LISTER[depth].i].NextRow);
	    }
       }

     Position.PutPieceBoard(LISTER[depth].Lister[LISTER[depth].i].CurrentPiece,LISTER[depth].Lister[LISTER[depth].i].CurrentColumn,LISTER[depth].Lister[LISTER[depth].i].CurrentRow,LISTER[depth].Lister[LISTER[depth].i].NextColumn,LISTER[depth].Lister[LISTER[depth].i].NextRow);
     AllPosition++;
     val=-ABSearch(Position,depth-1, -beta, -alpha,color,Board);

     Position=Temp[depth];

     if (val >= beta)
	    return beta;
     if (val > alpha)
	   { alpha = val;
	     Data[depth].CurrentPiece=LISTER[depth].Lister[LISTER[depth].i].CurrentPiece;
	     Data[depth].NextPiece=LISTER[depth].Lister[LISTER[depth].i].NextPiece;
	     Data[depth].CurrentColumn=LISTER[depth].Lister[LISTER[depth].i].CurrentColumn;
	     Data[depth].CurrentRow=LISTER[depth].Lister[LISTER[depth].i].CurrentRow;
	     Data[depth].NextColumn=LISTER[depth].Lister[LISTER[depth].i].NextColumn;
	     Data[depth].NextRow=LISTER[depth].Lister[LISTER[depth].i].NextRow;
	   }
   }
 return alpha;
}


//########################################################################
//
//                        MinMax Search algoritm
//
//#########################################################################
long Max(Chessboard Position,int depth,CHESSBOARD Board);
long Min(Chessboard Position,int depth,CHESSBOARD Board);
long MinMax(Chessboard Position,int depth,int color,CHESSBOARD Board)
{  if (color==1)    // White is the "maximizing" player.
	return Max(Position,depth,Board);
    else                          // Black is the "minimizing" player.
	return Min(Position,depth,Board);
}


long Max(Chessboard Position,int depth,CHESSBOARD Board)
{
    PlayTimer(Position,ComputerPlayer);
    Board.Mouse_Over(Position);

    long best = -20000;
    if (depth <= 0)
	return Evaluate(Position);
	ListAdd(Position,White,depth);
	 for(LISTER[depth].i=0;LISTER[depth].i < LISTER[depth].Index;LISTER[depth].i++)
	  {
	   Temp[depth]=Position;
	   Position.PutPieceBoard(LISTER[depth].Lister[LISTER[depth].i].CurrentPiece,LISTER[depth].Lister[LISTER[depth].i].CurrentColumn,LISTER[depth].Lister[LISTER[depth].i].CurrentRow,LISTER[depth].Lister[LISTER[depth].i].NextColumn,LISTER[depth].Lister[LISTER[depth].i].NextRow);
	   AllPosition++;
	   long val = Min(Position,depth - 1,Board);
	   Position=Temp[depth];
	   if (val > best)
	       { best = val;
		 Data[depth].CurrentPiece=LISTER[depth].Lister[LISTER[depth].i].CurrentPiece;
		 Data[depth].NextPiece=LISTER[depth].Lister[LISTER[depth].i].NextPiece;
		 Data[depth].CurrentColumn=LISTER[depth].Lister[LISTER[depth].i].CurrentColumn;
		 Data[depth].CurrentRow=LISTER[depth].Lister[LISTER[depth].i].CurrentRow;
		 Data[depth].NextColumn=LISTER[depth].Lister[LISTER[depth].i].NextColumn;
		 Data[depth].NextRow=LISTER[depth].Lister[LISTER[depth].i].NextRow;
	       }
	}
    return best;
}

long Min(Chessboard Position,int depth,CHESSBOARD Board)
{
    PlayTimer(Position,ComputerPlayer);

    Board.Mouse_Over(Position);

    long best = 20000;  // <-- Note that this is different than in "Max".
    if (depth <= 0)
	return Evaluate(Position);
	ListAdd(Position,Black,depth);
	for(LISTER[depth].i=0;LISTER[depth].i < LISTER[depth].Index;LISTER[depth].i++)
	 {
	   Temp[depth]=Position;
	   Position.PutPieceBoard(LISTER[depth].Lister[LISTER[depth].i].CurrentPiece,LISTER[depth].Lister[LISTER[depth].i].CurrentColumn,LISTER[depth].Lister[LISTER[depth].i].CurrentRow,LISTER[depth].Lister[LISTER[depth].i].NextColumn,LISTER[depth].Lister[LISTER[depth].i].NextRow);
	   AllPosition++;
	   long val = Max(Position,depth - 1,Board);
	   Position=Temp[depth];
	   if (val < best)
	       { 
		best = val;
		 Data[depth].CurrentPiece=LISTER[depth].Lister[LISTER[depth].i].CurrentPiece;
		 Data[depth].NextPiece=LISTER[depth].Lister[LISTER[depth].i].NextPiece;
		 Data[depth].CurrentColumn=LISTER[depth].Lister[LISTER[depth].i].CurrentColumn;
		 Data[depth].CurrentRow=LISTER[depth].Lister[LISTER[depth].i].CurrentRow;
		 Data[depth].NextColumn=LISTER[depth].Lister[LISTER[depth].i].NextColumn;
		 Data[depth].NextRow=LISTER[depth].Lister[LISTER[depth].i].NextRow;
	       }

	}
    return best;
}
