#pragma once

#include <cstdint>
#include <optional>
#include <qdatetime.h>
#include <string>

#include "DataClasses/value.h"

namespace DataClasses
{
	class Transaction
	{
	public:
		Transaction(int32_t transactionId, std::string const& description, Value const& value, QDate const& date,
			int32_t accountId, int32_t labelId, std::optional<int32_t> connectedTransactionId = std::nullopt);
		~Transaction() = default;

	public:
		int32_t TransactionId;
		std::string Description;
		Value TransactionValue;
		QDate Date;
		int32_t AccountId;
		int32_t LabelId;
		std::optional<int32_t> ConnectedTransactionId;
	};
}
