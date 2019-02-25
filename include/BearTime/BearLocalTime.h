#pragma once
namespace BearCore
{
	class BEARTOOL_API BearLocalTime
	{
	public:
		static int32 GetDateYear();
		static int32 GetDateMonth();
		static int32 GetDateDay();
		static int32 GetDateHour();
		static int32 GetDateMinute();
		static int32 GetDateSecond();
		static void GetDateAndTime(BearStringBase& data);
		static void GetDate(BearStringBase& data);
		static int32 GetDayWeek(int32 day,int32 month,int32 year);
		static int32 GetDayWeek();
	};
}
