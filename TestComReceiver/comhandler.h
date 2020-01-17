#ifndef COMHANDLER_H
#define COMHANDLER_H

#include <QObject>
#include <QByteArray>
#include <QSerialPort>

#define ERRCODE_COM_BUSY 211

class ComHandler : public QObject {
	Q_OBJECT
public:
	ComHandler(const QString &port = QString("COM2"),
			QSerialPort::BaudRate br = QSerialPort::Baud115200,
			QSerialPort::DataBits dataBits = QSerialPort::Data8,
			QSerialPort::Parity parity = QSerialPort::NoParity,
			QSerialPort::StopBits stopBits = QSerialPort::OneStop,
			QSerialPort::FlowControl flowControl = QSerialPort::NoFlowControl );
	~ComHandler();
	void SetMaxIncomeBuffer(quint32 maxSize);
private:
	QByteArray m_rawData;
	QSerialPort m_inputPort;
	QString m_portName;
	QSerialPort::BaudRate	m_baudRate;
	QSerialPort::DataBits	m_dataBits;
	QSerialPort::Parity		m_parity;
	QSerialPort::StopBits	m_stopBits;
	QSerialPort::FlowControl m_flowControl;
signals:
	void NewRawDataReady(QByteArray dataToSend);
	void ping();
public slots:
	void Start(const QString &port= QString("COM2"), QSerialPort::BaudRate br = QSerialPort::Baud115200);
private slots:
	void ReadRawData();
};

#endif // COMHANDLER_H
