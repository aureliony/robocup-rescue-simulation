#pragma once

static int parent[V];
static double gscores[V];
static bool closedList[V] = {false};

static inline int con(int x,int y){return y * WIDTH + x;}
static inline int conX(int d){return d % WIDTH;}
static inline int conY(int d){return d / WIDTH;}
static inline int conv(int x, int y){
	x = max(0, min(359, x));
	y = max(0, min(269, y));
	x = min((int)round(x*(WIDTH/360.0)), WIDTH-1);
	y = min((int)round(y*(HEIGHT/270.0)), HEIGHT-1);
	return round(y * (HEIGHT/270.0) * WIDTH + x * (WIDTH/360.0));
}
static inline int convX(int d){return round((d % WIDTH) * (360.0/WIDTH));}
static inline int convY(int d){return round((d / WIDTH) * (270.0/HEIGHT));}
static inline int convFinalX(int d){return convX(d);}
static inline int convFinalY(int d){return convY(d);}

#define sqrt2 1.414213562373095
/*w2map values
	0 - green
	1 - white
	2 - grey
	3 - black
*/
static int rDist[] = {1, 3, 25, 1000, 1000};

static inline int convPosToNode(int from, int to)
{
	switch(to)
	{
		case 1: return from-WIDTH-1;
		case 2: return from-WIDTH;
		case 3: return from-WIDTH+1;
		case 4: return from-1;
		case 5: return from+1;
		case 6: return from+WIDTH-1;
		case 7: return from+WIDTH;
		case 8: return from+WIDTH+1;
	}
	assert(0);
	return 0;
}

static inline int convToRelPos(int from, int to)
{
	int x = conX(from) - conX(to);
	int y = conY(from) - conY(to);
	if(x==-1&&y==1)  return 1;
	if(x==0&&y==1)   return 2;
	if(x==1&&y==1)   return 3;
	if(x==-1&&y==0)  return 4;
	if(x==1&&y==0)   return 5;
	if(x==-1&&y==-1) return 6;
	if(x==0&&y==-1)  return 7;
	if(x==1&&y==-1)  return 8;
	assert(0);
	return 0;
}

static inline double getCcost(int from, int to, int relPos)
{
	double lineDist = (relPos==1||relPos==3||relPos==6||relPos==8) ? sqrt2 : 1;
	return lineDist * 0.5 * (rDist[w2map[from]] + rDist[w2map[to]]);
}

static inline double getHcost(int from, int goal)
{
	// return 0.0;
	double D = rDist[0], D2 = sqrt2 * rDist[0];
	int dx = abs(conX(from) - conX(goal));
	int dy = abs(conY(from) - conY(goal));
    return D * (dx + dy) + (D2 - 2 * D) * min(dx, dy);
}


static double aStar(int start, int goal)
{
	w2map = LoadedObjects>0 ? w2mapWithTrap : w2mapNoTrap;
	for(int i=0; i<V; i++)
	{
		parent[i] = -1;
		closedList[i] = false;
		gscores[i] = INF;
	}
	gscores[start] = 0;
	parent[start] = start;

	priority_queue<pair<double,int>, vector<pair<double,int>>, greater<pair<double,int>>> openList;
	openList.push(make_pair(getHcost(start, goal), start));

	while (!openList.empty())
	{
		int curr = openList.top().second;
		openList.pop();
		if(curr == goal) break;
		if(closedList[curr]) continue;

		closedList[curr] = true;

		for(int i=1; i<=8; i++)
		{
			if(conX(curr)==0&&(i==1||i==4||i==6)) continue;
			if(conX(curr)==WIDTH-1&&(i==3||i==5||i==8)) continue;
			if(conY(curr)==0&&(i==1||i==2||i==3)) continue;
			if(conY(curr)==HEIGHT-1&&(i==6||i==7||i==8)) continue;

			int next=convPosToNode(curr,i);

			//discard if out of w2map
			if(conX(next)<0||conX(next)>=WIDTH||conY(next)<0||conY(next)>=HEIGHT) continue;

			//discard if already closedList
			if(!closedList[next])
			{
				//update vertex
				double oldgscore = gscores[next];
				//computecost
				double newgscore = gscores[curr] + getCcost(curr, next, i);
				if(newgscore < oldgscore)
				{
					parent[next] = curr;
					gscores[next] = newgscore;
				}

				//continue updatingvertex
				if(gscores[next] < oldgscore)
				{
					openList.push(make_pair(gscores[next] + getHcost(curr, next), next));
				}
			}
		}
	}

	path.clear();
	path.push_front(goal);
	int i = goal;
	while(i != start)
	{
		path.push_front(parent[i]);
		i = parent[i];
	}
	
	// for(int i=0;i<V;i++)
	// {
	// 	if(closedList[i])
	// 		printf("(%d,%d)\n",conX(i),conY(i));
	// }

	return gscores[goal];
}