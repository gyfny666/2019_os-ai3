#include <Windows.h>
#include <iostream>
#include <vector>
using namespace std;
int Max(int &xiazhiPos);
int Min(int &xiazhiPos);
#define ply 3//X
#define com 4//O
//�����������飬1��2��ʾ�����ߣ�0��ʾ����
int qiju_ui[7][7]=
{
    1,1,1,1,1,1,1,
    2,0,2,0,2,0,2,
    2,1,2,1,2,1,2,
    2,0,2,0,2,0,2,
    2,1,2,1,2,1,2,
    2,0,2,0,2,0,2,
    1,1,1,1,1,1,1,
};
//����������飬�Ÿ�����
int qiju[3][3]=
{
    0,0,0,
    0,0,0,
    0,0,0,
};
//�����ж������ںᡢ����б�������Ƿ�����3�ӵ�����
int xydir[4][2]={
    1,0,
    1,1,
    0,1,
    -1,1,
};
//���ڴ���������꼰����Ľṹ��
struct Node
{
    int x;
    int y;
    int dir_x;
    int dir_y;
    int type;
    Node(int x,int y,int dir_x,int dir_y,int type){
        this->x=x;
        this->y=y;
        this->dir_x=dir_x;
        this->dir_y=dir_y;
        this->type=type;
    }
};
//�����Ӵ��������У������鳤�ȴﵽ3������������3��
vector<Node> buf;
//˫���������ӵı�����0��ʾX���ӣ�1��ʾO���ӣ���Ϸ��X������
bool xiazhi=0;
//���ƺ���
void draw()
{
    for (int i=0;i<3;i++){
        for (int j=0;j<3;j++){
            qiju_ui[i*2+1][j*2+1]=qiju[i][j];
        }
    }
    for (int i=0;i<7;i++){
        for (int j=0;j<7;j++){
            if (qiju_ui[i][j]==1){
                cout<<"��";
            }
                else if (qiju_ui[i][j]==2){
                    cout<<"��";
                }
                    else if (qiju_ui[i][j]==ply){
                        cout<<"��";
                    }
                        else if (qiju_ui[i][j]==com){
                            cout<<"��";
                        }
                            else{
                                cout<<" ?";
                            }
        }
        cout<<endl;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�ж������Ƿ�����3��?
void three_bix(int x,int y,int dir_x,int dir_y,int type,bool &over,bool first)
{
    if (first==true){
        if (qiju[y][x]==ply || qiju[y][x]==com){
            for (int i=0;!over && i<4;i++){
                buf.clear();
                buf.push_back(Node(x,y,dir_x,dir_y,qiju[y][x]));
                three_bix(x+xydir[i][0],y+xydir[i][1],xydir[i][0],xydir[i][1],qiju[y][x],over,false);
            }
        }
    }
    else{
        if (y<0 || x<0 || y>=3 || x>=3){
            return;
        }
        if (qiju[y][x]==0){
            return;
        }
        if (qiju[y][x]==type){
            buf.push_back(Node(x,y,dir_x,dir_y,type));
            if (buf.size()==3){
                over=true;
                return;
            }
                else{
                    three_bix(x+dir_x,y+dir_y,dir_x,dir_y,type,over,false);
                }
        }
    }
}
    //qi_over�����������ۺ���������ֵΪ��ʱ����ʾ�Ѿ�������Ҷ�ӽڵ㣬��ֽ���������������ֵ����֮����������
bool qi_over(int &result)//-1:��Ӯ ? 0:ƽ�� ? 1:��Ӯ ??
{
    bool full=true;
    for (int i=0;i<3;i++){
        for (int j=0;j<3;j++){
            bool over=false;
            three_bix(j,i,0,0,0,over,true);
            if (over==true){
                if (buf.front().type==com){
                    result=-1;
                    return true;
                }
                else if (buf.front().type==ply){
                    result=1;
                    return true;
                }
            }
                else{
                    if (qiju[i][j]==0){
                        full=false;
                    }
                }
        }
    }
    if (full){
        result=0;
        return true;
    }
    return false;
}////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�����ĸ������������������Ӻͳ�������
void player_xiazhi(int pos) //pos��1��ʼ
{
    int x=(pos-1)%3;
    int y=(pos-1)/3;
    qiju[y][x]=ply;
}
void player_back(int pos)
{
    int x=(pos-1)%3;
    int y=(pos-1)/3;
    qiju[y][x]=0;
}
void com_xiazhi(int pos)
{
    int x=(pos-1)%3;
    int y=(pos-1)/3;
    qiju[y][x]=com;
}
void com_back(int pos)
{
    int x=(pos-1)%3;
    int y=(pos-1)/3;
    qiju[y][x]=0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��Ҫ�ĺ����㷨����С�����㷨
int Max(int &xiazhiPos)
{
    int best = -999;
    int result;
    if (qi_over(result)==true){//��ֽ�������Ӯ,��Ӯ,ƽ�֡�
        return result;
    }
    for (int i=0;i<9;i++){
        if (qiju[i/3][i%3]==0){
            player_xiazhi(i+1);
            int val = Min(xiazhiPos);
            player_back(i+1);
            if (val>best){
                best = val;
                xiazhiPos=i+1;
            }
            if (val==1){
                break;
            }
        }
    }
    return best;
}
int Min(int &xiazhiPos)
{
    int best = 999;
    int result;
    if (qi_over(result)==true){//��ֽ�������Ӯ,��Ӯ,ƽ�֡�
        return result;
    }
    for (int i=0;i<9;i++){
        if (qiju[i/3][i%3]==0){
            com_xiazhi(i+1);
            int val = Max(xiazhiPos);
            com_back(i+1);
            if (val < best){
                best = val;
                xiazhiPos=i+1;
            }
            if (val==-1){
                break;
            }
        }
    }
    return best;
}
int MinMax(int &xiazhiPos)
{
    if (xiazhi == 0){ //X���֣�������X����������ֵ��Xȡ���
        return Max(xiazhiPos);
    }
    else{//Oȡ��С
        return Min(xiazhiPos);
    }
}////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, _TCHAR* argv[])
{
    while(1){
        system("cls");
        draw();
        cout<<"[1~9]��ʾ���(��)���ӵĸ�������"<<endl;
        if (xiazhi==0){//���
            int pos;
            cin>>pos;
            player_xiazhi(pos);
        }
            else{
                int xiazhiPos;
                MinMax(xiazhiPos);
                com_xiazhi(xiazhiPos);
            }
        xiazhi=!xiazhi; //��������
    }
    return 0;
}

