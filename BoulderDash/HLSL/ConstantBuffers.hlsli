cbuffer cbOnce : register(b0) {
	matrix VP;									// view*projection matrix
	float2 inverseScreenSize;					// inverse size of screen
	uint screenWidth;							// size of thread in X dim
	uint screenHeight;							// size of thread in Y dim
};
