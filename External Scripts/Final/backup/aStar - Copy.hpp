#ifndef ASTAR_HPP
#define ASTAR_HPP

#include "rp_heap.hpp"

int came_from[V];
double cost_so_far[V];
bool visited[V] = {false};

inline int con(int x,int y){return y * WIDTH + x;}
inline int conX(int d){return d % WIDTH;}
inline int conY(int d){return d / WIDTH;}
inline int conv(int x, int y){
	x = max(0, min(359, x));
	y = max(0, min(269, y));
	x = min((int)round(x/(360.0/WIDTH)),WIDTH-1);
	y = min((int)round(y/(270.0/HEIGHT)),HEIGHT-1);
	return y * WIDTH + x;
}
inline int convX(int d){return (d % WIDTH) * (360/WIDTH);}
inline int convY(int d){return (d / WIDTH) * (270/HEIGHT);}
inline int convFinalX(int d){return convX(d);}
inline int convFinalY(int d){return convY(d);}

#define sqrt2 1.414213562373095
/*w2map values
	0 - green
	1 - white
	2 - grey
	3 - black
*/
static const double rDist[]={1.0,5.0,25.0,1000.0};
static const int angles[]={-1,135,180,225,90,270,45,0,315};

inline int convPosToNode(int from, int to)
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

inline int convToRelPos(int from, int to)
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

inline int getCompassRelPos(void)
{
	if(Compass<=22.5||Compass>=337.5) return 7;
	for(int i=1;i<=8;i++)
	{
		if(i==7) continue;
		else if(abs(Compass-angles[i])<=22.5) return i;
	}
	assert(0);
	return 0;
}

inline double costBetween(int currDirection, int from, int to, int relPos)
{
	int ang=0;double dirPenalty=1.0;

	//calculate the angleDiff
	ang = abs(angles[currDirection]-angles[relPos]);
	ang = min(ang, 360-ang);
	dirPenalty = 1.0 + (ang/360.0);

	double lineDist = (relPos==1||relPos==3||relPos==6||relPos==8) ? sqrt2 : 1.0;
	// printf("%.2f, %.2f\n", lineDist,dirPenalty);

	return lineDist * dirPenalty * (0.5*rDist[w2map[from]] + 0.5*rDist[w2map[to]]);
}

inline double getHcost(int from, int goal)
{
	// return 0.0;
	double D = rDist[0], D2 = sqrt2 * rDist[0];
	int dx = abs(conX(from)-conX(goal)), dy = abs(conY(from)-conY(goal));
    return D * (dx + dy) + (D2 - 2.0 * D) * min(dx, dy);
}


double aStar(int start, int goal)
{
	int numIterations=0;
	int currDirection=-1;

	for(int i=0; i<V; i++)
	{
		came_from[i] = -1;
		visited[i] = false;
		cost_so_far[i] = INF;
	}
	cost_so_far[start] = 0.0;
	
	priority_queue< pair<double,int>, vector< pair<double,int> >, greater< pair<double,int> > > openList;
	openList.push(make_pair(0.0, start));
 	
	while (!openList.empty())
	{
		int curr = openList.top().second;
		numIterations++;
		if(curr == goal) break;
		openList.pop();
		if(visited[curr]) continue;
		visited[curr] = true;

		if(came_from[curr]!=-1) currDirection=convToRelPos(came_from[curr], curr);
		else currDirection=getCompassRelPos();

		for(int i=1; i<=8; i++)
		{
			numIterations++;
			if(conX(curr)==0&&(i==1||i==4||i==6)) continue;
			if(conX(curr)==WIDTH-1&&(i==3||i==5||i==8)) continue;
			if(conY(curr)==0&&(i==1||i==2||i==3)) continue;
			if(conY(curr)==HEIGHT-1&&(i==6||i==7||i==8)) continue;

			int next=convPosToNode(curr,i);

			//discard if out of w2map
			if(conX(next)<0||conX(next)>=WIDTH||conY(next)<0||conY(next)>=HEIGHT) continue;
			
			//discard if already visited
			if(visited[next]) continue;

			double new_cost = cost_so_far[curr] + costBetween(currDirection, curr, next, i);

			if(new_cost < cost_so_far[next])
			{
				cost_so_far[next] = new_cost;
				openList.push(make_pair(new_cost + getHcost(next, goal), next));
				came_from[next] = curr;
			}
		}
	}

	path.clear();
	path.push_front(goal);
	int i = goal;
	while(i!=start)
	{
		path.push_front(came_from[i]);
		i = came_from[i];
	}
	
	// for(int i=0;i<V;i++)
	// {
	// 	if(visited[i])
	// 		printf("(%d,%d)\n",conX(i),conY(i));
	// }

	// printf("numIterations = %d\n", numIterations);

	return cost_so_far[goal];
}

#endif //ASTAR_HPP