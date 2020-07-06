#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CardGame.h"
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGraphicsProxyWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QDebug>
#include <QCloseEvent>
#include <QTimeLine>
#include <qmessagebox.h>
#include <iostream>
#include <fstream>
#include <QProgressDialog>
#include <QThread>

//#include <QMediaPlayer>
//#include <Qurl>
//#include <qsound.h>
//#include <QSoundEffect>
using namespace std;
struct round_info {
	int round;//第几轮
	int self, other;//分别什么数字
	bool win = false;//胜负
	int next;//另一位玩家翻牌号
};
class CardGame : public QMainWindow
{
	Q_OBJECT

public:
	CardGame(QWidget *parent = Q_NULLPTR,int co_time=0);
	int conect_time;
	//QMediaPlayer *player;
	/*QSoundEffect *effect;*/
	//QSound *bells;
	QGraphicsScene *scene;
	QGraphicsScene *scene2;
	QGraphicsScene *scene3;
	QLabel *Lm;
	bool choose = false;
	bool cho1=false, cho2=false, cho3=false;
	int round = 1;
	QWidget *wid1_up;
	QWidget *wid1_down;
	QWidget *wid2_up;
	QWidget *wid2_down;
	QWidget *wid3_up;
	QWidget *wid3_down;
	QWidget *wid;
	QTimer *timer;
	QWidget *box;
	QLabel *mess;
	QPushButton *btn;
	QGraphicsProxyWidget *gw1, *gw2, *gw3, *gw4, *gw5, *gw6;
	QTimer *interval;
	QGraphicsProxyWidget *mask1;
	QGraphicsProxyWidget *mask2;
	QGraphicsProxyWidget *mask3;
	int *punish_number = new int[21];
	round_info *RI = new round_info[21];
	int dectome, dectoot;
	double scoreA = 0;
	double scoreB = 0;
	void round_end_flush();
	void noise_select();
	

private:
	Ui::CardGameClass ui;
	
private slots:
	void on_Bt1_clicked();
	void on_Bt2_clicked();
	void on_Bt3_clicked();
	void give_punish();
	void show_nextround();
	void punish();
	void show_view1();
	void show_view2();
	void show_view3();
	void show_buttons();
	void on_timer_timeout();
	void on_Next_round_clicked();
	void showpunish();
	void on_confirm_btn_clicked();
	void on_continue_Btn_clicked();
	void othersshow();
protected:
	void closeEvent(QCloseEvent *event);
	
};

