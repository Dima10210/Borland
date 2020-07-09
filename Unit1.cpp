//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
int a[15][20] = {//создание поля 0-проход,1-стена,3-персонаж,4-финиш.
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1},
{1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
{1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
{3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 4},
{1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
{1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
{1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
{1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
{1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};
for (int i = 0; i < 15; i++)
        for (int j = 0; j < 20; j++)
                field[i][j] = a[i][j];
Form1->DrawField();
};

void TForm1::DrawField()//отрисовка поля
 {

 for (int i = 0; i < 15; i++){
        for (int j = 0; j < 20; j++){
                if(Form1->field[i][j]==0){

                        Form1->Image1->Canvas->Pen->Color=clWhite;
                        Form1->Image1->Canvas->Brush->Color=clWhite;

                }
                if(Form1->field[i][j]==1){
                        Form1->Image1->Canvas->Pen->Color=clBlack;
                        Form1->Image1->Canvas->Brush->Color=clBlack;

                }
                if(Form1->field[i][j]==4){
                        Form1->Image1->Canvas->Pen->Color=clRed;
                        Form1->Image1->Canvas->Brush->Color=clYellow;

                }
                if(Form1->field[i][j]==3){
                        Form1->Image1->Canvas->Pen->Color=clRed;
                        Form1->Image1->Canvas->Brush->Color=clGreen;

                }
                Form1->Image1->Canvas->Rectangle(j*30,i*30,j*30+30,i*30+30);
        }
 }
 }
//---------------------------------------------------------------------------
//функция отрисовки хода
void TForm1::redraw(int cur_i, int cur_j, int new_i, int new_j){
        Form1->Image1->Canvas->Pen->Color=clWhite;
        Form1->Image1->Canvas->Brush->Color=clWhite;
        Form1->Image1->Canvas->Rectangle(cur_j*30,cur_i*30,cur_j*30+30,cur_i*30+30);
        Form1->Image1->Canvas->Pen->Color=clRed;
        Form1->Image1->Canvas->Brush->Color=clGreen;
        Form1->Image1->Canvas->Rectangle(new_j*30,new_i*30,new_j*30+30,new_i*30+30);
        Form1->Image1->Canvas->OnChange;
}
//функция поиска пути
void TForm1::search_path(){
        int field2[15][20];//буферное поле
        int cur_i = 7,cur_j=0;//координаты начала лабиринта
        int end_i = 7, end_j =19;//координаты конца лабиринта
        for (int i = 0; i < 15; i++)
                for (int j = 0; j < 20; j++)
                        field2[i][j] = field[i][j];//добавление массива в буфер, если будет необходимо изменять его во время поиска пути.
        int wall = 1;//переменная отвечающая за направление движения 1-вправо,2-вниз,3-влево,4-вверх.
        bool step = False;//переменная проверяющая совершено ли движение
        while(True){
        Application->ProcessMessages();//необходимо, чтобы приложение не зависало и отрисовывало ходы

                if(wall == 1){
                if(field2[cur_i][cur_j+1]==4){   //проверка на победу
                        Form1->redraw(cur_i,cur_j,cur_i,cur_j+1);
                        break;
                }
                        if(field2[cur_i][cur_j+1]==0){
                                Form1->redraw(cur_i,cur_j,cur_i,cur_j+1);
                                cur_j++;
                                step = True;
                                if(field2[cur_i+1][cur_j]==0)wall=2;else
                                if(field2[cur_i][cur_j+1]==1){wall=2;
                                if(field2[cur_i-1][cur_j]==0)wall=4;} //проверка допустимого передвижения
                        }
                }
                else if(wall == 2){
                        if(field2[cur_i+1][cur_j]==0){
                                Form1->redraw(cur_i,cur_j,cur_i+1,cur_j);
                                cur_i++;
                                step = True;
                                if(field2[cur_i][cur_j-1]==0)wall=3;else
                                if(field2[cur_i+1][cur_j]==1){
                                        if(field2[cur_i][cur_j+1]==1){
                                        if(field2[cur_i][cur_j-1]==0)wall=3;else
                                        if(field2[cur_i][cur_j+1]==0)wall=1;else
                                        wall=4;
                                        }
                                }
                        }
                }
                else if(wall == 3){
                        if(field2[cur_i][cur_j-1]==0){
                                Form1->redraw(cur_i,cur_j,cur_i,cur_j-1);
                                cur_j--;
                                step = True;

                                if(field2[cur_i-1][cur_j]==0)wall=4;else
                                if(field2[cur_i][cur_j-1]==1){
                                if(field2[cur_i+1][cur_j]==0)wall=2;else
                                if(field2[cur_i][cur_j+1]==0)wall=1;
                                }
                        }
                }
                else if(wall == 4){
                        if(field2[cur_i-1][cur_j]==0){
                                Form1->redraw(cur_i,cur_j,cur_i-1,cur_j);
                                cur_i--;
                                step = True;
                                if(field2[cur_i][cur_j+1]==0)wall=1;else
                                if(field2[cur_i-1][cur_j]==1)wall=3;

                        }
                }
                if((cur_i==end_i)&&(cur_j==end_j)) break;


        Sleep(200);//сон, чтобы уменьшить скорость передвижения
        if(!step){//проверка на движение в ходу
                if(wall == 4){
                        wall = 1;
                }
                else wall++;
        }
        step = False;
        }
}

void __fastcall TForm1::Button1Click(TObject *Sender)
{
           Form1->search_path();

}
//---------------------------------------------------------------------------

