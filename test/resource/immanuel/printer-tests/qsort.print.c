void (swap(int (*a), int (*b)))
{
	int tmp;
	(tmp = (*a));
	((*a) = (*b));
	((*b) = tmp);
}

void (quicksort(int (*begin), int (*end)))
{
	int (*ptr);
	int (*split);
	if (((end - begin) <= 1))
		return;
	(ptr = begin);
	(split = (begin + 1));
	while (((++ptr) != end)) {
		if (((*ptr) < (*begin))) {
			(swap(ptr, split));
			(++split);
		}
	}
	(swap(begin, (split - 1)));
	(quicksort(begin, (split - 1)));
	(quicksort(split, end));
}
