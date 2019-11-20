#include <Windows.h>
#include <iostream>
#include <vector>
using namespace std;
int Max(int &xiazhiPos);
int Min(int &xiazhiPos);
#define ply 3//X
#define com 4//O
//定义棋盘数组，1，2表示横竖线，0表示棋子
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
//定义棋局数组，九个格子
int qiju[3][3]=
{
    0,0,0,
    0,0,0,
    0,0,0,
};
//用于判断棋子在横、竖、斜方向上是否连成3子的数组
int xydir[4][2]={
    1,0,
    1,1,
    0,1,
    -1,1,
};
//用于存放棋子坐标及方向的结构体
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
//将着子存入数组中，当数组长度达到3，表明已连成3子
vector<Node> buf;
//双方轮流下子的变量，0表示X下子，1表示O下子，游戏中X是先手
bool xiazhi=0;
//绘制函数
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
                cout<<"—";
            }
                else if (qiju_ui[i][j]==2){
                    cout<<"｜";
                }
                    else if (qiju_ui[i][j]==ply){
                        cout<<"×";
                    }
                        else if (qiju_ui[i][j]==com){
                            cout<<"○";
                        }
                            else{
                                cout<<" ?";
                            }
        }
        cout<<endl;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//判断棋子是否连成3子?
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
    //qi_over函数就是评价函数，返回值为真时，表示已经搜索到叶子节点，棋局结束，并返回评价值，反之，继续搜索
bool qi_over(int &result)//-1:○赢 ? 0:平局 ? 1:×赢 ??
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
//以下四个函数是玩家与电脑下子和撤消下子
void player_xiazhi(int pos) //pos从1开始
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
//主要的核心算法，极小极大算法
int Max(int &xiazhiPos)
{
    int best = -999;
    int result;
    if (qi_over(result)==true){//棋局结束【×赢,○赢,平局】
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
    if (qi_over(result)==true){//棋局结束【×赢,○赢,平局】
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
    if (xiazhi == 0){ //X先手，我们以X来返回评价值，X取最大
        return Max(xiazhiPos);
    }
    else{//O取最小
        return Min(xiazhiPos);
    }
}////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, _TCHAR* argv[])
{
    while(1){
        system("cls");
        draw();
        cout<<"[1~9]表示玩家(×)下子的格子索引"<<endl;
        if (xiazhi==0){//玩家
            int pos;
            cin>>pos;
            player_xiazhi(pos);
        }
            else{
                int xiazhiPos;
                MinMax(xiazhiPos);
                com_xiazhi(xiazhiPos);
            }
        xiazhi=!xiazhi; //轮流下子
    }
    return 0;
}

