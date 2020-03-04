#include "DataClasses/transaction.h"

namespace DataClasses
{
	Transaction::Transaction(int32_t transactionId, std::string const& description, Value const& value, QDate const& date,
		int32_t accountId, int32_t labelId, std::optional<int32_t> connectedTransactionId)
		: TransactionId(transactionId), Description(description), TransactionValue(value), Date(date), AccountId(accountId), LabelId(labelId), ConnectedTransactionId(connectedTransactionId)
	{
	}
}
