//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef PROXY_H
#define PROXY_H

// Modify This File

class Vect2D
{
public:
	Vect2D(const Vect2D &tmp);
	Vect2D &operator =( const Vect2D &tmp);
	Vect2D();
	~Vect2D();

	Vect2D(const float inX, const float inY);

	void setX(const float inX);
	void setY(const float inY);
	void set(const float inX, const float inY);

	float getX() const;
	float getY() const;

	//-----------------------------------------------
	// Rules   this function cannot be inlined 
	//         or implemented directly
	//-----------------------------------------------
	//  Vect2D operator + (const Vect2D &tmp) const;
	//-----------------------------------------------

private:
	float x;
	float y;

	//-----------------------------------------------
	// Add friends here... if you want (hint)
	//-----------------------------------------------
	friend struct VaddV;
	friend struct VaddVaddV;
	friend struct VaddVaddVaddV;
	friend struct VaddVaddVaddVaddV;
};


struct VaddV
{
	const Vect2D& v1;
	const Vect2D& v2;

	VaddV(const Vect2D& t1, const Vect2D& t2)
		: v1(t1), v2(t2)
	{
	};

	operator Vect2D()
	{
		return Vect2D(v1.x + v2.x,
			v1.y + v2.y);
	}
};

inline VaddV operator + (const Vect2D& t1, const Vect2D& t2)
{
	return VaddV(t1, t2);
}


struct VaddVaddV
{
	const Vect2D& v1;
	const Vect2D& v2;
	const Vect2D& v3;

	VaddVaddV(const VaddV& t1, const Vect2D& t2)
		: v1(t1.v1), v2(t1.v2), v3(t2)
	{
	};

	operator Vect2D()
	{
		return Vect2D(v1.x + v2.x + v3.x,
			v1.y + v2.y + v3.y);
	}
};

inline VaddVaddV operator + (const VaddV& t1, const Vect2D& t2)
{
	return VaddVaddV(t1, t2);
}


struct VaddVaddVaddV
{
	const Vect2D& v1;
	const Vect2D& v2;
	const Vect2D& v3;
	const Vect2D& v4;

	VaddVaddVaddV(const VaddVaddV& t1, const Vect2D& t2)
		: v1(t1.v1), v2(t1.v2), v3(t1.v3), v4(t2)
	{
	};

	operator Vect2D()
	{
		return Vect2D(v1.x + v2.x + v3.x + v4.x,
			v1.y + v2.y + v3.y + v4.y);
	}
};

inline VaddVaddVaddV operator + (const VaddVaddV& t1, const Vect2D& t2)
{
	return VaddVaddVaddV(t1, t2);
}


struct VaddVaddVaddVaddV
{
	const Vect2D& v1;
	const Vect2D& v2;
	const Vect2D& v3;
	const Vect2D& v4;
	const Vect2D& v5;

	VaddVaddVaddVaddV(const VaddVaddVaddV& t1, const Vect2D& t2)
		: v1(t1.v1), v2(t1.v2), v3(t1.v3), v4(t1.v4), v5(t2)
	{
	};

	operator Vect2D()
	{
		return Vect2D(v1.x + v2.x + v3.x + v4.x + v5.x,
			v1.y + v2.y + v3.y + v4.y + v5.y);
	}
};

inline VaddVaddVaddVaddV operator + (const VaddVaddVaddV& t1, const Vect2D& t2)
{
	return VaddVaddVaddVaddV(t1, t2);
}


#endif

// ---  End of File ---------------