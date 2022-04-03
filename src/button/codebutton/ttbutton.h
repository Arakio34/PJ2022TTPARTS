#ifndef TTBUTTON_H
#define TTBUTTON_H
struct bValue{
	int left;
	int ok;
	int right;
	int vleft;
	int vok;
	int vright;
};

void setupButton(struct bValue* b,int left, int ok, int right);

void readbValue(struct bValue * b);

void printbValue(struct bValue * b);

#endif
