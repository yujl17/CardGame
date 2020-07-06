#include "CardGame.h"
#include <QtWidgets/QApplication>



int main(int argc, char *argv[])
{

	QApplication a(argc, argv);
	srand(time(NULL));
	int conect_time = rand() % 2000 + 4000;
	CardGame *w = new CardGame(NULL, conect_time);
	QProgressDialog *progressDialog;
	progressDialog = new QProgressDialog();
	progressDialog->setFixedSize(800, 600);
	progressDialog->setWindowIconText("CardGame");
	progressDialog->setLabelText("connecting...");
	
	//progressDialog->setRange(0, 0);
	progressDialog->setModal(true);
	progressDialog->setMaximum(0);
	progressDialog->setMinimum(0);
	progressDialog->show();
	QTimer *conect_timer = new QTimer();
	conect_timer->start(conect_time);
	QObject::connect(conect_timer, SIGNAL(timeout()), progressDialog, SLOT(close()));
	QObject::connect(conect_timer, SIGNAL(timeout()), w, SLOT(showFullScreen()));

	return a.exec();

}
