#include "dataparser.h"

DataParser::DataParser(QObject *parent) : QObject(parent)
{
}

void DataParser::RawDataParser(QByteArray income)
{
	int startIndex = income.indexOf(PREFIX) + PREFIX_BYTES;
	income = income.mid(startIndex, sizeof(QVector4D));
	lastVector = *(reinterpret_cast<QVector4D*>(income.data()));
	emit DataWasChanged(lastVector);
}
