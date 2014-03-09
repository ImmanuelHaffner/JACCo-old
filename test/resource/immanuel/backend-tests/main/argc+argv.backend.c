31
Cc w3c

int main(int argc, char **argv)
{
	int n;
	n = 0;

	++argv; // ignore first argument: file name

	if ( **(argv) == 67 ) // == 'C'
		n = n + 1;

	if ( *(*argv + 1) == 99 ) // == 'c'
		n = n + 2;

	if ( **(argv + 1) == 119 ) // == 'w'
		n = n + 4;

	if ( *(*(argv + 1) + 1) == 51 ) // == '3'
		n = n + 8;

	if ( *(*(argv + 1) + 2) == 99 ) // == 'c'
		n = n + 16;

	return n;
}
