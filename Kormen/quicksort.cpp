void swap(int v[], int i, int j)
{
    int temp  = v[i];
    v[i] = v[j];
    v[j] = temp;
}
void quicksort(int v[], int n)
{
    int i, last;
    if (n<=1) {
        return;
    }

    swap(v, 0, rand() % n);
    last = 0;
    for(i=1; i<n; i++) {
        if (v[i]<v[0]) {
            swap(v, ++last, i);
        }
    }
    swap(v, 0, last);
    quicksort(v, last);
    quicksort(v+last+1, n-last-1);
}
