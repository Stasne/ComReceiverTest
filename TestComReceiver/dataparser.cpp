#include "dataparser.h"

DataParser::DataParser(QObject *parent) : QObject(parent)
{
}

void DataParser::RawDataParser(QByteArray income)
{
	uint16_t startIndex = income.indexOf(PREFIX) + PREFIX_BYTES;
	income = income.mid(startIndex, sizeof(IncomeParcel));
	lastPacket = *(reinterpret_cast<IncomeParcel*>(income.data()));
	emit DataWasChanged(lastPacket);
}
