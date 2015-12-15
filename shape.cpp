#include <cmath>
#include <valarray>
#include <cstdlib>
#include <iostream>
#include <unistd.h>

class Triangle{//make polygon later
	public:
		double positions[3][2];
		double center_point[2];
		int screensize;
		Triangle(double length, double screenwidth){
			//positions

/*			positions[0][0] = screenwidth/2;				//x
			positions[0][1] = (screenwidth - length*std::sqrt(3)/2)/2;	//y

			positions[1][0] = (screenwidth - length)/2;
			positions[1][1] = (screenwidth - length*std::sqrt(3)/2)/2
						+ length*std::sqrt(3)/2;

			positions[2][0] = positions[1][0]+length;
			positions[2][1] = positions[1][1];
*/
			positions[0][0] = 0;	//x
			positions[0][1] = 0;	//y

			positions[1][0] = 0;
			positions[1][1] = screenwidth-2;

			positions[2][0] = screenwidth/2;
			positions[2][1] = screenwidth-2;

			screensize = screenwidth;
		};
		void turn(double);
		void render();
};

class Polygon{

};

double* rotate(double xpoint, double ypoint, double xcenter,double ycenter, double rads){
	//idea here is find the vector from center of rotation
	//and then change that vector's angle to theta + degree
//	double angle = atan((ypoint-ycenter)/(xpoint-xcenter));
	double angle = atan((xpoint-xcenter)/(ypoint-ycenter));
	double distance = std::sqrt(pow(xcenter-xpoint,2)+pow(ycenter-ypoint,2));
	double pos[2];
	std::cout<<angle+rads<<"\n";
	pos[0] = sin(angle-rads)*distance+ycenter;
	pos[1] = cos(angle-rads)*distance+xcenter;
	return pos;
}

void Triangle::turn(double angle){
	double *a;
	for(int i=0;i<3;i++){
		a = rotate(positions[i][0],positions[i][1],screensize/2,screensize/2,angle);
		positions[i][0] = *a;
		positions[i][1] = *(a+1);
	}
}

bool intersect(double x1, double x2, double y1, double y2, int sx, int sy){
		//prefix s means square; s_1 is top left, s_2 is bottom right
	int swap;
	if(x1>x2){//drops a lot of conditionals in the later if statements
		swap = x1;
		x1 = x2;
		x2 = swap;

		swap = y1;
		y1 = y2;
		y2 = swap;
	}
	if(x1<=sx && x2>=sx){ //checks if x values intersect square
		double slope = ((double)(y1-y2))/((double)(x1-x2));//TODO fix divide by 0
		int leftintersect = y1 + slope*(sx-x1);
		int rightintersect = y1 + slope*(sx+1-x2);
		if(leftintersect>=sy){
			if(leftintersect<=sy+1){
				return true;
			}
		}
	}
	return false;
}

void Triangle::render(){
	//creation

	//P: How do we get this imaginary line to convert into an ascii line
	//G: With intersections
	//P: That's pretty vague, how?
	//G: Idfk
	//
	//P: Maybe iterate through and see if it touches the
	//  basically square that each character represents
	//G: yeah yeah yeah
	//P: But how do we check if it intersects?
	//G: Hmm... I've got it! we simulate its sides and do a line intersect
	//  to see if it intersects with any of those
	//P: No, that's probably not the most efficient, we can just see if
	//  the min x is less or max x is more and test for the two y values at those:
	//  left and right
	//G: Brilliant as always, P.
	//P: Thank you very much
	bool sect;
	std::system("clear");
	for(int i=0;i<screensize;i++){
		for(int j=0;j<screensize;j++){
			sect = false;
			for(int k=0;k<3;k++){
				if(intersect(
					positions[k][0],
					positions[(k+1)%3][0],
					positions[k][1],
					positions[(k+1)%3][1],
					j,
					i
				)){
					sect = true;
				}
			}
			if(sect){
				std::cout<<"--";
			}else{
				std::cout<<" ";
			}
		}
		std::cout<<"\n";
	}
}


class Line{
	public:
		int p1[2];
		int p2[2];
		Line(int _x, int _y, int _x_, int _y_){
			p1[0] = _x;
			p1[1] = _y;
			p2[0] = _x_;
			p2[1] = _y_;
		};
		void render(int);
};

void Line::render(int screensize){
	bool sect = false;
	std::system("clear");
	for(int i=0;i<screensize;i++){
		for(int j=0;j<screensize;j++){
			sect = false;
			if(intersect(
				p1[0],
				p2[0],
				p1[1],
				p2[1],
				i,
				j
			)){
				sect = true;
			}
			if(sect){
				std::cout<<"--";
			}else{
				std::cout<<"  ";
			}
		}
		std::cout<<"\n";
	}
}


int main(){
	Triangle trig(40, 40);
	for(int i=0;i<8;i++){
		trig.render();
		trig.turn(3.1415/8);
		usleep(1000000);
	}
	/*Line l(20,20,10,0);
	l.render(40);
	double* a;
	for(int i=0;i<5;i++){
		a = rotate(l.p2[0],l.p2[1],l.p1[0],l.p1[1],3.1415/5);
		l.p2[0] = *a;
		l.p2[1] = *(a+1);
		l.render(40);
		usleep(1000000);
	}*/
	return 0;
}