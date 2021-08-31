
#pragma once

#include <QMainWindow>
#include "qglobalshortcut.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindow *ui;
	QGlobalShortcut mGlobalShortcut;
};
