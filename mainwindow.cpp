#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QThread>
#include <QThreadPool>
#include <QTimer>
#include "wastetimetask.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
		, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	stopped = false;
	connect(ui->pushButton1, SIGNAL(clicked()), this, SLOT(clicked()));
	connect(ui->pushButton2, SIGNAL(clicked()), this, SLOT(clicked()));
	connect(ui->pushButton3, SIGNAL(clicked()), this, SLOT(clicked()));
}

void MainWindow::clicked() {
	QObject *sender = QObject::sender();
	if(sender->objectName() == "pushButton1") {
		QPushButton *pb = static_cast<QPushButton*>(sender);
		pb->setEnabled(false);
		ui->pushButton3->setEnabled(true);
        WasteTimeTask *t = new WasteTimeTask(this, 1, &stopped, 2, 15);
        QThreadPool::globalInstance()->start(t);
	} else if(sender->objectName() == "pushButton2") {
		QPushButton *pb = static_cast<QPushButton*>(sender);
		pb->setEnabled(false);
		ui->pushButton3->setEnabled(true);
        WasteTimeTask *t = new WasteTimeTask(this, 2, &stopped, 1, 15);
        QThreadPool::globalInstance()->start(t);
	} else {
		stopped = true;
		ui->pushButton3->setEnabled(false);
		is_done();
        ui->plainTextEdit->clear();
    }
}

void MainWindow::is_done() {
	if(QThreadPool::globalInstance()->activeThreadCount()) {
		QTimer::singleShot(100, this, SLOT(is_done()));
	} else {
		ui->pushButton1->setEnabled(true);
		ui->pushButton2->setEnabled(true);
		stopped = false;
	}
}

void MainWindow::updateProgress(const QString &message) {
   ui->plainTextEdit->appendPlainText(message);
}

void MainWindow::closeEvent(QCloseEvent *event) {
	stopped = true;
	if(QThreadPool::globalInstance()->activeThreadCount()) {
		QThreadPool::globalInstance()->waitForDone();
	}

	event->accept();
}

MainWindow::~MainWindow()
{
	delete ui;
}

