#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStringList>


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->pushButtonOkSerial, SIGNAL(pressed()), this, SLOT(ConfirmComSettings()));
	QStringList comPorts;
	comPorts << "COM1" << "COM2" << "COM6" << "COM8";
	ui->comboBoxCom->addItems(comPorts);

	QStringList baudRates;
	baudRates << "9600" << "115200";
	ui->comboBoxBaud->addItems(baudRates);
	ui->comboBoxBaud->setCurrentIndex(1);

	connect(&m_comReceiver, SIGNAL(ping()), this, SLOT(RadioBlink()));

	connect(&m_comReceiver, SIGNAL(NewRawDataReady(QByteArray)), &m_dataParser, SLOT(RawDataParser(QByteArray)));
	connect(&m_dataParser, SIGNAL(DataWasChanged(QVector4D)), this, SLOT(UpdateView(QVector4D)));
}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::ConfirmComSettings()
{
	try
	{
		m_comReceiver.Start(ui->comboBoxCom->currentText());
		//m_comReceiver.SetIncomeMaxBuffer(sizeof(IncomeParcel));
		ui->pushButtonOkSerial->setEnabled(false);
		ui->comboBoxBaud->setEnabled(false);
		ui->comboBoxCom->setEnabled(false);
	}
	catch (...)
	{
		error.setText("Cannot connect to this port.");
		error.show();
	}

}

void MainWindow::RadioBlink()
{
	ui->radioButton->toggle();
}
void MainWindow::UpdateView(QVector4D income)
{
	ui->lineEdit_W->setText(QString::number(income.w()));
	ui->lineEdit_X->setText(QString::number(income.x()));
	ui->lineEdit_Y->setText(QString::number(income.y()));
	ui->lineEdit_Z->setText(QString::number(income.z()));
}

