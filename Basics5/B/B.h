//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef B_H
#define B_H

class BankHoliday
{
public:
	BankHoliday();
	virtual ~BankHoliday() = default;
	virtual void init();
};

class StPatricks : public BankHoliday
{
public:
	StPatricks();
	const char *GetDay();

private:
	virtual void init() override;
	const char *day;
};

#endif

// End of File