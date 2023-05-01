#include "Position.hpp"

Position::Position(int xx, int yy): x(xx), y(yy){
	/*
	Class constructor 'Position' with two integer coordinates.
	*/
	if((xx < 0 || yy < 0) && (xx != -1 || yy != -1)) throw string("Invalid coordinate(s) : negative.");
}

Position::Position(const Position &p, int dx, int dy){
	/*
	Class constructor 'Position' with a 'Position' and two shifts (integers).
	*/
	if(p.x + dx < 0 || p.y + dy < 0) throw string("Invalid coordinate(s) : negative.");
	x = p.x + dx;
	y = p.y + dy;
}

Position::Position(string str){
	/*
	Class constructor 'Position' with a string.
	*/
	if(str == "none"){
		x = -1;
		y = -1;
	}
	else{
		// Capitalize the string
		string v;
		string s;
		char c;
		for(int i = 0; i < str.length() ; i ++){
			c = str[i];
			c = toupper(c);
			v = c;
			s += v;
		}
		if(s.size() <= 1) throw string("Invalid coordinates : length - too short.");
		if(s[0] < 65 || s[0] > 90) throw string("Invalid coordinates : format - no letters at the beginning.");

		x = 0;
		y = 0;
		string s_x;
		string s_y;

		int i = 0;
		while(s[i] >= 'A' && s[i] <= 'Z'){
			i++;
		}

		s_x = s.substr(0, i);
		int len = s_x.length() - 1;
		for(int l = 0; l <= s_x.length() - 1; l++){
			x += pow(26, len) * (s_x[l] - 'A');
			len -= 1;
		}

		int j = i;
		while(s[j] >= '0' && s[j] <= '9'){
			j++;
		}

		s_y = s.substr(i, j - i);

		if(j != s.length()) throw string("Invalid coordinates : format - crossed letters and numbers.");

		y = stoi(s_y);
	}
}


string Position::toString() const{
	/*
	Method to convert 'Position' object into 'string'.
	*/
	if(x == -1 && y == -1) return "none";
	int p = 0;
	while(pow(26,p) <= x + 1){
		p += 1;
	}
	int k;
	int residu = x + 1;
	string s_1;
	string s;
	char l;
	int poww;
	/*if(p == 0){
		l = residu + 'A';
		s_1 = l;
		s += s_1;
	}*/
	/*else{*/
	for(int i = p - 1; i >= 0; i--){
		poww = pow(26,i);
		k = residu / poww;
		residu = residu - k * poww;
		l = k + 'A' - 1;
		s_1 = l;
		s += s_1;
	}
	return s + to_string(y + 1);
}

int Position::get_x() const{
	/*
	Getter method to coordinate 'x' attribute.
	*/
	return x;
}

int Position::get_y() const{
	/*
	Getter method to coordinate 'y' attribute.
	*/
	return y;
}

int Position::get_distX(const Position &pos) const{
	/*
	Method to get the (absolute) distance (on the 'x'-axis) between two positions.
	*/
	return abs(get_x() - pos.get_x());
}

int Position::get_distY(const Position &pos) const{
	/*
	Method to get the (absolute) distance (on the 'y'-axis) between two positions.
	*/
	return abs(get_y() - pos.get_y());
}

bool Position::operator==(const Position &p) const{
	/*
	Method to test the equality. Returns 'true' if the current 'Position' is equal to the other one.
	*/
	return (x == p.get_x()) && (y == p.get_y());
}

bool Position::operator!=(const Position &p) const{
	/*
	Method to test the non-equality. Returns 'true' if the current 'Position' is different from the other one.
	*/
	return !(*this == p);
}

bool Position::sameDiagonal(const Position &pos) const{
	/*
	Method to check if two positions are on the same diagonal. Returns 'true' if there are.
	*/
	return get_distX(pos) == get_distY(pos);
}
