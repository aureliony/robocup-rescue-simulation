static inline void sweep(int angle, int maxspd, int minspd) {
	// angle = 15;
	// minspd = 1;
	// maxspd = 4;
	(Compass/angle)%2==1 ? speed(minspd,maxspd) : speed(maxspd,minspd);
}
