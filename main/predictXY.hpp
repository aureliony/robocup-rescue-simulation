#pragma once

class Vector2 {
public:

	double x,y;
	bool reverse;

	void setWheels(int WL, int WR)
	{
		double coeff=215.0;
		reverse = WL<0 && WR<0;
		x = 0;
		y = abs(WL + WR)/coeff;
	}

	pair<double,double> rotate(double prevX, double prevY, double prevAngle, double currAngle, int numIT)
	{
		//convert degrees to radians
		currAngle*=0.0174532925199432958;
		prevAngle*=0.0174532925199432958;

		double rate_of_rotation = (currAngle - prevAngle)/numIT;
		pair<double,double> result = make_pair(prevX, prevY);

		for (int i=0; i<numIT; i++)
		{
			currAngle = prevAngle + rate_of_rotation*i;
			double sin_ = sin(currAngle);
			double cos_ = cos(currAngle);

			double tx = -sin_ * y;
			double ty = cos_ * y;

			if (!reverse)
			{
				result.first += tx;
				result.second += ty;
			}
			else
			{
				result.first -= tx;
				result.second -= ty;
			}

		}
		return result;
	}
} ;