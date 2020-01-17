#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "comhandler.h"
#include "dataparser.h"

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
	ComHandler m_comReceiver;
	DataParser m_dataParser;
	QMessageBox error;
signals:
	void startComListener();
private slots:
	void ConfirmComSettings();
public slots:
	void RadioBlink();
	void UpdateView(IncomeParcel);
};

#endif // MAINWINDOW_H
