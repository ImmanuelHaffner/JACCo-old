33


int main() {
	int a[2];
	int *b[2];
	b[0] = a;
	b[1] = a;
	a[0] = 10;
	a[1] = 23;
	return b[0][1] + b[1][0];
}
