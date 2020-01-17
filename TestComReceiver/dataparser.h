#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <QObject>
#include <QByteArray>
#include <stdint.h>
#define PREFIX 0x40
#define PREFIX_BYTES 1
struct IncomeParcel
{
	float x;
	float y;
	float z;
	float w;
};

class DataParser : public QObject
{
	Q_OBJECT
public:
	explicit DataParser(QObject *parent = nullptr);
private:
	IncomeParcel lastPacket;
signals:
	void DataWasChanged(IncomeParcel);

public slots:
	void RawDataParser(QByteArray income);
};

#endif // DATAPARSER_H
