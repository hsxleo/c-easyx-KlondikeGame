#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")//��Ƶ

//���ƴ�С
#define CARD_WIDTH  70
#define CARD_HEIGHT  100
IMAGE background;  //��Ϸ����ͼ
IMAGE card[60];    //����ͼƬ

int hint[20][20];   //��̨����
int show[20][20];   //��ʾ����

int len[11];   //ÿһ�еĳ���
int left[10];   //��ߵ�ʮ����
int left_index = -1;
int left_len = 10;

int main();
//���Ʋ˵�
void drawMenu() {
	//���ɻ���
	initgraph(600, 600);  //���ɻ���
	//�˵�����ͼƬ
	putimage(0, 0, &background);

	//����ѡ��   ��ʼ��Ϸ  ���а�
	settextcolor(WHITE);          //����������ɫ
	settextstyle(40, 0, "������κ"); //����������ʽ
	setbkmode(TRANSPARENT);       //���ֱ���͸��
	outtextxy(200, 120, "��ʼ��Ϸ");
	outtextxy(200, 330, "�˳���Ϸ");


}

//�˵���꽻��
void mouseMenu() {

	drawMenu();      //���Ʋ˵�����
	MOUSEMSG m;  //������   ������ȡ�����Ϣ

	while (true) {
		//��ȡ���λ��
		m = GetMouseMsg();

		//�ж����λ��
		if (m.x >= 200 && m.x <= 340 && m.y >= 120 && m.y <= 160) {  //����� ��ʼ��Ϸ ��λ��
			if (m.uMsg == WM_LBUTTONDOWN) {   //��갴��
				return;  //��ʼ��Ϸ
			}
		}
		else if (m.x >= 200 && m.x <= 340 && m.y >= 330 && m.y <= 370) {  //����� �˳���Ϸ ��λ��
			if (m.uMsg == WM_LBUTTONDOWN) {   //��갴��
				exit(0);  //�˳���Ϸ
			}
		}
	}
}

//���������
void randCard() {
	int i, j;
	int tmp[52];
	for (i = 0;i < 52;i++) {
		tmp[i] = i + 1;
	}
	int n = 80;  //��������80��
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

	//������ʾ����
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

//����һ�еĳ���
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

//������Ϸ
void drawGame() {
	putimage(0, 0, &background);
	setcolor(BLACK);          //������ɫ
	settextstyle(20, 0, "terminal"); //����������ʽ
	setbkmode(TRANSPARENT);       //���ֱ���͸��
	//�����ĸ���
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
	

	//����һ����
	rectangle(100, 20, 170, 120);

	//��Ҫ���ݴ�ӡ����
	for (i = 0;i < 7;i++) {
		for (j = 0;j < len[i];j++) {
			putimage(100 + i * 100, 150 + j * 30, &card[show[j][i]]);
		}
	}

	//���Ͻǵ���
	for (i = 7;i < 11;i++) {
		putimage((i-3) * 100, 20, &card[show[len[i] - 1][i]]);
	}

	//���Ͻǵ���
	if (left_index == -1) {
		putimage(100, 20, &card[0]);
	}
	else if(left_len >= 1){
		putimage(100, 20, &card[left[left_index]]);
	}

	setcolor(BLACK);          //������ɫ
	settextstyle(30, 0, "������κ"); //����������ʽ
	setbkmode(TRANSPARENT);       //���ֱ���͸��
	outtextxy(700, 600, "���ز˵�");
}



//����Ϸ
void playGame() {
	int i, j;
	int c1, c2;
	int c3, c4;
	MOUSEMSG m;
	while (1) {
		m = GetMouseMsg();

		//���ز˵�
		if (m.x >= 700 && m.x <= 820 && m.y >= 600 && m.y <= 630) {
			if (m.uMsg == WM_LBUTTONDOWN) {
				main();
			}
			
		}

		//���Ͻ��Ƶ��ƶ�
		if (m.x >= 100 && m.x <= 170 && m.y >= 20 && m.y <= 150) {
			if (m.uMsg == WM_LBUTTONDOWN) {
				c3 = left_index;
				c1 = -1;
			}
		}
		//�м䲿��
		for (i = 0;i < 7;i++) {
			if (m.x >= 100 + i * 100 && m.x <= 170 + i * 100 && m.y >= 150 + (len[i] - 1) * 30 && m.y <= 250 + (len[i] - 1) * 30) {
				if (m.uMsg == WM_LBUTTONUP && c1 == -1) {
					c4 = i;
					if (left[c3] % 13 == 0 && len[c4] == 0) {   //k �� �ƶ��ĵط��ǿհ�
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
						setcolor(RED);          //������ɫ
						settextstyle(30, 0, "������κ"); //����������ʽ
						setbkmode(TRANSPARENT);       //���ֱ���͸��
						outtextxy(700, 500, "�ƶ�ʧ��");
						Sleep(1000);
					}
					drawGame();
				}
			}
		}
		//���Ͻǵ��ĸ��ط�
		for (i = 3;i < 7;i++) {
			if (m.x >= 100 + i * 100 && m.x <= 170 + i * 100 && m.y >= 20 && m.y <= 120) {
				if (m.uMsg == WM_LBUTTONUP && c1 == -1) {
					c4 = i + 4;
					if (left[c3] == 1 + (i - 3) * 13 && len[c4] == 0) {  //����û��  ֻ�ܷ�A
						show[len[c4]][c4] = left[c3];
						len[c4]++;
						for (j = c3;j < left_len;j++) {
							left[j] = left[j + 1];
						}
						left_len--;
					}
					else if (len[c4] != 0 && show[len[c4] - 1][c4] - left[c3] == -1) {   //ͬ��ɫ �Ҵ���һ
						show[len[c4]][c4] = left[c3];
						len[c4]++;
						for (j = c3;j < left_len;j++) {
							left[j] = left[j + 1];
						}
						left_len--;
					}
					else {
						setcolor(RED);          //������ɫ
						settextstyle(30, 0, "������κ"); //����������ʽ
						setbkmode(TRANSPARENT);       //���ֱ���͸��
						outtextxy(700, 500, "�ƶ�ʧ��");
						Sleep(1000);
					}
					drawGame();
				}
			}
		}



		//�м����ƶ�
		for (i = 0;i < 7;i++) {
			if (m.x >= 100 + i * 100 && m.x <= 170 + i * 100 && m.y >= 150 + (len[i]-1) * 30 && m.y <= 250 + (len[i]-1) * 30) {
				if (m.uMsg == WM_LBUTTONDOWN) {
					c1 = i;
					c3 = -1;
				}
				if(m.uMsg == WM_LBUTTONUP && c3 == -1) {
					c2 = i;
					if (show[len[c1] - 1][c1] % 13 == 0 && len[c2] == 0) {   //k �� �ƶ��ĵط��ǿհ�
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
						setcolor(RED);          //������ɫ
						settextstyle(30, 0, "������κ"); //����������ʽ
						setbkmode(TRANSPARENT);       //���ֱ���͸��
						outtextxy(700, 500, "�ƶ�ʧ��");
						Sleep(1000);
					}
					drawGame();
				}
			}
		}
		//���Ͻǵ��ĸ��ط�
		for (i = 3;i < 7;i++) {
			if (m.x >= 100 + i * 100 && m.x <= 170 + i * 100 && m.y >= 20 && m.y <= 120) {
				if (m.uMsg == WM_LBUTTONUP && c3 == -1) {
					c2 = i + 4;
					if (show[len[c1] - 1][c1] == 1+(i-3)*13 && len[c2] == 0) {  //����û��  ֻ�ܷ�A
						show[len[c2]][c2] = show[len[c1] - 1][c1];
						len[c2]++;
						len[c1]--;
					}
					else if(len[c2] != 0 && show[len[c2] - 1][c2] - show[len[c1] - 1][c1] == -1){   //ͬ��ɫ �Ҵ���һ
						show[len[c2]][c2] = show[len[c1] - 1][c1];
						len[c2]++;
						len[c1]--;
					}
					else {
						setcolor(RED);          //������ɫ
						settextstyle(30, 0, "������κ"); //����������ʽ
						setbkmode(TRANSPARENT);       //���ֱ���͸��
						outtextxy(700, 500, "�ƶ�ʧ��");
						Sleep(1000);
					}
					drawGame();
				}
			}
		}


		//������Ͻǵ���
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
			setcolor(BLACK);          //������ɫ
			settextstyle(30, 0, "������κ"); //����������ʽ
			setbkmode(TRANSPARENT);       //���ֱ���͸��
			outtextxy(350, 450, "��Ϸʤ����");
			_getch();
			exit(0);
		}
	}
}


int main() {
	//��������
	mciSendString("open music.mp3 alias game", nullptr, 0, nullptr);
	mciSendString("play game repeat", nullptr, 0, nullptr);
	loadimage(&background, "image\\background.jpg", 900, 700);  //��ȡ����ͼƬ
	int i;
	char str[20];
	for (i = 0;i <= 52;i++) {
		sprintf(str, "image\\%d.png", i);
		loadimage(&card[i], str, CARD_WIDTH, CARD_HEIGHT);
	}

	
	//��ʼ������
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