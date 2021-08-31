#include <QDebug>
#include <QKeySequence>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	connect(ui->registrate, &QPushButton::clicked, this, [this](){
		mGlobalShortcut.setShortcut(ui->key->keySequence());
	});

	connect(ui->unregistrate, &QPushButton::clicked, this, [this](){
		mGlobalShortcut.unsetShortcut();
	});

	connect(&mGlobalShortcut, &QGlobalShortcut::activated, this, [this](){
		ui->counter->setValue(ui->counter->value() + 1);
	});
}

MainWindow::~MainWindow()
{
	delete ui;
	mGlobalShortcut.unsetShortcut();
}
