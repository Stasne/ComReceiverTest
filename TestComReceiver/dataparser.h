#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <QObject>
#include <QByteArray>
#include <QVector4D>

#define PREFIX 0x40
#define PREFIX_BYTES 1

class DataParser : public QObject
{
	Q_OBJECT
public:
	explicit DataParser(QObject *parent = nullptr);
private:
	QVector4D lastVector;
signals:
	void DataWasChanged(QVector4D);

public slots:
	void RawDataParser(QByteArray income);
};

#endif // DATAPARSER_H
