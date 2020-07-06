#include "CardGame.h"
//A组先选

CardGame::CardGame(QWidget *parent, int co_time)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.punishtext_label->hide();
	ui.punishtitle_label->hide();
	ui.punish_label->hide();
	ui.givepunishtext_label->hide();
	//ui.Bt1->hide();
	//ui.Bt2->hide();
	//ui.Bt3->hide();
	ui.info_label->hide();
	ui.lineEdit->hide();
	ui.continue_Btn->hide();
	conect_time = co_time;
	ui.A_score_label->setText(QString::number(scoreA));
	ui.B_score_label->setText(QString::number(scoreB));
	scene = new QGraphicsScene();
	scene2 = new QGraphicsScene();
	scene3 = new QGraphicsScene();
	ui.view1->setScene(scene);
	ui.view2->setScene(scene2);
	ui.view3->setScene(scene3);
	ui.Next_round->hide();
	ui.confirm_btn->hide();
	srand(time(NULL));
	int r;
	r = rand() % 2;
	if (r == 0) {
		RI[1].win = true;
		RI[2].win = false;
	}
	else {
		RI[1].win = false;
		RI[2].win = true;
	}
	//前十轮中胜利的三轮
	int a = 0, b = 0, c = 0;
	while (a == b) {
		a = rand() % 9 + 3;
		b = rand() % 9 + 3;
	}
	c = rand() % 9 + 3;
	while (c == a || c == b) {
		c = rand() % 9 + 3;
	}
	//后八轮中胜的两轮
	int k = 0, t = 0;
	while (k == t) {
		k = rand() % 8 + 13;
		t = rand() % 8 + 13;
	}
	for (int i = 3; i <= 12; i++) {
		RI[i].win = false;
	}
	for (int i = 13; i <= 20; i++) {
		RI[i].win = true;
	}
	RI[a].win = true;
	RI[b].win = true;
	RI[c].win = true;
	RI[k].win = false;
	RI[t].win = false;
	fstream f;
	f.open(".//record.txt", ios::out | ios::app);
	for (int i = 1; i <= 20; i++) {
		punish_number[i] = 0;
		RI[i].round = i;
		int a = 0, b = 0;
		int big, small;
		while (a == b) {
			a = rand() % 10 + 1;
			b = rand() % 10 + 1;
		}
		if (a > b) {
			big = a;
			small = b;
		}
		else {
			big = b;
			small = a;
		}
		RI[i].next = rand() % 2 + 1;
		
		if (RI[i].win) {
			RI[i].self = big;
			RI[i].other = small;
		}
		else {
			RI[i].self = small;
			RI[i].other = big;
		}
		f << "ROUND : " << RI[i].round << " ,WIN: " << RI[i].win << " ,SELF: " << RI[i].self
			<< " ,OTHER: " << RI[i].other << endl;
	}
	f.close();
	
	ui.radioButton->hide();
	ui.radioButton_2->hide();
	ui.radioButton_3->hide();
	ui.radioButton_4->hide();
	ui.radioButton_5->hide();
	ui.radioButton_6->hide();
	

	QPixmap *Pix = new QPixmap(":/CardGame/mask.jpg");
	Pix->scaled(ui.Lable_mask1->size(), Qt::KeepAspectRatio);

	ui.Lable_mask1->setScaledContents(true);
	ui.Lable_mask1->setPixmap(*Pix);
	ui.Lable_mask1->show();
	ui.Lable_mask2->setScaledContents(true);
	ui.Lable_mask2->setPixmap(*Pix);
	ui.Lable_mask2->show();
	ui.Lable_mask3->setScaledContents(true);
	ui.Lable_mask3->setPixmap(*Pix);
	ui.Lable_mask3->show();
	//QTimer *conetimer = new QTimer();
	//conetimer->start(conect_time);
	//QObject::connect(conetimer, SIGNAL(timeout()), this, SLOT(othersshow()));
	//QObject::connect(conetimer, SIGNAL(timeout()), conetimer, SLOT(stop()));
}

void CardGame::on_Bt1_clicked() {
	if (choose||cho1) {
		return;
	}
	choose = true;
	
	timer = new QTimer(this);
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(on_timer_timeout()));
	timer->start(5000);
	show_view1();
	if (round % 2 == 1)
	{
		interval = new QTimer(this);
		srand(time(NULL));
		int no = rand() % 2000 + 2000;
		interval->start(no);
		if (RI[round].next == 1) {
			QObject::connect(interval, SIGNAL(timeout()), this, SLOT(show_view2()));
		}
		else {
			QObject::connect(interval, SIGNAL(timeout()), this, SLOT(show_view3()));
		}
		QObject::connect(interval, SIGNAL(timeout()), interval, SLOT(stop()));
	}
}

void CardGame::on_Bt2_clicked()
{
	if (choose||cho2) {
		return;
	}
	choose = true;
	timer = new QTimer(this);
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(on_timer_timeout()));
	timer->start(5000);
	
	show_view2();
	if (round % 2 == 1) {
		interval = new QTimer(this);
		srand(time(NULL));
		int no = rand() % 2000 + 2000;
		interval->start(no);
		if (RI[round].next == 1) {
			QObject::connect(interval, SIGNAL(timeout()), this, SLOT(show_view3()));
		}
		else {
			QObject::connect(interval, SIGNAL(timeout()), this, SLOT(show_view1()));
		}
		QObject::connect(interval, SIGNAL(timeout()), interval, SLOT(stop()));
	}
}

void CardGame::on_Bt3_clicked()
{
	if (choose||cho3) {
		return;
	}
	choose = true;
	
	timer = new QTimer(this);
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(on_timer_timeout()));
	timer->start(5000);
	show_view3();
	if (round % 2 == 1) {
		interval = new QTimer(this);
		srand(time(NULL));
		int no = rand() % 2000 + 2000;
		interval->start(no);
		if (RI[round].next == 1) {
			QObject::connect(interval, SIGNAL(timeout()), this, SLOT(show_view1()));
		}
		else {
			QObject::connect(interval, SIGNAL(timeout()), this, SLOT(show_view2()));
		}
		QObject::connect(interval, SIGNAL(timeout()), interval, SLOT(stop()));

	}
}

void CardGame::give_punish()
{
	
}

void CardGame::show_nextround()
{
	ui.Next_round->show();
}

void CardGame::show_view1()
{
	ui.Lable_mask1->hide();
	QString path;
	if (round % 2 == 0) {//偶数轮
		if (cho2 || cho3) {
			path = QString(":/CardGame/0") + QString::number(RI[round].self) + QString(".jpg");
		}
		else {
			path = QString(":/CardGame/0") + QString::number(RI[round].other) + QString(".jpg");
		}
	}
	else {//奇数
		if (cho2 || cho3) {
			path = QString(":/CardGame/0") + QString::number(RI[round].other) + QString(".jpg");
		}
		else {
			path = QString(":/CardGame/0") + QString::number(RI[round].self) + QString(".jpg");
		}
	}
	cho1 = true;
	wid1_up = new QWidget;
	QPixmap *Pix1 = new QPixmap(":/CardGame/mask.jpg");
	QLabel *L1 = new QLabel(wid1_up);
	L1->resize(140, 200);
	Pix1->scaled(L1->size(), Qt::KeepAspectRatio);
	L1->setScaledContents(true);
	L1->setPixmap(*Pix1);

	wid1_down = new QWidget;
	QPixmap *Pix2 = new QPixmap(path);
	QLabel *L2 = new QLabel(wid1_down);
	L2->resize(140, 200);
	Pix2->scaled(L2->size(), Qt::KeepAspectRatio);
	L2->setScaledContents(true);
	L2->setPixmap(*Pix2);

	QGraphicsProxyWidget *graphicsWid1 = scene->addWidget(wid1_up);
	gw1 = graphicsWid1;
	QGraphicsProxyWidget *graphicsWid2 = scene->addWidget(wid1_down);
	gw2 = graphicsWid2;
	graphicsWid2->setTransform(QTransform().translate(graphicsWid2->boundingRect().width() / 2, graphicsWid2->boundingRect().height() / 2)
		.rotate(-180, Qt::YAxis)
		.translate(-graphicsWid2->boundingRect().width() / 2, -graphicsWid2->boundingRect().height() / 2));
	graphicsWid1->setVisible(true);
	graphicsWid2->setVisible(false);
	//新建线型值闹钟
	QTimeLine *timeLine = new QTimeLine(1500, scene);
	timeLine->setStartFrame(0);
	timeLine->setEndFrame(180);
	//每次值发生变化，旋转一定角度
	QObject::connect(timeLine, &QTimeLine::frameChanged, [timeLine, graphicsWid1, graphicsWid2](const int frame) {
		//对于登录窗体正常旋转
		graphicsWid1->setTransform(QTransform().translate(graphicsWid1->boundingRect().width() / 2, graphicsWid1->boundingRect().height() / 2)
			.rotate(frame, Qt::YAxis)
			.translate(-graphicsWid1->boundingRect().width() / 2, -graphicsWid1->boundingRect().height() / 2));
		//对于设置窗体由于开始旋转到了-180度，所以现在应该是-179,-176,-170....,0,这里应该是frame-180;也就是加上起点为-180度啦
		graphicsWid2->setTransform(QTransform().translate(graphicsWid2->boundingRect().width() / 2, graphicsWid2->boundingRect().height() / 2)
			.rotate(frame - 180, Qt::YAxis)
			.translate(-graphicsWid2->boundingRect().width() / 2, -graphicsWid2->boundingRect().height() / 2));
		if (frame >= 90 && frame < 180) {
			graphicsWid1->setVisible(false);
			graphicsWid2->setVisible(true);
		}
	});
	timeLine->start();

}

void CardGame::show_view2()
{
	ui.Lable_mask2->hide();
	QString path;
	if (round % 2 == 0) {//偶数轮
		if (cho1 || cho3) {
			path = QString(":/CardGame/0") + QString::number(RI[round].self) + QString(".jpg");
		}
		else {
			path = QString(":/CardGame/0") + QString::number(RI[round].other) + QString(".jpg");
		}
	}
	else {//奇数
		if (cho1 || cho3) {
			path = QString(":/CardGame/0") + QString::number(RI[round].other) + QString(".jpg");
		}
		else {
			path = QString(":/CardGame/0") + QString::number(RI[round].self) + QString(".jpg");
		}
	}
	cho2 = true;
	wid2_up = new QWidget;
	QPixmap *Pix1 = new QPixmap(":/CardGame/mask.jpg");
	QLabel *L1 = new QLabel(wid2_up);
	L1->resize(140, 200);
	Pix1->scaled(L1->size(), Qt::KeepAspectRatio);
	L1->setScaledContents(true);
	L1->setPixmap(*Pix1);

	wid2_down = new QWidget;
	QPixmap *Pix2 = new QPixmap(path);
	QLabel *L2 = new QLabel(wid2_down);
	L2->resize(140, 200);
	Pix2->scaled(L2->size(), Qt::KeepAspectRatio);
	L2->setScaledContents(true);
	L2->setPixmap(*Pix2);

	QGraphicsProxyWidget *graphicsWid1 = scene2->addWidget(wid2_up);
	gw3 = graphicsWid1;
	QGraphicsProxyWidget *graphicsWid2 = scene2->addWidget(wid2_down);
	gw4 = graphicsWid2;
	graphicsWid2->setTransform(QTransform().translate(graphicsWid2->boundingRect().width() / 2, graphicsWid2->boundingRect().height() / 2)
		.rotate(-180, Qt::YAxis)
		.translate(-graphicsWid2->boundingRect().width() / 2, -graphicsWid2->boundingRect().height() / 2));
	graphicsWid1->setVisible(true);
	graphicsWid2->setVisible(false);
	//新建线型值闹钟
	QTimeLine *timeLine = new QTimeLine(1500, scene2);
	timeLine->setStartFrame(0);
	timeLine->setEndFrame(180);
	//每次值发生变化，旋转一定角度
	QObject::connect(timeLine, &QTimeLine::frameChanged, [timeLine, graphicsWid1, graphicsWid2](const int frame) {
		//对于登录窗体正常旋转
		graphicsWid1->setTransform(QTransform().translate(graphicsWid1->boundingRect().width() / 2, graphicsWid1->boundingRect().height() / 2)
			.rotate(frame, Qt::YAxis)
			.translate(-graphicsWid1->boundingRect().width() / 2, -graphicsWid1->boundingRect().height() / 2));
		//对于设置窗体由于开始旋转到了-180度，所以现在应该是-179,-176,-170....,0,这里应该是frame-180;也就是加上起点为-180度啦
		graphicsWid2->setTransform(QTransform().translate(graphicsWid2->boundingRect().width() / 2, graphicsWid2->boundingRect().height() / 2)
			.rotate(frame - 180, Qt::YAxis)
			.translate(-graphicsWid2->boundingRect().width() / 2, -graphicsWid2->boundingRect().height() / 2));
		if (frame >= 90 && frame < 180) {
			graphicsWid1->setVisible(false);
			graphicsWid2->setVisible(true);
		}
	});
	timeLine->start();
}

void CardGame::show_view3()
{
	ui.Lable_mask3->hide();
	QString path;
	if (round % 2 == 0) {//偶数轮
		if (cho2 || cho1) {
			path = QString(":/CardGame/0") + QString::number(RI[round].self) + QString(".jpg");
		}
		else {
			path = QString(":/CardGame/0") + QString::number(RI[round].other) + QString(".jpg");
		}
	}
	else {//奇数
		if (cho1 || cho2) {
			path = QString(":/CardGame/0") + QString::number(RI[round].other) + QString(".jpg");
		}
		else {
			path = QString(":/CardGame/0") + QString::number(RI[round].self) + QString(".jpg");
		}
	}
	cho3 = true;
	wid3_up = new QWidget;
	QPixmap *Pix1 = new QPixmap(":/CardGame/mask.jpg");
	QLabel *L1 = new QLabel(wid3_up);
	L1->resize(140, 200);
	Pix1->scaled(L1->size(), Qt::KeepAspectRatio);
	L1->setScaledContents(true);
	L1->setPixmap(*Pix1);

	wid3_down = new QWidget;
	QPixmap *Pix2 = new QPixmap(path);
	QLabel *L2 = new QLabel(wid3_down);
	L2->resize(140, 200);
	Pix2->scaled(L2->size(), Qt::KeepAspectRatio);
	L2->setScaledContents(true);
	L2->setPixmap(*Pix2);

	QGraphicsProxyWidget *graphicsWid1 = scene3->addWidget(wid3_up);
	gw5 = graphicsWid1;
	QGraphicsProxyWidget *graphicsWid2 = scene3->addWidget(wid3_down);
	gw6 = graphicsWid2;
	graphicsWid2->setTransform(QTransform().translate(graphicsWid2->boundingRect().width() / 2, graphicsWid2->boundingRect().height() / 2)
		.rotate(-180, Qt::YAxis)
		.translate(-graphicsWid2->boundingRect().width() / 2, -graphicsWid2->boundingRect().height() / 2));
	graphicsWid1->setVisible(true);
	graphicsWid2->setVisible(false);
	//新建线型值闹钟
	QTimeLine *timeLine = new QTimeLine(1500, scene3);
	timeLine->setStartFrame(0);
	timeLine->setEndFrame(180);
	//每次值发生变化，旋转一定角度
	QObject::connect(timeLine, &QTimeLine::frameChanged, [timeLine, graphicsWid1, graphicsWid2](const int frame) {
		//对于登录窗体正常旋转
		graphicsWid1->setTransform(QTransform().translate(graphicsWid1->boundingRect().width() / 2, graphicsWid1->boundingRect().height() / 2)
			.rotate(frame, Qt::YAxis)
			.translate(-graphicsWid1->boundingRect().width() / 2, -graphicsWid1->boundingRect().height() / 2));
		//对于设置窗体由于开始旋转到了-180度，所以现在应该是-179,-176,-170....,0,这里应该是frame-180;也就是加上起点为-180度啦
		graphicsWid2->setTransform(QTransform().translate(graphicsWid2->boundingRect().width() / 2, graphicsWid2->boundingRect().height() / 2)
			.rotate(frame - 180, Qt::YAxis)
			.translate(-graphicsWid2->boundingRect().width() / 2, -graphicsWid2->boundingRect().height() / 2));
		if (frame >= 90 && frame < 180) {
			graphicsWid1->setVisible(false);
			graphicsWid2->setVisible(true);
		}
	});
	timeLine->start();
}

void CardGame::show_buttons()
{
	ui.Bt1->show();
	ui.Bt2->show();
	ui.Bt3->show();
}

void CardGame::on_timer_timeout()
{
	timer->stop();
	if (RI[round].win) {
		QMessageBox::information(NULL, "INFO", "YOU WIN", QMessageBox::Yes);
		noise_select();
	}
	else {
		QMessageBox::information(NULL, "INFO", "YOU LOSE", QMessageBox::Yes);
		QTimer *ti = new QTimer(this);
		QObject::connect(ti, SIGNAL(timeout()), this, SLOT(punish()));
		QObject::connect(ti, SIGNAL(timeout()), ti, SLOT(stop()));
		ti->start(1000);
	}
	
	if (cho1) {
		gw1->setVisible(false);
		gw2->setVisible(false);
		cho1 = false;
	}
	if (cho2) {
		gw3->setVisible(false);
		gw4->setVisible(false);
		cho2 = false;
	}
	if (cho3) {
		gw5->setVisible(false);
		gw6->setVisible(false);
		cho3 = false;
	}
	
	round_end_flush();
	
}

void CardGame::on_Next_round_clicked()
{
	fstream f;
	f.open(".//record.txt", ios::out | ios::app);
	f << "ROUND : " << round << " ,PUNISH LEVEL: " << punish_number[round] << endl;
	f.close();
	round++;
	ui.label->setText("CARD GAME ROUND : " + QString::number(round));
	ui.punishtext_label->hide();
	ui.punishtitle_label->hide();
	ui.punish_label->hide();
	ui.givepunishtext_label->hide();
	if (round != 13) {
		if (round % 2 == 1)//先发
		{
			QTimer *inttime = new QTimer();
			srand(time(NULL));
			inttime->start(1000 + rand() % 1000);
			QObject::connect(inttime, SIGNAL(timeout()), this, SLOT(show_buttons()));
			QObject::connect(inttime, SIGNAL(timeout()), inttime, SLOT(stop()));
		}
		else {//后发
			othersshow();
		}
		ui.view1->show();
		ui.view2->show();
		ui.view3->show();
		ui.Lable_mask1->show();
		ui.Lable_mask2->show();
		ui.Lable_mask3->show();
		
	}
	ui.Next_round->hide();
	choose = false;
	if (round == 13) {
		ui.Bt1->hide();
		ui.Bt2->hide();
		ui.Bt3->hide();
		ui.info_label->show();
		ui.lineEdit->show();
		ui.continue_Btn->show();
	}
	if (round == 21) {
		QMessageBox::information(NULL, "THANKS", "YOU HAVE ALREQDY FINISH THE GAME, THANK YOU !", QMessageBox::Yes);
		this->close();
	}
}

void CardGame::showpunish()
{
	ui.punish_label->show();
	ui.A_score_label->setText(QString::number(scoreA));
}

void CardGame::on_confirm_btn_clicked()//施加惩罚
{

	if (ui.radioButton->isChecked()|| ui.radioButton_2->isChecked()|| ui.radioButton_3->isChecked()|| 
		ui.radioButton_4->isChecked()|| ui.radioButton_5->isChecked()|| ui.radioButton_6->isChecked()) {
		QTimer *ti = new QTimer();
		QObject::connect(ti, SIGNAL(timeout()), this, SLOT(show_nextround()));
		QObject::connect(ti, SIGNAL(timeout()), ti, SLOT(stop()));
		srand(time(NULL));
		int no = rand() % 2000 + 4000;
		ti->start(no);
		int dec = 0;
		
		if (ui.radioButton->isChecked()) {
			ui.punish_label->setText("1");
			dec = 1;
			ui.radioButton->setCheckable(false);
			ui.radioButton->setCheckable(true);
		}
		if (ui.radioButton_2->isChecked()) {
			ui.punish_label->setText("2");
			dec = 2;
			ui.radioButton_2->setCheckable(false);
			ui.radioButton_2->setCheckable(true);
		}
		if (ui.radioButton_3->isChecked()) {
			ui.punish_label->setText("3");
			dec = 3;
			ui.radioButton_3->setCheckable(false);
			ui.radioButton_3->setCheckable(true);
		}
		if (ui.radioButton_4->isChecked()) {
			ui.punish_label->setText("4");
			dec = 4;
			ui.radioButton_4->setCheckable(false);
			ui.radioButton_4->setCheckable(true);
		}
		if (ui.radioButton_5->isChecked()) {
			ui.punish_label->setText("5");
			dec = 5;
			ui.radioButton_5->setCheckable(false);
			ui.radioButton_5->setCheckable(true);
		}
		if (ui.radioButton_6->isChecked()) {
			ui.punish_label->setText("6");
			dec = 6;
			ui.radioButton_6->setCheckable(false);
			ui.radioButton_6->setCheckable(true);
		}
		scoreB -= dec;
		punish_number[round] = dec;
		ui.B_score_label->setText(QString::number(scoreB));
		ui.punish_label->setText(QString::number(dec));
		ui.punish_label->show();
		ui.confirm_btn->hide();
		ui.radioButton->hide();
		ui.radioButton_2->hide();
		ui.radioButton_3->hide();
		ui.radioButton_4->hide();
		ui.radioButton_5->hide();
		ui.radioButton_6->hide();
	}
	else {
		QMessageBox::information(NULL, "INFO", "Please select a punish score!");
		return;
	}

}

void CardGame::on_continue_Btn_clicked()
{
	QString pass;
	pass = ui.lineEdit->text();
	if (pass == QString::fromStdString("zhxuns")) {
		ui.continue_Btn->hide();
		ui.lineEdit->hide();
		ui.info_label->hide();
		ui.view1->show();
		ui.view2->show();
		ui.view3->show();
		ui.Lable_mask1->show();
		ui.Lable_mask2->show();
		ui.Lable_mask3->show();
		show_buttons();
	}
	else {
		QMessageBox::information(NULL, "INFO", "WRONG ANSWER !", QMessageBox::Yes);
	}
}

void CardGame::closeEvent(QCloseEvent * event)
{
}

void CardGame::round_end_flush()
{
	ui.Bt1->hide();
	ui.view1->hide();
	ui.Bt2->hide();
	ui.view2->hide();
	ui.Bt3->hide();
	ui.view3->hide();
	ui.Lable_mask1->hide();
	ui.Lable_mask2->hide();
	ui.Lable_mask3->hide();
}

void CardGame::noise_select()
{
	ui.radioButton->show();
	ui.radioButton_2->show();
	ui.radioButton_3->show();
	ui.radioButton_4->show();
	ui.radioButton_5->show();
	ui.radioButton_6->show();
	ui.givepunishtext_label->show();
	ui.punishtitle_label->show();
	ui.confirm_btn->show();
}

void CardGame::othersshow()
{
	interval = new QTimer(this);
	srand(time(NULL));
	int no = rand() % 2000 + 2000;
	interval->start(no);
	srand(time(NULL));
	int sele = rand() % 3 + 1;
	if (sele == 1) {
		cho2 = true;
		QObject::connect(interval, SIGNAL(timeout()), this, SLOT(show_view1()));
		cho2 = false;
	}
	if (sele == 2) {
		cho1 = true;
		QObject::connect(interval, SIGNAL(timeout()), this, SLOT(show_view2()));
		cho1 = false;
	}
	if (sele == 3) {
		cho2 = true;
		QObject::connect(interval, SIGNAL(timeout()), this, SLOT(show_view3()));
		cho2 = false;
	}
	QObject::connect(interval, SIGNAL(timeout()), interval, SLOT(stop()));
	QObject::connect(interval, SIGNAL(timeout()), this, SLOT(show_buttons()));
}

void CardGame::punish()
{
	QTimer *ti = new QTimer();
	QObject::connect(ti, SIGNAL(timeout()), this, SLOT(show_nextround()));
	QObject::connect(ti, SIGNAL(timeout()), ti, SLOT(stop()));
	srand(time(NULL));
	int no = rand() % 2000 + 4000;
	ti->start(no);
	int dec = 0;
	ui.punishtext_label->show();
	if (round == 1 || round == 2) {
		ui.punish_label->setText("3");
		dec = 3;
	}
	else{
		ui.punish_label->setText("6");
		dec = 6;
	}
	scoreA -= dec;
	QTimer *wa = new QTimer();
	srand(time(NULL));
	wa->start(2000 + rand() % 2000);
	QObject::connect(wa, SIGNAL(timeout()),this, SLOT(showpunish()));
	QObject::connect(wa, SIGNAL(timeout()), wa, SLOT(stop()));
	ui.punish_label->setText(QString::number(dec));
}
