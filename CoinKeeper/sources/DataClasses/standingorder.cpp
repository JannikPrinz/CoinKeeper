#include "DataClasses/standingorder.h"

#include "constants.h"

namespace DataClasses
{
    StandingOrder::StandingOrder(int32_t standingOrderId, int32_t accountId, int32_t labelId, Value const& value, std::string const& description,
        StandingOrderType type, QDate const& date, std::optional<int32_t> const& connectedAccountId)
        : StandingOrderId(standingOrderId), AccountId(accountId), LabelId(labelId), StandingOrderValue(value), Description(description), Type(type), Date(date), ConnectedAccountId(connectedAccountId)
    {
    }

    std::string StandingOrder::GetStringFromStandingOrderType(StandingOrderType type)
    {
        switch (type)
        {
        case StandingOrderType::EveryDay:
            return TEXT_STANDING_ORDER_EVERY_DAY;
            break;
        case StandingOrderType::EveryWeek:
            return TEXT_STANDING_ORDER_EVERY_WEEK;
            break;
        case StandingOrderType::EveryMonth:
            return TEXT_STANDING_ORDER_EVERY_MONTH;
            break;
        case StandingOrderType::EveryQuarter:
            return TEXT_STANDING_ORDER_EVERY_QUARTER;
            break;
        case StandingOrderType::Every4Months:
            return TEXT_STANDING_ORDER_EVERY_4_MONTHS;
            break;
        case StandingOrderType::EveryYear:
            return TEXT_STANDING_ORDER_EVERY_YEAR;
            break;
        default:
            return "";
            break;
        }
    }
}
