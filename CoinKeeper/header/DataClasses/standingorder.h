#pragma once

#include <cstdint>
#include <optional>
#include <qdatetime.h>

#include "DataClasses/value.h"

namespace DataClasses
{
	class StandingOrder
	{
	public:
		static const int32_t NUMBER_OF_STANDING_ORDER_TYPES = 6;

		enum class StandingOrderType
		{
			EveryDay = 0, EveryWeek = 1, EveryMonth = 2, EveryQuarter = 3, Every4Months = 4, EveryYear = 5
		};

	public:
		StandingOrder(int32_t standingOrderId, int32_t accountId, int32_t labelId, Value const& value, std::string const& description,
			StandingOrderType type, QDate const& date, std::optional<int32_t> const& connectedAccountId);
		~StandingOrder() = default;

	public:
		static std::string GetStringFromStandingOrderType(StandingOrderType type);

	public:
		int32_t StandingOrderId;
		int32_t AccountId;
		int32_t LabelId;
		Value StandingOrderValue;
		std::string Description;
		StandingOrderType Type;
		QDate Date;
		std::optional<int32_t> ConnectedAccountId;
	};
}
