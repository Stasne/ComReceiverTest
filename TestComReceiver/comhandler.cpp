#include "comhandler.h"

ComHandler::ComHandler(const QString &port,
					   QSerialPort::BaudRate br,
					   QSerialPort::DataBits dataBits,
					   QSerialPort::Parity parity,
					   QSerialPort::StopBits stopBits,
					   QSerialPort::FlowControl flowControl) :

	m_portName	(port),
	m_baudRate	(br),
	m_dataBits	(dataBits),
	m_parity	(parity),
	m_stopBits	(stopBits),
	m_flowControl(flowControl)
{


}

ComHandler::~ComHandler()
{
	m_inputPort.close();
}
void ComHandler::Start(const QString &port, QSerialPort::BaudRate br )
{
	m_baudRate = br;
	m_inputPort.setPortName	(port);
	m_inputPort.open(QIODevice::ReadOnly);
	if (!m_inputPort.isOpen())
	{
		throw (ERRCODE_COM_BUSY);
	}

	m_inputPort.setBaudRate	(m_baudRate);
	m_inputPort.setDataBits	(m_dataBits);
	m_inputPort.setParity	(m_parity);
	m_inputPort.setStopBits	(m_stopBits);
	m_inputPort.setFlowControl(m_flowControl);

	connect(&m_inputPort, SIGNAL(readyRead()), this, SLOT(ReadRawData()));
	connect(&m_inputPort, SIGNAL(readyRead()), this, SIGNAL(ping()));	// просто индикация живого порта
}
void ComHandler::SetMaxIncomeBuffer(quint32 maxSize)
{
	if(m_inputPort.isOpen())
	{
		m_inputPort.setReadBufferSize(maxSize);
	}

}

void ComHandler::ReadRawData()
{
	m_rawData = m_inputPort.readAll();
	emit NewRawDataReady(m_rawData);
}
