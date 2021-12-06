#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")//音频

//卡牌大小
#define CARD_WIDTH  70
#define CARD_HEIGHT  100
IMAGE background;  //游戏背景图
IMAGE card[60];    //卡牌图片

int hint[20][20];   //后台的牌
int show[20][20];   //显示的牌

int len[11];   //每一列的长度
int left[10];   //左边的十张牌
int left_index = -1;
int left_len = 10;

int main();
//绘制菜单
void drawMenu() {
	//生成画布
	initgraph(600, 600);  //生成画布
	//菜单背景图片
	putimage(0, 0, &background);

	//绘制选项   开始游戏  排行榜
	settextcolor(WHITE);          //设置字体颜色
	settextstyle(40, 0, "华文新魏"); //设置文字样式
	setbkmode(TRANSPARENT);       //文字背景透明
	outtextxy(200, 120, "开始游戏");
	outtextxy(200, 330, "退出游戏");


}

//菜单鼠标交互
void mouseMenu() {

	drawMenu();      //绘制菜单界面
	MOUSEMSG m;  //鼠标变量   用来获取鼠标信息

	while (true) {
		//获取鼠标位置
		m = GetMouseMsg();

		//判断鼠标位置
		if (m.x >= 200 && m.x <= 340 && m.y >= 120 && m.y <= 160) {  //鼠标在 开始游戏 的位置
			if (m.uMsg == WM_LBUTTONDOWN) {   //鼠标按下
				return;  //开始游戏
			}
		}
		else if (m.x >= 200 && m.x <= 340 && m.y >= 330 && m.y <= 370) {  //鼠标在 退出游戏 的位置
			if (m.uMsg == WM_LBUTTONDOWN) {   //鼠标按下
				exit(0);  //退出游戏
			}
		}
	}
}

//随机生成牌
void randCard() {
	int i, j;
	int tmp[52];
	for (i = 0;i < 52;i++) {
		tmp[i] = i + 1;
	}
	int n = 80;  //两两交换80次
	srand((unsigned)time(NULL));
	while (n--) {
		int t1 = rand() % 51 + 1;
		int t2 = rand() % 51 + 1;
		int t = tmp[t1];
		tmp[t1] = tmp[t2];
		tmp[t2] = t;
	}
	n = 51;
	for (i = 0;i < 6;i++) {
		for (j = 0;j < 7;j++) {
			hint[i][j] = tmp[n--];
		}
	}
	for (i = 0;i < 10;i++) {
		left[i] = tmp[n--];
	}

	//用来显示的牌
	for (i = 0;i < 6;i++) {
		for (j = 0;j < 7;j++) {
			if (i == 0 || i == 1) {
				show[i][j] = 0;
			}
			else {
				show[i][j] = hint[i][j];
			}
		}
	}
}

//计算一列的长度
void calcLen() {
	int i, j;
	for (i = 0; i < 11; i++) {
		for (j = 0; j < 20; j++) {
			if (show[j][i] == -1) {
				len[i] = j;
				break;
			}
		}
	}

}

//绘制游戏
void drawGame() {
	putimage(0, 0, &background);
	setcolor(BLACK);          //设置颜色
	settextstyle(20, 0, "terminal"); //设置文字样式
	setbkmode(TRANSPARENT);       //文字背景透明
	//右上四个框
	int i, j;
	
	for (i = 0;i < 4;i++) {
		rectangle(400 + i * 100, 20, 470 + i * 100, 120);
	}

	char s[5];
	if (len[7] == 0) {
		sprintf(s, "%c", 6);
		outtextxy(430, 55, s);
	}
	if (len[8] == 0) {
		sprintf(s, "%c", 5);
		outtextxy(530, 55, s);
	}
	setcolor(RED);
	if (len[9] == 0) {
		sprintf(s, "%c", 3);
		outtextxy(630, 55, s);
	}
	if (len[10] == 0) {
		sprintf(s, "%c", 4);
		outtextxy(730, 55, s);
	}
	

	//左上一个框
	rectangle(100, 20, 170, 120);

	//主要内容打印出来
	for (i = 0;i < 7;i++) {
		for (j = 0;j < len[i];j++) {
			putimage(100 + i * 100, 150 + j * 30, &card[show[j][i]]);
		}
	}

	//右上角的牌
	for (i = 7;i < 11;i++) {
		putimage((i-3) * 100, 20, &card[show[len[i] - 1][i]]);
	}

	//左上角的牌
	if (left_index == -1) {
		putimage(100, 20, &card[0]);
	}
	else if(left_len >= 1){
		putimage(100, 20, &card[left[left_index]]);
	}

	setcolor(BLACK);          //设置颜色
	settextstyle(30, 0, "华文新魏"); //设置文字样式
	setbkmode(TRANSPARENT);       //文字背景透明
	outtextxy(700, 600, "返回菜单");
}



//玩游戏
void playGame() {
	int i, j;
	int c1, c2;
	int c3, c4;
	MOUSEMSG m;
	while (1) {
		m = GetMouseMsg();

		//返回菜单
		if (m.x >= 700 && m.x <= 820 && m.y >= 600 && m.y <= 630) {
			if (m.uMsg == WM_LBUTTONDOWN) {
				main();
			}
			
		}

		//左上角牌的移动
		if (m.x >= 100 && m.x <= 170 && m.y >= 20 && m.y <= 150) {
			if (m.uMsg == WM_LBUTTONDOWN) {
				c3 = left_index;
				c1 = -1;
			}
		}
		//中间部分
		for (i = 0;i < 7;i++) {
			if (m.x >= 100 + i * 100 && m.x <= 170 + i * 100 && m.y >= 150 + (len[i] - 1) * 30 && m.y <= 250 + (len[i] - 1) * 30) {
				if (m.uMsg == WM_LBUTTONUP && c1 == -1) {
					c4 = i;
					if (left[c3] % 13 == 0 && len[c4] == 0) {   //k 且 移动的地方是空白
						show[len[c4]][c4] = left[c3];
						len[c4]++;
						for (j = c3;j < left_len;j++) {
							left[j] = left[j + 1];
						}
						left_len--;
					}
					else if (left[c3] % 13 != 0 && show[len[c4] - 1][c4] - left[c3] == 1){
						show[len[c4]][c4] = left[c3];
						len[c4]++;
						for (j = c3;j < left_len;j++) {
							left[j] = left[j + 1];
						}
						left_len--;
					}
					else {
						setcolor(RED);          //设置颜色
						settextstyle(30, 0, "华文新魏"); //设置文字样式
						setbkmode(TRANSPARENT);       //文字背景透明
						outtextxy(700, 500, "移动失败");
						Sleep(1000);
					}
					drawGame();
				}
			}
		}
		//右上角的四个地方
		for (i = 3;i < 7;i++) {
			if (m.x >= 100 + i * 100 && m.x <= 170 + i * 100 && m.y >= 20 && m.y <= 120) {
				if (m.uMsg == WM_LBUTTONUP && c1 == -1) {
					c4 = i + 4;
					if (left[c3] == 1 + (i - 3) * 13 && len[c4] == 0) {  //上面没牌  只能放A
						show[len[c4]][c4] = left[c3];
						len[c4]++;
						for (j = c3;j < left_len;j++) {
							left[j] = left[j + 1];
						}
						left_len--;
					}
					else if (len[c4] != 0 && show[len[c4] - 1][c4] - left[c3] == -1) {   //同花色 且大于一
						show[len[c4]][c4] = left[c3];
						len[c4]++;
						for (j = c3;j < left_len;j++) {
							left[j] = left[j + 1];
						}
						left_len--;
					}
					else {
						setcolor(RED);          //设置颜色
						settextstyle(30, 0, "华文新魏"); //设置文字样式
						setbkmode(TRANSPARENT);       //文字背景透明
						outtextxy(700, 500, "移动失败");
						Sleep(1000);
					}
					drawGame();
				}
			}
		}



		//中间牌移动
		for (i = 0;i < 7;i++) {
			if (m.x >= 100 + i * 100 && m.x <= 170 + i * 100 && m.y >= 150 + (len[i]-1) * 30 && m.y <= 250 + (len[i]-1) * 30) {
				if (m.uMsg == WM_LBUTTONDOWN) {
					c1 = i;
					c3 = -1;
				}
				if(m.uMsg == WM_LBUTTONUP && c3 == -1) {
					c2 = i;
					if (show[len[c1] - 1][c1] % 13 == 0 && len[c2] == 0) {   //k 且 移动的地方是空白
						show[len[c2]][c2] = show[len[c1] - 1][c1];
						len[c2]++;
						len[c1]--;

					}
					else if (show[len[c1] - 1][c1] % 13 != 0 && show[len[c2] - 1][c2] - show[len[c1] - 1][c1] == 1) {
						show[len[c2]][c2] = show[len[c1] - 1][c1];
						len[c2]++;
						len[c1]--;
						if (len[c1] == 3 || len[c1] == 2) {
							show[len[c1] - 1][c1] = hint[len[c1] - 1][c1];
						}
					}
					else {
						setcolor(RED);          //设置颜色
						settextstyle(30, 0, "华文新魏"); //设置文字样式
						setbkmode(TRANSPARENT);       //文字背景透明
						outtextxy(700, 500, "移动失败");
						Sleep(1000);
					}
					drawGame();
				}
			}
		}
		//右上角的四个地方
		for (i = 3;i < 7;i++) {
			if (m.x >= 100 + i * 100 && m.x <= 170 + i * 100 && m.y >= 20 && m.y <= 120) {
				if (m.uMsg == WM_LBUTTONUP && c3 == -1) {
					c2 = i + 4;
					if (show[len[c1] - 1][c1] == 1+(i-3)*13 && len[c2] == 0) {  //上面没牌  只能放A
						show[len[c2]][c2] = show[len[c1] - 1][c1];
						len[c2]++;
						len[c1]--;
					}
					else if(len[c2] != 0 && show[len[c2] - 1][c2] - show[len[c1] - 1][c1] == -1){   //同花色 且大于一
						show[len[c2]][c2] = show[len[c1] - 1][c1];
						len[c2]++;
						len[c1]--;
					}
					else {
						setcolor(RED);          //设置颜色
						settextstyle(30, 0, "华文新魏"); //设置文字样式
						setbkmode(TRANSPARENT);       //文字背景透明
						outtextxy(700, 500, "移动失败");
						Sleep(1000);
					}
					drawGame();
				}
			}
		}


		//点击左上角的牌
		if (m.x >= 100 && m.x <= 170 && m.y >= 20 && m.y <= 120) {
			if (m.uMsg == WM_LBUTTONUP) {
				if (m.x >= 100 && m.x <= 170 && m.y >= 20 && m.y <= 120) {
					left_index++;
					if (left_index >= left_len) {
						left_index = 0;
					}
					drawGame();
				}
			}
		}

		for (i = 7;i < 11;i++) {
			if (show[len[i] - 1][i] % 13 != 0) {
				break;
			}
		}
		if (i == 11) {
			setcolor(BLACK);          //设置颜色
			settextstyle(30, 0, "华文新魏"); //设置文字样式
			setbkmode(TRANSPARENT);       //文字背景透明
			outtextxy(350, 450, "游戏胜利！");
			_getch();
			exit(0);
		}
	}
}


int main() {
	//播放音乐
	mciSendString("open music.mp3 alias game", nullptr, 0, nullptr);
	mciSendString("play game repeat", nullptr, 0, nullptr);
	loadimage(&background, "image\\background.jpg", 900, 700);  //读取背景图片
	int i;
	char str[20];
	for (i = 0;i <= 52;i++) {
		sprintf(str, "image\\%d.png", i);
		loadimage(&card[i], str, CARD_WIDTH, CARD_HEIGHT);
	}

	
	//初始化变量
	memset(hint, -1, sizeof(hint));
	memset(show, -1, sizeof(show));
	memset(left, -1, sizeof(left));
	memset(len, -1, sizeof(len));
	left_index = -1;

	mouseMenu();
	initgraph(900, 700);
	randCard();
	calcLen();
	drawGame();
	playGame();
	_getch();
	
}